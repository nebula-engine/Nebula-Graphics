//#include <neb/app/base.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/camera/view/Base.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

typedef neb::gfx::camera::view::Base THIS;

THIS::Base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		THIS::load(neb::fnd::glsl::program::Base const * const p)
{
	assert(p);

	auto v = view();

	glUniformMatrix4fv(
			p->get_uniform_table_value(neb::gfx::glsl::uniforms::VIEW),
			1,
			GL_FALSE,
			&v[0][0]);

	checkerror("glUniformMatrix4fv");
}


