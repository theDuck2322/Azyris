#pragma once
#include <string>
#include <glad/glad.h>
#include "utils/Types.h"
#include <glm/glm.hpp>

#include <stb_image.h>


namespace Az
{
    class Texture
    {
    public:
        Texture() = default;

        bool loadFromFile(const std::string& filePath);
        void Bind(u32 slot = 0);
        void Unbind();
        void Delete();

        inline glm::vec2 GetSize() { return glm::vec2(m_Width, m_Height); }
        inline bool textureIsLoaded() { return m_TextureIsLoaded; }

        inline uint32_t GetID() { return m_TextureID; }

    private:
        u32 m_Width;
        u32 m_Height;
        u32 m_TextureID;
        bool m_TextureIsLoaded = false;
    };
}
