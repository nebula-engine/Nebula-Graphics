#ifndef NEB_GFX_GLSL_BUFFER_MESH_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {
	class mesh {
		public:
			void				init(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);
			void				bind();
			void				unbind();
			void				enableAttribs(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);
			void				vertexAttribPointer(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);
			

			union {
				GLuint			buffer_array_[2];
				struct {
					GLuint		indices_;
					GLuint		vbo_;
				};
			};
	};
}}}}

#endif

