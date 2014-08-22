#ifndef NEB_GFX_OPENGL_UNIFORM_HPP
#define NEB_GFX_OPENGL_UNIFORM_HPP

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace neb { namespace gfx { namespace ogl {
	void		glUniformv(GLint location, GLsizei count, glm::vec3 const & value);
	void		glUniformv(GLint location, GLsizei count, glm::vec4 const & value);
	void		glUniformv(GLint location, GLsizei count, float const & value);
}}}

#endif
