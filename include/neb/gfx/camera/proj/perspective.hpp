#ifndef __GLUTPP_CAMERA_PROJECTION_PERSPECTIVE_HPP
#define __GLUTPP_CAMERA_PROJECTION_PERSPECTIVE_HPP

#include <neb/gfx/camera/proj/base.hpp>

namespace neb { namespace gfx {namespace camera { namespace proj {
	class Perspective:
		virtual public neb::gfx::camera::proj::Base
	{
		public:
			Perspective();
			virtual glm::mat4&			proj();
			virtual void				calculate();
			/** @brief step */
			void					step(gal::etc::timestep const & ts);

			//
			void					set(float,float,float);
		private:
			/** @brief field of view angle */
			float					fovy_;
			/** @brief near clipping plane */
			float					zn_;
			/** @brief far clipping plane */
			float					zf_;

	};
}}}}

#endif

