#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/free.hpp>





void	neb::glsl::Uniform::Vector::Int::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}




