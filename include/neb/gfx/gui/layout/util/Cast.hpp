#ifndef NEB_GFX_GUI_LAYOUT_UTIL_CAST_HPP
#define NEB_GFX_GUI_LAYOUT_UTIL_CAST_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx { namespace gui { namespace layout { namespace util {
	class Cast:
		virtual public neb::fnd::itf::shared
	{
		public:
		std::shared_ptr<neb::gfx::gui::layout::base>		is_gfx_gui_layout_base();
	};
}}}}}

#endif
