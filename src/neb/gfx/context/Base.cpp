
#include <gal/log/log.hpp>
#include <gal/stl/deleter.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/scene/Base.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/context/Base.hpp>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/context/util/Parent.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/NormalMap.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/camera/view/Free.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>

typedef neb::gfx::context::base THIS;

/*neb::gfx::context::base::base() {
}*/
THIS::base()
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
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
void		THIS::resize(int w, int h)
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
	
	auto parent = getParent();
	
	typedef neb::fnd::environ::util::Parent E;

	auto lamb = [&] (E::map_type::pointer p)
	{
		p->resize(w, h);
	};
	
	parent->E::map_.for_each(lamb);
}
void		THIS::step(gal::etc::timestep const & ts)
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
	auto e = getParent()->neb::fnd::environ::util::Parent::front();
	/// @TODO fix this
	//if(e) e->step(ts);	
}
void		THIS::render()
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
	/**
	 * prepare rendering environment and then call the drawable
	 */
	//auto e = getParent()->neb::fnd::environ::util::Parent::front();
	//if(!e)
	//{
	//	printv(CRITICAL, "context has no environ\n");
	//	abort();
	//	return;
	//}
	
	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);
	
	//e->render(self->getParent());
	
	auto parent = getParent();
	
	typedef neb::fnd::environ::util::Parent E;

	auto lamb = [&] (E::map_type::pointer p)
	{
		p->render(parent);
	};
	
	parent->E::map_.for_each(lamb);
}		
/*
std::shared_ptr<neb::fnd::environ::Base>	THIS::get_environ()
{
	return environ_;
}
*/
void		THIS::setTexture(
					std::shared_ptr<neb::fnd::itf::shared> tex)
{
	abort();
}

