#include <stdio.h>

#include <gal/log/log.hpp>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/Context/Base.hh>

#include <neb/core/util/log.hpp>
#include <neb/core/util/debug.hpp>
#include <neb/core/util/config.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>
//#include <neb/core/core/actor/util/Type.hh>
#include <neb/core/timer/Types.hh>
#include <neb/core/timer/Actor/Release.hpp>
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/core/mesh_instanced.hpp>
#include <neb/gfx/texture.hpp>

using namespace std;

typedef neb::core::core::actor::util::parent A;

neb::gfx::core::scene::base::base(std::shared_ptr<neb::core::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent)
{
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;
}
neb::gfx::core::scene::base::~base() {
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::scene::base::init() {
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;
	
	light_array_[0].alloc(32);
	light_array_[1].alloc(32);

	// meshes

	math::geo::cuboid cube(1.0,1.0,1.0);
	
	meshes_.cuboid_.reset(new neb::gfx::mesh::instanced);
	meshes_.cuboid_->mesh_.construct(&cube);

	meshes_.cuboid_->instances_.reset(new neb::gfx::mesh::instanced::instances_type);
	meshes_.cuboid_->instances_->alloc(256);


	tex_shadow_map_ = std::make_shared<neb::gfx::texture>();
	tex_shadow_map_->init_shadow(2048, 2048, std::shared_ptr<neb::gfx::context::base>());


}
void			neb::gfx::core::scene::base::release() {
	LOG(lg, neb::core::core::scene::sl, debug) << __PRETTY_FUNCTION__;
	
	neb::core::core::scene::base::release();
}
/*void			neb::gfx::core::scene::base::load_lights(std::shared_ptr<neb::gfx::glsl::program::base> p) {

	neb::core::core::light::util::count light_count;

	auto la = [&] (A::map_type::iterator<0> it) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(it->ptr_);
		assert(actor);
		actor->load_lights(light_count, neb::core::pose());
	};

	A::map_.for_each<0>(la);

	p->get_uniform_scalar("light_count_point")->load(light_count.point);
	p->get_uniform_scalar("light_count_spot")->load(light_count.spot);
	p->get_uniform_scalar("light_count_directional")->load(light_count.directional);

}*/
void			neb::gfx::core::scene::base::draw(
		std::shared_ptr<neb::gfx::context::base> context,
		std::shared_ptr<neb::gfx::glsl::program::base> p) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	assert(p);
	
	auto program_3d = std::dynamic_pointer_cast<neb::gfx::glsl::program::threed>(p);
	if(program_3d) {
		// lights
		light_array_[0].load_uniform(program_3d->light_locations_.location);
	}
	
	if(tex_shadow_map_) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(tex_shadow_map_->target_, tex_shadow_map_->o_);

		GLint loc = p->uniform_table_[neb::gfx::glsl::uniforms::TEX_SHADOW_MAP];
		neb::gfx::ogl::glUniform(loc, 0);
	}

	// meshes
	assert(meshes_.cuboid_);
	meshes_.cuboid_->draw(p);

	/*
	// meshes
	auto la = [&] (A::map_type::iterator<0> it) {
	auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(it->ptr_);
	assert(actor);
	actor->draw(context, program_3d, neb::core::pose());
	};


	A::map_.for_each<0>(la);
	*/
}
void						neb::gfx::core::scene::base::resize(int w, int h) {
}
void						neb::gfx::core::scene::base::step(gal::etc::timestep const & ts) {
}
/*weak_ptr<neb::core::core::actor::base>		neb::gfx::core::scene::base::createActorBase(neb::core::pose const & pose) {
  auto actor(make_shared<neb::gfx::core::actor::base>(isSceneBase()));
  insert(actor);
  return actor;
  }*/
std::weak_ptr<neb::core::core::actor::base>	neb::gfx::core::scene::base::createActorLightPoint(vec3 p) {

	neb::core::pose pose(p);

	auto actor = createActorBase(pose).lock();

	insert(actor);

	auto shape = actor->createShapeBase(neb::core::pose()).lock();

	shape->createLightPoint();

	return actor;
}



