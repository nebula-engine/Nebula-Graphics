#include <neb/fnd/plug/gfx/core/actor/util/decl.hpp>

#include <neb/gfx/core/actor/base.hpp>

namespace NS0 = neb::fnd::plug::gfx::core::actor;
namespace NS1 = neb::gfx::core::actor;

typedef NS0::Base T0;

typedef NS1::base T;

extern "C" T0*	actor_create(int i)
{
	return new T;
	
	return 0;
}
extern "C" void	actor_destroy(T0* t)
{
	delete t;
}

