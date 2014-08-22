#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>


#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/util/log.hpp>

#include <neb/core/math/geo/polygon.hpp>

neb::gfx::core::shape::base::base(std::shared_ptr<neb::core::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	assert(parent);
}
neb::gfx::core::shape::base::~base() {}
void					neb::gfx::core::shape::base::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	createMesh();
}
void					neb::gfx::core::shape::base::release() {
}
void					neb::gfx::core::shape::base::step(gal::etc::timestep const & ts) {

	//material_front_.step(ts);
}
void					neb::gfx::core::shape::base::setPose(neb::core::pose const & pose) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto npose = pose * pose_;

	neb::gfx::core::light::util::parent::setPose(npose);
}
void					neb::gfx::core::shape::base::draw(
		std::shared_ptr<neb::gfx::context::base> context,
		std::shared_ptr<neb::gfx::glsl::program::base> p,
		neb::core::pose const & pose) {

	auto npose = pose * pose_;
	
	draw_elements(context, p, npose);
	

}
void			neb::gfx::core::shape::base::model_load(neb::core::pose const & pose) {

	auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();

	mat4 space = pose.mat4_cast() * glm::scale(s_);

	p->get_uniform_scalar("model")->load(space);
}
void			neb::gfx::core::shape::base::draw_elements(
		std::shared_ptr<neb::gfx::context::base> context,
		std::shared_ptr<neb::gfx::glsl::program::base> p,
		neb::core::pose const & pose)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	if(mesh_) {
		
		mesh_->draw_elements(context, p, pose, s_);
		/*
		switch(p->name_) {
			case neb::program_name::e::IMAGE:
				if(mesh_->texture_ && !(mesh_->normal_map_))
					mesh_->draw_elements(context, p, pose, s_);
				break;
			case neb::program_name::e::NORM:
				if(!(mesh_->texture_) && mesh_->normal_map_)
					mesh_->draw_elements(context, p, pose, s_);
				break;
			case neb::program_name::e::LIGHT:
				if(!(mesh_->texture_) && !(mesh_->normal_map_))
					mesh_->draw_elements(context, p, pose, s_);
				break;
			default:
				abort();
		}*/
	}
}
std::weak_ptr<neb::core::core::light::base>		neb::gfx::core::shape::base::createLightPoint() {

	auto self(std::dynamic_pointer_cast<neb::core::core::shape::base>(shared_from_this()));

	auto light = sp::make_shared<neb::gfx::core::light::point>(self);

	neb::core::core::light::util::parent::insert(light);
	
	light->init();
	

	return light;
}
void						neb::gfx::core::shape::base::createMesh() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

}




