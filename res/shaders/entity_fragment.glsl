#version 330 core

out vec4 color;

in vec2 tex_coords_frag;
in float depth;

uniform sampler2D text;
uniform int fog_power;
uniform bool is_blind;

void main() {
	color = texture(text, tex_coords_frag);

	if (color.a <= 0.01)
		discard;

	if (fog_power > 0 && fog_power <= 4) {
		float fogStart;
		float fogEnd;

		switch(fog_power) {
			case 1: // Weak fog
				fogStart = 8.f;
				fogEnd = 24.f;
			break;
			case 2: // Normal fog
				fogStart = 5.f;
				fogEnd = 17.f;
			break;
			case 3: // Strong fog
				fogStart = 3.f;
				fogEnd = 11.f;
			break;
			case 4: // Extreme fog
				fogStart = 0.f;
				fogEnd = 6.f;
			break;
			default: break;
		}

		float fogLength = fogEnd - fogStart;
		float fogFactor = (fogEnd - depth) / fogLength;
		fogFactor = clamp(fogFactor, 0.f, 1.f);

		color = mix(vec4(0.6f, 0.45f, 0.45f, 1.f), color, fogFactor);
	}

	if (is_blind) {
		float achromapsiaFactor = clamp((5.f - depth) / 5.f, 0.f, 0.5f);
		vec3 gray = vec3(dot(color.rgb, vec3(0.299f, 0.587f, 0.114f)));
		color = mix(vec4(gray, 1.f), color, achromapsiaFactor);

		float whiteBlindnessFactor = clamp((14.f - depth) / 9.f, 0.f, 1.f);
		color = mix(vec4(1.f), color, whiteBlindnessFactor);
	}

	if (color.a <= 0.01)
		discard;
}