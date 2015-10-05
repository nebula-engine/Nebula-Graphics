#include <neb/fnd/plug/gfx/camera/proj/util/decl.hpp>
#include <neb/fnd/plug/gfx/camera/proj/Base.hpp>

#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/proj/ortho.hpp>

namespace NS0 = neb::fnd::plug::gfx::camera::proj;
namespace NS1 = neb::gfx::camera::proj;

typedef NS0::Base T0;

typedef NS1::Perspective P;
typedef NS1::Ortho O;

extern "C" T0*	camera_proj_create(int i)
{
	switch(i) {
	case NS0::type::PERSPECTIVE:
		return new P;
	case NS0::type::ORTHO:
		return new O;
	default:
		abort();
	}

	return 0;
}
extern "C" void	camera_proj_destroy(T0* t)
{
	delete t;
}

