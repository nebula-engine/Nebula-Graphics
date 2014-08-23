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
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, float const * const & value) {
	glUniform1fv(location, count, value);

	std::stringstream ss;
	ss
		<< std::setw(16) << "glUniform1fv"
		<< std::setw(16) << location
		<< std::setw(16) << count;
	checkerror(ss.str());
}
void		neb::gfx::ogl::glUniformv(GLint location, GLsizei count, int const * const & value) {
	glUniform1iv(location, count, value);

	std::stringstream ss;
	ss
		<< std::setw(16) << "glUniform1iv"
		<< std::setw(16) << location
		<< std::setw(16) << count;
	checkerror(ss.str());
}
void		neb::gfx::ogl::glUniform(GLint location, int const & value) {
	glUniform1i(location, value);
	
	std::stringstream ss;
	ss
		<< std::setw(16) << "glUniform1i"
		<< std::setw(16) << location;

	checkerror(ss.str());
}

