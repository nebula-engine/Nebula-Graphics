#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/buffer/mesh.hpp>
#include <neb/gfx/glsl/program/threed.hpp>

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



