#include <gal/log/log.hpp>

#include <neb/app/__gfx_glsl.hpp>
#include <neb/timer/Actor/Base.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/debug.hh>


neb::Timer::actor::base::base(sp::shared_ptr<neb::core::actor::base> actor, double seconds):
	timer_(neb::app::__gfx_glsl::global()->ios_, boost::posix_time::seconds(seconds)),
	actor_(actor)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;

	assert(!neb::app::__gfx_glsl::global()->ios_.stopped());
	
	// cannot do this: shared_from_this shouldnt be used in ctor??
	
	//timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));

}
neb::Timer::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;
	
}
void		neb::Timer::actor::base::activate() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb timer", debug) << __PRETTY_FUNCTION__;
	
	timer_.async_wait(boost::bind(&neb::Timer::actor::base::doSomething, shared_from_this()));
	
}



