#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__


#include <deque>

#include <neb/core/app/__base.hpp>

#include <neb/gfx/gui/object/Base.hh>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				class terminal:
					virtual public neb::gfx::gui::object::base
				{
					public:
						enum {
							max_line_count = 10
						};
						virtual void			init();
						virtual void			draw(std::shared_ptr<neb::glsl::program> p);
						virtual int			key_fun(
								std::shared_ptr<neb::gfx::window::base> const & window, int,int,int,int);
						virtual int			charFun(
								shared_ptr<neb::gfx::window::base> const & window,
								unsigned int codepoint);

						weak_ptr<neb::core::app::__base::console_type>		console_;
				};
			}
		}
	}
}

#endif

