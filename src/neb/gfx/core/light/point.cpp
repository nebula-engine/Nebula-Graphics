#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/log.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
#include <neb/gfx/texture.hpp>

neb::gfx::core::light::point::point(std::shared_ptr<neb::core::core::light::util::parent> parent):
	neb::core::core::light::base(parent),
	neb::gfx::core::light::base(parent, 0)
{}
void	neb::gfx::core::light::point::load(neb::core::core::light::util::count & light_count, neb::core::pose const & pose) {

	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*        
		  neb::gfx::core::light::base::load(light_count.point, pose);

		  auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();


		  p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
		  p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
		  p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
		  light_count.point++;
		  */
}
void			neb::gfx::core::light::point::init()
{
	neb::gfx::core::light::base::init();

	auto scene = getScene().lock();
	assert(scene);

	auto self = std::dynamic_pointer_cast<neb::gfx::core::light::point>(shared_from_this());
	
	auto app = neb::gfx::app::__gfx::global().lock();
	
	
	auto window = app->createWindow().lock();

	auto context = window->createContextFBOMulti().lock();
	
	auto environ = context->createEnvironShadowPoint().lock();
	
	context->setDrawable(scene);
	
	context->texture_ = scene->tex_shadow_map_;
	
	environ->light_ = self;
	
	setShadowEnviron(environ);

}
void		neb::gfx::core::light::point::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
	assert(environ);
	shadow_environ_ = environ;
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(environ);
	assert(e);
	
	auto proj = e->proj_->proj();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);
	
	glm::mat4 pb = bias * proj;
	glm::mat4 vpb;
	
	for(GLint layer = 0; layer < 6; layer++) {
	
		auto view = e->view_[layer]->view();
	
		vpb = pb * view;
		shadow_vpb_[layer] = vpb;

	}

	auto scene = getScene().lock();

	// request texture layers
	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(6);

	shadow_sampler_[0].x = texture_layers_->operator[](0);
	shadow_sampler_[0].y = texture_layers_->operator[](1);
	shadow_sampler_[0].z = texture_layers_->operator[](2);
	shadow_sampler_[1].x = texture_layers_->operator[](3);
	shadow_sampler_[1].y = texture_layers_->operator[](4);
	shadow_sampler_[1].z = texture_layers_->operator[](5);
	
	auto parent = getScene().lock();

	parent->light_array_[light_array_].set_shadow_vpb_0(light_array_slot_, shadow_vpb_[0]);
	parent->light_array_[light_array_].set_shadow_vpb_1(light_array_slot_, shadow_vpb_[1]);
	parent->light_array_[light_array_].set_shadow_vpb_2(light_array_slot_, shadow_vpb_[2]);
	parent->light_array_[light_array_].set_shadow_vpb_3(light_array_slot_, shadow_vpb_[3]);
	parent->light_array_[light_array_].set_shadow_vpb_4(light_array_slot_, shadow_vpb_[4]);
	parent->light_array_[light_array_].set_shadow_vpb_5(light_array_slot_, shadow_vpb_[5]);
			

	parent->light_array_[light_array_].set_shadow_sampler_0(light_array_slot_, shadow_sampler_[0]);
	parent->light_array_[light_array_].set_shadow_sampler_1(light_array_slot_, shadow_sampler_[1]);
			
			

}


