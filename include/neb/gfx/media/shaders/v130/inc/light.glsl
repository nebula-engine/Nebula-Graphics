
struct Light_Point
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float atten_const;
	float atten_linear;
	float atten_quad;
};

struct Light_Spot
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 spot_direction;
	float spot_cutoff;
	float spot_exponent;
	float spot_light_cos_cutoff;
	float atten_const;
	float atten_linear;
	float atten_quad;
};

struct Light_Directional
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

