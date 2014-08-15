
#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/Camera/View/Free.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>
#include <neb/gfx/util/log.hpp>


neb::gfx::context::base::base() {
}
neb::gfx::context::base::base(sp::shared_ptr<neb::gfx::context::util::parent> parent): parent_(parent) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
neb::gfx::context::base&		neb::gfx::context::base::operator=(neb::gfx::context::base const & r){
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	return *this;
}
void		neb::gfx::context::base::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::release() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::resize(int w, int h) {
	if(environ_) environ_->resize(w,h);
}
void		neb::gfx::context::base::step(gal::std::timestep const & ts) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	if(environ_) environ_->step(ts);	
}
void		neb::gfx::context::base::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	if(!environ_) return;
	auto self = sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);
	environ_->render(self);
}		


