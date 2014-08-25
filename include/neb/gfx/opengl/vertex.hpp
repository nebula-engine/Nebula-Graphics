
#include <GL/glew.h>

namespace neb { namespace gfx { namespace ogl {

	void			vertexAttribPointer(
			const GLenum*		target,
			GLint*			index,
			const GLint*		size,
			const GLenum*		type,
			const GLboolean*	normalized,
			const GLsizei*		stride,
			GLvoid * const *	pointer,
			GLuint*			buffer,
			const unsigned int*	buffer_index,
			const GLuint*		divisor,
			unsigned int		count);

	void			bufferSubData(
			const GLenum*		target,
			GLuint*			buffer,
			GLintptr*		begin,
			GLintptr*		end,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			GLvoid** const		data,
			unsigned int		count);

	void			bufferData(
			const GLenum*		target,
			const GLuint*		buffer,
			const GLsizeiptr*	datasize,
			const GLsizeiptr*	size,
			GLvoid** const		data,
			const GLenum*		usage,
			const unsigned int	count);

	void			bufferDataNull(
			const GLenum*		target,
			GLuint*			buffer,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			const GLenum*		usage,
			unsigned int		count);



}}}

