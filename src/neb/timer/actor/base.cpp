#include <gal/log/log.hpp>

#include <neb/timer/Actor/Base.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/core/debug.hh>
#include <neb/core/util/log.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>


neb::Timer::actor::base::base(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	timer_(neb::app::__gfx_glsl::global().lock()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	if(DEBUG_NEB) LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;

	assert(!neb::app::__gfx_glsl::global().lock()->ios_.stopped());
	
	// cannot do this: shared_from_this shouldnt be used in ctor??
	
	//timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));

}
neb::Timer::actor::base::~base() {
	if(DEBUG_NEB) LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
	
}
void		neb::Timer::actor::base::activate() {
	if(DEBUG_NEB) LOG(lg, neb::core::sl, debug) << __PRETTY_FUNCTION__;
	
	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));
	
}



