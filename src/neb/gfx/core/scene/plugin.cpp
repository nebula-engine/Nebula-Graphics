#include <neb/fnd/plug/gfx/core/scene/util/decl.hpp>

#include <neb/gfx/core/scene/base.hpp>

namespace NS0 = neb::fnd::plug::gfx::core::scene;
namespace NS1 = neb::gfx::core::scene;

typedef NS0::Base T0;

typedef NS1::base T;

extern "C" T0*	scene_create(int i)
{
	return new T;
	
	return 0;
}
extern "C" void	scene_destroy(T0* t)
{
	delete t;
}

