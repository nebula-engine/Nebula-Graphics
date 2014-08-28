#include <stdio.h>
#include <assert.h>
#include <iomanip>

#include <GL/glew.h>

#include <gal/log/log.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::camera::proj::base::base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::camera::proj::base::load(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	
	
	//glViewport(0, 0, parent_->viewport_.w_, parent_->viewport_.h_);
	
	p->get_uniform_scalar("proj")->load(proj());
}
void		neb::gfx::camera::proj::base::step(gal::etc::timestep const & ts) {

}


neb::gfx::camera::proj::perspective::perspective(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::proj::base(parent),
	fovy_(45.0f),
	zn_(2.0f),
	zf_(10000.0f)
{

}
/*void		neb::gfx::camera::proj::perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
mat4		neb::gfx::camera::proj::perspective::proj() {

	auto parent = parent_.lock();
	assert(parent);

	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "fovy" << ::std::setw(8) << fovy_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "aspect" << ::std::setw(8) << parent->viewport_.aspect_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zn" << ::std::setw(8) << zn_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zf" << ::std::setw(8) << zf_;
	
	if(parent->viewport_.aspect_ == 0.0) {
		parent->viewport_.aspect_ = 1.0;
	}

	mat4 ret = glm::perspective(fovy_, parent->viewport_.aspect_, zn_, zf_);
	
	//ret.print();
	
	return ret;
}
void		neb::gfx::camera::proj::perspective::step(gal::etc::timestep const & ts) {

}








