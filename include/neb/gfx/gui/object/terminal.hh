#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <deque>

#include <neb/core/app/__base.hpp>

#include <neb/gfx/gui/object/Base.hh>



namespace neb { namespace gfx { namespace gui { namespace object {
	class terminal:
		virtual public neb::gfx::gui::object::base
	{
		public:
			terminal();
			virtual void			init();
			virtual void			draw(std::shared_ptr<neb::glsl::program> p);
			virtual int			key_fun(
					std::shared_ptr<neb::gfx::window::base> const & window, int,int,int,int);
			virtual int			charFun(
					shared_ptr<neb::gfx::window::base> const & window,
					unsigned int codepoint);



			weak_ptr<neb::core::app::__base::console_type>		console_;

			// display
			std::vector<std::string>		history_;
			unsigned int				history_current_;
			unsigned int				page_offset_;
			unsigned int				max_line_count_;
	};
}}}}

#endif

