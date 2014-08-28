#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/free.hpp>

void	neb::gfx::glsl::uniform::Scalar::Int::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}
void	neb::gfx::glsl::uniform::Scalar::Sampler2D::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}





