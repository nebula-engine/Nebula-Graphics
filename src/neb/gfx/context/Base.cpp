
#include <gal/log/log.hpp>
#include <gal/stl/deleter.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/context/Base.hh>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/context/util/Parent.hh>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/NormalMap.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/camera/view/Free.hh>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/util/log.hpp>

typedef neb::gfx::context::base THIS;

/*neb::gfx::context::base::base() {
}*/
THIS::base()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
/*neb::gfx::context::base&		neb::gfx::context::base::operator=(neb::gfx::context::base const & r){
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	return *this;
}*/
/*void		neb::gfx::context::base::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::release() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}*/
void		neb::gfx::context::base::resize(int w, int h) {
	if(environ_) environ_->resize(w,h);
}
void		neb::gfx::context::base::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	if(environ_) environ_->step(ts);	
}
void		neb::gfx::context::base::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	if(!environ_)
	{
		LOG(lg, neb::gfx::sl, warning) << "context has no environ";
		return;
	}

	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);
	
	environ_->render(self);
}		
void							neb::gfx::context::base::setDrawable(
		std::shared_ptr<neb::core::drawable::Base> drawable)
{
	auto d = std::dynamic_pointer_cast<neb::gfx::drawable::base>(drawable);
	assert(d);
	assert(environ_);
	environ_->drawable_ = d;
}
void			THIS::setEnviron(std::shared_ptr<neb::core::environ::Base> env)
{
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::base>(env);
	assert(e);
	environ_ = e;
}


