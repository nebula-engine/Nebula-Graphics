#include <iomanip>
#include <sstream>

#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/uniform.hpp>

void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec3 const * const & value) {
	glUniform3fv(location, count, (float*)value);
	checkerror("glUniform3fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec4 const * const & value) {
	glUniform4fv(location, count, (float*)value);
	checkerror("glUniform4fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::mat4 const * const & value) {
	glUniformMatrix4fv(location, count, GL_FALSE, (float*)value);
	checkerror("glUniformMatrix4fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, float const * const & value) {
	glUniform1fv(location, count, value);
	checkerror("glUniform1fv %i %i\n", location, count);
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, int const * const & value) {
	checkerror("unknown");
	glUniform1iv(location, count, value);
	checkerror("glUniform1iv %i %i\n", location, count);
}
void		neb::gfx::ogl::glUniform(GLint location, int const & value) {
	glUniform1i(location, value);
	checkerror("glUniform1i %i\n", location);
}

