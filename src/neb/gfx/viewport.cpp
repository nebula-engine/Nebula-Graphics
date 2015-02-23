//#include <gal/log/log.hpp> removed by c_header_checker

//#include <neb/fnd/util/debug.hpp> removed by c_header_checker

#include <neb/gfx/Viewport.hpp>
#include <neb/gfx/util/log.hpp>

neb::gfx::Viewport::Viewport():
	x_(0),
	y_(0),
	w_(0),
	h_(0),
	aspect_(0)
{}
void		neb::gfx::Viewport::load() {
	glViewport(x_, y_, w_, h_);
}
void		neb::gfx::Viewport::resize(int w, int h) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	w_ = w;
	h_ = h;
	
	aspect_ = (float)w_ / (float)h_;
}

