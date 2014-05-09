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

void	Neb::glsl::Uniform::Scalar::Mat4::load(physx::PxMat44 m) {
	assert(o_ != -1);
	glUniformMatrix4fv(o_, 1, false, (float*)&m);
	checkerror("glUniform1i");
}



/*
void	Neb::glsl::Uniform::Vector::Mat3::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}

void	Neb::glsl::Uniform::Vector::Mat3::load(int c, int i) {
	glUniform1i(o_[c], i);
	checkerror("glUniform1i");
}
*/



