#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <neb/core/core/actor/util/decl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/Camera/View/Base.hh>
//#include <neb/config.hh>

namespace neb {
	namespace gfx {
		namespace Camera {
			namespace view {
				class Ridealong: public neb::gfx::camera::view::base {
					public:
						Ridealong(std::shared_ptr<neb::gfx::environ::base>, weak_ptr<neb::core::core::actor::base> actor);
						virtual mat4				view();
						virtual void				step(gal::etc::timestep const & ts);
						weak_ptr<neb::core::core::actor::base>	actor_;
				};
			}
		}
	}
}


#endif


