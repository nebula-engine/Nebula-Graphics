#ifndef __GLUTPP_ATTRIBUTE_H__
#define __GLUTPP_ATTRIBUTE_H__

#include <memory>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl {
	class attrib {
		public:
			attrib();
			void		init(char const *, GLuint);
			int		locate(std::shared_ptr<neb::gfx::glsl::program::base> p);
			void		enable();
			void		disable();

			char const *	name_;
			GLuint		o_;
			GLuint		o_bind_;
	};
}}}

#endif
