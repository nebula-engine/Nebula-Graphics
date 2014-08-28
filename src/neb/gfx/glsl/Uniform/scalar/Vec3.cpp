#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>


//#include <neb/scene/scene.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/free.hpp>


void	neb::gfx::glsl::uniform::Scalar::Vec3::load(float* v) {
	glUniform3fv(o_, 1, v);
	checkerror("glUniform3fv");
}
void	neb::gfx::glsl::uniform::Scalar::Vec3::load(vec3 const & v) {
	glUniform3fv(o_, 1, &v[0]);
	checkerror("glUniform3fv");
}


void	neb::gfx::glsl::uniform::Scalar::Vec4::load(float* v) {
	glUniform4fv(o_, 1, v);
	checkerror("glUniform4fv");
}
void	neb::gfx::glsl::uniform::Scalar::Vec4::load(vec4 const & v) {
	glUniform4fv(o_, 1, &v[0]);
	checkerror("glUniform4fv");
}


