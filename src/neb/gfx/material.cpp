//#include <stdio.h> removed by c_header_checker

//#include <neb/fnd/core/scene/base.hpp>

//#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/material.hpp>
//#include <neb/gfx/glsl/program/threed.hpp>
//#include <neb/gfx/glsl/uniform/scalar.hpp>

/*
gru::Color::color<float> operator<<(gru::Color::color<float> c, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}
float operator<<(float f, tinyxml2::XMLElement* element) {
	if(element != NULL) {
		char const * buf = element->GetText();
		
		sscanf(buf, "%f,%f,%f,%f", &c.r, &c.g, &c.b, &c.a);
	}
	
	return c;
}
*/

neb::gfx::material::raw::raw() {
	ambient_ = neb::fnd::math::color::color::white();
	diffuse_ = neb::fnd::math::color::color::cyan();
	specular_ = neb::fnd::math::color::color::white();
	emission_ = neb::fnd::math::color::color::black();
	shininess_ = 500;
}
/* implement through serialize(ar)
void	neb::material::raw::load(tinyxml2::XMLElement* element) {
	
	if(element == NULL)
	{
		printf("no element\n");
		return;
	}
	
	ambient_ << element->FirstChildElement("ambient");
	diffuse_  << element->FirstChildElement("diffuse");
	specular_ << element->FirstChildElement("specular");
	emission_ << element->FirstChildElement("emission");
	
	shininess_ << element->FirstChildElement("shininess");

	printf("diffuse = ");	
	diffuse_.print();
}
*/



neb::gfx::material::material::material()
{}
void	neb::gfx::material::material::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::material::material::load(std::shared_ptr<neb::gfx::glsl::program::Base> p) {
/*
	p->get_uniform_scalar("front.ambient")->load((glm::vec4)raw_.ambient_);
	p->get_uniform_scalar("front.diffuse")->load((glm::vec4)raw_.diffuse_);
	p->get_uniform_scalar("front.specular")->load((glm::vec4)raw_.specular_);
	p->get_uniform_scalar("front.emission")->load((glm::vec4)raw_.emission_);
	p->get_uniform_scalar("front.shininess")->load(raw_.shininess_);
	*/
}
void		neb::gfx::material::material::step(gal::etc::timestep const & ts) {
		
	//raw_.diffuse_.step(time);
}


