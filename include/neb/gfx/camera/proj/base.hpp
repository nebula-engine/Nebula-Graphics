#ifndef GLUTPP_CAMERA_PROJECTION_BASE_HPP
#define GLUTPP_CAMERA_PROJECTION_BASE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <gal/etc/timestep.hpp>
#include <gal/stl/verbosity.hpp>

#include <neb/fnd/glsl/program/util/decl.hpp>

#include <neb/fnd/plug/gfx/camera/proj/Base.hpp>

#include <neb/gfx/tmp/Child.hpp>
#include <neb/gfx/camera/proj/util/cast.hpp>
#include <neb/gfx/environ/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


namespace neb { namespace gfx { namespace camera { namespace proj {
	/** @brief @Base */
	class Base:
		public gal::tmp::Verbosity<neb::gfx::camera::proj::Base>,
		virtual public neb::fnd::plug::gfx::camera::proj::Base,
		virtual public neb::gfx::camera::proj::util::cast
	{
		public:
			using gal::tmp::Verbosity<neb::gfx::camera::proj::Base>::printv;
			/** @brief Constructor */
			Base();
			/***/
			virtual void					init(parent_t * const &) = 0;
			virtual void					calculate_geometry() = 0;
			/***/
			virtual glm::mat4				proj() = 0;
			virtual void					calculate() = 0;
			void						load(neb::fnd::glsl::program::Base * const & p);
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


