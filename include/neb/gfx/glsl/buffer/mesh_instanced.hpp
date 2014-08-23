#ifndef NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {
	class mesh_instanced {
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
				GLuint			buffer_array_[3];
				struct {
					GLuint		model_;
					GLuint		image_sampler_;
					GLuint		normal_map_sampler_;
				};
			};
	};
}}}}

#endif


