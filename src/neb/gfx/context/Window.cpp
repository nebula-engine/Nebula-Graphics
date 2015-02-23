#include <neb/fnd/window/Base.hpp>

#include <neb/gfx/context/Window.hpp>

typedef neb::gfx::context::Window THIS;

THIS::Window()
{
}
void		THIS::init(parent_t * const & p)
{
	setParent(p);
	
	//neb::gfx::context::base::init(p);

	auto window = getParent()->getParent()->is_fnd_window_base();

	resize(window->get_width(), window->get_height());
}


