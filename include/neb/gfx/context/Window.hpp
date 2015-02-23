#ifndef NEBULA_GRAPHICS_CONTEXT_WINDOW_HH
#define NEBULA_GRAPHICS_CONTEXT_WINDOW_HH

#include <memory>

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/context/Window.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/context/Base.hpp>

namespace neb { namespace gfx { namespace context {
	/** @brief %Context
	 *
	 * A context with a window as the target.
	 *
	 * @todo allow for manual ordering of context::window objects in window's context map
	 * such that things like layouts are render ON TOP of existing scene.'
	 */
	class Window:
		//virtual public neb::fnd::context::Window,
		virtual public neb::gfx::context::base
	{
		public:
			Window();
			virtual void			init(parent_t * const & p);
			//virtual void			step(gal::etc::timestep const & ts);
			
	};
}}}

#endif
