#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTextureCoord;
layout (location = 2) in vec3 iNormals;
layout (location = 3) in vec4 iColor;
layout (location = 4) in vec3 iTangent;

out vec4 color;

void main()
{
	gl_Position = vec4(iPosition, 1.0);
	color = iColor;
}