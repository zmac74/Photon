#version 460 core

in vec2 textureCoord;

uniform sampler2D SCENE_COLOR;
uniform sampler2D SCENE_DEPTH;
uniform sampler2D COLOR;

out vec4 fragColor;

void main()
{
	 float range = 0.25;
	 float intesnity = 0.0;
	 float smoothness = 1.0;
	 float strength = 0.6;

	 range = 0.25 * smoothness;

	 float outerRange = 0.65;
	 float innerRange = 0.40;

	 vec3 vignetteColor = vec3(0.0, 0.0, 0.0);
	 fragColor = texture(COLOR, textureCoord);

	 vec2 point = textureCoord - 0.5;
	 float dist = length(point);

	 float vignette = smoothstep(outerRange, innerRange, dist);
	 vec3 vingetteResult = mix(fragColor.rgb, fragColor.rgb * vignette, strength);

	 fragColor = vec4(vingetteResult, 1.0);
}