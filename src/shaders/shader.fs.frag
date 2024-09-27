#version 330 core
in vec3 color;
in vec3 normal;
in vec3 fragPosition;

uniform float AMBIENT_STRENGTH;
uniform vec3 LIGHT_POSITION;
uniform vec3 LIGHT_COLOR;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(normal);
    vec3 ambient = AMBIENT_STRENGTH * LIGHT_COLOR;
    vec3 lightDirection = normalize(fragPosition - LIGHT_POSITION);
    float diffuseValue = max(dot(norm, lightDirection), 0.f);
    vec3 diffuseVector = diffuseValue * LIGHT_COLOR;
    vec3 result = color * (diffuseVector + ambient);
    FragColor = vec4(result, 1.f);
}