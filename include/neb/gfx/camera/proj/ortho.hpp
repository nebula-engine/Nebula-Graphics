#ifndef __GLUTPP_CAMERA_PROJECTION_ORTHO_H__
#define __GLUTPP_CAMERA_PROJECTION_ORTHO_H__

#include <vector>
#include <memory>

#include <neb/gfx/camera/proj/base.hpp>

namespace neb {namespace gfx {namespace camera {namespace proj {
	/** @brief @Base */
	class Ortho:
		virtual public neb::gfx::camera::proj::Base
	{
		public:
			Ortho();

			virtual glm::mat4&			proj();
			virtual void				calculate();

			virtual void				step(gal::etc::timestep const & ts);
			void					set(float,float,float,float,float,float);
		protected:
			float					left_;
			float					right_;
			float					bottom_;
			float					top_;
			float					near_;
			float					far_;

	};

}}}}

#endif


