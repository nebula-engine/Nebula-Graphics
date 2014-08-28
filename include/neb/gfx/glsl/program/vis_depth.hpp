#ifndef NEB_GFX_GLSL_PROGRAM_VIS_DEPTH_HPP
#define NEB_GFX_GLSL_PROGRAM_VIS_DEPTH_HPP

#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class vis_depth:
		public neb::gfx::glsl::program::base
	{
		public:
			vis_depth(): neb::gfx::glsl::program::base() {}

			virtual ~vis_depth() {}

			virtual void						init();

	};
}}}}

#endif


