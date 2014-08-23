
#include <neb/gfx/glsl/program/text.hpp>

void		neb::gfx::glsl::program::text::init() {

	neb::gfx::glsl::program::base::init();

	add_shader("v130/text/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/text/fs.glsl", GL_FRAGMENT_SHADER);

	compile();

	add_attrib(neb::attrib_name::e::COOR, "coord", 0);

	scanUniforms();
	locate();
}



