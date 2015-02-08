#ifndef NEBULA_GRAPHICS_RENDER_DESC_HPP
#define NEBULA_GRAPHICS_RENDER_DESC_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/camera/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx {

	class RenderDesc
	{
		public:
			RenderDesc();
			RenderDesc(
					camera::view::Base* nv,
					camera::proj::Base* np,
					glsl::program::Base* nd3,
					glsl::program::Base* nd3_HF,
					glsl::program::Base* nd3_inst);
			camera::view::Base*		v;
			camera::proj::Base*		p;
			glsl::program::Base*		d3;
			glsl::program::Base*		d3_HF;
			glsl::program::Base*		d3_inst;
	};
}}

#endif
