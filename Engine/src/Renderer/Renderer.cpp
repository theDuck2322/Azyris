#include "Renderer.h"
#include <iostream>
#include <array>

namespace Az
{
    static const size_t MaxQuadCount = 10000;
    //static const size_t MaxQuadCount = 1;
    static const size_t MaxVertexCount = MaxQuadCount * 4;
    static const size_t MaxIndexCount = MaxQuadCount * 6;
    static const size_t MaxTextures = 32;

    Renderer::RenderData Renderer::s_RenderData;

    Az::Camera2D* Renderer::m_Camera = nullptr;
    Az::Shader* Renderer::m_Shader = nullptr;

    bool Renderer::m_IsBatchRunning = false;

    void Renderer::BindCamera(Az::Camera2D* camera)
    {
        m_Camera = camera;
    }

    void Renderer::BindShader(Az::Shader* shader)
    {
        m_Shader = shader;
    }

    void Renderer::Init()
    {
        AZ_Assert(m_Camera != nullptr, "Camera is nullptr");
        AZ_Assert(m_Shader != nullptr, "Shader is nullptr");

        m_Shader->use();

        int samplers[32] = { 0 };

        for (int i = 0; i < 32; i++)
        {
            samplers[i] = i;
        }
        m_Shader->setUniform("u_Textures", samplers, 32);


        // Initialize the QuadBuffer
        s_RenderData.QuadBuffer = new Vertex[MaxVertexCount];

        glCreateVertexArrays(1, &s_RenderData.QuadVA);
        glBindVertexArray(s_RenderData.QuadVA);

        glCreateBuffers(1, &s_RenderData.QuadVB);
        glBindBuffer(GL_ARRAY_BUFFER, s_RenderData.QuadVB);
        glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexArrayAttrib(s_RenderData.QuadVA, 0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

        glEnableVertexArrayAttrib(s_RenderData.QuadVA, 1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

        glEnableVertexArrayAttrib(s_RenderData.QuadVA, 2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

        glEnableVertexArrayAttrib(s_RenderData.QuadVA, 3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex));

        // Index buffer
        uint32_t indices[MaxIndexCount];
        uint32_t offset = 0;
        for (size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indices[i] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
            indices[i + 3] = 2 + offset;
            indices[i + 4] = 3 + offset;
            indices[i + 5] = 0 + offset;
            offset += 4;
        }

        glCreateBuffers(1, &s_RenderData.QuadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderData.QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // White texture
        glCreateTextures(GL_TEXTURE_2D, 1, &s_RenderData.TextureSlots[0]);
        glBindTexture(GL_TEXTURE_2D, s_RenderData.TextureSlots[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        uint32_t whitePixel = 0xffffffff;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whitePixel);

        // Set slot 0 to white texture
        s_RenderData.TextureSlotIndex = 1;
    }

    void Renderer::Shutdown()
    {
        glDeleteVertexArrays(1, &s_RenderData.QuadVA);
        glDeleteBuffers(1, &s_RenderData.QuadVB);
        glDeleteBuffers(1, &s_RenderData.QuadIB);

        delete[] s_RenderData.QuadBuffer;
    }

    void Renderer::BeginBatch()
    {
        s_RenderData.QuadBufferPtr = s_RenderData.QuadBuffer;
        s_RenderData.IndexCount = 0;
        s_RenderData.TextureSlotIndex = 1;
        m_IsBatchRunning = true;
    }

    void Renderer::EndBatch()
    {
        m_IsBatchRunning = false;
        GLsizeiptr size = (uint8_t*)s_RenderData.QuadBufferPtr - (uint8_t*)s_RenderData.QuadBuffer;
        glBindBuffer(GL_ARRAY_BUFFER, s_RenderData.QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_RenderData.QuadBuffer);
    }

    void Renderer::Flush()
    {
        for (uint32_t i = 0; i < s_RenderData.TextureSlotIndex; i++)
        {
            glBindTextureUnit(i, s_RenderData.TextureSlots[i]);
        }


        m_Shader->use();

        glm::mat4 model = glm::mat4(1.0f);
        m_Shader->setUniform("u_ProjectionView", m_Camera->GetViewProjectionMatrix());
        m_Shader->setUniform("u_Model", model);


        glBindVertexArray(s_RenderData.QuadVA);
        glDrawElements(GL_TRIANGLES, s_RenderData.IndexCount, GL_UNSIGNED_INT, nullptr);
        s_RenderData.Stats.DrawCount++;
        m_Shader->Unbind();
        //std::cout << s_RenderData.Stats.DrawCount<< std::endl;

        s_RenderData.IndexCount = 0;
    }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        float textureIndex = 0.0f; // white texture

        glm::vec3 d1 = { position.x - (size.x / 2.0f), position.y - (size.y / 2.0f), position.z };
        glm::vec3 d2 = { position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.z };
        glm::vec3 d3 = { position.x + (size.x / 2.0f), position.y + (size.y / 2.0f), position.z };
        glm::vec3 d4 = { position.x - (size.x / 2.0f), position.y + (size.y / 2.0f), position.z };

        s_RenderData.QuadBufferPtr->Position = d1;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d2;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d3;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d4;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;
    }

    void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& size, uint32_t textureID)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount || s_RenderData.TextureSlotIndex >= MaxTextures)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        // Find texture index
        float textureIndex = 0.0f;
        for (size_t i = 1; i < s_RenderData.TextureSlotIndex; i++)
        {
            if (s_RenderData.TextureSlots[i] == textureID)
            {
                textureIndex = (float)i;
                break;
            }
        }

        // Add texture if it's not found
        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_RenderData.TextureSlotIndex;
            s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = textureID;
            s_RenderData.TextureSlotIndex++;
        }

        glm::vec3 d1 = { position.x - (size.x / 2.0f), position.y - (size.y / 2.0f), position.z };
        glm::vec3 d2 = { position.x + (size.x / 2.0f), position.y - (size.y / 2.0f), position.z };
        glm::vec3 d3 = { position.x + (size.x / 2.0f), position.y + (size.y / 2.0f), position.z };
        glm::vec3 d4 = { position.x - (size.x / 2.0f), position.y + (size.y / 2.0f), position.z };

        s_RenderData.QuadBufferPtr->Position = d1;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d2;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d3;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d4;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;
    }

    void Renderer::DrawQuadOLD(Az::Shapes::Rect& dst, Az::Shapes::Rect* src, Az::Texture texture, bool flipX)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount || s_RenderData.TextureSlotIndex >= MaxTextures)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        Az::Shapes::Rect _src = {};

        if (src == nullptr)
        {
            _src.Position = glm::vec3(0, 0, 0);
            _src.Size = glm::vec3(texture.GetSize(), 0);
        }
        else
        {
            _src = *src;
        }

        float textW = texture.GetSize().x;
        float textH = texture.GetSize().y;

        f32 invTextW = 1.0f / textW;
        f32 invTextH = 1.0f / textH;

        glm::vec2 p1 = { _src.Position.x, _src.Position.y };                              // Top-left
        glm::vec2 p2 = { _src.Position.x, _src.Position.y + _src.Size.y };                // Bottom-left
        glm::vec2 p3 = { _src.Position.x + _src.Size.x, _src.Position.y + _src.Size.y };  // Bottom-right
        glm::vec2 p4 = { _src.Position.x + _src.Size.x, _src.Position.y };                // Top-right

        if (flipX)
        {
            std::swap(p1, p4);
            std::swap(p2, p3);
        }

        p1 = glm::vec2(p1.x * invTextW, 1.0f - (p1.y * invTextH)); // Top-left
        p2 = glm::vec2(p2.x * invTextW, 1.0f - (p2.y * invTextH)); // Bottom-left
        p3 = glm::vec2(p3.x * invTextW, 1.0f - (p3.y * invTextH)); // Bottom-right
        p4 = glm::vec2(p4.x * invTextW, 1.0f - (p4.y * invTextH)); // Top-right

        glm::vec2 temp = p1;
        p1 = p2; // Move bottom-left to top-left
        p2 = p3; // Move bottom-right to bottom-left
        p3 = p4; // Move top-right to bottom-right
        p4 = temp; // Move original top-left to top-right


        // Find texture index
        float textureIndex = 0.0f;
        for (size_t i = 1; i < s_RenderData.TextureSlotIndex; i++)
        {
            if (s_RenderData.TextureSlots[i] == texture.GetID())
            {
                textureIndex = (float)i;
                break;
            }
        }

        // Add texture if it's not found
        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_RenderData.TextureSlotIndex;
            s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = texture.GetID();
            s_RenderData.TextureSlotIndex++;
        }

        s_RenderData.QuadBufferPtr->Position = dst.Position;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p1 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x + dst.Size.x, dst.Position.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p2 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x + dst.Size.x, dst.Position.y + dst.Size.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p3 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x, dst.Position.y + dst.Size.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p4 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;

    }

    void Renderer::DrawQuadOLD(Az::Shapes::Rect& dst, glm::vec4& color)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount || s_RenderData.TextureSlotIndex >= MaxTextures)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        float textureIndex = 0.0f; // white texture

        s_RenderData.QuadBufferPtr->Position = dst.Position;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x + dst.Size.x, dst.Position.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x + dst.Size.x, dst.Position.y + dst.Size.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = { dst.Position.x, dst.Position.y + dst.Size.y, dst.Position.z };
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;

    }

    void Renderer::DrawQuad(Az::Shapes::Rect& dst, Az::Shapes::Rect* src, Az::Texture texture, bool flipX)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount || s_RenderData.TextureSlotIndex >= MaxTextures)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        Az::Shapes::Rect _src = {};

        if (src == nullptr)
        {
            _src.Position = glm::vec3(0, 0, 0);
            _src.Size = glm::vec3(texture.GetSize(), 0);
        }
        else
        {
            _src = *src;
        }

        float textW = texture.GetSize().x;
        float textH = texture.GetSize().y;

        f32 invTextW = 1.0f / textW;
        f32 invTextH = 1.0f / textH;

        glm::vec2 p1 = { _src.Position.x, _src.Position.y };                              // Top-left
        glm::vec2 p2 = { _src.Position.x, _src.Position.y + _src.Size.y };                // Bottom-left
        glm::vec2 p3 = { _src.Position.x + _src.Size.x, _src.Position.y + _src.Size.y };  // Bottom-right
        glm::vec2 p4 = { _src.Position.x + _src.Size.x, _src.Position.y };                // Top-right

        if (flipX)
        {
            std::swap(p1, p4);
            std::swap(p2, p3);
        }

        p1 = glm::vec2(p1.x * invTextW, 1.0f - (p1.y * invTextH)); // Top-left
        p2 = glm::vec2(p2.x * invTextW, 1.0f - (p2.y * invTextH)); // Bottom-left
        p3 = glm::vec2(p3.x * invTextW, 1.0f - (p3.y * invTextH)); // Bottom-right
        p4 = glm::vec2(p4.x * invTextW, 1.0f - (p4.y * invTextH)); // Top-right

        glm::vec2 temp = p1;
        p1 = p2; // Move bottom-left to top-left
        p2 = p3; // Move bottom-right to bottom-left
        p3 = p4; // Move top-right to bottom-right
        p4 = temp; // Move original top-left to top-right


        // Find texture index
        float textureIndex = 0.0f;
        for (size_t i = 1; i < s_RenderData.TextureSlotIndex; i++)
        {
            if (s_RenderData.TextureSlots[i] == texture.GetID())
            {
                textureIndex = (float)i;
                break;
            }
        }

        // Add texture if it's not found
        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_RenderData.TextureSlotIndex;
            s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = texture.GetID();
            s_RenderData.TextureSlotIndex++;
        }

        glm::vec3 d1 = { dst.Position.x - (dst.Size.x / 2.0f), dst.Position.y - (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d2 = { dst.Position.x + (dst.Size.x / 2.0f), dst.Position.y - (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d3 = { dst.Position.x + (dst.Size.x / 2.0f), dst.Position.y + (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d4 = { dst.Position.x - (dst.Size.x / 2.0f), dst.Position.y + (dst.Size.y / 2.0f), dst.Position.z };


        if (dst.rotation != 0.0f)
        {
            d1 = rotatePoint(d1, dst.Position, toRadians(dst.rotation));
            d2 = rotatePoint(d2, dst.Position, toRadians(dst.rotation));
            d3 = rotatePoint(d3, dst.Position, toRadians(dst.rotation));
            d4 = rotatePoint(d4, dst.Position, toRadians(dst.rotation));
        }


        s_RenderData.QuadBufferPtr->Position = d1;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p1 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d2;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p2 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d3;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p3 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d4;
        s_RenderData.QuadBufferPtr->Color = glm::vec4(1.0f);
        s_RenderData.QuadBufferPtr->TexCoord = { p4 };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;

    }

    void Renderer::DrawQuad(Az::Shapes::Rect& dst, const glm::vec4& color)
    {
        if (s_RenderData.IndexCount >= MaxIndexCount || s_RenderData.TextureSlotIndex >= MaxTextures)
        {
            EndBatch();
            Flush();
            BeginBatch();
        }

        float textureIndex = 0.0f; // white texture

        glm::vec3 d1 = { dst.Position.x - (dst.Size.x / 2.0f), dst.Position.y - (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d2 = { dst.Position.x + (dst.Size.x / 2.0f), dst.Position.y - (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d3 = { dst.Position.x + (dst.Size.x / 2.0f), dst.Position.y + (dst.Size.y / 2.0f), dst.Position.z };
        glm::vec3 d4 = { dst.Position.x - (dst.Size.x / 2.0f), dst.Position.y + (dst.Size.y / 2.0f), dst.Position.z };

        if (dst.rotation != 0.0f)
        {
            d1 = rotatePoint(d1, dst.Position, toRadians(dst.rotation));
            d2 = rotatePoint(d2, dst.Position, toRadians(dst.rotation));
            d3 = rotatePoint(d3, dst.Position, toRadians(dst.rotation));
            d4 = rotatePoint(d4, dst.Position, toRadians(dst.rotation));
        }

        s_RenderData.QuadBufferPtr->Position = d1;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d2;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d3;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.QuadBufferPtr->Position = d4;
        s_RenderData.QuadBufferPtr->Color = color;
        s_RenderData.QuadBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_RenderData.QuadBufferPtr->TexIndex = textureIndex;
        s_RenderData.QuadBufferPtr++;

        s_RenderData.IndexCount += 6;
        s_RenderData.Stats.QuadCount++;

    }

    const Renderer::Stats& Renderer::GetStats()
    {
        return s_RenderData.Stats;
    }

    void Renderer::ResetStats()
    {
        s_RenderData.Stats = {};
    }
}
