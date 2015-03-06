#include <GLFW/glfw3.h>

#include <neb/gfx/JoystickState.hpp>

typedef neb::gfx::js THIS;

THIS::js():
	_M_present(false),
	_M_axes_count(0),
	_M_button_count(0)
{
}
void	THIS::update(int i)
{
	// axes
	const float* axes = glfwGetJoystickAxes(i, &_M_axes_count);

	memcpy(_M_axes, axes, sizeof(float) * _M_axes_count);
	
	// buttons
	const unsigned char* btn = glfwGetJoystickButtons(i, &_M_button_count);

	for(int j = 0; j < _M_button_count; j++) {
		switch(btn[j]) {
			case GLFW_PRESS:
				if(_M_buttons[j] == GLFW_RELEASE) {
					joystickButtonFun_(j, GLFW_PRESS);
				}
				break;
			case GLFW_RELEASE:
				if(_M_buttons[j] == GLFW_PRESS) {
					joystickButtonFun_(j, GLFW_RELEASE);
				}
				break;
		}
	}

	memcpy(_M_buttons, btn, sizeof(unsigned char) * _M_button_count);
}
int			THIS::get_axes_count()
{
	return _M_axes_count;
}
int			THIS::get_button_count()
{
	return _M_button_count;
}
float			THIS::get_axes(int i)
{
	return _M_axes[i];
}

