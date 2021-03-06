
#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <iomanip>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include <neb/fnd/util/config.hpp> // neb/fnd/util/config.hpp.in

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/config.hpp> // neb/gfx/util/config.hpp.in
#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/app/__gfx_glsl.hpp>

std::vector<std::string>		readLines(std::string filename)
{
	filename = NEB_SHARE_DIR"/media/shaders/" + filename;

	std::ifstream ifs(filename);

	
	if(!ifs.is_open()) {
		printf("file not found %s\n", filename.c_str());
		abort();
	}

	std::vector<std::string> lines;
	for(std::string line; std::getline(ifs, line);) {
		lines.push_back(line);
	}
	return lines;
}
std::vector<std::string>		preprocess(const char * filename)
{
	std::vector<std::string> lines1 = readLines(filename);
	std::vector<std::string> lines2;
	
	for(std::string line : lines1) {
		if(line.find("#include") == 0) {

			size_t b = line.find('"');
			size_t e = line.find('"', b+1);

			std::string filename_inc = line.substr(b+1, e-b-1);

			//printf("include %s\n", filename_inc.c_str());

			auto linesi = preprocess(filename_inc.c_str());

			for(auto linei : linesi) lines2.push_back(linei);
		} else {
			lines2.push_back(line);
		}
	}
	
	return lines2;
}
void			neb::gfx::glsl::shader::load(const char * filename, GLenum shader_type)
{	
	printv_func(DEBUG);
	printv(DEBUG, "loading %s\n", filename);

	// read text
	
	std::vector<std::string> lines = preprocess(filename);
	
	std::stringstream ss;
	std::copy(lines.begin(), lines.end(), std::ostream_iterator<std::string>(ss, "\n"));

	int c = 0;
	for(auto str : lines)
		printv(DEBUG, "%3i:%s\n", c++, str.c_str());

	std::string str(ss.str());
	const char * data = str.c_str();
	
	// opengl
	o_ = glCreateShader(shader_type);
	checkerror("glCreateShader");

	if (!o_)
	{
		printv(CRITICAL, "create shader failed\n");
		exit(0);
	}

	glShaderSource(o_, 1, (const GLchar**)&data, NULL);


	glCompileShader(o_);

	GLint status = 0;
	glGetShaderiv(o_, GL_COMPILE_STATUS, &status);

	char buffer[4096];
	int len;
	glGetShaderInfoLog(o_, 4096, &len, buffer);

	if(len>0)
	{
		printv(ERROR, "%s: %s\n", filename, buffer);
	}

	if(!status)
	{
		glDeleteShader(o_);
		printv(CRITICAL, "compile failed\n");
		exit(0);
	}

	printv(DEBUG, "shader file '%s' loaded\n", filename);
}
/*
   int isExtensionSupported(const char *extension)
   {
   const GLubyte *extensions = NULL;
   const GLubyte *start;
   GLubyte *where, *terminator;

// Extension names should not have spaces.
where = (GLubyte *) strchr(extension, ' ');
if (where || *extension == '\0')
return 0;
extensions = glGetString(GL_EXTENSIONS);
// It takes a bit of care to be fool-proof about parsing the
// OpenGL extensions string. Don't be fooled by sub-strings,
// etc.
start = extensions;
for (;;)
{
//printf("%s\n",start);

where = (GLubyte *) strstr((const char *) start, extension);
if (!where)
break;
terminator = where + strlen(extension);
if (where == start || *(where - 1) == ' ')
if (*terminator == ' ' || *terminator == '\0')
return 1;
start = terminator;
}
return 0;
}
int isSupported(const char *extension)
{
if(isExtensionSupported(extension))
{
printf("%s is supported\n",extension);
return 1;
}

printf("%s is not supported\n",extension);
exit(0);

}

void CheckExt()
{
isSupported("GL_ARB_vertex_shader");
isSupported("GL_ARB_fragment_shader");
}

void neb::shader::CompileProgram(GLuint &program, GLuint shaderObjects[], int numShaders)
{
program = glCreateProgram();

for(int a=0; a<numShaders; a++)
{
// Attach The Shader Objects To The Program Object
glAttachShader(program, shaderObjects[a]);
}

// Link The Program Object
glLinkProgram(program);

GLint blen = 0;	
GLsizei slen = 0;

glGetProgramiv(program, GL_INFO_LOG_LENGTH , &blen);       

if (blen > 1)
{
GLchar* compiler_log = (GLchar*)malloc(blen);

glGetInfoLogARB(program, blen, &slen, compiler_log);
printf("compiler_log:%s\n", compiler_log);
free (compiler_log);
}

printf("program=%i\n",program);

}
*/
