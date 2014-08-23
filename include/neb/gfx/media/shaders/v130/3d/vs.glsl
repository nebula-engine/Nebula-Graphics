#version 130

out vec4	vs_P;
out vec3	vs_N;
out vec2	vs_texcoor;
out vec3	vs_T;
out vec3	vs_B;
out float	vs_instance_image_sampler;
out float	vs_instance_normal_map_sampler;
out vec4	vs_instance_diffuse;
out vec4	vs_instance_ambient;
out vec4	vs_instance_specular;
out vec4	vs_instance_emission;
out float	vs_instance_shininess;

uniform mat4 view;
uniform mat4 proj;

in vec3		position; // 0
in vec3		normal; // 1
in vec2		texcoor; // 2
in vec3		tangent; // 3
in vec3		binormal; // 4
in vec4		instance_model0;
in vec4		instance_model1;
in vec4		instance_model2;
in vec4		instance_model3;
in float	instance_image_sampler;
in float	instance_normal_map_sampler;
in vec4		instance_diffuse;
in vec4		instance_ambient;
in vec4		instance_specular;
in vec4		instance_emission;
in float	instance_shininess;

void main(void) {

	mat4 model = mat4(
			instance_model0,
			instance_model1,
			instance_model2,
			instance_model3);

	mat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_P = modelview * vec4(position,1.0);

	// Calculate normal in view-space
	vs_N = normalize(mat3(modelview) * normal);
	vs_T = normalize(mat3(modelview) * tangent);
	vs_B = normalize(mat3(modelview) * binormal);

	vs_texcoor = texcoor;

	vs_instance_image_sampler = instance_image_sampler;
	vs_instance_normal_map_sampler = instance_normal_map_sampler;

	vs_instance_diffuse = instance_diffuse;
	vs_instance_ambient = instance_ambient;
	vs_instance_specular = instance_specular;
	vs_instance_emission = instance_emission;
	vs_instance_shininess = instance_shininess;

	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_P;
}


