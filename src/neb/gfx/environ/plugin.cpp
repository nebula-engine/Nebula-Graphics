#include <neb/fnd/plug/gfx/environ/util/decl.hpp>
#include <neb/fnd/plug/gfx/environ/Base.hpp>

#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/two.hpp>

namespace NS0 = neb::fnd::plug::gfx::environ;
namespace NS1 = neb::gfx::environ;

typedef NS0::Base T0;

typedef NS1::SceneDefault SD;
typedef NS1::Two T;

extern "C" T0*	environ_create(int i)
{
	switch(i) {
	case NS0::type::SCENE_DEFAULT:
		return new SD;
	case NS0::type::TWO:
		return new T;
	default:
		abort();
	}

	return 0;
}
extern "C" void	environ_destroy(T0* t)
{
	delete t;
}

