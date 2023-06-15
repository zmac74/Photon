#version 460 core

in vec2 textureCoord;

uniform sampler2D SCENE_COLOR;
uniform sampler2D SCENE_DEPTH;
uniform sampler2D COLOR;

out vec4 fragColor;

void main()
{
	fragColor = vec4(vec3(1.0 - texture(COLOR, textureCoord)), 1.0);
}