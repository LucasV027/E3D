#version 330 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexUV;

out vec3 color;
out vec2 uv;

uniform mat4 mvp;

void main()
{
    color = vertexColor;
    uv = vertexUV;
    gl_Position = mvp * vertexPos;
}