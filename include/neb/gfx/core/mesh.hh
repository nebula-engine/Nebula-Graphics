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

#include <neb/core/math/geo/decl.hpp>

#include <neb/gfx/material.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/core/buffer.hpp>
#include <neb/gfx/Context/Util/decl.hpp>

namespace neb { namespace gfx {
	class mesh {
		public:
			typedef map< neb::gfx::context::base*, shared_ptr<neb::gfx::core::buffer> >			map_t;

			mesh();
			~mesh();

			void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version);
			void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version);

			void				construct(math::geo::polyhedron*);
			void				print(int sl);

			void				init_buffer(
					shared_ptr<neb::gfx::context::base> context,
					shared_ptr<neb::glsl::program> p);
			void				draw_elements(
					sp::shared_ptr<neb::gfx::context::base> context,
					sp::shared_ptr<neb::glsl::program> p,
					neb::core::pose const & pose,
					glm::vec3 scale);


			neb::material::material			material_front_;

			/** @todo boost wont let me use shared ptr here! */
			vector<math::geo::vertex>		vertices_;
			vector<GLushort>			indices_;

			map_t					context_;
	};
}}

#endif


