#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/shadow_directional.hpp>

void		neb::gfx::glsl::program::shadow_directional::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::glsl::program::shadow_directional>(shared_from_this());


	
	neb::gfx::glsl::program::base::init();

	add_shader("v130/shadow/directional/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/shadow/directional/fs.glsl", GL_FRAGMENT_SHADER);

	compile();

	GLint param;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param);
	LOG(lg, neb::gfx::sl, info) << "GL_MAX_VERTEX_ATTRIBS " << param;

//	add_attrib(neb::gfx::glsl::attribs::POSITION,	"position",	1);
	/*add_attrib(neb::gfx::glsl::attribs::NORMAL,		"normal",	2);
	add_attrib(neb::gfx::glsl::attribs::TEXCOOR,	"texcoor",	3);
	add_attrib(neb::gfx::glsl::attribs::TANGENT,	"tangent",	4);
	add_attrib(neb::gfx::glsl::attribs::BINORMAL,	"binormal",	5);*/
/*
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_MODEL0,		"instance_model0",		6);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_MODEL1,		"instance_model1",		7);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_MODEL2,		"instance_model2",		8);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_MODEL3,		"instance_model3",		9);
*/
/*	add_attrib(neb::gfx::glsl::attribs::INSTANCE_SAMPLER,		"instance_sampler",		10);

	add_attrib(neb::gfx::glsl::attribs::INSTANCE_DIFFUSE,		"instance_diffuse",		11);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_AMBIENT,		"instance_ambient",		12);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_SPECULAR,		"instance_specular",		13);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_EMISSION,		"instance_emission",		14);
	add_attrib(neb::gfx::glsl::attribs::INSTANCE_SHININESS,		"instance_shininess",		15);
*/

	scanUniforms();
	locate();


	//light_locations_.init(self);

}

