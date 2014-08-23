#ifndef __GLUTPP_MESH_H__
#define __GLUTPP_MESH_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

//#include <galaxy/flag.hpp>

/*
#include <math/vec4.hpp>
#include <math/vec3.hpp>
#include <math/vec2.hpp>
#include <math/transform.hpp>
#include <math/geo/polyhedron.hpp>
*/

#include <neb/core/pose.hpp>
#include <neb/core/math/geo/decl.hpp>

#include <neb/gfx/material.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/buffer/mesh.hpp>
#include <neb/gfx/Context/Util/decl.hpp>

namespace neb { namespace gfx {
	class mesh {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::buffer::mesh>			buffer_shared;
			typedef std::map<neb::gfx::glsl::program::threed*, buffer_shared>	buffer_map;

			mesh();
			~mesh();

			void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);

			void				construct(math::geo::polyhedron*);
			void				print(int sl);

			void				buffer_data(
					std::shared_ptr<neb::gfx::glsl::buffer::mesh> buf);

			void				init_buffer(
					std::shared_ptr<neb::gfx::glsl::program::threed> p);

			void				draw_elements(
					std::shared_ptr<neb::gfx::glsl::program::threed> program,
					neb::core::pose const & pose,
					glm::vec3 scale);
			void				draw_elements(
					std::shared_ptr<neb::gfx::glsl::program::threed> program,
					std::shared_ptr<neb::gfx::glsl::buffer::mesh> buffer,
					neb::core::pose const & pose,
					glm::vec3 scale);

			neb::material::material			material_front_;

			/** @todo boost wont let me use shared ptr here! */
			std::vector<math::geo::vertex>		vertices_;
			std::vector<GLushort>			indices_;

			buffer_map				buffers_;


			std::shared_ptr<neb::gfx::texture>		texture_;
			std::shared_ptr<neb::gfx::texture>		normal_map_;
	};
}}

#endif


