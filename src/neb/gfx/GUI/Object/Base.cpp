#include <string.h>
#include <algorithm>

#include <neb/gfx/gui/object/Base.hh>

neb::gfx::gui::object::base::base():
	x_(0.0),
	y_(0.0),
	w_(0.3),
	h_(0.3),
	font_color_(neb::core::color::color::magenta()),
	bg_color_()
{}
void		neb::gfx::gui::object::base::init() {
	neb::itf::shared::init();
}
int		neb::gfx::gui::object::base::mouse_button_fun(std::shared_ptr<neb::gfx::window::base> const & window, int,int,int) {
	printf("%s\n", __PRETTY_FUNCTION__);

	font_color_ = neb::core::color::color::green();

	return 1;
}



