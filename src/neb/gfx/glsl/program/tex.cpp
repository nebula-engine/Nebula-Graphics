
#include <neb/gfx/glsl/program/tex.hpp>

void		neb::gfx::glsl::program::tex::init() {

	neb::gfx::glsl::program::base::init();

	add_shader("v130/tex/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/tex/fs.glsl", GL_FRAGMENT_SHADER);
	
	compile();
	
//	add_attrib(neb::gfx::glsl::attribs::COOR, "coord", 0);

	scanUniforms();
	locate();
}



