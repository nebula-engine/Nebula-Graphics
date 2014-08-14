#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/log/log.hpp>



#include <neb/core/debug.hh>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/GUI/Object/terminal.hh>

typedef gal::console::temp<gal::console::backend::python, gal::console::frontend::store> console_type;

void		neb::gfx::gui::object::terminal::init() {
	if(DEBUG_NEB) LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	neb::gfx::gui::object::base::init();
	
	console_ = make_shared<console_type>();
	console_->init();

	//auto app = neb::app::base::global();

	//cs_ = app->command_set_;

	//assert(cs_);
}
void		neb::gfx::gui::object::terminal::draw(sp::shared_ptr<neb::glsl::program> p) {
	if(DEBUG_NEB) LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	if(!console_) return;
	
	if(!flag_.any(neb::gfx::gui::object::util::flag::ENABLED)) return;

	float sx = 1.0/ 600.0;
	float sy = 1.0/ 600.0;

	//draw_quad(x_, y_, w_, h_, bg_color_);

	//float y = y_ + 0.5;
	float y = y_ + 0.25;
	float line_height = 0.1;
	
	for(auto l : console_->lines_) {
		draw_text(p, x_, y, sx, sy, font_color_, l.c_str());
		y -= line_height;
	}

	string line = "$ " + console_->line_;

	draw_text(p, x_, y, sx, sy, font_color_, line.c_str());
}
int			neb::gfx::gui::object::terminal::charFun(
		shared_ptr<neb::gfx::window::base> const & window,
		unsigned int codepoint)
{
	if(DEBUG_NEB) LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	if(flag_.any(neb::gfx::gui::object::util::flag::ENABLED)) {
		if(console_) {
			console_->push(codepoint);
		}
	}
	return 1;
}
int			neb::gfx::gui::object::terminal::key_fun(
		sp::shared_ptr<neb::gfx::window::base> const & window,
		int key,
		int scancode,
		int action,
		int mods)
{
	if(DEBUG_NEB) LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	if(!flag_.any(neb::gfx::gui::object::util::flag::ENABLED) && !(key == GLFW_KEY_ESCAPE)) {
		return 0;
	}

	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_ESCAPE:
				flag_.toggle(neb::gfx::gui::object::util::flag::ENABLED);
				break;
			case GLFW_KEY_BACKSPACE:
				if(!console_->line_.empty()) {
					console_->line_.pop_back();
				}
				break;
			case GLFW_KEY_ENTER:
				console_->enter();
				break;
		}
	}

	// block everything
	return 1;
}




