#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

#include <memory>

#include <gal/stl/child.hpp>

#include <neb/fnd/context/util/decl.hpp>
#include <neb/fnd/util/decl.hpp>

#include <neb/fnd/plug/gfx/context/Base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/environ/util/decl.hpp>
#include <neb/gfx/Viewport.hpp>
#include <neb/gfx/context/util/Cast.hpp>
//#include <neb/gfx/gui/layout/base.hpp>
//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/drawable/base.hpp>

//#include <neb/fnd/scene/base.hpp>

namespace neb { namespace gfx { namespace context {
	/** @brief Context
	 *
	 * A rectangle on which to render.
	 * 
	 * - target (window, FBO, etc.)
	 * - viewport
	 * - projection and view camera
	 * - drawable (scene, layout, etc.)
	 * 
	 * @todo allow for manual ordering of context::window objects in window's context map
	 * such that things like layouts are render ON TOP of existing scene.'
	 */
	class base:
		virtual public neb::fnd::plug::gfx::context::Base,
		virtual public neb::gfx::context::util::cast
	{
		public:
			//typedef neb::fnd::context::util::Parent parent_t;
			base();
			//base&							operator=(base const & r);
			virtual void						init(parent_t * const &) = 0;
			//void							release();
			virtual void						step(gal::etc::timestep const & ts);
			virtual void						render();
			virtual void						resize(int w, int h);
			virtual void						setDrawable(std::shared_ptr<neb::fnd::drawable::Base>);
			virtual void						setEnviron(std::shared_ptr<neb::fnd::environ::Base>);
			//virtual std::shared_ptr<neb::fnd::environ::Base>	get_environ();
		public:
			//std::shared_ptr<neb::gfx::environ::base>		environ_;
	};

}}}

#endif


