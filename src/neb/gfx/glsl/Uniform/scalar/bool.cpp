#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/free.hpp>

void	neb::glsl::Uniform::Scalar::Bool::load_b(bool const & b) {
	glUniform1i(o_, b);
	checkerror("glUniform1i");
}
void	neb::glsl::Uniform::Scalar::Bool::load_b(bool && b) {
	glUniform1i(o_, b);
	checkerror("glUniform1i");
}









