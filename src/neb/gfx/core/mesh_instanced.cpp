
#include <neb/gfx/core/mesh_instanced.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/free.hpp>

void			neb::gfx::mesh_instanced::init(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	mesh_.init_buffer(program);



	auto buf(std::make_shared<neb::gfx::glsl::buffer::mesh_instanced>());
	buffers_[program.get()] = buf;
	
	buf->init(program);
	
	bufferData(buf);

}

void			neb::gfx::mesh_instanced::bufferData(
		std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf)
{
	checkerror("unknown");

	/*
	   std::cout << "size array = " << instances_->size_array() << std::endl;
	   std::cout << "size =       " << instances_->size() << std::endl;
	   std::cout << "data:" << std::endl;
	   for(GLsizei i = 0; i < instances_->size(); i++) {
	   std::cout << data[i] << std::endl;
	   std::cout << "image      = " << data_image[i] << std::endl;
	   std::cout << "normal_map = " << data_normal_map[i] << std::endl;
	   }
	   */

	auto size = instances_->size();
	//auto size_array = instances_->size_array();

	void* data[] = {
		instances_->get<0, glm::mat4>(),
		instances_->get<1, GLfloat>(),
		instances_->get<2, GLfloat>(),
		instances_->get<3, glm::vec4>()
	};
	unsigned int datasize[] = {
		sizeof(glm::mat4),
		sizeof(GLfloat),
		sizeof(GLfloat),
		sizeof(glm::vec4)
	};
	GLuint buffer[] = {
		buf->model_,
		buf->image_sampler_,
		buf->normal_map_sampler_,
		buf->diffuse_
	};

	/*
	for(unsigned int c = 0; c < 3; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		glBufferData(
				GL_ARRAY_BUFFER,
				size_array * datasize[c],
				NULL,
				GL_STREAM_DRAW);
		glBufferSubData(
				GL_ARRAY_BUFFER,
				0,
				size * datasize[c],
				data[c]);
		checkerror("glBufferSubData");
	}
	*/
	for(unsigned int c = 0; c < 4; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		glBufferData(
				GL_ARRAY_BUFFER,
				size * datasize[c],
				data[c],
				GL_STREAM_DRAW);
		checkerror("glBufferSubData");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}	
void			neb::gfx::mesh_instanced::draw(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	if(!buffers_[program.get()])
	{	
		init(program);
	}
	auto buf = buffers_[program.get()];

	if(!buf) return;


	instances_->update_slots();

	bufferData(buf);

	draw(program, buf);
}
void			neb::gfx::mesh_instanced::draw(
		std::shared_ptr<neb::gfx::glsl::program::threed>	program,
		std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf)
{

	auto buf_mesh = mesh_.buffers_[program.get()];
	assert(buf_mesh);

	if(0) {
		mesh_.buffer_data(buf_mesh);
		bufferData(buf);
	}
	if(0) {
		buf->enableAttribs(program);
		buf_mesh->enableAttribs(program);
	}

	buf->vertexAttribPointer(program);
	buf_mesh->vertexAttribPointer(program);

	if(0) {
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::POSITION)->o_,				0);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::NORMAL)->o_,				0);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,				0);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::TANGENT)->o_,				0);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::BINORMAL)->o_,				0);
	}
	if(0) {
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL0)->o_,			1);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL1)->o_,			1);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL2)->o_,			1);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL3)->o_,			1);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_IMAGE_SAMPLER)->o_,		1);
		glVertexAttribDivisor(program->get_attrib(neb::attrib_name::e::INSTANCE_NORMAL_MAP_SAMPLER)->o_,	1);
	}

	std::cout << "instances size = " << instances_->size() << std::endl;
	std::cout << "mesh size      = " << mesh_.indices_.size() << std::endl;

	buf_mesh->bind();

	glDrawElementsInstanced(GL_TRIANGLES, mesh_.indices_.size(), GL_UNSIGNED_SHORT, 0, instances_->size());
	checkerror("glDrawElementsInstanced");

	buf_mesh->unbind();
}

