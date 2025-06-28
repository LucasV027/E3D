#version 330 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec3 vertexColor;

uniform mat4 mvp;
out vec3 color;

void main()
{
    color = vertexColor;
    gl_Position = mvp * vertexPos;
}