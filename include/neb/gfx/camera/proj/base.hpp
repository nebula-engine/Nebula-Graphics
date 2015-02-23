#ifndef GLUTPP_CAMERA_PROJECTION_BASE_HPP
#define GLUTPP_CAMERA_PROJECTION_BASE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <gal/etc/timestep.hpp>

#include <neb/fnd/glsl/program/util/decl.hpp>

#include <neb/gfx/tmp/Child.hpp>
#include <neb/gfx/camera/proj/util/cast.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


namespace neb { namespace gfx { namespace camera { namespace proj {
	/** @brief @Base */
	class Base:
		virtual public neb::gfx::tmp::Child<neb::gfx::environ::base>,
		virtual public neb::gfx::camera::proj::util::cast
	{
		public:
			typedef typename gal::stl::child<neb::gfx::environ::base>::parent_t parent_t;
			/** @brief Constructor */
			Base();
			/***/
			virtual void					init(parent_t * const &) = 0;
			/***/
			virtual glm::mat4&				proj() = 0;
			virtual void					calculate() = 0;
			virtual void					calculate_geometry() = 0;
			void						load(neb::fnd::glsl::program::Base const * const p);
			/** @brief step
			 * @todo explain when in timeline this occurs and in which thread and why
			 */
			void						step(gal::etc::timestep const & ts);
		protected:
			// persistence
			glm::mat4					_M_matrix;
	};
}}}}


#endif


