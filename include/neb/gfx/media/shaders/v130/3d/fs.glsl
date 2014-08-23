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
in vec4		vs_instance_ambient;
in vec4		vs_instance_specular;
in vec4		vs_instance_emission;
in float	vs_instance_shininess;

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
		amb = vs_instance_ambient * image_color;
		dif = vs_instance_diffuse * image_color;
		spc = vs_instance_specular * image_color;
	} else {
		amb = vs_instance_ambient;
		dif = vs_instance_diffuse;
		spc = vs_instance_specular;
	}

	if(vs_instance_normal_map_sampler >= 0.0) {	
		vec3 norm_vector = texture(normal_map, vec3(vs_texcoor, vs_instance_normal_map_sampler)).xyz;
		N = normalize(N + (mat3(vs_T, vs_B, vs_N) * norm_vector));
	}
	
	
	lf_lights(amb, dif, spc);

	color += vs_instance_emission;
}


	
