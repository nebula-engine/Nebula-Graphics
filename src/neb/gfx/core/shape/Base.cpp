#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/core/light/Point.hpp>
#include <neb/gfx/core/light/Spot.hpp>
#include <neb/gfx/core/light/Directional.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/mesh/tri1.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/opengl/uniform.hpp>

#include <neb/fnd/math/geo/polygon.hpp>

typedef neb::gfx::core::shape::base THIS;

THIS::base()
{
	printv_func(DEBUG);
}
THIS::~base() {}
void					THIS::init(parent_t * const & p)
{
	printv_func(DEBUG);

	setParent(p);

	if(!neb::fnd::app::Base::is_valid()) return;

	createMesh();
}
void					THIS::release()
{
	//neb::fnd::core::shape::base::release();
}
void					THIS::step(gal::etc::timestep const & ts)
{

	//material_front_.step(ts);
}
void				THIS::v_set_pose_data(
		FND * const & ptr,
		neb::fnd::math::pose const & gpose)
{
	printv_func(DEBUG);
	//LOG(lg, neb::gfx::core::shape::sl, debug) << gpose.mat4_cast();

	//neb::fnd::core::shape::base::__set_pose_data(gpose);

	auto p = getParent();

	if(mesh_slot_) {
		auto model = gpose.mat4_cast() * glm::scale(p->scale_);
		
		mesh_slot_->set<0>(model);
		//LOG(lg, neb::gfx::core::shape::sl, debug) << "slot " << mesh_slot_->index_;
	}
}
/*void					THIS::setPose(neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	
	auto npose = pose * pose_;

	neb::gfx::core::light::util::parent::setPose(npose);
}*/
void					THIS::draw(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	auto parent = getParent();

	auto npose = pose * parent->pose_;
	
	draw_elements(ptr, p, npose);
}
void			THIS::drawHF(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
}
void			THIS::model_load(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	printv_func(DEBUG);

	auto parent = getParent();

	glm::mat4 space = pose.mat4_cast() * glm::scale(parent->scale_);

	auto v = p->get_uniform_table_value(neb::gfx::glsl::uniforms::MODEL);

	assert(v != -1);

	neb::gfx::ogl::glUniform(v, space);
}
void			THIS::draw_elements(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	printv_func(DEBUG);

	auto parent = getParent();

	assert(p);

	if(mesh_) {
		mesh_->drawElements(p, pose, parent->scale_);
	} else {
		draw_legacy(ptr, p, pose);
	}
}
void			THIS::drawDebug(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	printv_func(DEBUG);
	
	auto parent = getParent();

	assert(p);
	
	if(mesh_)
	{
		mesh_->drawDebug(p, pose, parent->scale_);
	}
}
void						THIS::createMesh()
{
	printv_func(DEBUG);
}
void						THIS::draw_legacy(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	printv_func(DEBUG);
}



