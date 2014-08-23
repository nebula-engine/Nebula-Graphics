#ifndef NEB_GFX_GLSL_PROGRAM_TEXT_HPP
#define NEB_GFX_GLSL_PROGRAM_TEXT_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class text: public neb::gfx::glsl::program::base {
		public:
			text(): neb::gfx::glsl::program::base() {}
			virtual ~text() {}

			virtual void						init();

	};
}}}}

#endif

