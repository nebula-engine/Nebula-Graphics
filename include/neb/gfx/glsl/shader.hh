#ifndef __GLUTPP_SHADER_H__
#define __GLUTPP_SHADER_H__

#include <GLFW/glfw3.h>

#include <gal/stl/verbosity.hpp>

namespace neb { namespace gfx { namespace glsl {
	class shader:
		public gal::tmp::Verbosity<neb::gfx::glsl::shader>
	{
	public:
		void		load(const char * filename, GLenum shader_type);
		GLuint		o_;
	};
}}}

#endif
