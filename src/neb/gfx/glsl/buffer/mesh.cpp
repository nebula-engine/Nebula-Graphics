#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/buffer/mesh.hpp>
#include <neb/gfx/glsl/program/threed.hpp>


constexpr GLenum			neb::gfx::glsl::buffer::tri1::target_[BUFFER_COUNT] = {
	GL_ARRAY_BUFFER,
	GL_ELEMENT_ARRAY_BUFFER
};
constexpr GLenum			neb::gfx::glsl::buffer::tri1::usage_[BUFFER_COUNT] = {
	GL_STATIC_DRAW,
	GL_STATIC_DRAW
};
constexpr GLsizeiptr		neb::gfx::glsl::buffer::tri1::datasize_[BUFFER_COUNT] = {
	sizeof(math::geo::vertex),
	sizeof(GLushort)
};
constexpr GLint			neb::gfx::glsl::buffer::tri1::size_array_[ATTRIB_COUNT] = {
	3,3,2,3,3
};
constexpr GLenum			neb::gfx::glsl::buffer::tri1::type_[ATTRIB_COUNT] = {
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT,
	GL_FLOAT
};
constexpr GLboolean		neb::gfx::glsl::buffer::tri1::normalized_[ATTRIB_COUNT] = {
	GL_FALSE,
	GL_FALSE,
	GL_FALSE,
	GL_FALSE,
	GL_FALSE
};
/*			constexpr GLvoid* pointer[ATTRIB_COUNT] = {
			(GLvoid*)((long)&v.p[0]		- (long)&v),
			(GLvoid*)((long)&v.n[0]		- (long)&v),
			(GLvoid*)((long)&v.tc[0]	- (long)&v),
			(GLvoid*)((long)&v.tangent[0]	- (long)&v),
			(GLvoid*)((long)&v.binormal[0]	- (long)&v)
			};*/
constexpr GLvoid*		neb::gfx::glsl::buffer::tri1::pointer_[ATTRIB_COUNT] = {
	(GLvoid*)0,
	(GLvoid*)12,
	(GLvoid*)24,
	(GLvoid*)32,
	(GLvoid*)44
};

constexpr GLsizei		neb::gfx::glsl::buffer::tri1::stride_[ATTRIB_COUNT] = {
	sizeof(math::geo::vertex),
	sizeof(math::geo::vertex),
	sizeof(math::geo::vertex),
	sizeof(math::geo::vertex),
	sizeof(math::geo::vertex)
};
constexpr unsigned int		neb::gfx::glsl::buffer::tri1::buffer_index_[ATTRIB_COUNT] = {
	0,0,0,0,0
};
constexpr GLuint			neb::gfx::glsl::buffer::tri1::divisor_[ATTRIB_COUNT] = {
	0,0,0,0,0
};





void			neb::gfx::glsl::buffer::tri1::init(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	base_type::init();

	vertexAttribPointer();

	index_ = new GLint[5];
	index_[0] = program->get_attrib(neb::attrib_name::e::POSITION)->o_;
	index_[1] = program->get_attrib(neb::attrib_name::e::NORMAL)->o_;
	index_[2] = program->get_attrib(neb::attrib_name::e::TEXCOOR)->o_;
	index_[3] = program->get_attrib(neb::attrib_name::e::TANGENT)->o_;
	index_[4] = program->get_attrib(neb::attrib_name::e::BINORMAL)->o_;
}



