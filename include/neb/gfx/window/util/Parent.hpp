#ifndef NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_WINDOW_UTIL_PARENT_HH

#include <neb/core/window/util/Parent.hpp>

#include <neb/gfx/window/Base.hpp>

namespace neb { namespace gfx { namespace window { namespace util {
	class parent:
		virtual public neb::fnd::window::util::Parent
	{
		public:
			virtual void		render();
	};
}}}}

#endif
