///// FRAGMENT SHADER

#version 460 core


in vec4 v_Color;          // Color passed from vertex shader
in vec2 v_TexCoord;       // Texture coordinates passed from vertex shader
in float v_TexIndex;      // Texture index passed from vertex shader

out vec4 FragColor;       // Final color of the fragment

uniform sampler2D u_Textures[32];  // Array of texture samplers

void main()
{
    // Fetch the texture from the texture array based on the texture index
    vec4 pixelColor = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
    if(pixelColor.a < 0.01f)
    {
        discard;
    }
    FragColor = pixelColor;
}