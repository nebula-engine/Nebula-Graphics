
#include <nebula/physics.hpp>
#include <nebula/simulation_callback.hpp>

void 	neb::simulation_callback::onConstraintBreak(
		physx::PxConstraintInfo *constraints, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void	neb::simulation_callback::onContact(
		const physx::PxContactPairHeader & pairHeader,
		const physx::PxContactPair *pairs,
		physx::PxU32 nbPairs) {
	
	printf("%s\n", __PRETTY_FUNCTION__);
	
	physx::PxActor* pxactor0 = pairHeader.actors[0];
	physx::PxActor* pxactor1 = pairHeader.actors[1];
	
	/* cast the userdata to a plain old pointer
	 * then call @c isActor to get the shared opinter
	 * doing so keeps the actors alive long enough to return from the call to @c hit
	 * allows the scene to release the actors safely during the call to @c hit
	 */
	neb::Actor::Actor* actor0 = reinterpret_cast<neb::Actor::Actor*>(pxactor0->userData)->isActor();
	neb::Actor::Actor* actor1 = reinterpret_cast<neb::Actor::Actor*>(pxactor1->userData)->isActor();
	
	for(physx::PxU32 i=0; i < nbPairs; i++)
	{
		const physx::PxContactPair& cp = pairs[i];
		
		if(cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			actor0->hit();
			actor1->hit();
		}
	}
}
void 	neb::simulation_callback::onWake(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::simulation_callback::onSleep(physx::PxActor **actors, physx::PxU32 count) {
	printf("%s\n", __PRETTY_FUNCTION__);
}
void 	neb::simulation_callback::onTrigger(physx::PxTriggerPair *pairs, physx::PxU32 count)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

