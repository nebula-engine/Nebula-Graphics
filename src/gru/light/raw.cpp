#include <math/free.h>

#include <glutpp/light/raw.h>

glutpp::light::raw::raw():
	pos_(math::vec4(0.0, 0.0, 0.0, 1.0)),
	ambient_(math::black),
	diffuse_(math::white),
	specular_(math::white),
	spot_direction_(math::vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
void	glutpp::light::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;

	pos_ = math::xml_parse_vec4(element->FirstChildElement("p"));
	
	ambient_ = math::xml_parse_color(
			element->FirstChildElement("ambient"),
			ambient_);
	
	diffuse_ = math::xml_parse_color(
			element->FirstChildElement("diffuse"),
			diffuse_);
	
	specular_ = math::xml_parse_color(
			element->FirstChildElement("specular"),
			specular_);
	
	
	
	spot_direction_ = math::xml_parse_vec3(
		element->FirstChildElement("spot_direction"),
		math::vec3(0.0, 0.0, 0.0));
	
	spot_cutoff_           = math::xml_parse_float(element->FirstChildElement("spot_cutoff"), M_PI);
	spot_exponent_         = math::xml_parse_float(element->FirstChildElement("spot_exponent"), 0.0);
	spot_light_cos_cutoff_ = math::xml_parse_float(element->FirstChildElement("spot_cutoff"), M_PI);
	
	
	atten_const_  = math::xml_parse_float(element->FirstChildElement("atten_const"), 1.0);
	atten_linear_ = math::xml_parse_float(element->FirstChildElement("atten_linear"), 0.0);
	atten_quad_   = math::xml_parse_float(element->FirstChildElement("atten_quad"), 0.0);
	
	print();
}
void	glutpp::light::raw::print() {

	printf("pos_                   = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			pos_.x, pos_.y, pos_.z, pos_.w);
	printf("ambient_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			ambient_.r, ambient_.g, ambient_.b, ambient_.a);
	printf("diffuse_               = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			diffuse_.r, diffuse_.g, diffuse_.b, diffuse_.a);
	printf("specular_              = % 2.1f % 2.1f % 2.1f % 2.1f\n",
			specular_.r, specular_.g, specular_.b, specular_.a);
	printf("spot_direction_        = % 2.1f % 2.1f % 2.1f\n",
			spot_direction_.x, spot_direction_.y, spot_direction_.z);
	printf("spot_cutoff_           = % 2.1f\n", spot_cutoff_);
	printf("spot_exponent_         = % 2.1f\n", spot_exponent_);
	printf("spot_light_cos_cutoff_ = % 2.1f\n", spot_light_cos_cutoff_);
	printf("atten_const_           = % 2.1f\n", atten_const_);
	printf("atten_linear_          = % 2.1f\n", atten_linear_);
	printf("atten_quad_            = % 2.1f\n", atten_quad_);
}

