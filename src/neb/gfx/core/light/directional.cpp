#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/Context/fbo.hpp>

neb::gfx::core::light::directional::directional(std::shared_ptr<neb::core::core::light::util::parent> parent):
	neb::core::core::light::base(parent),
	neb::gfx::core::light::base(parent, DIRECTIONAL)
{

}
void			neb::gfx::core::light::directional::init()
{
	neb::gfx::core::light::base::init();

	auto scene = getScene().lock();
	assert(scene);

	auto self = std::dynamic_pointer_cast<neb::gfx::core::light::directional>(shared_from_this());
	
	auto app = neb::gfx::app::__gfx::global().lock();

	auto window = app->createWindow().lock();
	auto context = window->createContextFBO().lock();
	auto environ = context->createEnvironShadowDirectional().lock();
	
	context->setDrawable(scene);
	
	context->texture_ = scene->tex_shadow_map_;

	environ->light_ = self;

	setShadowEnviron(environ);

}
void		neb::gfx::core::light::directional::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
	assert(environ);
	shadow_environ_ = environ;
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow_directional>(environ);
	assert(e);
	
	auto proj = e->proj_->proj();
	auto view = e->view_->view();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	glm::mat4 vpb = bias * proj * view;
	
	shadow_vpb_[0] = vpb;
	shadow_sampler_[0].x = 0;// = vec3(1,-1,-1);
	
	auto parent = getScene().lock();

	parent->light_array_[light_array_].set_shadow_vpb_0(
			light_array_slot_,
			shadow_vpb_[0]);
	parent->light_array_[light_array_].set_shadow_sampler_0(
			light_array_slot_,
			shadow_sampler_[0]);

}

