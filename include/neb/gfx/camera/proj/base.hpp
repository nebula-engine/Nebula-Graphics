#ifndef GLUTPP_CAMERA_PROJECTION_BASE_HPP
#define GLUTPP_CAMERA_PROJECTION_BASE_HPP

#include <vector>
#include <memory>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {namespace gfx {namespace camera {namespace projection {
	/** @brief @Base */
	class base {
		public:
			/** @brief Constructor */
			base(std::shared_ptr<neb::gfx::environ::base>);

			virtual glm::mat4				proj() = 0;
			void						load(std::shared_ptr<neb::gfx::glsl::program::base> p);
			/** @brief step
			 * @todo explain when in timeline this occurs and in which thread and why
			 */
			void						step(gal::etc::timestep const & ts);
		protected:
			/** @brief Parent */
			std::weak_ptr<neb::gfx::environ::base>		parent_;
	};
}}}}


#endif


