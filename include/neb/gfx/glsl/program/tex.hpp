#ifndef NEB_GFX_GLSL_PROGRAM_TEX_HPP
#define NEB_GFX_GLSL_PROGRAM_TEX_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {

	class tex: public neb::gfx::glsl::program::base {
		public:
			tex(): neb::gfx::glsl::program::base() {}
			virtual ~tex() {}

			virtual void						init();

	};
}}}}

#endif

