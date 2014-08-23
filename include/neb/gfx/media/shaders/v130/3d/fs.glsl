#version 130

#include "v130/inc/material.glsl"

in vec4		vs_P;
in vec3		vs_N;
in vec2		vs_texcoor;
in vec3 	vs_T;
in vec3		vs_B;
in float	vs_instance_image_sampler;
in float	vs_instance_normal_map_sampler;
in vec4		vs_instance_diffuse;

uniform sampler2DArray	image;
uniform sampler2DArray	normal_map;

#include "v130/inc/light.glsl"

uniform mat4 view;

out vec4 color;

vec4 P;
vec3 N;
vec3 L;

#include "v130/inc/light_function.glsl"

void main(void)
{
	float tau = 6.28318530718;

	P = normalize(vs_P);
	N = vs_N;
	
	color = vec4(0.0);
	
	vec4 amb, dif, spc;
	
	
	if(vs_instance_image_sampler >= 0.0) {
		vec4 image_color = texture(image, vec3(vs_texcoor, vs_instance_image_sampler));
		amb = image_color;
		dif = vs_instance_diffuse * image_color;
		spc = image_color;
	} else {
		amb = vec4(0);
		dif = vs_instance_diffuse;
		spc = vec4(0);
	}

	if(vs_instance_normal_map_sampler >= 0.0) {	
		vec3 norm_vector = texture(normal_map, vec3(vs_texcoor, vs_instance_normal_map_sampler)).xyz;
		N = normalize(N + (mat3(vs_T, vs_B, vs_N) * norm_vector));
	}
	
	
	lf_lights(amb, dif, spc);

	color += vec4(0);
	color += vec4(0.5, 0.5, 0.5, 1.0);
}


	
