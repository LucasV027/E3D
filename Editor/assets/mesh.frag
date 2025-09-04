#version 450 core

out vec4 FragColor;

in vec3 normal;
in vec2 uv;

flat in uint st;
in vec3 c;
in vec3 ld;

void main()
{
    // No shading type color (RED)
    vec3 color = vec3(1.0, 0.0, 0.0);

    float intensity = dot(normalize(normal), normalize(ld));

    // Basic shading
    if (st == 0) {
        color = c * intensity;
    }
    // Toon shading
    if (st == 1) {
        for (uint i = 0; i < 10; i++) {
            float threshold = 1 - (1 / (i + 1));
            if (intensity < threshold) {
                color = c * threshold;
                break;
            }
        }
    }

    FragColor = vec4(color, 1.0);

}