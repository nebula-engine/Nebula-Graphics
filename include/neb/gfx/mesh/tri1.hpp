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

#include <neb/core/math/pose.hpp>
#include <neb/core/math/geo/decl.hpp>

#include <neb/gfx/material.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/buffer/tri1.hpp>
#include <neb/gfx/context/util/decl.hpp>
#include <neb/gfx/mesh/base.hpp>

namespace ba = boost::archive;

namespace neb { namespace gfx { namespace mesh {

	class tri1: public elements<neb::gfx::glsl::buffer::elements<GLushort>, neb::gfx::glsl::buffer::tri1>
	{
		public:
			//typedef std::map<neb::gfx::glsl::program::base*, buffer*>	program_buffer_map;

			typedef neb::gfx::glsl::buffer::tri1				buffer;
			typedef neb::gfx::glsl::program::base				program;
			typedef elements<neb::gfx::glsl::buffer::elements<GLushort>, neb::gfx::glsl::buffer::tri1>	base_t;
		
			// DO NOT CHANGE! coded in phx heightfield
			typedef GLushort index_type;

			tri1();
			~tri1();

			virtual GLsizeiptr*		begin();
			virtual GLsizeiptr*		end();
			virtual GLvoid** const		data();
			GLsizeiptr*			size_array();
			GLsizeiptr*			size();

			void				serialize(
					ba::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(
					ba::polymorphic_oarchive & ar, unsigned int const & version);

			void				construct(nc::math::geo::polyhedron*);
			void				print(int sl);

			/*		
					void				init_buffer(
					program* p);
					void				draw_elements(
					program* p,
					buffer_shared,
					neb::core::math::pose const & pose,
					glm::vec3 scale);
			 */
			/**
			 * do specific things like custom uniforms, then call mesh::base::drawElements
			 */
			void				drawDebug(
					program const * const & p,
					neb::core::math::pose const & pose,
					glm::vec3 scale);
			void				drawElements(
					program const * const & p,
					neb::core::math::pose const & pose,
					glm::vec3 scale);


			ng::material::material			material_front_;
			
			void					setVerts(std::vector<nc::math::geo::vertex> const &);
			void					setIndices(std::vector<index_type> const &);
			
			GLuint					getNbVerts();
			GLuint					getNbIndices();
		private:
			std::vector<nc::math::geo::vertex>	vertices_;
			std::vector<index_type>			indices_;
		public:
			std::shared_ptr<neb::gfx::texture>	texture_;
			std::shared_ptr<neb::gfx::texture>	normal_map_;
	};
}}}

#endif


