#include <gal/log/log.hpp>


#include <neb/core/util/debug.hpp>
#include <neb/core/util/cast.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/camera/view/Free.hpp>
#include <neb/gfx/camera/view/Ridealong.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>

#include <neb/gfx/environ/three.hpp>
//#include <neb/gfx/drawable/base.hpp> removed by c_header_checker
#include <neb/gfx/util/log.hpp>
//#include <neb/gfx/glsl/program/threed.hpp> removed by c_header_checker

typedef neb::gfx::environ::three THIS;

void		neb::gfx::environ::three::init(parent_t * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());

	//programs_.reset(new neb::gfx::glsl::program::threed("3d"));
	//programs_->init();


	// camera
//	if(!view_) {
//		view_.reset(new neb::gfx::camera::view::Free(self));
//	}

	//proj_.reset(new neb::gfx::camera::proj::Perspective(self));
	createCameraPerspective();

	//camera_->init(shared_from_this());
}




