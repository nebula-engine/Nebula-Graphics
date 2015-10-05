#include <neb/fnd/plug/gfx/camera/view/util/decl.hpp>
#include <neb/fnd/plug/gfx/camera/view/Base.hpp>

#include <neb/gfx/camera/view/Ridealong.hpp>
//#include <neb/gfx/camera/view/Ortho.hpp>

namespace NS0 = neb::fnd::plug::gfx::camera::view;
namespace NS1 = neb::gfx::camera::view;

typedef NS0::Base T0;

typedef NS1::Ridealong R;
//typedef NS1::Ortho O;

extern "C" T0*	camera_view_create(int i)
{
	switch(i) {
	case NS0::type::RIDEALONG:
		return new R;
	//se NS0::type::ORTHO:
	//eturn new O;
	default:
		abort();
	}

	return 0;
}
extern "C" void	camera_view_destroy(T0* t)
{
	delete t;
}

