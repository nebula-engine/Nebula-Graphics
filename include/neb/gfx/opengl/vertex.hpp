

namespace neb { namespace gfx { namespace ogl {

	void			vertexAttribPointer(
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
			GLuint*			buffer_,
			GLintptr*		begin,
			GLintptr*		end,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			const GLvoid**		data,
			unsigned int		count);

	void			bufferData(
			const GLenum*		target,
			GLuint*			buffer,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			const GLvoid**		data,
			unsigned int		count);

	void			bufferDataNull(
			const GLenum*		target,
			GLuint*			buffer,
			const GLsizeiptr*	datasize,
			GLsizeiptr*		size,
			const GLenum*		usage,
			unsigned int		count);
			


}}}

