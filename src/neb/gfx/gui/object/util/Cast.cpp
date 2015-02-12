#include <neb/gfx/gui/object/terminal.hh>
#include <neb/gfx/gui/object/util/Cast.hpp>

typedef neb::gfx::gui::object::util::Cast THIS;

std::shared_ptr<neb::gfx::gui::object::base>		THIS::is_gfx_gui_object_base()
{
	auto o = std::dynamic_pointer_cast<neb::gfx::gui::object::base>(shared_from_this());
	return o;
}
std::shared_ptr<neb::gfx::gui::object::terminal>	THIS::is_gfx_gui_object_terminal()
{
	auto o = std::dynamic_pointer_cast<neb::gfx::gui::object::terminal>(shared_from_this());
	return o;
}

