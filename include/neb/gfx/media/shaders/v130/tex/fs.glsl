#version 130

in vec2 texcoord;

uniform sampler2D tex;

out vec4 color;

void main(void)
{
	//color = vec4(1.0, 1.0, 1.0, texture2D(tex, texcoord).a) * font_color;
	color = vec4(texture2D(tex, texcoord).r,0,0,1);
}


