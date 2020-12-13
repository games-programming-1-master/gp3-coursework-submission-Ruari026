#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 viewProjection;

out vec3 vertWorldPos;
out vec2 vertTexCoord;

void main()
{
    vertWorldPos = (model * vec4(aPos.xyz, 1.0)).xyz;
    vertTexCoord = aTexCoord;

    gl_Position = viewProjection * model * vec4(aPos, 1.0);
}