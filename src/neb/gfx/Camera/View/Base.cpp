//#include <neb/app/base.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::camera::view::base::base(std::shared_ptr<neb::gfx::environ::base> parent):
	parent_(parent)
{
}
void		neb::gfx::camera::view::base::load(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	
	p->get_uniform_scalar("view")->load(view());
}


