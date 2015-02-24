#include <neb/fnd/app/Base.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/app/glfw.hpp>

typedef neb::gfx::app::glfw THIS;

void			THIS::static_error_fun(
		int error, char const * description)
{
	printf("%s\n", description);
	abort();
	//throw neb::gfx::exception();
}
void			THIS::static_window_pos_fun(
		GLFWwindow* window, int x, int y)
{
	//GLUTPP_DEBUG_0_FUNCTION;
	
	auto w = get_gfx_app_glfw()->get_window(window);
	
	w->callback_window_pos_fun(/*window,*/x,y);
}
void			THIS::static_window_size_fun(
		GLFWwindow* window, int width, int h)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = get_gfx_app_glfw()->get_window(window);

	w->callback_window_size_fun(/*window, */width, h);
}
void			THIS::static_window_close_fun(
		GLFWwindow* window)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = get_gfx_app_glfw()->get_window(window);

	w->callback_window_close_fun(/*window*/);
}
void			THIS::static_window_refresh_fun(
		GLFWwindow* window)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = get_gfx_app_glfw()->get_window(window);

	w->callback_window_refresh_fun(/*window*/);
}
void			THIS::static_mouse_button_fun(
		GLFWwindow* window, int button, int action, int mods)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = get_gfx_app_glfw()->get_window(window);

	w->callback_mouse_button_fun(/*window, */button, action, mods);
}
void			THIS::static_key_fun(
		GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//GLUTPP_DEBUG_0_FUNCTION;

	auto w = get_gfx_app_glfw()->get_window(window);

	w->callback_key_fun(/*window, */key, scancode, action, mods);
}
void			THIS::staticCharFun(
		GLFWwindow* window, unsigned int codepoint)
{
	auto w = get_gfx_app_glfw()->get_window(window);
	w->callbackCharFun(/*window, */codepoint);
}
void			THIS::__init()
{
	glfwSetErrorCallback(static_error_fun);
	//try {
		glfwInit();
		getParent()->flag_.set(neb::fnd::app::util::flag::INIT_GLFW);
	//} catch(std::exception& e);
}
void			THIS::init_glew()
{
	if(!getParent()->flag_.any(neb::fnd::app::util::flag::INIT_GLEW))
	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("GLEW: %s\n", glewGetErrorString(err));
			exit(EXIT_FAILURE);
		}

		getParent()->flag_.set(neb::fnd::app::util::flag::INIT_GLEW);
	}
}
void			THIS::release()
{
}
void			THIS::step(gal::etc::timestep const & ts)
{
	//neb::gfx::window::util::parent::step(ts);
}
neb::fnd::window::Base*			THIS::get_window(GLFWwindow* window)
{
	auto it = windows_glfw_.find(window);
	assert(it != windows_glfw_.cend());
	auto w = it->second.lock();
	assert(w);

	return w.get();
}
void							THIS::onFirstContext()
{
	if(getParent()->flag_.any(neb::fnd::app::util::flag::FIRST_CONTEXT)) return;
	getParent()->flag_.set(neb::fnd::app::util::flag::FIRST_CONTEXT);
	
	/* Print version info */
	GLubyte const *vendor_string = glGetString(GL_VENDOR);
	GLubyte const *renderer_string = glGetString(GL_RENDERER);
	GLubyte const *version_string = glGetString(GL_VERSION);
	GLubyte const *shading_lang_version_string = glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLubyte const *extensions_string = glGetString(GL_EXTENSIONS);

	printf("OpenGL Vendor:                   %s\n", vendor_string);
	printf("OpenGL Renderer:                 %s\n", renderer_string);
	printf("OpenGL Version:                  %s\n", version_string);
	printf("OpenGL Shading Language Version: %s\n", shading_lang_version_string);
	printf("OpenGL Extensions:               %s\n", extensions_string);
	
	//exit(0);	
}
void							THIS::update_joysticks()
{
	for(int i = 0; i <= GLFW_JOYSTICK_LAST; i++) {
		_M_joystick_state[i].update();
	}
}
neb::gfx::app::glfw*					THIS::get_gfx_app_glfw()
{
	auto a = neb::fnd::app::Base::g_app_;
	assert(a);
	
	auto go = a->G::get_object();

	auto g = std::dynamic_pointer_cast<neb::gfx::app::glfw>(go);
	assert(g);
	return g.get();
}


