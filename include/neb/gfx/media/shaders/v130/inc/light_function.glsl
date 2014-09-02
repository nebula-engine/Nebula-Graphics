

void	lf_lights(in vec4 amb, in vec4 dif, in vec4 spc) {

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	vec4 pos;
	vec3 light_pos;
	vec3 spot_direction;

	float atten;

	//float shininess = 10.0;
	
	bool shadow = false;
	
	float depth0;
	float depth1;
	float depth2;
	float depth3;
	float depth4;
	float depth5;

	float bias = 0.005;

	for(int i = 0; i < light_count; i++) // for all light sources
	{
		if(light_closed[i] == 0) continue;
		
		
		// shadow
		if(light_shadow_sampler_0[i].x >= 0.0) {
			
			// directional or spot?
			vec4 shadow_coor_0 = light_shadow_vpb_0[i] * vs_m_P;
			
			depth0 = texture(shadow_map, vec3(shadow_coor_0.xy, light_shadow_sampler_0[i].x)).z + bias;
	
			if(depth0 < shadow_coor_0.z) shadow = true;
		
			// point?
			if(light_shadow_sampler_0[i].y >= 0.0) {

				vec4 shadow_coor_1 = light_shadow_vpb_1[i] * vs_m_P;
				vec4 shadow_coor_2 = light_shadow_vpb_2[i] * vs_m_P;
				vec4 shadow_coor_3 = light_shadow_vpb_3[i] * vs_m_P;
				vec4 shadow_coor_4 = light_shadow_vpb_4[i] * vs_m_P;
				vec4 shadow_coor_5 = light_shadow_vpb_5[i] * vs_m_P;

				depth1 = texture(shadow_map, vec3(shadow_coor_1.xy, light_shadow_sampler_0[i].y)).z;
				depth2 = texture(shadow_map, vec3(shadow_coor_2.xy, light_shadow_sampler_0[i].z)).z;
				depth3 = texture(shadow_map, vec3(shadow_coor_3.xy, light_shadow_sampler_1[i].x)).z;
				depth4 = texture(shadow_map, vec3(shadow_coor_4.xy, light_shadow_sampler_1[i].y)).z;
				depth5 = texture(shadow_map, vec3(shadow_coor_5.xy, light_shadow_sampler_1[i].z)).z;

				if(depth1 < shadow_coor_1.z) shadow = true;
				if(depth2 < shadow_coor_2.z) shadow = true;
				if(depth3 < shadow_coor_3.z) shadow = true;
				if(depth4 < shadow_coor_4.z) shadow = true;
				if(depth5 < shadow_coor_5.z) shadow = true;
			}
		}



		// ambient
		ambient = light_ambient[i] * amb;

		// diffuse
		pos = vec4(light_position[i], 1.0);



		if(light_type[i] == 2) { // directional

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
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), vs_instance_shininess)),1.0);
		}

		if(shadow) {
			diffuse *= 0.5;
			specular *= 0.5;
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
