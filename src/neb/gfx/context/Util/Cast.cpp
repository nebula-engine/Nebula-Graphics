#include <neb/gfx/context/util/Cast.hh>
#include <neb/gfx/context/Base.hh>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/context/fbo.hpp>

std::shared_ptr<neb::gfx::context::base>		neb::gfx::context::util::cast::isContextBase()
{
	return std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
}
std::shared_ptr<neb::gfx::context::window>		neb::gfx::context::util::cast::isContextWindow()
{
	return std::dynamic_pointer_cast<neb::gfx::context::window>(shared_from_this());
}
std::shared_ptr<neb::gfx::context::fbo>			neb::gfx::context::util::cast::isContextFBO()
{
	return std::dynamic_pointer_cast<neb::gfx::context::fbo>(shared_from_this());
}

