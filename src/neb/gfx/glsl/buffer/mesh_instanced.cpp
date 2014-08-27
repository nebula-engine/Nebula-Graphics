#include <iomanip>

#include <gal/log/log.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>

constexpr GLenum		neb::gfx::glsl::buffer::instanced::usage_[BUFFER_COUNT];
constexpr GLsizeiptr		neb::gfx::glsl::buffer::instanced::datasize_[BUFFER_COUNT];
constexpr GLenum		neb::gfx::glsl::buffer::instanced::target_[BUFFER_COUNT];
constexpr GLint			neb::gfx::glsl::buffer::instanced::size_array_[ATTRIB_COUNT];
constexpr GLsizei		neb::gfx::glsl::buffer::instanced::stride_[ATTRIB_COUNT];
constexpr GLenum		neb::gfx::glsl::buffer::instanced::type_[ATTRIB_COUNT];
constexpr GLboolean		neb::gfx::glsl::buffer::instanced::normalized_[ATTRIB_COUNT];
constexpr unsigned int		neb::gfx::glsl::buffer::instanced::buffer_index_[ATTRIB_COUNT];
constexpr GLuint		neb::gfx::glsl::buffer::instanced::divisor_[ATTRIB_COUNT];
constexpr void*			neb::gfx::glsl::buffer::instanced::pointer_[ATTRIB_COUNT];

void			neb::gfx::glsl::buffer::instanced::init(program_shared program) {

	base_type::init();

	index_ = new GLint[10];
	index_[0] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_MODEL0];
	index_[1] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_MODEL1];
	index_[2] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_MODEL2];
	index_[3] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_MODEL3];
	index_[4] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_SAMPLER];
	index_[5] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_DIFFUSE];
	index_[6] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_AMBIENT];
	index_[7] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_SPECULAR];
	index_[8] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_EMISSION];
	index_[9] = program->attrib_table_[neb::gfx::glsl::attribs::INSTANCE_SHININESS];
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


