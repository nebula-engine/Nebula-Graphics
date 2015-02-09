#include <neb/gfx/window/util/Cast.hpp>
#include <neb/gfx/window/Base.hpp>

std::shared_ptr<neb::gfx::window::Base>	neb::gfx::window::util::cast::is_gfx_window_base()
{
	return std::dynamic_pointer_cast<neb::gfx::window::Base>(shared_from_this());
}

