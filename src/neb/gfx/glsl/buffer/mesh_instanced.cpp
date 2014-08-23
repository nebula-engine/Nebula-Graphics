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

	glGenBuffers(3, buffer_array_);
	checkerror("glGenBuffers");

	// Initialize with empty (NULL) buffer; it will be updated later, each frame.

	GLsizei datasize[] = {
		sizeof(glm::mat4),
		sizeof(GLfloat),
		sizeof(GLfloat)
	};
	
	for(unsigned int c = 0; c < 3; c++) {
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


	GLuint attrib_model =		program->get_attrib(neb::attrib_name::e::INSTANCE_MODEL0)->o_;
	GLuint attrib_image =		program->get_attrib(neb::attrib_name::e::INSTANCE_IMAGE_SAMPLER)->o_;
	GLuint attrib_normal_map =	program->get_attrib(neb::attrib_name::e::INSTANCE_NORMAL_MAP_SAMPLER)->o_;


	checkerror("unknown");

	glm::mat4 m;
	void* offset[] = {
		(void*)((long)&m[0] - (long)&m),
		(void*)((long)&m[1] - (long)&m),
		(void*)((long)&m[2] - (long)&m),
		(void*)((long)&m[3] - (long)&m)
	};


	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "sizeof(glm::mat4)" << std::setw(8) << sizeof(glm::mat4);
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "offset[0]" << std::setw(8) << offset[0];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "offset[1]" << std::setw(8) << offset[1];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "offset[2]" << std::setw(8) << offset[2];
	LOG(lg, neb::gfx::sl, info) << std::setw(32) << "offset[3]" << std::setw(8) << offset[3];

	GLsizei stride = sizeof(glm::mat4);

	glBindBuffer(GL_ARRAY_BUFFER, model_);
	for(unsigned int i = 0; i < 4; i++) {
		glEnableVertexAttribArray(attrib_model + i);
		glVertexAttribPointer(
				attrib_model + i,
				4,
				GL_FLOAT, // type
				GL_FALSE, // normalized?
				stride, // stride
				offset[i] // array buffer offset
				);
		checkerror("glVertexAttribPointer model");
		glVertexAttribDivisor(attrib_model + i, 1);
	}

	GLuint buffer[] = {
		image_sampler_,
		normal_map_sampler_
	};
	GLuint attrib[] = {
		attrib_image,
		attrib_normal_map
	};

	for(unsigned int c = 0; c < 2; c++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[c]);
		glEnableVertexAttribArray(attrib[c]);
		glVertexAttribPointer(
				attrib[c],
				1,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
				);
		checkerror("glVertexAttribPointer image");
		glVertexAttribDivisor(attrib[c], 1);
	}

}


