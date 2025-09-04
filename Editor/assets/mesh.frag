#version 450 core

out vec4 FragColor;

in vec3 normal;
in vec2 uv;

void main()
{
    vec3 ld = vec3(0.0, 10.0, 0.0);
    float intensity = dot(normalize(normal), normalize(ld));
    vec3 color = vec3(0.2, 0.6, 0.4);
    FragColor = vec4(intensity * color, 1.0);
}