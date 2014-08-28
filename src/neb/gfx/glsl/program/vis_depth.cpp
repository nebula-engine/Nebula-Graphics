#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/vis_depth.hpp>

void		neb::gfx::glsl::program::vis_depth::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::glsl::program::vis_depth>(shared_from_this());

	
	neb::gfx::glsl::program::base::init();

	add_shader("v130/vis/depth/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/vis/depth/fs.glsl", GL_FRAGMENT_SHADER);

	compile();


	scanUniforms();
	locate();


}

