#include <neb/fnd/plug/gfx/app/Base.hpp>

#include <neb/gfx/app/base.hpp>

namespace NS0 = neb::fnd::plug::gfx::app;
namespace NS1 = neb::gfx::app;

typedef NS0::Base T0;

typedef NS1::Base T;

extern "C" T0*	app_create(int)
{
	return new T;
}
extern "C" void	app_destroy(T0* t)
{
	delete t;
}

