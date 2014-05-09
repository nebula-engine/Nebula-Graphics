#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


#include <Nebula/Scene/scene.hpp>
#include <Nebula/Graphics/glsl/Uniform/uniform.hpp>
#include <Nebula/Graphics/window/window.hpp>
#include <Nebula/free.hpp>

void	Neb::glsl::Uniform::Scalar::Int::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}
void	Neb::glsl::Uniform::Scalar::Sampler2D::load(int i) {
	glUniform1i(o_, i);
	checkerror("glUniform1i");
}





void	Neb::glsl::Uniform::Vector::Int::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}




