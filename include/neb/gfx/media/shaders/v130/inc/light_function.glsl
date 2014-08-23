

void	lf_lights(in vec4 amb, in vec4 dif, in vec4 spc) {

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	vec4 pos;
	vec3 light_pos;
	vec3 spot_direction;

	float atten;

	for(int i = 0; i < light_count; i++) // for all light sources
	{
		if(light_closed[i] == 0) continue;

		// ambient
		ambient = light_ambient[i] * amb;

		// diffuse

		pos = vec4(light_position[i], 1.0);

		

		if(light_type[i] == 2) {

			light_pos = mat3(view) * light_position[i];

			L = normalize(light_pos);

			atten = 1.0;

		} else {

			light_pos = vec3(view * pos);

			L = light_pos - vs_P.xyz;

			float l = length(L);

			L = normalize(L);

			atten = 1.0 / (
					light_atten_const[i] +
					light_atten_linear[i] * l +
					light_atten_quad[i] * l * l);

		}

		float angle = max(0.0, dot(N,L));

		if(light_type[i] == 1) {
			spot_direction = mat3(view) * light_spot_direction[i];

			float clamped_cos = max(0.0, dot(-L, normalize(spot_direction)));

			if(clamped_cos < cos(light_spot_cutoff[i])) // outside spotlight cone
			{
				atten = 0.0;
			}
			else // inside spotlight cone
			{
				atten = atten * pow(clamped_cos, light_spot_exponent[i]);   
			}
		}

		diffuse = atten * light_diffuse[i] * dif * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * light_specular[i] * spc *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
}

/*
   void spot(in vec4 amb, in vec4 dif, in vec4 spc)
   {
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   vec3 light_pos;
   vec3 light_spot_direction;
   float atten;

   for(int i = 0; i < light_count_spot; i++) // for all light sources
   {
// light
//light_pos = modelview + lights[i].position;


// ambient
ambient = lights_spot[i].ambient * amb;

// diffuse

diffuse = lf_diffuse();

// specular
if (dot(N,L) < 0.0) // light source behind
{
specular = vec4(0.0, 0.0, 0.0, 0.0);
}
else // light source in front
{
specular = atten * lights_spot[i].specular * spc *
vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
}

color += ambient + diffuse + specular;
}
}*/
/*
   void directional(in vec4 amb, in vec4 dif, in vec4 spc)
   {
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   vec3 light_pos;
   vec3 light_spot_direction;
   float atten;

   for(int i = 0; i < light_count_directional; i++) // for all light sources
   {
// ambient
ambient = lights_directional[i].ambient * amb;

// diffuse
atten = 1.0; // no atten

// rotate to view space
light_pos = mat3(view) * lights_directional[i].position;


L = normalize(light_pos);

float angle = max(0.0, dot(N,L));

diffuse = atten * lights_directional[i].diffuse * dif * vec4(vec3(angle),1.0);

// specular
if (dot(N,L) < 0.0) // light source behind
{
specular = vec4(0.0, 0.0, 0.0, 0.0);
}
else // light source in front
{
specular = atten * lights_directional[i].specular * spc *
vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
}

color += ambient + diffuse + specular;
}
}
 */
