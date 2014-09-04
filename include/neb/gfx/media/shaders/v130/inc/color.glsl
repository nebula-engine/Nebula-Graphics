

vec4	uint_to_vec4(in uint uc)
{
	float a = float(uc & 255u) / 255.0;
	uc >>= 8;
	float b = float(uc & 255u) / 255.0;
	uc >>= 8;
	float g = float(uc & 255u) / 255.0;
	uc >>= 8;
	float r = float(uc & 255u) / 255.0;
	
	return vec4(r,g,b,a);
}


