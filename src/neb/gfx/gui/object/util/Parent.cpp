#include <neb/gfx/gui/object/util/parent.hpp>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/gui/layout/util/parent.hpp>

typedef neb::gfx::gui::object::util::parent THIS;

neb::fnd::app::Base* const	THIS::get_fnd_app()
{
	auto l = is_gfx_gui_layout_base();
	assert(l);
	return l->get_fnd_app();
}


