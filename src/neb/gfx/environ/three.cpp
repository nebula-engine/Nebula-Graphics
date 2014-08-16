#include <gal/log/log.hpp>


#include <neb/core/util/debug.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/Camera/View/Free.hh>
#include <neb/gfx/Camera/View/ridealong.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>

#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/util/log.hpp>

void		neb::gfx::environ::three::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	// camera
	if(!view_) {
		view_.reset(new neb::gfx::Camera::View::Free(self));
	}

	proj_.reset(new neb::gfx::Camera::Projection::Perspective(self));
	//camera_->init(shared_from_this());
	
}
void		neb::gfx::environ::three::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	if(proj_) proj_->step(ts);	
	if(view_) view_->step(ts);	

}
void		neb::gfx::environ::three::render(std::shared_ptr<neb::gfx::context::base> context) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */

	
	auto drawable = drawable_.lock();

	if(!drawable) return;

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	auto app = neb::app::__gfx_glsl::global().lock();

	/** wrong for color maybe! */	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	assert(proj_);
	assert(view_);
	
	// get program choice from drawable
	/** @todo replace with 'environ' which determines program and camera types and accepts certian types of drawables */
	
	auto p = app->use_program(neb::program_name::e::LIGHT);
	proj_->load(p);
	view_->load(p);
	drawable->draw(context, p);
	
	p = app->use_program(neb::program_name::e::NORM);
	proj_->load(p);
	view_->load(p);
	drawable->draw(context, p);

	p = app->use_program(neb::program_name::e::IMAGE);
	proj_->load(p);
	view_->load(p);
	drawable->draw(context, p);
}		
weak_ptr<neb::gfx::Camera::View::Ridealong>		neb::gfx::environ::three::createViewRidealong(
		weak_ptr<neb::core::core::actor::base> actor)
{
	auto self(dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this()));

	auto view = make_shared<neb::gfx::Camera::View::Ridealong>(self, actor);
	view_ = view;
	return view;
}





