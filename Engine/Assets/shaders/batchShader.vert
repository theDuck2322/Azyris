#version 460 core

layout(location = 0) in vec3 a_Position;   // Vertex Position
layout(location = 1) in vec4 a_Color;      // Vertex Color
layout(location = 2) in vec2 a_TexCoord;   // Texture Coordinates
layout(location = 3) in float a_TexIndex;  // Texture Index

out vec4 v_Color;        // Color to pass to fragment shader
out vec2 v_TexCoord;     // Texture coordinates to pass to fragment shader
out float v_TexIndex;    // Texture index to fragment shader

uniform mat4 u_ProjectionView; // Projection matrix
uniform mat4 u_Model;           // Model matrix

void main()
{
    // Calculate final vertex position in world space
    gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0f);
    
    // Pass color, texture coordinates, and texture index to fragment shader
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
}