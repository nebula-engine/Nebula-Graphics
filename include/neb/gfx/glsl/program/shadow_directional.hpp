#ifndef NEB_GFX_GLSL_PROGRAM_SHADOW_DIRECTIONAL_HPP
#define NEB_GFX_GLSL_PROGRAM_SHADOW_DIRECTIONAL_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class shadow_directional: public neb::gfx::glsl::program::base {
		public:
			shadow_directional(): neb::gfx::glsl::program::base() {}
			virtual ~shadow_directional() {}

			virtual void						init();

		};
}}}}

#endif


