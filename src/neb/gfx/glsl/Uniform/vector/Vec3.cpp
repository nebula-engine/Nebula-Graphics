#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


//#include <neb/scene/scene.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/free.hpp>


void	neb::gfx::glsl::uniform::Vector::Vec3::load(int c, float* v) {
	glUniform3fv(o_[c], 1, v);
	checkerror("glUniform3fv");
}

void	neb::gfx::glsl::uniform::Vector::Vec4::load(int c, float* v) {
	GLint o = o_[c];
	assert(o != -1);
	glUniform4fv(o, 1, v);
	checkerror("glUniform4fv");
}

void	neb::gfx::glsl::uniform::Vector::Vec3::load(int c, vec3 const & v) {
	glUniform3fv(o_[c], 1, &v[0]);
	checkerror("glUniform3fv");
}

void	neb::gfx::glsl::uniform::Vector::Vec4::load(int c, vec4 const & v) {
	GLint o = o_[c];
	assert(o != -1);
	glUniform4fv(o, 1, &v[0]);
	checkerror("glUniform4fv");
}


