#version 460 core

in vec4 color;
in vec3 normal;
in vec2 textureCoord;

out vec4 fragColor;

uniform sampler2D baseColor;

void main()
{
	fragColor = vec4(normal, 1.0);
}