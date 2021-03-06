
#include <neb/fnd/RenderDesc.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/Ridealong.hpp>
#include <neb/gfx/camera/view/Manual.hpp>
#include <neb/gfx/environ/NormalMap.hpp>

//#include <neb/gfx/core/scene/base.hpp> removed by c_header_checker

typedef neb::gfx::environ::NormalMap THIS;

void		THIS::init(parent_t * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	neb::gfx::environ::single<neb::gfx::camera::view::Base>::init(p);
	neb::gfx::environ::three::init(p);

	programs_.d3_.reset(new neb::gfx::glsl::program::Base("3d"));
	programs_.d3_->init();

	programs_.d3_HF_.reset(new neb::gfx::glsl::program::Base("normal_map"));
	programs_.d3_HF_->init();

	programs_.d3_inst_.reset(new neb::gfx::glsl::program::Base("3d_inst"));
	programs_.d3_inst_->init();
	
	// camera
	/*
	if(!getParent()->view_) {
		getParent()->view_.reset(new neb::gfx::camera::view::manual(self));
	}
	*/
}
void		THIS::render(std::shared_ptr<neb::gfx::context::base> context)
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

	auto proj = getParent()->proj_;
	auto view = getParent()->get_view();

	drawable->draw(
			neb::fnd::RenderDesc(
				view.get(),
				proj.get(),
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get()
				)
		      );

}	


