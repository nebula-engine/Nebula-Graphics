#include <stdio.h>
//#include <stdlib.h> removed by c_header_checker
#include <string.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/gl.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
//#include <neb/gfx/window/Base.hh>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
//#include <neb/gfx/free.hpp> removed by c_header_checker
//#include <neb/gfx/util/log.hpp> removed by c_header_checker

int		isExtensionSupported(const char *extension) {
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;

	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
	extensions = glGetString(GL_EXTENSIONS);
	/* It takes a bit of care to be fool-proof about parsing the
	   OpenGL extensions string. Don't be fooled by sub-strings,
	   etc. */
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
int isSupported(const char *extension) {
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



bool	isGLError() {
	return (glGetError() != GL_NO_ERROR);
}


