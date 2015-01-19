#version 130

in vec2 texCoord;
out vec4 outputColor;

uniform sampler2D gSampler;

void main()
{
	outputColor = texture2D(gSampler, texCoord);
}
