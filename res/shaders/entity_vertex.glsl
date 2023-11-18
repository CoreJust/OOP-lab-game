#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 tex_coords;

out vec2 tex_coords_frag;
out float depth;

uniform mat4 model_matrix;
uniform mat4 proj_view_matrix;
uniform vec3 player_pos;

void main() {
	gl_Position = proj_view_matrix * model_matrix * vec4(vertex, 1.f);
	tex_coords_frag = tex_coords;
	depth = length((model_matrix * vec4(vertex, 1.f)).xyz - player_pos);
}