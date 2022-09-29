#version 460 core

in vec4 color;
in vec2 textureCoord;

out vec4 fragColor;

uniform sampler2D baseColor;

void main()
{
	fragColor = texture(baseColor, textureCoord);
}