#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <neb/gfx/app/base.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/gui/object/textview.hh>

typedef neb::gfx::gui::object::textview THIS;

THIS::textview()
{
}
void			THIS::clear_label()
{
	label_.clear();
}
void			THIS::draw(std::shared_ptr<neb::gfx::glsl::program::Base> p)
{
	//printf("%s\n",__PRETTY_FUNCTION__);

	float sx = 1.0/600.0;
	float sy = 1.0/600.0;

	auto app = get_gfx_app();

	app->draw_quad(x_, y_, w_, h_, bg_color_);
	app->draw_text(x_, y_, sx, sy, font_color_, label_, 0);
}
int			THIS::mouseButtonFun(
		std::shared_ptr<neb::fnd::input::source> const & src,
		int button,
		int action,
		int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	return neb::gfx::gui::object::base::mouseButtonFun(src, button, action, mods);
}
int	neb::gfx::gui::object::textview::keyFun(
		std::shared_ptr<neb::fnd::input::source> const & src,
		int key,
		int scancode,
		int action,
		int mods)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	return 0;
}




