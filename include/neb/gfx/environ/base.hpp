#ifndef NEBULA_GFX_ENVIRON_BASE_HPP
#define NEBULA_GFX_ENVIRON_BASE_HPP

#include <gal/etc/timestep.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/util/cast.hpp>
#include <neb/gfx/Viewport.hpp>


namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class base:
		virtual public neb::gfx::environ::util::cast
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::base>		program_shared;
		public:
			virtual ~base() {}


			virtual void		init();
			virtual void		step(gal::etc::timestep const & ts);


			virtual void		resize(int w, int h);


			virtual void		render(std::shared_ptr<neb::gfx::context::base> context) = 0;
		public:	
			/** @brief %Viewport
			 * 
			 * sub-rectangle within target
			 */
			neb::gfx::Viewport					viewport_;


			std::weak_ptr<neb::gfx::drawable::base>			drawable_;
			/** @brief %glsl %program
			 * 
			 * @note OWNED
			 */
			program_shared			program_;

	};


}}}


#endif
