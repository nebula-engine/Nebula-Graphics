#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/gui/layout/util/Cast.hpp>

typedef neb::gfx::gui::layout::util::Cast THIS;

std::shared_ptr<neb::gfx::gui::layout::base>		THIS::is_gfx_gui_layout_base()
{
	auto o = std::dynamic_pointer_cast<neb::gfx::gui::layout::base>(shared_from_this());
	return o;
}


