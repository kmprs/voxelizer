#version 330 core
layout (location = 0) in vec3 positionIn;
layout (location = 1) in vec3 normalIn;

out vec3 color;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 VOXEL_COLOR;

void main()
{
    gl_Position = projection * view * model * vec4(positionIn, 1.0f);
    color = VOXEL_COLOR;
    normal = normalIn;
    fragPosition = vec3(model * vec4(positionIn, 1.f));
}