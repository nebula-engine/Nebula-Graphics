#include <neb/fnd/plug/gfx/context/Base.hpp>

#include <neb/gfx/context/Window.hpp>

namespace NS0 = neb::fnd::plug::gfx::context;
namespace NS1 = neb::gfx::context;

typedef NS0::Base T0;

typedef NS1::Window W;

extern "C" T0*	context_create(int i)
{
	switch(i) {
	case NS0::type::WINDOW:
		return new W;
	default:
		abort();
	}

	return 0;
}
extern "C" void	context_destroy(T0* t)
{
	delete t;
}

