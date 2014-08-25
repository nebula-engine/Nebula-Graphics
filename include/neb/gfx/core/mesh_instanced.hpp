#ifndef NEB_GFX_MESH_INSTANCED_HPP
#define NEB_GFX_MESH_INSTANCED_HPP

#include <neb/gfx/core/mesh_base.hpp>
#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_continuous.hpp>
#include <neb/gfx/glsl/buffer/mesh_instanced.hpp>


namespace neb { namespace gfx { namespace mesh {
	class instanced: public neb::gfx::mesh::base<neb::gfx::glsl::buffer::instanced> {
		public:
			typedef neb::gfx::glsl::program::threed			program_type;
			typedef std::shared_ptr<program_type>			program_shared;
			typedef neb::gfx::glsl::buffer::instanced		buffer_type;
			typedef std::shared_ptr<buffer_type>			buffer_shared;
			typedef std::map<program_type*, buffer_shared>		buffer_map;

			typedef neb::gfx::array_continuous<
				glm::mat4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				glm::vec4,
				float
				>		instances_type;
			typedef instances_type::slot				slot_type;



		public:
			void							init(program_shared);
			virtual GLsizeiptr*					begin();
			virtual GLsizeiptr*					end();
			virtual GLsizeiptr*					size();
			virtual GLvoid**					data();

			void							draw(program_shared);
			void							draw(program_shared, buffer_shared);
		public:
			neb::gfx::mesh::tri1					mesh_;
			
			GLvoid**						data_;

			buffer_map						buffers_;

			std::shared_ptr<instances_type>				instances_;
	};
}}}

#endif

