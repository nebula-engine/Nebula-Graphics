
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/core/mesh_instanced.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/free.hpp>

void			neb::gfx::mesh::instanced::init(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	mesh_.init_buffer(program);


	auto buf(std::make_shared<neb::gfx::glsl::buffer::instanced>());
	buffers_[program.get()] = buf;
	
	buf->init(program);
	
	bufferDataNull(buf);
}
/*void			neb::gfx::mesh::instanced::bufferSubData(
		std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf)
{
	checkerror("unknown");

	void* data[] = {
		instances_->get<0, glm::mat4>(),
		instances_->get<1, glm::vec4>(),
		instances_->get<2, glm::vec4>(),
		instances_->get<3, glm::vec4>(),
		instances_->get<4, glm::vec4>(),
		instances_->get<5, glm::vec4>(),
		instances_->get<6, GLfloat>()
	};

	GLuint* buffer = buf->buffer_;

	auto b = instances_->update_begin_;
	auto e = instances_->update_end_;

	if(e < b) return;

	auto len = e - b + 1;
	
	LOG(lg, neb::gfx::sl, debug) << "update " << b << " to " << e;
	
	for(unsigned int c = 0; c < BUFFER_COUNT; c++) {

		GLintptr offset = b * buffer_type::datasize[c];

		LOG(lg, neb::gfx::sl, debug)
			<< std::setw(16) << offset
			<< std::setw(16) << len * datasize[c];

		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		glBufferSubData(
				GL_ARRAY_BUFFER,
				offset,
				len * datasize[c],
				(GLvoid*)((GLintptr)data[c] + offset));
		checkerror("glBufferSubData");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	instances_->reset_update();
}*/
/*void			neb::gfx::mesh::instanced::bufferDataNull(
		std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf)
{
	checkerror("unknown");

	auto size = instances_->size_array();

	GLuint* buffer = buf->buffer_array_;

	for(unsigned int c = 0; c < BUFFER_COUNT; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		glBufferData(
				GL_ARRAY_BUFFER,
				size * datasize[c],
				NULL,
				GL_STREAM_DRAW);
		checkerror("glBufferSubData");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	}*/

GLsizeiptr*		neb::gfx::mesh::instanced::size_array() {

	for(unsigned int c = 0; c < BUFFER_COUNT; c++)
	{
		size_array_[c] = instances_->size_array();
	}

	return size_array_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::size() {

	begin();
	end();

	for(unsigned int c = 0; c < BUFFER_COUNT; c++)
	{
		size_[c] = end_[c] - begin_[c] + 1;
	}

	return size_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::end() {
	end_[0] = instances_->update_end_;
	end_[1] = instances_->update_end_;
	end_[2] = instances_->update_end_;
	end_[3] = instances_->update_end_;
	end_[4] = instances_->update_end_;
	end_[5] = instances_->update_end_;
	end_[6] = instances_->update_end_;
	return end_;
}
GLsizeiptr*		neb::gfx::mesh::instanced::begin() {
	begin_[0] = instances_->update_begin_;
	begin_[1] = instances_->update_begin_;
	begin_[2] = instances_->update_begin_;
	begin_[3] = instances_->update_begin_;
	begin_[4] = instances_->update_begin_;
	begin_[5] = instances_->update_begin_;
	begin_[6] = instances_->update_begin_;
	return begin_;
}
GLvoid** const		neb::gfx::mesh::instanced::data() {
	data_[0] = instances_->get<0, glm::mat4>();
	data_[1] = instances_->get<1, glm::vec4>();
	data_[2] = instances_->get<2, glm::vec4>();
	data_[3] = instances_->get<3, glm::vec4>();
	data_[4] = instances_->get<4, glm::vec4>();
	data_[5] = instances_->get<5, glm::vec4>();
	data_[6] = instances_->get<6, GLfloat>();
	return data_;
}
/*void			neb::gfx::mesh::instanced::bufferData(
  std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf)
  {
  checkerror("unknown");

  auto size = instances_->size();


  GLuint* buffer = buf->buffer_array_;

  neb::gfx::ogl::bufferData(
  buffer_array_,
  datasize,
  size,
  data,
  GL_STREAM_DRAW,
  BUFFER_COUNT
  );


  }*/	
void			neb::gfx::mesh::instanced::draw(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	if(!buffers_[program.get()])
	{	
		init(program);
	}
	auto buf = buffers_[program.get()];

	if(!buf) return;


	instances_->update_slots();

	//bufferData(buf);
	bufferSubData(buf);

	draw(program, buf);
}
void			neb::gfx::mesh::instanced::draw(
		std::shared_ptr<neb::gfx::glsl::program::threed>	program,
		std::shared_ptr<neb::gfx::glsl::buffer::instanced>	buf)
{

	auto buf_mesh = mesh_.buffers_[program.get()];
	assert(buf_mesh);

	buf->vertexAttribPointer();
	buf_mesh->vertexAttribPointer();

	LOG(lg, neb::gfx::sl, debug) << "instances size = " << instances_->size();
	LOG(lg, neb::gfx::sl, debug) << "mesh size      = " << mesh_.indices_.size();

	buf_mesh->bind();

	glDrawElementsInstanced(GL_TRIANGLES, mesh_.indices_.size(), GL_UNSIGNED_SHORT, 0, instances_->size());

	checkerror("glDrawElementsInstanced");

	buf_mesh->unbind();
}

