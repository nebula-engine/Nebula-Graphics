
#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/uniform.hpp>

void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec3 const & value) {
	glUniform3fv(location, count, &value[0]);
	checkerror("glUniform3fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, glm::vec4 const & value) {
	glUniform4fv(location, count, &value[0]);
	checkerror("glUniform4fv");
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, float const & value) {
	glUniform1fv(location, count, &value);
	checkerror("glUniform1fv");
}


