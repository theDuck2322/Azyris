#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <Buffers/Buffers.h>

#include <Renderer/Shader.h>
#include <Renderer/Camera2D.h>
#include <Renderer/Texture.h>

#include <utils/Helpers.h>

namespace Az
{
    class Renderer
    {
    public:

        static void BindCamera(Az::Camera2D* camera);
        static void BindShader(Az::Shader* shader);

        static void Init();
        static void Shutdown();

        static void BeginBatch();
        static void EndBatch();
        static void Flush();

        // QUICK functions
        static void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, float degree = 0);
        static void DrawQuad(const glm::vec3& position, const glm::vec3& size, uint32_t textureID, float degree = 0);

        static void DrawQuad(Az::Rect& dst, Az::Rect* src, Az::Texture texture, bool flipX = 0);
        static void DrawQuad(Az::Rect& dst, const glm::vec4& color);
        
        static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec4& color, float thickness = 2.5f);

        static void DrawRect(const glm::vec3& position, const glm::vec3& size, float degree, const glm::vec4& color, float thickness = 2.5f);
        static void DrawRect(Az::Rect& dst, const glm::vec4& color, float thickness = 2.5f);


        inline static bool batchRunning() { return m_IsBatchRunning; }

        static void ResetStats();

        struct Stats
        {
            uint32_t DrawCount = 0;
            uint32_t QuadCount = 0;
        };

        static const Stats& GetStats();

    private:
        struct Vertex
        {
            glm::vec3 Position;
            glm::vec4 Color;
            glm::vec2 TexCoord;
            float TexIndex;
        };

        struct RenderData
        {
            GLuint QuadVA = 0;
            GLuint QuadVB = 0;
            GLuint QuadIB = 0;

            uint32_t IndexCount = 0;
            uint32_t TextureSlotIndex = 1;
            uint32_t TextureSlots[32] = { 0 };  // slot 0 reserved for white texture

            Vertex* QuadBuffer = nullptr;
            Vertex* QuadBufferPtr = nullptr;

            Stats Stats;
        };

        static RenderData s_RenderData;

        static Az::Camera2D* m_Camera;
        static Az::Shader* m_Shader;

        static bool m_IsBatchRunning;
    };
}
