#include <Galaxy-Log/log.hpp>

#include <neb/core/debug.hh>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/Viewport.hpp>

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
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx", debug) << __PRETTY_FUNCTION__;

	w_ = w;
	h_ = h;
	
	aspect_ = (real)w_ / (real)h_;
}

