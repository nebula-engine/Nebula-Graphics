
#include <neb/fnd/util/cast.hpp>
#include <neb/fnd/RenderDesc.hpp>

//#include <neb/gfx/util/log.hpp> removed by c_header_checker
#include <neb/gfx/camera/view/Ridealong.hpp>
#include <neb/gfx/camera/view/Free.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>

#include <neb/gfx/core/scene/base.hpp>

typedef neb::gfx::environ::SceneDefault THIS;

void		THIS::init(parent_t * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	neb::gfx::environ::single<neb::gfx::camera::view::Base>::init(p);
	neb::gfx::environ::three::init(p);

	//programs_.reset(new neb::gfx::glsl::program::threed("3d"));
	//programs_->init();
	
	
	
	// camera
	/*
	if(!getParent()->view_) {
		getParent()->view_.reset(new neb::gfx::camera::view::Free(self));
	}
	*/
}
void		neb::gfx::environ::SceneDefault::render(std::shared_ptr<neb::gfx::context::base> context)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// prepare rendering environment and then call the drawable
	
	auto drawable = getParent()->drawable_.lock();

	if(!drawable) {
		LOG(lg, neb::gfx::sl, warning) << "drawable is NULL";
		return;
	}

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::__gfx_glsl::global().lock();

	// wrong for color maybe! 	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//assert(proj_);
	//assert(view_);
	
	//program_->use();
	
	viewport_.load();
	
	//proj_->load(program_);
	//view_->load(program_);

	auto view = getParent()->get_view().get();
	auto proj = getParent()->proj_.get();
	

	drawable->draw(
			neb::fnd::RenderDesc(
				view,
				proj,
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get()
				)
		      );

	auto scene = neb::could_be<neb::fnd::drawable::Base, neb::fnd::core::scene::base>(drawable);

	/*
	if(scene) scene->drawDebug(
				neb::fnd::RenderDesc(
					view,
					proj,
					programs_.d3_.get(),
					programs_.d3_HF_.get(),
					programs_.d3_inst_.get()
					)
				);
	*/


	if(0) { /** @todo make this a dynamic flag! */
		/*
		if(scene) scene->drawPhysxVisualization(
				neb::fnd::RenderDesc(
					view,
					proj,
					programs_.d3_.get(),
					programs_.d3_HF_.get(),
					programs_.d3_inst_.get()
					)
				);
				*/
	}
}	

