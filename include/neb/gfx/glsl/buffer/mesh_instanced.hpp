#ifndef NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {
	class mesh_instanced {
		public:
			enum {
				ATTRIB_COUNT = 10,
				BUFFER_COUNT = 7
			};

			const GLenum type[ATTRIB_COUNT] = {
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT,
				GL_FLOAT
			};

			const GLboolean normalized[ATTRIB_COUNT] = {
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE,
				GL_FALSE
			};

			const GLuint buffer[ATTRIB_COUNT] = {
				model_,
				model_,
				model_,
				model_,
				sampler_,
				diffuse_,
				buffer_array_[4],
				buffer_array_[5],
				buffer_array_[6],
				buffer_array_[7]
			};

		public:
			void				init(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);
			void				bind();
			void				unbind();
			void				vertexAttribPointer(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);
			void				enableAttribs(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);


			union {
				GLuint			buffer_array_[BUFFER_COUNT];
				struct {
					GLuint		model_;
					GLuint		sampler_;
					GLuint		diffuse_;
					GLuint		ambient_;
					GLuint		specular_;
					GLuint		emission_;
					GLuint		shininess_;
				};
			};
	};
}}}}

#endif


