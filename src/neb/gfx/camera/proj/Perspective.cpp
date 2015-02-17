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

//#include <neb/phx/test.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/environ/base.hpp>
//#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>

typedef neb::gfx::camera::proj::Perspective THIS;

THIS::Perspective():
	fovy_(45.0f),
	zn_(2.0f),
	zf_(1000.0f)
{
	//calculate();
}
/*void		neb::gfx::camera::proj::Perspective::init(RENDERABLE_S renderable) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	renderable_ = renderable;
}*/
glm::mat4&		THIS::proj()
{
	return _M_matrix;
}
void			THIS::set(float fovy, float near, float far)
{
	fovy_ = fovy;
	zn_ = near;
	zf_ = far;
	calculate();
}
void			THIS::calculate()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto parent = getParent();

	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "fovy" << ::std::setw(8) << fovy_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "aspect" << ::std::setw(8) << parent->viewport_.aspect_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zn" << ::std::setw(8) << zn_;
	LOG(lg, neb::gfx::sl, debug) << ::std::setw(8) << "zf" << ::std::setw(8) << zf_;
	
	if(parent->viewport_.aspect_ == 0.0) {
		parent->viewport_.aspect_ = 1.0;
	}

	_M_matrix = glm::perspective(fovy_, parent->viewport_.aspect_, zn_, zf_);

	calculate_geometry();
}
void			THIS::step(gal::etc::timestep const & ts)
{

}




