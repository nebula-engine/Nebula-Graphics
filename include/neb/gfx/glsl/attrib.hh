#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl {
	class attrib {
		public:
			static constexpr char const * attrib_string_[attribs::COUNT] = {
				"coor",
				"tex",
				"position",
				"normal",
				"texcoor",
				"tangent",
				"binormal",
				"instance_model_0",
				"instance_model_1",
				"instance_model_2",
				"instance_model_3",
				"instance_sampler",
				"instance_diffuse",
				"instance_ambient",
				"instance_specular",
				"instance_emission",
				"instance_shininess"
			};

			attrib();
			void		init(char const *, GLuint);
			int		locate(std::shared_ptr<neb::gfx::glsl::program::base> p);
			void		enable();
			void		disable();

			char const *	name_;
			GLint		o_;
			GLuint		o_bind_;
	};
}}}

#endif
