#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/log.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hh>

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
void		neb::gfx::core::light::point::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
	assert(environ);
	shadow_environ_ = environ;
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(environ);
	assert(e);
	
	auto proj = e->proj_->proj();
	auto view = e->view_[0]->view();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	glm::mat4 vpb = bias * proj * view;
	
	shadow_vpb_[0] = vpb;
	shadow_sampler_[0].x = 1;// = vec3(1,-1,-1);
	
	auto parent = getScene().lock();

	parent->light_array_[light_array_].set_shadow_vpb_0(
			light_array_slot_,
			shadow_vpb_[0]);
	parent->light_array_[light_array_].set_shadow_sampler_0(
			light_array_slot_,
			shadow_sampler_[0]);

}


