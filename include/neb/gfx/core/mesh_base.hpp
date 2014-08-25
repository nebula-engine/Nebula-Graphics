#ifndef NEB_GFX_CORE_BUFFER_BASE_HPP
#define NEB_GFX_CORE_BUFFER_BASE_HPP

#include <iomanip>

#include <GL/glew.h>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/opengl/vertex.hpp>
#include <neb/gfx/glsl/buffer/traits.hpp>

namespace neb { namespace gfx { namespace mesh {
	template<typename BUFFER> class base {
		protected:
			enum {
				BUFFER_COUNT = neb::gfx::glsl::buffer::traits<BUFFER>::BUFFER_COUNT,
				ATTRIB_COUNT = neb::gfx::glsl::buffer::traits<BUFFER>::ATTRIB_COUNT
			};

			virtual GLsizeiptr*		begin() = 0;
			virtual GLsizeiptr*		end() = 0;
			virtual GLsizeiptr*		size() = 0;
			virtual GLvoid** const		data() = 0;

			/** set by function of same name then sent to bufferData functions */
			GLvoid**			data_;
			GLsizeiptr*			size_;


			void			bufferData(std::shared_ptr<BUFFER> buffer)
			{
				neb::gfx::ogl::bufferData(
						BUFFER::target_,
						buffer->buffer_,
						BUFFER::datasize_,
						size(),
						(GLvoid** const)data(),
						BUFFER::usage_,
						BUFFER_COUNT
						);
			}
			void			bufferSubData(std::shared_ptr<BUFFER> buffer)
			{

				//LOG(lg, neb::gfx::sl, debug) << "update " << b << " to " << e;

				neb::gfx::ogl::bufferSubData(
						BUFFER::target_,
						buffer->buffer_,
						begin(),
						end(),
						BUFFER::datasize_,
						size(),
						(GLvoid** const)data(),
						BUFFER_COUNT
						);

					}
			void			bufferDataNull(std::shared_ptr<BUFFER> buffer)
			{

				neb::gfx::ogl::bufferDataNull(
						BUFFER::target_,
						buffer->buffer_,
						BUFFER::datasize_,
						size(),
						BUFFER::usage_,
						BUFFER_COUNT
						);

			}


	};

}}}

#endif
