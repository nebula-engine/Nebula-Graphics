#ifndef __NEBULA_UI_OBJECT_TERMINAL_H__
#define __NEBULA_UI_OBJECT_TERMINAL_H__

#include <gal/console/console.hpp>

#include <deque>


#include <neb/gfx/GUI/Object/Base.hh>

namespace neb {	namespace gfx {	namespace gui {	namespace object {
	class terminal:
		virtual public neb::gfx::gui::object::base
	{
		public:
			typedef gal::console::temp<gal::console::frontend::store, gal::console::backend::python> console_type;
			
			enum {
				max_line_count = 10
			};

			//terminal();

			virtual void		init();

			virtual void		draw(sp::shared_ptr<neb::glsl::program> p);
			//virtual void		connect();

			virtual int		key_fun(
					sp::shared_ptr<neb::gfx::window::base> const & window, int,int,int,int);

			::std::shared_ptr<console_type>		console_;

	};
}}}}

#endif

