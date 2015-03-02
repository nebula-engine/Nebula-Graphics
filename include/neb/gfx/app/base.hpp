#ifndef NEB_GFX_APP_BASE_HPP
#define NEB_GFX_APP_BASE_HPP

#include <gal/stl/verbosity.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/app/glfw.hpp>

namespace neb { namespace gfx { namespace app {
	/** @brief base */
	class Base:
		public gal::tmp::Verbosity<neb::gfx::app::Base>,
		virtual public neb::gfx::app::draw,
		virtual public neb::gfx::app::glsl,
		virtual public neb::gfx::app::glfw
	{
		public:
			using gal::tmp::Verbosity<neb::gfx::app::Base>::printv;
			//static weak_ptr<neb::gfx::app::Base>		initialize();
		protected:
			virtual void					init(parent_t * const & p);
			virtual void					__init();
			virtual void					__release();
		public:
			//virtual void					render();
			virtual void					release();
			virtual void					step(gal::etc::timestep const & ts);
			//virtual void					loop();
			virtual void					update();
			virtual double			get_time();
	};
}}}

#endif
