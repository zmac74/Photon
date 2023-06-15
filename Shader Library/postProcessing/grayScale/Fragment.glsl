#version 460 core

in vec2 textureCoord;

uniform sampler2D SCENE_COLOR;
uniform sampler2D SCENE_DEPTH;
uniform sampler2D COLOR;

out vec4 fragColor;

void main()
{
	fragColor = texture(COLOR, textureCoord);
	float average =  ((0.2126 * fragColor.r) + (0.7152 * fragColor.g) + (0.0722 * fragColor.b));
	fragColor = vec4(average, average, average, 1.0);
}