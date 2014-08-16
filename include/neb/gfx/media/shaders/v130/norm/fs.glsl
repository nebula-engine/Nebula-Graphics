#version 130

#include "v130/inc/light.glsl"
#include "v130/inc/material.glsl"

in vec4 vs_P;
in vec3 vs_N;
in vec2 vs_texcoor;
in vec3 vs_tangent;
in vec3 vs_binormal;

uniform Light_Point		lights_point[20];
uniform Light_Spot		lights_spot[20];
uniform Light_Directional	lights_directional[20];


uniform int light_count_point;
uniform int light_count_spot;
uniform int light_count_directional;

uniform mat4 view;
uniform Material front;

uniform sampler2D normal_map;

out vec4 color;

vec4 P;
vec3 N;
vec3 L;

#include "v130/inc/light_function.glsl"

void main(void)
{
	float tau = 6.28318530718;

	// Normalize the incoming N, L and V vectors
	N = normalize(vs_N);
	P = normalize(vs_P);
	
	color = vec4(0.0);
	
	vec3 norm_vector = texture2D(normal_map, vs_texcoor).xyz;
	
	N = normalize(N + (mat3(vs_tangent, vs_binormal, vs_N) * norm_vector));
	
	point(front.ambient, front.diffuse, front.specular);
	spot(front.ambient, front.diffuse, front.specular);
	directional(front.ambient, front.diffuse, front.specular);

	color += front.emission;
}


	
