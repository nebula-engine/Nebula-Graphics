#include <neb/fnd/plug/gfx/core/shape/util/decl.hpp>

#include <neb/gfx/core/shape/box.hpp>

namespace NS0 = neb::fnd::plug::gfx::core::shape;
namespace NS1 = neb::gfx::core::shape;

typedef NS0::Base T0;

typedef neb::gfx::core::shape::base B;
typedef neb::gfx::core::shape::box C;

extern "C" T0*	shape_create(int i)
{
	switch(i) {
	case NS0::type::CUBOID:
		return new C;
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

