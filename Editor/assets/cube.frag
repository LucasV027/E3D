#version 450 core

out vec4 FragColor;

in vec3 color;
in vec2 uv;

uniform sampler2D texSampler;

void main()
{
    FragColor = vec4(texture(texSampler, uv).rgb, 1.0f);
}