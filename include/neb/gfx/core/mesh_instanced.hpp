#ifndef NEB_GFX_MESH_INSTANCED_HPP
#define NEB_GFX_MESH_INSTANCED_HPP

#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_continuous.hpp>

namespace neb { namespace gfx {
	class mesh_instanced {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>			buffer_shared;
			typedef std::map<neb::gfx::glsl::program::threed*, buffer_shared>		buffer_map;

			typedef neb::gfx::array_continuous<glm::mat4, float, float, glm::vec4>		instances_type;
			typedef instances_type::slot							slot_type;
		public:
			void							init(
					std::shared_ptr<neb::gfx::glsl::program::threed> program);
			void							draw(
					std::shared_ptr<neb::gfx::glsl::program::threed> program);
			void							draw(
					std::shared_ptr<neb::gfx::glsl::program::threed>	program,
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
			void			bufferData(
					std::shared_ptr<neb::gfx::glsl::buffer::mesh_instanced>	buf);
		public:
			neb::gfx::mesh						mesh_;


			buffer_map						buffers_;

			std::shared_ptr<instances_type>				instances_;
	};
}}

#endif

