#include <neb/gfx/core/light/directional.hpp>

neb::gfx::core::light::directional::directional(std::shared_ptr<neb::core::core::light::util::parent> parent):
	neb::core::core::light::base(parent),
	neb::gfx::core::light::base(parent, DIRECTIONAL)
{

}


