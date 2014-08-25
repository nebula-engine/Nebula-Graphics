#include <iomanip>

#include <gal/log/log.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>

void			neb::gfx::glsl::buffer::instanced::init(program_shared program) {

	base_type::init();

	index_ = new GLint[10];
	index_[0] = program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL0)->o_;
	index_[1] = program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL1)->o_;
	index_[2] = program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL2)->o_;
	index_[3] = program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL3)->o_;
	index_[4] = program->get_attrib(neb::attrib_name::e::INSTANCE_SAMPLER)->o_;
	index_[5] = program->get_attrib(neb::attrib_name::e::INSTANCE_DIFFUSE)->o_;
	index_[6] = program->get_attrib(neb::attrib_name::e::INSTANCE_AMBIENT)->o_;
	index_[7] = program->get_attrib(neb::attrib_name::e::INSTANCE_SPECULAR)->o_;
	index_[8] = program->get_attrib(neb::attrib_name::e::INSTANCE_EMISSION)->o_;
	index_[9] = program->get_attrib(neb::attrib_name::e::INSTANCE_SHININESS)->o_;
}
/*void			neb::gfx::glsl::buffer::instanced::vertexAttribPointer(
  std::shared_ptr<neb::gfx::glsl::program::threed> program)
  {	

  for(unsigned int c = 0; c < ATTRIB_COUNT; c++) {
  glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
  checkerror("glBindBuffer");
  glEnableVertexAttribArray(index[c]);
  checkerror("glEnableVertexAttribArray");

  glVertexAttribPointer(
  index[c],
  size[c],
  type[c],
  normalized[c],
  stride[c],
  pointer[c]
  );

  checkerror("glVertexAttribPointer");

  glVertexAttribDivisor(index[c], 1);
  checkerror("glVertexAttribDivisor");
  }
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  }*/


