#include <neb/gfx/environ/base.hpp>

void		neb::gfx::environ::base::init(parent_t * const & p)
{
	setParent(p);
}
void		neb::gfx::environ::base::step(gal::etc::timestep const & ts)
{
}
void		neb::gfx::environ::base::resize(int w, int h)
{
	printv_func(DEBUG);

	viewport_.resize(w,h);
}
bool		neb::gfx::environ::base::shouldRender()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return true;
}


