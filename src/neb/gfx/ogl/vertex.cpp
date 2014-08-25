
#include <neb/gfx/opengl/vertex.hpp>

neb::gfx::ogl::vertexAttribPointer(
		GLuint*		index,
		GLint*		size,
		GLenum*		type,
		GLboolean*	normalized,
		GLsizei*	stride,
		const GLvoid**	pointer,
		GLuint*		buffer,
		unsigned int*	buffer_index,
		GLuint*		divisor,
		unsigned int	count)
{
	for(unsigned int c = 0; c < count; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[buffer_index]);
		glEnableVertexAttribArray(index[c]);
		glVertexAttribPointer(
				attrib[c],
				size[c],
				type[c],
				normalized[c],
				stride[c],
				pointer[c]);
		glVertexAttribDivisor(index[c], divisor[c]);
	}
}
void			neb::gfx::ogl::bufferData(
		GLenum*		target,
		GLuint*		buffer,
		GLsizeiptr*	datasize,
		GLsizeiptr	size,
		const GLvoid**	data,
		GLenum		usage,
		unsigned int	count)
{

	for(unsigned int c = 0; c < count; c++)
	{
		glBindBuffer(target[c], buffer[c]);
	
		glBufferData(
				target[c],
				size * datasize[c],
				data[c],
				GL_STREAM_DRAW);

		checkerror("glBufferSubData");
	}
	
	glBindBuffer(target[c], 0);

}
void			neb::gfx::ogl::bufferData(
		GLenum*		target,
		GLuint*		buffer,
		GLsizeiptr*	datasize,
		GLsizeiptr	size,
		const GLvoid**	data,
		GLenum		usage,
		unsigned int	count)
{

	for(unsigned int c = 0; c < count; c++)
	{
		glBindBuffer(target[c], buffer[c]);
	
		glBufferData(
				target[c],
				size * datasize[c],
				data[c],
				GL_STREAM_DRAW);

		checkerror("glBufferSubData");
	}
	
	glBindBuffer(target[c], 0);

}
void			neb::gfx::ogl::bufferSubData(
		const GLenum*		target,
		GLuint*			buffer,
		GLintptr*		begin,
		GLintptr*		end,
		GLsizeiptr*		datasize,
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
		
		glBindBuffer(target[c], buffer[c]);
		
		glBufferSubData(
				target[c],
				offset,
				size[c] * datasize[c],
				(GLvoid*)((GLintptr)data[c] + offset));

		checkerror("glBufferSubData");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}




