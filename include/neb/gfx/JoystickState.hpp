#ifndef NEB_GFX_JOYSTICKSTATE_HPP
#define NEB_GFX_JOYSTICKSTATE_HPP

#include <neb/core/input/signals.hpp>

namespace neb { namespace gfx {
	class JoystickState
	{
		public:
			virtual void		update();
		private:
			float			_M_axes[6];
			unsigned char		_M_buttons[32];

			unsigned char		_M_axes_count;
			unsigned char		_M_button_count;

			neb::fnd::input::signal::JoystickButtonFun	_M_button_signal;
	};
}}

#endif
