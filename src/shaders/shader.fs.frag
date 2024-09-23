#version 330 core
in vec3 color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.f, 1.f, 1.f, 1.0f) * vec4(color, 1.0f) + vec4(.5f,.5f,.5f,0.f);
}