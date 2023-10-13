#version 330 core

layout (location = 0) in uint vertex;
layout (location = 1) in vec2 tex_coords;

out vec2 tex_coords_frag;

void main() {
	gl_Position = vec4(vertex & 0xfff, (vertex & 0xfff000) >> 12, (vertex & 0xff000000) >> 24, 1.0);
	tex_coords_frag = tex_coords;
}