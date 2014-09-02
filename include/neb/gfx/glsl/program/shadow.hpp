#ifndef NEB_GFX_GLSL_PROGRAM_SHADOW_DIRECTIONAL_HPP
#define NEB_GFX_GLSL_PROGRAM_SHADOW_DIRECTIONAL_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class shadow:
		public neb::gfx::glsl::program::base
	{
		public:
			shadow(): neb::gfx::glsl::program::base() {}

			virtual ~shadow() {}

			virtual void						init();

	};
}}}}

#endif


