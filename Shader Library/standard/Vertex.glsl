#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTextureCoord;
layout (location = 2) in vec3 iNormal;
layout (location = 3) in vec4 iColor;
layout (location = 4) in vec3 iTangent;

out vec4 color;
out vec2 textureCoord;

uniform mat4 transform;
uniform mat4 camera;

void main()
{
	gl_Position = camera * vec4(iPosition, 1.0);
	color = iColor;
	textureCoord = iTextureCoord;
}