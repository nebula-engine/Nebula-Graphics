#ifndef NEB_GFX_GUI_OBJECT_UTIL_CAST_HPP
#define NEB_GFX_GUI_OBJECT_UTIL_CAST_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/gui/object/util/decl.hpp>

namespace neb { namespace gfx { namespace gui { namespace object { namespace util {
	class Cast:
		virtual public neb::fnd::itf::shared
	{
		std::shared_ptr<neb::gfx::gui::object::base>		is_gfx_gui_object_base();
		std::shared_ptr<neb::gfx::gui::object::terminal>	is_gfx_gui_object_terminal();
	};
}}}}}

#endif
