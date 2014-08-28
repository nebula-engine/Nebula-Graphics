#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/window/Base.hh>

neb::gfx::context::window::window(std::shared_ptr<neb::gfx::window::base> window):
	neb::gfx::context::base(window)
{
}
void		neb::gfx::context::window::init() {
	neb::gfx::context::base::__init();

	auto window = parent_.lock()->isWindowBase();

	resize(window->w_, window->h_);
}


