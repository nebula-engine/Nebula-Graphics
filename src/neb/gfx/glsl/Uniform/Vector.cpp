#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <iostream>

#include <assert.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/glut.h>

#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>


neb::gfx::glsl::Uniform::Vector::base::base(std::string name):
	name_(name),
	c_(0)
{
	for(int i = 0; i < LEN; i++) {
		o_[i] = -1;
	}

	assert(!name_.empty());

	//printf("%s\n",__PRETTY_FUNCTION__);
}
void			neb::gfx::glsl::Uniform::Vector::base::locate(std::shared_ptr<neb::gfx::glsl::program::base> p) {
	printf("%s\n",__PRETTY_FUNCTION__);

	assert(p);

	char o_str[8];
	//char name[128];

	assert(!name_.empty());
	
	std::string name;
	
	for(int c = 0; c < LEN; c++) {
		
		sprintf(o_str, "%i", c);
		
		name = name_ + "[" + o_str + "]";
		
		//printf("str = '%s' c = %i\n", o_str, c);
		
		GLint o = glGetUniformLocation(p->o_, name.c_str());
		
		std::cout << std::setw(16) << name << std::setw(16) << o << std::endl;
		
		if(o == -1) {
			c_ = c;
			break;
		}
		
		o_[c] = o;
	}
}



