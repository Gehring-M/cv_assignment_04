#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

out vec3 tNormal;
out vec3 tFragPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

// uniforms for the flag simulation
uniform float uAccumTime;
uniform vec3 uAmplitude;
uniform vec3 uPhi;
uniform vec3 uOmega;
uniform vec3 uDirectionX;
uniform vec3 uDirectionY;

void main(void)
{
    // init sum 
    float sum = 0.0;

    // debug 
    vec3 dummy_result = (uAmplitude + uPhi + uOmega + uDirectionX + uDirectionY) * uAccumTime;

    // compute the displacement for each wavefunction
    for (int i = 0; i < 3; i++)
    {
        vec2 directions = vec2(uDirectionX[i], uDirectionY[i]);
        sum = sum + (uAmplitude[i] * sin(dot(normalize(directions), aPosition.yz) * uOmega[i] + uPhi[i] * uAccumTime));
    }

    gl_Position = uProj * uView * uModel * vec4(aPosition, 1.0);
    tFragPos = vec3(uModel * vec4(aPosition, 1.0));
    tNormal = normalize(mat3(transpose(inverse(uModel))) * aNormal);
}