#ifndef NEB_GFX_JOYSTICKSTATE_HPP
#define NEB_GFX_JOYSTICKSTATE_HPP

#include <gal/shared.hpp>

#include <neb/fnd/input/js.hpp>

namespace neb { namespace gfx {
	class js:
		virtual public gal::enable_shared_from_this<neb::gfx::js>,
		virtual public neb::fnd::input::js
	{
		public:
			js();
			virtual int			get_axes_count();
			virtual int			get_button_count();
			virtual float			get_axes(int i);
			virtual void			update(int i);
		private:
			bool				_M_present;
			float				_M_axes[6];
			unsigned char			_M_buttons[32];

			int				_M_axes_count;
			int				_M_button_count;
	};
}}

#endif
