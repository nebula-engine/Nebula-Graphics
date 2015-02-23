#ifndef __GLUTPP_CAMERA_MANUAL_
#define __GLUTPP_CAMERA_MANUAL

#include <vector>

#include <neb/gfx/camera/view/Base.hpp>

namespace neb { namespace gfx { namespace camera { namespace view {

	/** @brief free flying camera
	 * this camera can move freely through the scene
	 * user input in interpreted as three-component velocity and yaw and pitch rate
	 */
	class manual:
		virtual public neb::gfx::camera::view::Base
	{
		public:
			manual();
			virtual glm::mat4			view();
			virtual void				step(gal::etc::timestep const & ts);
			void					init(parent_t * const & p);
			glm::vec3				eye_;
			glm::vec3				center_;
			glm::vec3				up_;
	};

}}}}

#endif


