#ifndef NEBULA_GFX_ENVIRON_NORMAL_MAP_HPP
#define NEBULA_GFX_ENVIRON_NORMAL_MAP_HPP

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/core/environ/visualization/Normal.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/environ/single.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class NormalMap:
		virtual public neb::fnd::environ::visualization::Normal,
		virtual public neb::gfx::environ::single<neb::gfx::camera::view::base>,
		virtual public neb::gfx::environ::three
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::base>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::base>		proj_shared;
		public:
			virtual void		init();

			//virtual void		step(gal::etc::timestep const & ts);

			virtual void		render(
					std::shared_ptr<neb::gfx::context::base> context);
	};


}}}


#endif
