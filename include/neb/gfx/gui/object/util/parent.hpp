#ifndef NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_GUI_OBJECT_UTIL_PARENT_HH

#include <neb/core/util/decl.hpp>
#include <neb/core/util/parent.hpp>

#include <neb/gfx/gui/object/util/Cast.hpp>
#include <neb/gfx/gui/layout/util/Cast.hpp>
#include <neb/gfx/gui/object/util/decl.hpp>

namespace neb { namespace gfx { namespace gui { namespace object { namespace util {
	/** @brief parent
	*/
	class parent :
		virtual public neb::fnd::util::parent<neb::gfx::gui::object::base, parent>,
		virtual public neb::gfx::gui::layout::util::Cast,
		virtual public neb::gfx::gui::object::util::Cast
	{
		public:
			neb::fnd::app::Base* const	get_fnd_app();
	};
}}}}}

#endif

