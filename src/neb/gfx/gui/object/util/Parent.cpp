#include <neb/gfx/gui/object/util/parent.hpp>

typedef neb::gfx::gui::object::util::parent THIS;

neb::fnd::app::Base* const	THIS::get_fnd_app()
{
	auto l = is_gfx_gui_layout_base();
}


