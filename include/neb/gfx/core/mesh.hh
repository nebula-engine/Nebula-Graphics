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
#include <neb/gfx/core/mesh_base.hpp>

namespace ba = boost::archive;

namespace neb { namespace gfx { namespace mesh {
	class tri1: public base<neb::gfx::glsl::buffer::tri1> {
		public:
			typedef std::shared_ptr<neb::gfx::glsl::buffer::tri1>			buffer_shared;
			typedef std::map<neb::gfx::glsl::program::threed*, buffer_shared>	buffer_map;
			typedef std::shared_ptr<neb::gfx::glsl::program::threed>		program_shared;

			tri1();
			~tri1();

			virtual GLsizeiptr*		begin() {
				begin_[0] = 0;
				begin_[1] = 0;
				return begin_;
			}
			virtual GLsizeiptr*		end() {
				begin_[0] = vertices_.size();
				begin_[1] = indices_.size();
				return begin_;
			}
			virtual GLvoid** const		data() {
				data_[0] = &vertices_[0];
				data_[1] = &indices_[0];
				return data_;
			}
			GLsizeiptr*			size_array() {
				return size();
			}
			GLsizeiptr*			size() {
				assert(!vertices_.empty());
				assert(!indices_.empty());
				
				size_[0] = vertices_.size();
				size_[1] = indices_.size();
				return size_;
			}

			void				serialize(
					ba::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(
					ba::polymorphic_oarchive & ar, unsigned int const & version);

			void				construct(math::geo::polyhedron*);
			void				print(int sl);

			void				init_buffer(program_shared p);
			void				draw_elements(
					program_shared,
					neb::core::pose const & pose,
					glm::vec3 scale);
			void				draw_elements(
					program_shared,
					buffer_shared,
					neb::core::pose const & pose,
					glm::vec3 scale);

			neb::material::material			material_front_;

			/** @todo boost wont let me use shared ptr here! */
			std::vector<math::geo::vertex>			vertices_;
			std::vector<GLushort>				indices_;

			buffer_map					buffers_;


			std::shared_ptr<neb::gfx::texture>		texture_;
			std::shared_ptr<neb::gfx::texture>		normal_map_;
	};
}}}

#endif


