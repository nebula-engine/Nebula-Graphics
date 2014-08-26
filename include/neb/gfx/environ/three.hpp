#ifndef NEBULA_GFX_ENVIRON_THREE_HPP
#define NEBULA_GFX_ENVIRON_THREE_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class three: virtual public neb::gfx::environ::base {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::threed>	program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
		public:
			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context);
			std::weak_ptr<neb::gfx::camera::view::ridealong>		createViewridealong(
					std::weak_ptr<neb::core::core::actor::base> actor);
		public:
			/** @brief View Space Camera
			 * 
			 * @note OWNED
			 */			
			view_shared			view_;
			/** @brief Clip Space Camera
			 * 
			 * @note OWNED
			 */
			proj_shared			proj_;
			/** @brief %glsl %program
			 * 
			 * @note OWNED
			 */
			program_shared			program_;

	};


}}}


#endif
