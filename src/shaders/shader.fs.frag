#version 330 core
in vec3 color;
in vec3 normal;
in vec3 fragPosition;

uniform float AMBIENT_STRENGTH;
uniform float SPECULAR_STRENGHT;
uniform int SHININESS;
uniform vec3 LIGHT_POSITION;
uniform vec3 LIGHT_COLOR;
uniform vec3 CAMERA_POSITION;

out vec4 FragColor;


void main()
{
    vec3 norm = normalize(normal);
    vec3 ambient = AMBIENT_STRENGTH * LIGHT_COLOR;
    vec3 lightDirection = normalize(LIGHT_POSITION - fragPosition);
    float diffuseValue = max(dot(norm, lightDirection), 0.f);
    vec3 diffuseVector = diffuseValue * LIGHT_COLOR;

    vec3 viewDirection = normalize(CAMERA_POSITION - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), .0f), SHININESS);
    vec3 specular = SPECULAR_STRENGHT * spec * LIGHT_COLOR;

    vec3 result = color * (diffuseVector + ambient + specular);
    FragColor = vec4(result, 1.f);
}