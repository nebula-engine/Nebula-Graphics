#ifndef __GLUTPP_CAMERA_PROJECTION_H__
#define __GLUTPP_CAMERA_PROJECTION_H__

#include <vector>
#include <memory>

//#include <neb/config.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
//#include <neb/camera_control.hpp>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace Projection {
				/** @brief @Base */
				class base {
					public:
						/** @brief Constructor */
						base(std::shared_ptr<neb::gfx::environ::base>);

						virtual glm::mat4				proj() = 0;
						void					load(std::shared_ptr<neb::gfx::glsl::program::base> p);
						/** @brief step
						 * @todo explain when in timeline this occurs and in which thread and why
						 */
						void					step(gal::etc::timestep const & ts);
					protected:
						/** @brief Parent */
						std::shared_ptr<neb::gfx::environ::base>		parent_;
				};
				class Perspective: virtual public base {
					public:
						Perspective(std::shared_ptr<neb::gfx::environ::base>);
						//void		init(neb::renderable_shared);
						virtual glm::mat4				proj();

						/** @brief step */
						void					step(gal::etc::timestep const & ts);

						//

						/** @brief field of view angle */
						float					fovy_;
						/** @brief near clipping plane */
						float					zn_;
						/** @brief far clipping plane */
						float					zf_;

				};
			}
		}
	}
}
#endif
