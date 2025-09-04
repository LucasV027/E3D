#version 450 core

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

out vec3 normal;
out vec2 uv;

out uint st;
out vec3 c;
out vec3 ld;

uniform uint shadingType;
uniform mat4 mvp;
uniform vec3 color;
uniform vec3 lightDirection;

void main()
{
    normal = vertexNormal;
    uv = vertexUV;

    st = shadingType;
    c = color;
    ld = lightDirection;

    gl_Position = mvp * vertexPos;
}