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

#include <neb/fnd/util/debug.hpp>

#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/util/log.hpp>

typedef neb::gfx::glsl::program::Base THIS;

THIS::~Base()
{
}
THIS::Base(std::string name):
	o_(0),
	name_(name)
{
	shader_[0] = 0;
	shader_[1] = 0;

	//flag_shader_def_.set(neb::gfx::glsl::program::util::flag_shader::SHADOW);
}
void	neb::gfx::glsl::program::Base::init()
{
	//NEBULA_GLSL_PROGRAM_FUNC;

	if(glfwGetCurrentContext() == NULL) return;

	o_ = glCreateProgram();
	
	checkerror("glCreateProgram %i\n");

	add_shader("v130/" + name_ + "/vs.glsl", GL_VERTEX_SHADER);
	add_shader("v130/" + name_ + "/fs.glsl", GL_FRAGMENT_SHADER);
	
	compile();
	
	scanUniforms();
	locate();
}
void	neb::gfx::glsl::program::Base::add_shaders(std::vector<neb::gfx::glsl::shader> s)
{
	//GRU_GLSL_PROGRAM_FUNC
	
	for(unsigned int i = 0; i < s.size(); ++i )
	{
		printv(info, "shader %i attached to program %i\n",s[i].o_,o_);
		
		glAttachShader(o_, s.at(i).o_);
		checkerror("glAttachShader");
	}
}
void	neb::gfx::glsl::program::Base::add_shader(std::string filename, GLenum type)
{
	neb::gfx::glsl::shader s;
	s.load(filename.c_str(), type);
	
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
void	neb::gfx::glsl::program::Base::compile()
{
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
		printv(warning, "compiler_log:%s\n", compiler_log);
		free (compiler_log);
	}

	printv(debug, "program=%i\n",o_);

}
void	neb::gfx::glsl::program::Base::use() const {
	
	checkerror("unknown");
	
	glUseProgram(o_);
	checkerror("glUseProgram %i\n", o_);

	// load flags
	//glUniform1i(uniform_table_[neb::gfx::glsl::uniforms::FLAG], flag_shader_.val_);
	//checkerror("");
}
void			neb::gfx::glsl::program::Base::restoreDefaultShaderFlags()
{
	flag_shader_ = flag_shader_def_;

	glUniform1i(uniform_table_[neb::gfx::glsl::uniforms::FLAG], (GLint)flag_shader_);
	checkerror("");
}
void	neb::gfx::glsl::program::Base::locate()
{
	use();

	for(unsigned int c = 0; c < neb::gfx::glsl::attribs::COUNT; c++)
	{
		attrib_table_[c] = glGetAttribLocation(o_, neb::gfx::glsl::attribs::string[c]);
		printv(debug, "attrib  %32s %i\n", neb::gfx::glsl::attribs::string[c], attrib_table_[c]);
		checkerror("");
	}

	for(unsigned int c = 0; c < neb::gfx::glsl::uniforms::COUNT; c++)
	{
		uniform_table_[c] = glGetUniformLocation(o_, neb::gfx::glsl::uniforms::string[c]);
		printv(debug, "uniform %32s %i\n", neb::gfx::glsl::uniforms::string[c], uniform_table_[c]);
		checkerror("");
	}


	restoreDefaultShaderFlags();

}
char const * shaderTypeString(GLenum type)
{
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
void		neb::gfx::glsl::program::Base::scanUniforms()
{
	GLsizei len;
	GLint size;
	GLenum type;
	GLchar str_name[128];
	for(int i = 0; i < 1000; i++) {
		glGetActiveUniform(o_, i, 128, &len, &size, &type, str_name);

		if(isGLError()) break;


		// scalar or vector

		std::string name = str_name;
		
		printv(debug, "processing: %s\n", name.c_str());
		
		size_t find_open = name.find("[");
		size_t find_close = name.find("]");

		if(find_open != std::string::npos) {
			if(find_close == std::string::npos) abort();

			name = name.substr(0, find_open);

			printv(debug, "array  %32s%32s\n", name.c_str(),
					shaderTypeString(type));
		} else {
			printv(debug, "single %32s%32s\n", name.c_str(),
					shaderTypeString(type));
		}
	}
}
int		THIS::get_attrib_table_value(int k) const
{
	return attrib_table_[k];
}
int		THIS::get_uniform_table_value(int k) const
{
	return uniform_table_[k];
}




