#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iTextureCoord;

out vec2 textureCoord;

void main()
{
	gl_Position = vec4(iPosition.xy, 0.0, 1.0);
	textureCoord = iTextureCoord;
}