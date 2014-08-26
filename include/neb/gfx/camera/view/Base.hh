#ifndef __GLUTPP_CAMERA_H__
#define __GLUTPP_CAMERA_H__

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include <gal/etc/timestep.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/itf/shared.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/camera/view/util/flag.hpp>

namespace neb {namespace gfx {namespace camera {namespace view {

	/** @brief @Base */
	class base: virtual public neb::itf::shared {
		public:
			/** @brief Constructor */
			base(std::shared_ptr< ::neb::gfx::environ::base > parent);
			/** @brief Load view matrix into GLSL. */
			void						load(std::shared_ptr<neb::gfx::glsl::program::base> p);
			/** @brief Get view matrix. */
			virtual glm::mat4				view() = 0;
			/** @brief Step
			 *
			 * @todo explain when in timeline this occurs and in which thread and why
			 */
			virtual void					step(gal::etc::timestep const & ts) = 0;

			virtual void					connect(
					std::shared_ptr<neb::gfx::window::base> const & window) {}

		public:
			std::shared_ptr< ::neb::gfx::environ::base >		parent_;

			neb::gfx::camera::view::util::flag			flag_;
	};
}}}}

#endif


