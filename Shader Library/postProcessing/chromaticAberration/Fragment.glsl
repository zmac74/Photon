#version 460 core

in vec2 textureCoord;

uniform sampler2D SCENE_COLOR;
uniform sampler2D SCENE_DEPTH;
uniform sampler2D COLOR;

out vec4 fragColor;

void main()
{
	const float strength = 0.5;
	
	vec2 point = textureCoord - 0.5;
	float intensity = length(point) * length(point);

	float r = texture(COLOR, (textureCoord - (point * (intensity / 10.0 * strength)))).x;
	float g = texture(COLOR, (textureCoord)).y;
	float b = texture(COLOR, (textureCoord + (point * (intensity / 10.0 * strength)))).z;

	fragColor = vec4(r, g, b, 1.0);
}