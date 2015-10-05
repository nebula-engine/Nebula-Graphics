#include <stdio.h>
#include <assert.h>
#include <iomanip>

#include <GL/glew.h>

#include <gal/log/log.hpp>

//#include <math/quat.hpp>
//#include <math/mat44.hpp>

//#include <glm/gtc/matrix_transform.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/actor/Base.hpp>

//#include <neb/phx/test.hpp>

#include <neb/gfx/environ/base.hpp>
//#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
//#include <neb/gfx/util/log.hpp> removed by c_header_checker
//#include <neb/gfx/util/io.hpp> removed by c_header_checker
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/camera/proj/base.hpp>

typedef neb::gfx::camera::proj::Base THIS;

THIS::Base()
{
}
void		THIS::load(neb::fnd::glsl::program::Base * const & p)
{	
	printv_func(DEBUG);
	//glViewport(0, 0, parent_->viewport_.w_, parent_->viewport_.h_);

	printv(DEBUG, _M_matrix);

	neb::gfx::ogl::glUniform(
			p->get_uniform_table_value(neb::gfx::glsl::uniforms::PROJ),
			_M_matrix);
}
void		THIS::step(gal::etc::timestep const & ts)
{

}

