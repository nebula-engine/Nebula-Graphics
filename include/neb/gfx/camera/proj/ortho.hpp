#ifndef __GLUTPP_CAMERA_PROJECTION_ORTHO_H__
#define __GLUTPP_CAMERA_PROJECTION_ORTHO_H__

#include <vector>
#include <memory>

//#include <neb/config.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
//#include <neb/camera_control.hpp>

namespace neb {
	namespace gfx {
		namespace camera {
			namespace proj {
				/** @brief @Base */
				class ortho: virtual public base {
					public:
						Perspective(std::shared_ptr<neb::gfx::environ::base>);
						//void		init(neb::renderable_shared);
						virtual glm::mat4				proj();

						/** @brief step */
						void					step(gal::etc::timestep const & ts);

						//

						float					left_;
						float					right_;
						float					bottom_;
						float					top_;

				};
			}
		}
	}
}

#endif


