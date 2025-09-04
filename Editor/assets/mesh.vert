#version 450 core

layout (location = 0) in vec4 vertexPos;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vertexPos;
}