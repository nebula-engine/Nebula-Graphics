#include <gal/log/log.hpp>

#include <glm/gtx/transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/core/mesh_instanced.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/shape/box.hpp>
#include <neb/gfx/util/log.hpp>


neb::gfx::core::shape::box::box(std::shared_ptr<neb::core::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent),
	neb::gfx::core::shape::base(parent)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::shape::box::box::createMesh() {
	//mesh_.load("cube.obj");
	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	/*
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.reset(new neb::gfx::mesh);
	mesh_->construct(&cube);
	*/
	
	auto scene = std::dynamic_pointer_cast<neb::gfx::core::scene::base>(getScene().lock());
	
	if(!mesh_slot_) {
		auto model = getPoseGlobal().mat4_cast() * glm::scale(s_);
		
		mesh_slot_ = scene->meshes_.cuboid_->instances_->reg(model, -1.0, -1.0, neb::Color::cyan<float>());
	}
	
	//mesh_->texture_.reset(new neb::gfx::texture);
	//mesh_->texture_->load_png("/nfs/stak/students/r/rymalc/Documents/Pictures/crab.png", bufs);

}


