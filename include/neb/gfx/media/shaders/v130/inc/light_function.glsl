void point(in vec4 amb, in vec4 dif, in vec4 spc)
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 light_pos;
	vec3 light_spot_direction;
	float atten;

	for(int i = 0; i < light_count_point; i++) // for all light sources
	{
		// ambient
		ambient = lights_point[i].ambient * amb;

		vec4 pos = vec4(lights_point[i].position, 1.0);
		light_pos = vec3(view * pos);

		L = light_pos - vs_P.xyz;

		float l = length(L);

		L = normalize(L);

		atten = 1.0 / (
				lights_point[i].atten_const +
				lights_point[i].atten_linear * l +
				lights_point[i].atten_quad * l * l);


		float angle = max(0.0, dot(N,L));

		diffuse = atten * lights_point[i].diffuse * dif * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights_point[i].specular * spc *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
}

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
		light_spot_direction = mat3(view) * lights_spot[i].spot_direction;

		// ambient
		ambient = lights_spot[i].ambient * amb;

		// diffuse
		// translate to view space
		//light_pos = lights[i].position.xyz - view[0].xyz;
		//light_pos = mat3(view) * light_pos;

		vec4 pos = vec4(lights_point[i].position, 1.0);
		light_pos = vec3(view * pos);

		L = light_pos - vs_P.xyz;

		float l = length(L);

		L = normalize(L);

		atten = 1.0 / (
				lights_spot[i].atten_const +
				lights_spot[i].atten_linear * l +
				lights_spot[i].atten_quad * l * l);

		float clamped_cos = max(0.0, dot(-L, normalize(light_spot_direction)));

		if (clamped_cos < cos(lights_spot[i].spot_cutoff)) // outside spotlight cone?
		{
			atten = 0.0;
		}
		else // inside spotlight cone
		{
			atten = atten * pow(clamped_cos, lights_spot[i].spot_exponent);   
		}

		float angle = max(0.0, dot(N,L));

		diffuse = atten * lights_spot[i].diffuse * dif * vec4(vec3(angle),1.0);

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
}

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
