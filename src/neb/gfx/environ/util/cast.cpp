#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
//#include <neb/gfx/environ/util/cast.hpp> removed by c_header_checker

typedef neb::gfx::environ::Two TWO;

std::shared_ptr<TWO>		neb::gfx::environ::util::cast::isEnvironTwo()
{
	return std::dynamic_pointer_cast<TWO>(shared_from_this());
}
std::shared_ptr<neb::gfx::environ::three>	neb::gfx::environ::util::cast::isEnvironThree()
{
	return std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
}

