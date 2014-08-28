
#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/free.hpp>

void		neb::gfx::glsl::uniform::Vector::mat4::load(int c, glm::mat4 const & v) {
	GLint o = o_[c];
	assert(o != -1);
	glUniformMatrix4fv(o, 1, GL_FALSE, &v[0][0]);
	checkerror("glUniform4fv");
}


