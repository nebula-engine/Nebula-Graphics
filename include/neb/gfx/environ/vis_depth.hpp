#ifndef NEBULA_GFX_ENVIRON_VIS_DEPTH_HPP
#define NEBULA_GFX_ENVIRON_VIS_DEPTH_HPP

#include <neb/fnd/core/actor/util/decl.hpp>
#include <neb/fnd/environ/visualization/Depth.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/core/light/util/decl.hpp>

namespace neb { namespace gfx { namespace environ {
	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class vis_depth:
		//virtual public neb::fnd::environ::visualization::Depth,
		virtual public neb::gfx::environ::three
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::Base>	program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::Base>	view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::Base>	proj_shared;
			typedef neb::gfx::core::light::base		light_type;
			typedef std::shared_ptr<light_type>			light_shared;
			typedef std::weak_ptr<light_type>			light_weak;
		public:
			vis_depth();
			virtual void		init(parent_t * const & p);
			virtual void		step(gal::etc::timestep const & ts);
			virtual void		render(std::shared_ptr<neb::gfx::context::base> context);
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
			light_weak			light_;
	};
}}}


#endif

