#ifndef __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__
#define __NEBULA_CONTROL_RIGID_BODY_CONTROL_H__

#include <Nebula/Actor/Rigid_Actor.hh>
#include <Nebula/config.hh>

namespace Neb {
	namespace Actor {
		namespace Control {
			namespace RigidBody {
				/** @brief Rigid Body
				 * An object (what did I mean by 'object' here, an actor?) makes no distinction between local and remote.
				 * In a remote scene, the actor will send a control update message.
				 * In a local scene, the actor will call upon stored values; it makes no difference to the
				 * actor whether these value were set by calls to key_fun or by a control update message.
				 * This creates requirements for how control works. All infomation needed to determine 
				 * force and torque at a given point in time must be stored in raw.
				 **/
				class Base {
					public:
						Base();

						virtual int			key_fun(int,int,int,int);

						void				step_local(double);
						void				step_local0(double);
						void				step_local1(double);


						physx::PxVec3			f();
						physx::PxVec3			t();

						void				print();
					private:

					public:
						Neb::Actor::Base_w		actor_;

						physx::PxQuat			q_target_;
						physx::PxVec3			p_target_;

						physx::PxVec3			f_;
						physx::PxVec3			t_;

						physx::PxVec3			force_;
						physx::PxVec3			torque_;

		
						struct
						{
							boost::signals2::connection	key_fun_;
						} conn_;

						//gal::control::control		pid_;

				};
			}
		}
	}
}
#endif








