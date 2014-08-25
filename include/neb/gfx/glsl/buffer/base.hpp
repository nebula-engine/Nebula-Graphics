#ifndef NEB_GFX_GLSL_BUFFER_BASE_HPP
#define NEB_GFX_GLSL_BUFFER_BASE_HPP

#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/vertex.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/buffer/traits.hpp>

namespace neb { namespace gfx { namespace glsl { namespace buffer {

	template<typename BUFFER> class base: public traits<BUFFER> {
		public:
			typedef base<BUFFER> base_type;

			//enum {
			//	BUFFER_COUNT = traits<BUFFER>::BUFFER_COUNT
			//};

			void	init() {
				glGenBuffers(BUFFER::BUFFER_COUNT, buffer_);
				checkerror("glGenBuffers");
			}
			void			vertexAttribPointer()
			{
				neb::gfx::ogl::vertexAttribPointer(
						BUFFER::target_,
						index_,
						BUFFER::size_array_,
						BUFFER::type_,
						BUFFER::normalized_,
						BUFFER::stride_,
						BUFFER::pointer_,
						buffer_,
						BUFFER::buffer_index_,
						BUFFER::divisor_,
						traits<BUFFER>::ATTRIB_COUNT);
			}
			void			bind() {
				for(int c = 0; c < traits<BUFFER>::BUFFER_COUNT; c++)
				{
					glBindBuffer(BUFFER::target_[c], buffer_[c]);
				}
			}
			void			unbind() {
				for(int c = 0; c < traits<BUFFER>::BUFFER_COUNT; c++)
				{
					glBindBuffer(BUFFER::target_[c], 0);
				}
			}

			GLuint		buffer_[traits<BUFFER>::BUFFER_COUNT];
			/** attribute index */
			GLint*		index_;
	};

}}}}

#endif
