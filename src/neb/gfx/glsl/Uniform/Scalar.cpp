#include <stdio.h>
#include <string.h>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::glsl::uniform::Scalar::base::base(std::string name) {
	//printf("%s\n",__PRETTY_FUNCTION__);
	name_ = name;
	o_ = -1;
	//printf("uniform %s\n",name_);
	//checkerror("glGetUniformLocation");
	//locate();
}
void	neb::gfx::glsl::uniform::Scalar::base::locate(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	
	assert(p);
	
	assert(!name_.empty());
	
	o_ = glGetUniformLocation(p->o_, name_.c_str());
	
	printf("%s %s %i\n",__PRETTY_FUNCTION__, name_.c_str(), o_);

	checkerror("glGetUniformLocation");
}


