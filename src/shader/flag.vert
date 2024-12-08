#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 uModel;

out vec3 tNormal;

void main(void)
{
    gl_Position = vec4(aPosition, 1.0)
    tNormal = normalize(mat3(transpose(inverse(uModel))) * aNormal);
}