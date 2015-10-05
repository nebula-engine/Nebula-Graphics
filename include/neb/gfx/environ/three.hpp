#ifndef NEBULA_GFX_ENVIRON_THREE_HPP
#define NEBULA_GFX_ENVIRON_THREE_HPP

#include <neb/fnd/core/actor/util/decl.hpp>
#include <neb/fnd/camera/util/decl.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/environ/base.hpp>

namespace neb { namespace gfx { namespace environ {

	/** @brief base
	 *
	 * Abstract class that contains functions and data needed to render a specific kind of drawable.
	 */
	class three:
		virtual public neb::gfx::environ::base
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::Base>		program_shared;
			typedef std::shared_ptr<neb::gfx::camera::view::Base>		view_shared;
			typedef std::shared_ptr<neb::gfx::camera::proj::Base>		proj_shared;
		public:
			virtual void			init(parent_t * const & p) = 0;
			virtual void			render(neb::fnd::context::Base * const & context) = 0;
		public:
			struct {
				program_shared			d3_;
				program_shared			d3_HF_;
				program_shared			d3_inst_;
			} programs_;
	};
}}}

#endif
