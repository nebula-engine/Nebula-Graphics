#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/buffer/mesh.hpp>
#include <neb/gfx/glsl/program/threed.hpp>

void			neb::gfx::glsl::buffer::mesh::init(
		std::shared_ptr<neb::gfx::glsl::program::threed> p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	checkerror("unknown");

	glGenBuffers(2, buffer_array_);
	checkerror("glGenBuffers");

	vertexAttribPointer(p);
}
void			neb::gfx::glsl::buffer::mesh::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}
void			neb::gfx::glsl::buffer::mesh::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void			neb::gfx::glsl::buffer::mesh::enableAttribs(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	program->get_attrib(neb::attrib_name::e::POSITION)->enable();
	program->get_attrib(neb::attrib_name::e::NORMAL)->enable();
	program->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	program->get_attrib(neb::attrib_name::e::TANGENT)->enable();
	program->get_attrib(neb::attrib_name::e::BINORMAL)->enable();
}
void			neb::gfx::glsl::buffer::mesh::vertexAttribPointer(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{

	static math::geo::vertex v;
	
	GLint attrib[] = {
		program->get_attrib(neb::attrib_name::e::POSITION)->o_,
		program->get_attrib(neb::attrib_name::e::NORMAL)->o_,
		program->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,
		program->get_attrib(neb::attrib_name::e::TANGENT)->o_,
		program->get_attrib(neb::attrib_name::e::BINORMAL)->o_
	};
	GLint size[] = {
		3,3,2,3,3
	};
	GLenum type[] = {
		GL_FLOAT,
		GL_FLOAT,
		GL_FLOAT,
		GL_FLOAT,
		GL_FLOAT
	};
	GLvoid* pointer[] = {
		(GLvoid*)((long)&v.p[0]		- (long)&v),
		(GLvoid*)((long)&v.n[0]		- (long)&v),
		(GLvoid*)((long)&v.tc[0]	- (long)&v),
		(GLvoid*)((long)&v.tangent[0]	- (long)&v),
		(GLvoid*)((long)&v.binormal[0]	- (long)&v)
	};
	GLsizei stride = sizeof(math::geo::vertex);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	for(unsigned int c = 0; c < 5; c++) {
		glEnableVertexAttribArray(attrib[c]);
		glVertexAttribPointer(
				attrib[c],
				size[c],
				type[c],
				GL_FALSE,
				stride,
				pointer[c]);
		glVertexAttribDivisor(attrib[c], 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

