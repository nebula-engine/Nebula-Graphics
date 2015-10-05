#ifndef __GLUTPP_CAMERA_CONROL_H__
#define __GLUTPP_CAMERA_CONROL_H__

#include <vector>

#include <neb/fnd/input/sink.hpp>

#include <neb/gfx/camera/view/Base.hpp>

namespace neb { namespace gfx { namespace camera { namespace view {
	/** @brief free flying camera
	 * this camera can move freely through the scene
	 * user input in interpreted as three-component velocity and yaw and pitch rate
	 */
	class Free:
		virtual public neb::fnd::input::sink,
		virtual public neb::gfx::camera::view::Base
	{
		public:
			Free();
			virtual glm::mat4				view();
			virtual void					step(gal::etc::timestep const & ts);
			void						init(parent_t * const & p);
			virtual void					connect(
					std::shared_ptr<neb::fnd::input::source> const &);
			virtual int					keyFun(
					std::shared_ptr<neb::fnd::input::source> const &,
					int key,
					int scancode,
					int action,
					int mods);
			glm::vec3				move();
			/**
			 * orientation state
			 */
			float					pitch_;
			float					yaw_;
			glm::vec4				eye_;
			glm::vec3				center_;
			glm::vec3				look_;
			glm::vec3				up_;
			/**
			 * key values connected to each direction
			 */
			int					key_n_;
			int					key_s_;
			int					key_e_;
			int					key_w_;
			int					key_u_;
			int					key_d_;
			/**
			 * key values connected to orientation changes
			 */
			int					key_yaw_pos_;
			int					key_yaw_neg_;
			int					key_pitch_pos_;
			int					key_pitch_neg_;
			std::map<int,unsigned int>		key_flag_;
			std::map<int,glm::vec3>			head_;
			std::map<unsigned int,int>		head_flag_;
	};

}}}}

#endif

