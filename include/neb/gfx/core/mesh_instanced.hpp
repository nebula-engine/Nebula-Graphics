#ifndef NEB_GFX_MESH_INSTANCED_HPP
#define NEB_GFX_MESH_INSTANCED_HPP

#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_continuous.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>

namespace neb { namespace gfx {
	class mesh_instanced {
		public:
			typedef neb::gfx::glsl::buffer::mesh_instanced					buffer_type;
			typedef std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>			buffer_shared;
			typedef std::map<neb::gfx::glsl::program::threed*, buffer_shared>		buffer_map;

			typedef neb::gfx::array_continuous<
				glm::mat4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				float
				>		instances_type;
			typedef instances_type::slot							slot_type;

			enum {
				BUFFER_COUNT = buffer_type::BUFFER_COUNT
			};

			const unsigned int datasize[BUFFER_COUNT] = {
				sizeof(glm::mat4),	// model amtrix
				sizeof(glm::vec4),	// texture layers
				sizeof(glm::vec4),	// diffuse
				sizeof(glm::vec4),	// ambient
				sizeof(glm::vec4),	// specular
				sizeof(glm::vec4),	// emission
				sizeof(GLfloat),	// shininess
			};

		public:
			void							init(
					std::shared_ptr<neb::gfx::glsl::program::threed> program);
			void							draw(
					std::shared_ptr<neb::gfx::glsl::program::threed> program);
			void							draw(
					std::shared_ptr<neb::gfx::glsl::program::threed>	program,
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
			void							bufferData(
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
			void							bufferDataNull(
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
			void							bufferSubData(
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
		public:
			neb::gfx::mesh						mesh_;


			buffer_map						buffers_;

			std::shared_ptr<instances_type>				instances_;
	};
}}

#endif

