#ifndef NEBULA_GRAPHICS_CONTEXT_BASE_HH
#define NEBULA_GRAPHICS_CONTEXT_BASE_HH

#include <memory>


#include <neb/core/util/decl.hpp> // gru/config.hpp.in


#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/environ/util/decl.hpp>
#include <neb/gfx/Viewport.hpp>
#include <neb/gfx/Context/Util/Cast.hh>
//#include <neb/gfx/gui/layout/base.hpp>
//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/drawable/base.hpp>


//#include <neb/core/scene/base.hpp>

namespace neb {
	namespace gfx {
		namespace context {
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
				virtual public neb::itf::shared,
				virtual public neb::gfx::context::util::cast
			{
				public:
					//base();
					base(std::shared_ptr<neb::gfx::context::util::parent> parent);
					//base&						operator=(base const & r);
					//void						init();
					//void						release();
					virtual void					step(gal::etc::timestep const & ts);
					virtual void					render();
					virtual void					resize(int w, int h);


					std::weak_ptr<neb::gfx::environ::two>			createEnvironTwo();
					std::weak_ptr<neb::gfx::environ::three>			createEnvironThree();
					std::weak_ptr<neb::gfx::environ::shadow::point>		createEnvironShadowPoint();
					std::weak_ptr<neb::gfx::environ::shadow_directional>	createEnvironShadowDirectional();
					std::weak_ptr<neb::gfx::environ::vis_depth>		createEnvironVisDepth();
					void							setDrawable(std::shared_ptr<neb::gfx::drawable::base>);
				public:
					/** @brief %Parent
					 * 
					 * @note WEAK
					 */
					std::weak_ptr<neb::gfx::context::util::parent>			parent_;
				public:
					std::shared_ptr<neb::gfx::environ::base>			environ_;
			};
		}
	}
}
#endif



