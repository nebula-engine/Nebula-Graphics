#include <iomanip>

#include <gal/log/log.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>

void			neb::gfx::glsl::buffer::mesh_instanced::init(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	GLsizei size = 32;

	checkerror("unknown");

	glGenBuffers(4, buffer_array_);
	checkerror("glGenBuffers");

	// Initialize with empty (NULL) buffer; it will be updated later, each frame.

	GLsizei datasize[] = {
		sizeof(glm::mat4),
		sizeof(GLfloat),
		sizeof(GLfloat),
		sizeof(glm::vec4)
	};
	
	for(unsigned int c = 0; c < 4; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer_array_[c]);
		glBufferData(
				GL_ARRAY_BUFFER,
				size * datasize[c],
				NULL,
				GL_STREAM_DRAW);
		checkerror("glBufferData");
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//vertexAttribPointer(program);

}
void			neb::gfx::glsl::buffer::mesh_instanced::enableAttribs(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{
	program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL0)->enable();
	program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL1)->enable();
	program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL2)->enable();
	program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL3)->enable();
	program->get_attrib(neb::attrib_name::e::INSTANCE_IMAGE_SAMPLER)->enable();
	program->get_attrib(neb::attrib_name::e::INSTANCE_NORMAL_MAP_SAMPLER)->enable();
}
void			neb::gfx::glsl::buffer::mesh_instanced::vertexAttribPointer(
		std::shared_ptr<neb::gfx::glsl::program::threed> program)
{	


	checkerror("unknown");

	glm::mat4 m;
	void* pointer[] = {
		(void*)((long)&m[0] - (long)&m),
		(void*)((long)&m[1] - (long)&m),
		(void*)((long)&m[2] - (long)&m),
		(void*)((long)&m[3] - (long)&m),
		(void*)0,
		(void*)0,
		(void*)0
	};

	GLint index[] = {
		program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL0)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL1)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL2)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL3)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_IMAGE_SAMPLER)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_NORMAL_MAP_SAMPLER)->o_,
		program->get_attrib(neb::attrib_name::e::INSTANCE_DIFFUSE)->o_
	};

	GLint size[] = {
		4,4,4,4,1,1,4
	};

	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "sizeof(glm::mat4)" << std::setw(8) << sizeof(glm::mat4);
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "pointer[0]" << std::setw(8) << pointer[0];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "pointer[1]" << std::setw(8) << pointer[1];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "pointer[2]" << std::setw(8) << pointer[2];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "pointer[3]" << std::setw(8) << pointer[3];

	GLsizei stride[] = {
		sizeof(glm::mat4),
		sizeof(glm::mat4),
		sizeof(glm::mat4),
		sizeof(glm::mat4),
		0,
		0,
		0
	};

	GLuint buffer[] = {
		model_,
		model_,
		model_,
		model_,
		image_sampler_,
		normal_map_sampler_,
		diffuse_
	};

	for(unsigned int c = 0; c < 7; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		checkerror("glBindBuffer");
		glEnableVertexAttribArray(index[c]);
		checkerror("glEnableVertexAttribArray");
		glVertexAttribPointer(
				index[c],
				size[c],
				GL_FLOAT,
				GL_FALSE,
				stride[c],
				pointer[c]
				);
		checkerror("glVertexAttribPointer");
		glVertexAttribDivisor(index[c], 1);
		checkerror("glVertexAttribDivisor");
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


