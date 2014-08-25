
#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/vertex.hpp>

void			neb::gfx::ogl::vertexAttribPointer(
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
		unsigned int		count)
{
	for(unsigned int c = 0; c < count; c++)
	{

		glBindBuffer(
				target[buffer_index[c]],
				buffer[buffer_index[c]]);

		glEnableVertexAttribArray(
				index[c]);

		glVertexAttribPointer(
				index[c],
				size[c],
				type[c],
				normalized[c],
				stride[c],
				pointer[c]);

		glVertexAttribDivisor(
				index[c],
				divisor[c]);
	}
}
void			neb::gfx::ogl::bufferData(
		const GLenum*		target,
		const GLuint*		buffer,
		const GLsizeiptr*	datasize,
		const GLsizeiptr*	size,
		const GLvoid**		data,
		const GLenum*		usage,
		const unsigned int	count)
{

	for(unsigned int c = 0; c < count; c++)
	{
		glBindBuffer(
				target[c],
				buffer[c]);

		glBufferData(
				target[c],
				size[c] * datasize[c],
				data[c],
				usage[c]);

		checkerror("glBufferSubData");

		glBindBuffer(target[c], 0);

	}


}
void			neb::gfx::ogl::bufferDataNull(
		const GLenum*		target,
		GLuint*			buffer,
		const GLsizeiptr*	datasize,
		GLsizeiptr*		size,
		const GLenum*		usage,
		unsigned int		count)
{

	for(unsigned int c = 0; c < count; c++)
	{
		glBindBuffer(target[c], buffer[c]);

		glBufferData(
				target[c],
				size[c] * datasize[c],
				NULL,
				usage[c]);

		checkerror("glBufferSubData");

		glBindBuffer(target[c], 0);

	}


}
void			neb::gfx::ogl::bufferSubData(
		const GLenum*		target,
		GLuint*			buffer,
		GLintptr*		begin,
		GLintptr*		end,
		const GLsizeiptr*	datasize,
		GLsizeiptr*		size,
		const GLvoid**		data,
		unsigned int		count)
{

	GLsizeiptr offset;

	for(unsigned int c = 0; c < count; c++) {

		offset = begin[c] * datasize[c];

		//LOG(lg, neb::gfx::sl, debug)
		//	<< std::setw(16) << offset
		//	<< std::setw(16) << siz * BUFFER::datasize[c];

		glBindBuffer(
				target[c],
				buffer[c]);

		glBufferSubData(
				target[c],
				offset,
				size[c] * datasize[c],
				(GLvoid*)((GLintptr)data[c] + offset));

		checkerror("glBufferSubData");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}




