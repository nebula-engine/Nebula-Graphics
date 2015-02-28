#include <stdio.h>
#include <assert.h>
#include <iomanip>

#include <GL/glew.h>

#include <gal/log/log.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/actor/Base.hpp>
#include <neb/fnd/camera/proj/Base.hpp>

//#include <neb/phx/test.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/environ/base.hpp>
//#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
//#include <neb/gfx/util/io.hpp> removed by c_header_checker
//#include <neb/gfx/opengl/uniform.hpp> removed by c_header_checker

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
glm::mat4		THIS::proj()
{
	printv_func(DEBUG);
	return _M_matrix;
}
void			THIS::init(parent_t * const & parent)
{
	setParent(parent);

	calculate();
}
void			THIS::calculate_geometry()
{
}
void			THIS::release()
{
}
void			THIS::set(float fovy, float near, float far)
{
	printv_func(DEBUG);

	fovy_ = fovy;
	zn_ = near;
	zf_ = far;

	calculate();
}
void			THIS::calculate()
{
	printv_func(DEBUG);

	auto parent = getParent();
	auto fnd_env = parent->getParent();
	auto env = std::dynamic_pointer_cast<neb::gfx::environ::base>(fnd_env->G::get_object());
	
	neb::gfx::Viewport& vp = env->viewport_;

	printv(DEBUG, "fovy   %f\n", fovy_);
	printv(DEBUG, "aspect %f\n", vp.aspect_);
	printv(DEBUG, "zn     %f\n", zn_);
	printv(DEBUG, "zf     %f\n", zf_);
	
	if(vp.aspect_ == 0.0) {
		vp.aspect_ = 1.0;
	}

	_M_matrix = glm::perspective(fovy_, vp.aspect_, zn_, zf_);

	calculate_geometry();
}
void			THIS::step(gal::etc::timestep const & ts)
{

}




