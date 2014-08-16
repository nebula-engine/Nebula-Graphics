#ifndef NEBULA_GFX_ENVIRON_THREE_HPP
#define NEBULA_GFX_ENVIRON_THREE_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>

using namespace std;

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class three: virtual public neb::gfx::environ::base {
		public:
			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		render(std::shared_ptr<neb::gfx::context::base> context);
			weak_ptr<neb::gfx::Camera::View::Ridealong>		createViewRidealong(weak_ptr<neb::core::core::actor::base> actor);
		public:
					/** @brief View Space Camera
			 * 
			 * @note OWNED
			 */			
			std::shared_ptr<neb::gfx::Camera::View::base>			view_;
			/** @brief Clip Space Camera
			 * 
			 * @note OWNED
			 */
			std::shared_ptr<neb::gfx::Camera::Projection::base>		proj_;
			/** @brief %drawable
			 * 
			 * @note WEAK
			 * 
			 * content to draw
			 */
			//std::weak_ptr<neb::gfx::drawable::three>				drawable_;
	};


}}}


#endif
