#include <neb/fnd/plug/gfx/core/light/util/decl.hpp>

#include <neb/gfx/core/light/Point.hpp>
#include <neb/gfx/core/light/Spot.hpp>
#include <neb/gfx/core/light/Directional.hpp>

namespace NS0 = neb::fnd::plug::gfx::core::light;
namespace NS1 = neb::gfx::core::light;

typedef NS0::Base T0;

typedef neb::gfx::core::light::Point P;
typedef neb::gfx::core::light::Spot S;
typedef neb::gfx::core::light::Directional D;

extern "C" T0*	light_create(int i)
{
	printf("plugin gfx1 %s\n", __PRETTY_FUNCTION__);

	switch(i) {
	case NS0::type::POINT:
		return new P;
//	case NS0::type::SPOT:
//		return new S;
//	case NS0::type::DIRECTIONAL:
//		return new D;
	default:
		printf("error: invalid type: %i\n", i);
		abort();
	}
	
	return 0;
}
extern "C" void	light_destroy(T0* t)
{
	printf("plugin gfx1 %s\n", __PRETTY_FUNCTION__);
	delete t;
}

