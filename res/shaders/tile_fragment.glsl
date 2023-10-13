#version 330 core

out vec4 color;

in vec2 tex_coords_frag;

uniform sampler2D text;

void main() {
	color = texture(text, tex_coords_frag);
	if (color.a == 0)
		discard;
}