#ifndef NEBULA_GFX_ENVIRON_SHADOW_POINT_HPP
#define NEBULA_GFX_ENVIRON_SHADOW_POINT_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/core/light/util/decl.hpp>

namespace neb { namespace gfx { namespace environ { namespace shadow {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class point: virtual public neb::gfx::environ::base {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::shadow>		program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::shadow::point>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::perspective>		proj_shared;
			typedef neb::gfx::core::light::point					light_type;
			typedef std::shared_ptr<light_type>					light_shared;
			typedef std::weak_ptr<light_type>					light_weak;
			typedef std::weak_ptr<neb::gfx::environ::three>				environ3_weak;
		public:
			point();
			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context) { abort(); }
			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context,
					GLint layer);
			virtual bool		shouldRender();
			/** check per view */
			virtual bool		shouldRender(unsigned int);
		public:
			/** @brief View Space Camera
			 * 
			 * @note OWNED
			 */			
			view_shared			view_[6];
			/** @brief Clip Space Camera
			 * 
			 * @note OWNED
			 */
			proj_shared			proj_;

			/** environ that uses the shadow map
			 * frustrum used to determine which shadowmaps need to be rendered
			 */
			environ3_weak			environ3_;

			light_weak			light_;
	};


}}}}


#endif
