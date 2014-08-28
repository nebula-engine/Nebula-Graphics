#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

//#include <math/mat44.hpp>

//#include <neb/scene/scene.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/free.hpp>




void	neb::gfx::glsl::uniform::Scalar::Float::load(float f) {
	glUniform1f(o_, f);
	checkerror("glUniform1f");
}




