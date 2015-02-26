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

extern "C" T0*	shape_create(int i)
{
	switch(i) {
	case NS0::type::POINT:
		return new P;
	case NS0::type::SPOT:
		return new S;
	case NS0::type::DIRECTIONAL:
		return new D;
	default:
		abort();
	}
	
	return 0;
}
extern "C" void	shape_destroy(T0* t)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	delete t;
}

