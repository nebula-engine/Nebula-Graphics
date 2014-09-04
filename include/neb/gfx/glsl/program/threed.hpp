#ifndef NEB_GFX_GLSL_PROGRAM_THREED_HPP
#define NEB_GFX_GLSL_PROGRAM_THREED_HPP

#include <neb/gfx/glsl/uniform/light_array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class threed: public neb::gfx::glsl::program::base {
		public:
			threed(): neb::gfx::glsl::program::base() {}
			virtual ~threed() {}

			virtual void						init();

			neb::gfx::glsl::uniform::light_locations		light_locations_;
		};
}}}}

#endif

