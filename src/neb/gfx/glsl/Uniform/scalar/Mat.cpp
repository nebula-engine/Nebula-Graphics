#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/free.hpp>

void	neb::gfx::glsl::Uniform::Scalar::Mat4::load(mat4 const & m) {
	assert(o_ != -1);
	glUniformMatrix4fv(o_, 1, false, (float*)&m);
	checkerror("glUniform1i");
}




