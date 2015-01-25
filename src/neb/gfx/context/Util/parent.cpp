
#include <neb/gfx/context/util/Parent.hh>
#include <neb/gfx/context/fbo.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/vis_depth.hpp>

typedef neb::gfx::context::fbo		C_FBO;
typedef neb::gfx::context::fbo_multi	C_FBOM;
typedef neb::gfx::context::window	C_W;

void					neb::gfx::context::util::parent::render() {

	auto lamb = [&] (pointer p) {
		p->render();
	};

	map_.for_each(lamb);

}



