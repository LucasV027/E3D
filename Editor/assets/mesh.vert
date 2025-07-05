#version 450 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec3 vertexColor;

out vec3 color;

uniform mat4 mvp;

void main()
{
    color = vertexColor;
    gl_Position = mvp * vertexPos;
}