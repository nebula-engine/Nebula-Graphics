#ifndef NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP
#define NEB_GFX_GLSL_BUFFER_MESH_INSTANCED_HPP

#include <memory>

#include <GL/glew.h>

#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {
	class instanced:
		public neb::gfx::glsl::buffer::base<instanced>
	{
		public:
			typedef std::shared_ptr<neb::gfx::glsl::program::threed>	program_shared;
			typedef neb::gfx::glsl::buffer::base<instanced>			buffer_base_type;

			//static const glm::mat4 m;
			static constexpr void* pointer[ATTRIB_COUNT] = {
				(void*)0,
				(void*)16,
				(void*)32,
				(void*)48,
				(void*)0,
				(void*)0,
				(void*)0,
				(void*)0,
				(void*)0,
				(void*)0
			};
/*			static constexpr void* pointer[ATTRIB_COUNT] = {
				(void*)((long)&m[0] - (long)&m),
				(void*)((long)&m[1] - (long)&m),
				(void*)((long)&m[2] - (long)&m),
				(void*)((long)&m[3] - (long)&m),
				0,
				(void*)0,
				(void*)0,
				(void*)0,
				(void*)0,
				(void*)0
			};*/
			static constexpr GLenum		usage_[BUFFER_COUNT] = {
				GL_STREAM_DRAW,
				GL_STREAM_DRAW
			};
			static constexpr GLint		size_array_[ATTRIB_COUNT] = {
				4,4,4,4,4,4,4,4,4,1
			};
			static constexpr GLsizeiptr	datasize_[ATTRIB_COUNT] = {
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(glm::vec4),
				sizeof(GLfloat)
			};
			static constexpr GLsizei	stride_[ATTRIB_COUNT] = {
				sizeof(glm::mat4),
				sizeof(glm::mat4),
				sizeof(glm::mat4),
				sizeof(glm::mat4),
				0,0,0,0,0,0
			};
			static constexpr GLenum		type_[ATTRIB_COUNT] = {
				GL_FLOAT, GL_FLOAT, GL_FLOAT, 
				GL_FLOAT, GL_FLOAT, GL_FLOAT, 
				GL_FLOAT, GL_FLOAT, GL_FLOAT, 
				GL_FLOAT
			};
			static constexpr GLboolean	normalized_[ATTRIB_COUNT] = {
				GL_FALSE, GL_FALSE, GL_FALSE, 
				GL_FALSE, GL_FALSE, GL_FALSE, 
				GL_FALSE, GL_FALSE, GL_FALSE, 
				GL_FALSE
			};
			static constexpr unsigned int	buffer_index[ATTRIB_COUNT] = {
				0,0,0,0,1,2,3,4,5,6
			};
			static constexpr GLenum		target_[BUFFER_COUNT] = {
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER,
				GL_ARRAY_BUFFER
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

	};
}}}}

#endif


