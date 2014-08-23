#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/threed.hpp>

void		neb::gfx::glsl::program::threed::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::glsl::program::threed>(shared_from_this());


	
	neb::gfx::glsl::program::base::init();

	add_shader("v130/3d/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/3d/fs.glsl", GL_FRAGMENT_SHADER);

	compile();

	GLint param;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param);
	LOG(lg, neb::gfx::sl, info) << "GL_MAX_VERTEX_ATTRIBS " << param;

	add_attrib(neb::attrib_name::e::POSITION,	"position",	1);
	add_attrib(neb::attrib_name::e::NORMAL,		"normal",	2);
	add_attrib(neb::attrib_name::e::TEXCOOR,	"texcoor",	3);
	add_attrib(neb::attrib_name::e::TANGENT,	"tangent",	4);
	add_attrib(neb::attrib_name::e::BINORMAL,	"binormal",	5);

	add_attrib(neb::attrib_name::e::INSTANCE_MODEL0,		"instance_model0",		6);
	add_attrib(neb::attrib_name::e::INSTANCE_MODEL1,		"instance_model1",		7);
	add_attrib(neb::attrib_name::e::INSTANCE_MODEL2,		"instance_model2",		8);
	add_attrib(neb::attrib_name::e::INSTANCE_MODEL3,		"instance_model3",		9);

	add_attrib(neb::attrib_name::e::INSTANCE_SAMPLER,		"instance_sampler",		10);

	add_attrib(neb::attrib_name::e::INSTANCE_DIFFUSE,		"instance_diffuse",		11);
	add_attrib(neb::attrib_name::e::INSTANCE_AMBIENT,		"instance_ambient",		12);
	add_attrib(neb::attrib_name::e::INSTANCE_SPECULAR,		"instance_specular",		13);
	add_attrib(neb::attrib_name::e::INSTANCE_EMISSION,		"instance_emission",		14);
	add_attrib(neb::attrib_name::e::INSTANCE_SHININESS,		"instance_shininess",		15);

	scanUniforms();
	locate();


	light_locations_.init(self);

}

