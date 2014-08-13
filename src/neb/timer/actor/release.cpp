#include <gal/log/log.hpp>

#include <neb/timer/Actor/Release.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/core/debug.hh>
#include <neb/core/util/log.hpp>


neb::Timer::actor::Release::Release(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	neb::Timer::actor::base::base(actor, seconds)
{
	if(DEBUG_NEB) LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

}
void		neb::Timer::actor::Release::doSomething() {
	
	if(DEBUG_NEB) LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
	
	auto actor(actor_.lock());
	
	// actor was released after timer start
	if(!actor) return;
	
	auto parent = actor->parent_.lock();
	assert(parent);
	
	parent->erase(actor->i_);
	
}



