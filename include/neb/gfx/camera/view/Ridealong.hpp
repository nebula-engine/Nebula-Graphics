#ifndef __NEB_CAMERA_RIDEALONG_H__
#define __NEB_CAMERA_RIDEALONG_H__

#include <memory>
#include <map>

#include <neb/fnd/core/actor/util/decl.hpp>
#include <neb/fnd/camera/view/Ridealong.hpp>

#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/camera/view/Base.hpp>
//#include <neb/config.hh>

namespace neb { namespace gfx { namespace camera { namespace view {
	class Ridealong:
		//virtual public neb::fnd::camera::view::Ridealong,
		virtual public neb::gfx::camera::view::Base
	{
		public:
			Ridealong();
			virtual glm::mat4				view();
			virtual void					step(gal::etc::timestep const & ts);
	};
}}}}


#endif


