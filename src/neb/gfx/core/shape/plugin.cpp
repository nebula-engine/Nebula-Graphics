#include <neb/fnd/plug/gfx/core/shape/util/decl.hpp>

typedef neb::fnd::plug::gfx::core::shape NS0;
typedef neb::gfx::core::shape NS1;

typedef NS0::Base T0;

typedef neb::gfx::core::shape::Base B;

extern "C" T0*	shape_create(int i)
{
	switch(i) {
	case NS0::type::BASE:
		return new B;
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

