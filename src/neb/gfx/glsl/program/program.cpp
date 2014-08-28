#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <algorithm>
#include <cassert>
#include <iomanip>

#include <neb/core/util/debug.hpp>

#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>

neb::gfx::glsl::program::base::~base() {}
neb::gfx::glsl::program::base::base():
	o_(0)
{
	shader_[0] = 0;
	shader_[1] = 0;
}
void	neb::gfx::glsl::program::base::init()
{
	//NEBULA_GLSL_PROGRAM_FUNC;

	assert(glfwGetCurrentContext() != NULL);
	
	o_ = glCreateProgram();
	
	checkerror("glCreateProgram %i\n");

}
void	neb::gfx::glsl::program::base::add_shaders(std::vector<neb::gfx::glsl::shader> s)
{
	//GRU_GLSL_PROGRAM_FUNC
	
	for(unsigned int i = 0; i < s.size(); ++i )
	{
		printf("shader %i attached to program %i\n",s[i].o_,o_);
		
		glAttachShader(o_, s.at(i).o_);
		checkerror("glAttachShader");
	}
}
void	neb::gfx::glsl::program::base::add_shader(char const * filename, GLenum type)
{
	neb::gfx::glsl::shader s;
	s.load(filename, type);
	
	glAttachShader(o_, s.o_);
	checkerror("glAttachShader");
	
	switch(type)
	{
		case GL_VERTEX_SHADER:
			shader_[VERT] = 1;
			break;
		case GL_FRAGMENT_SHADER:
			shader_[FRAG] = 1;
			break;
		default:
			abort();
	}
}
void	neb::gfx::glsl::program::base::compile() {
	//GRU_GLSL_PROGRAM_FUNC
	
	assert(shader_[VERT] == 1);
	assert(shader_[FRAG] == 1);

	glLinkProgram(o_);
	checkerror("glLinkProgram");
	
	GLint blen = 0;	
	GLsizei slen = 0;
	
	glGetProgramiv(o_, GL_INFO_LOG_LENGTH , &blen);
	
	checkerror("glGetProgramiv");

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(o_, blen, &slen, compiler_log);
		printf("compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printf("program=%i\n",o_);

}
void	neb::gfx::glsl::program::base::use() {
	
	
	checkerror("unknown");
	
	glUseProgram(o_);
	checkerror("glUseProgram %i\n", o_);

	std::shared_ptr<neb::gfx::glsl::attrib> attrib;

	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;
		assert(attrib);
		//attrib->locate(shared_from_this());
	}
}
/*void	neb::gfx::glsl::program::base::add_attrib(neb::gfx::glsl::attribs name, char const * s, GLuint o_bind) {

  std::shared_ptr<neb::gfx::glsl::attrib> a(new neb::gfx::glsl::attrib);

  a->init(s, o_bind);

  attrib_[name] = a;
  }*/
void	neb::gfx::glsl::program::base::add_uniform_scalar(std::string name, GLenum type) {

	std::shared_ptr<neb::gfx::glsl::uniform::Scalar::base> u;

	switch(type) {
		case GL_BOOL:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Bool(name));
			break;
		case GL_INT:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Int(name));
			break;
		case GL_FLOAT:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Float(name));
			break;
		case GL_FLOAT_VEC3:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Vec3(name));
			break;
		case GL_FLOAT_VEC4:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Vec4(name));
			break;
		case GL_FLOAT_MAT4:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Mat4(name));
			break;
		case GL_SAMPLER_2D:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Sampler2D(name));
			break;
		case GL_SAMPLER_2D_ARRAY:
			u.reset(new neb::gfx::glsl::uniform::Scalar::Int(name));
			break;
		default:
			printf("unsupported glsl type \"%s\"\n", name.c_str());
			abort();
	}

	uniform_scalar_[name] = u;
}
void			neb::gfx::glsl::program::base::add_uniform_vector(std::string name, GLenum type) {

	std::shared_ptr<neb::gfx::glsl::uniform::Vector::base> u;

	switch(type) {
		case GL_INT:
			u.reset(new neb::gfx::glsl::uniform::Vector::Int(name));
			break;
		case GL_FLOAT:
			u.reset(new neb::gfx::glsl::uniform::Vector::Float(name));
			break;
		case GL_FLOAT_VEC3:
			u.reset(new neb::gfx::glsl::uniform::Vector::Vec3(name));
			break;
		case GL_FLOAT_VEC4:
			u.reset(new neb::gfx::glsl::uniform::Vector::Vec4(name));
			break;
		case GL_FLOAT_MAT4:
			u.reset(new neb::gfx::glsl::uniform::Vector::mat4(name));
			break;
		default:
			printf("unsupported glsl type \"%s\"\n", name.c_str());
			abort();
	}

	uniform_vector_[name] = u;

}
/*std::shared_ptr<neb::gfx::glsl::attrib>	neb::gfx::glsl::program::base::get_attrib(int name) {
  auto it = attrib_.find(name);

  if(it == attrib_.end())
  {
  printf("attribute %i not found\n",name);
  abort();
  }

  auto p = (*it).second;

  assert(p);

  return p;
  }*/
std::shared_ptr<neb::gfx::glsl::uniform::Scalar::base>	neb::gfx::glsl::program::base::get_uniform_scalar(std::string name) {
	//printf("%s\n", __PRETTY_FUNCTION__);

	auto it = uniform_scalar_.find(name);

	if(it == uniform_scalar_.end())
	{
		std::cout << "uniform \"" << name << "\" not found\n" << std::endl;
		abort();
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
std::shared_ptr<neb::gfx::glsl::uniform::Vector::base>		neb::gfx::glsl::program::base::get_uniform_vector(std::string name) {
	//printf("%s\n", __PRETTY_FUNCTION__);

	auto it = uniform_vector_.find(name);

	if(it == uniform_vector_.end()) {

		for(auto it2 = uniform_vector_.begin(); it2 != uniform_vector_.end(); ++it2) {
			std::cout << (*it2).first << std::endl;
		}

		std::cout << "uniform \"" << name << "\" not found\n" << std::endl;
		abort();
	}

	auto p = (*it).second;

	assert(p);

	return p;
}
void			neb::gfx::glsl::program::base::locate() {

	std::shared_ptr<neb::gfx::glsl::attrib> attrib;

	for(auto it = attrib_.begin(); it != attrib_.end(); ++it)
	{
		attrib = (*it).second;

		attrib->locate(shared_from_this());
	}



	for(unsigned int c = 0; c < neb::gfx::glsl::attribs::COUNT; c++)
	{
		attrib_table_[c] = glGetAttribLocation(o_, neb::gfx::glsl::attrib::attrib_string_[c]);
		printf("attrib  %32s %i\n", neb::gfx::glsl::attrib::attrib_string_[c], attrib_table_[c]);
		checkerror("");
	}

	for(unsigned int c = 0; c < neb::gfx::glsl::uniforms::COUNT; c++)
	{
		uniform_table_[c] = glGetUniformLocation(o_, neb::gfx::glsl::uniform::uniform_string_[c]);
		printf("uniform %32s %i\n", neb::gfx::glsl::uniform::uniform_string_[c], uniform_table_[c]);
		checkerror("");
	}







	{
		std::shared_ptr<neb::gfx::glsl::uniform::Scalar::base> u;

		for(auto it = uniform_scalar_.begin(); it != uniform_scalar_.end(); ++it) {
			u = (*it).second;
			u->locate(shared_from_this());
		}
	}	

	std::shared_ptr<neb::gfx::glsl::uniform::Vector::base> u;
	for(auto it = uniform_vector_.begin(); it != uniform_vector_.end(); ++it) {
		u = (*it).second;
		u->locate(shared_from_this());
	}
}
char const * shaderTypeString(GLenum type) {
	std::map<GLenum,char const *> m;

	m[GL_FLOAT]		="float";
	m[GL_FLOAT_VEC2]	="vec2";
	m[GL_FLOAT_VEC3]	="vec3";
	m[GL_FLOAT_VEC4]	="vec4";
	m[GL_DOUBLE]		="double";
	m[GL_DOUBLE_VEC2]	="dvec2";
	m[GL_DOUBLE_VEC3]	="dvec3";
	m[GL_DOUBLE_VEC4] 	="dvec4";
	m[GL_INT]		="int";
	m[GL_INT_VEC2]		="ivec2";
	m[GL_INT_VEC3]		="ivec3";
	m[GL_INT_VEC4]		="ivec4";
	m[GL_UNSIGNED_INT]	="unsigned int";
	m[GL_UNSIGNED_INT_VEC2]	="uvec2";
	m[GL_UNSIGNED_INT_VEC3]	="uvec3";
	m[GL_UNSIGNED_INT_VEC4]	="uvec4";
	m[GL_BOOL]				="bool";
	m[GL_BOOL_VEC2]				="bvec2";
	m[GL_BOOL_VEC3]				="bvec3";
	m[GL_BOOL_VEC4]				="bvec4";
	m[GL_FLOAT_MAT2]			="mat2";
	m[GL_FLOAT_MAT3]			="mat3";
	m[GL_FLOAT_MAT4]			="mat4";
	m[GL_FLOAT_MAT2x3]			="mat2x3";
	m[GL_FLOAT_MAT2x4]			="mat2x4";
	m[GL_FLOAT_MAT3x2]			="mat3x2";
	m[GL_FLOAT_MAT3x4]			="mat3x4";
	m[GL_FLOAT_MAT4x2]			="mat4x2";
	m[GL_FLOAT_MAT4x3]			="mat4x3";
	m[GL_DOUBLE_MAT2]			="dmat2";
	m[GL_DOUBLE_MAT3]			="dmat3";
	m[GL_DOUBLE_MAT4]			="dmat4";
	//	m[GL_DOUBLE_MAT2x3]			="dmat2x3";
	//	m[GL_DOUBLE_MAT2x4]			="dmat2x4";
	//	m[GL_DOUBLE_MAT3x2]			="dmat3x2";
	//	m[GL_DOUBLE_MAT3x4]			="dmat3x4";
	//	m[GL_DOUBLE_MAT4x2]			="dmat4x2";
	//	m[GL_DOUBLE_MAT4x3]			="dmat4x3";
	m[GL_SAMPLER_1D]			="sampler1D";
	m[GL_SAMPLER_2D]			="sampler2D";
	m[GL_SAMPLER_3D]			="sampler3D";
	m[GL_SAMPLER_CUBE]			="samplerCube";
	m[GL_SAMPLER_1D_SHADOW]			="sampler1DShadow";
	m[GL_SAMPLER_2D_SHADOW]			="sampler2DShadow";
	m[GL_SAMPLER_1D_ARRAY]			="sampler1DArray";
	m[GL_SAMPLER_2D_ARRAY]			="sampler2DArray";
	m[GL_SAMPLER_1D_ARRAY_SHADOW]			="sampler1DArrayShadow";
	m[GL_SAMPLER_2D_ARRAY_SHADOW]			="sampler2DArrayShadow";
	m[GL_SAMPLER_2D_MULTISAMPLE]			="sampler2DMS";
	m[GL_SAMPLER_2D_MULTISAMPLE_ARRAY]		="sampler2DMSArray";
	m[GL_SAMPLER_CUBE_SHADOW]			="samplerCubeShadow";
	m[GL_SAMPLER_BUFFER]				="samplerBuffer";
	m[GL_SAMPLER_2D_RECT]				="sampler2DRect";
	m[GL_SAMPLER_2D_RECT_SHADOW]			="sampler2DRectShadow";
	m[GL_INT_SAMPLER_1D]				="isampler1D";
	m[GL_INT_SAMPLER_2D]				="isampler2D";
	m[GL_INT_SAMPLER_3D]				="isampler3D";
	m[GL_INT_SAMPLER_CUBE]				="isamplerCube";
	m[GL_INT_SAMPLER_1D_ARRAY]			="isampler1DArray";
	m[GL_INT_SAMPLER_2D_ARRAY]			="isampler2DArray";
	m[GL_INT_SAMPLER_2D_MULTISAMPLE]		="isampler2DMS";
	m[GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY]		="isampler2DMSArray";
	m[GL_INT_SAMPLER_BUFFER]			="isamplerBuffer";
	m[GL_INT_SAMPLER_2D_RECT]			="isampler2DRect";
	m[GL_UNSIGNED_INT_SAMPLER_1D]			="usampler1D";
	m[GL_UNSIGNED_INT_SAMPLER_2D]			="usampler2D";
	m[GL_UNSIGNED_INT_SAMPLER_3D]			="usampler3D";
	m[GL_UNSIGNED_INT_SAMPLER_CUBE]			="usamplerCube";
	m[GL_UNSIGNED_INT_SAMPLER_1D_ARRAY]		="usampler2DArray";
	m[GL_UNSIGNED_INT_SAMPLER_2D_ARRAY]		="usampler2DArray";
	m[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE]	="usampler2DMS";
	m[GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY]	="usampler2DMSArray";
	m[GL_UNSIGNED_INT_SAMPLER_BUFFER]		="usamplerBuffer";
	m[GL_UNSIGNED_INT_SAMPLER_2D_RECT]		="usampler2DRect";

	auto it = m.find(type);

	if(it != m.end()) return it->second;

	return "unknown";
}
void		neb::gfx::glsl::program::base::scanUniforms() {
	GLsizei len;
	GLint size;
	GLenum type;
	GLchar str_name[128];
	for(int i = 0; i < 1000; i++) {
		glGetActiveUniform(o_, i, 128, &len, &size, &type, str_name);

		if(isGLError()) break;

		//printf("name=%32s type=%s\n", str_name, shaderTypeString(type));

		// scalar or vector


		std::string name = str_name;

		std::cout << "processing: " << name << std::endl;

		size_t find_open = name.find("[");
		size_t find_close = name.find("]");

		if(find_open != std::string::npos) {

			if(find_close == std::string::npos) {
				abort();
			}

			name = name.substr(0, find_open);


			auto it = uniform_vector_.find(name);
			if(it != uniform_vector_.end()) continue;

			add_uniform_vector(name, type);

			std::cout
				<< std::setw(16) << "array"
				<< std::setw(32) << name
				<< std::setw(32) << shaderTypeString(type)
				<< std::endl;


		} else {

			add_uniform_scalar(name, type);

			std::cout
				<< std::setw(16) << "single"
				<< std::setw(32) << name
				<< std::setw(32) << shaderTypeString(type)
				<< std::endl;
		}
	}
}


