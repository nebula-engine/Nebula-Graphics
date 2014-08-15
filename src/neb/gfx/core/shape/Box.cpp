#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/core/shape/box.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::core::shape::box::box(sp::shared_ptr<neb::core::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent),
	neb::gfx::core::shape::base(parent)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void neb::gfx::core::shape::box::box::createMesh() {
	//mesh_.load("cube.obj");
	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.construct(&cube);
}


