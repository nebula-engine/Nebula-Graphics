#include <neb/fnd/plug/gfx/window/Base.hpp>

#include <neb/gfx/window/Base.hpp>

namespace NS0 = neb::fnd::plug::gfx::window;
namespace NS1 = neb::gfx::window;

typedef NS0::Base T0;

typedef NS1::Base T;

extern "C" T0*	window_create(int)
{
	return new T;
	
	return 0;
}
extern "C" void	window_destroy(T0* t)
{
	delete t;
}

