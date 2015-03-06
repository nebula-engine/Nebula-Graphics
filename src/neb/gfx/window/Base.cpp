#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <map>

#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/scene/util/decl.hpp>
#include <neb/fnd/core/actor/Base.hpp>
#include <neb/fnd/core/light/base.hpp>
#include <neb/fnd/context/Window.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/opengl/png.hpp>
#include <neb/gfx/app/glfw.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/app/base.hpp>
#include <neb/gfx/camera/view/Base.hpp>
#include <neb/gfx/context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/window/util/Parent.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/app/base.hpp>

typedef neb::gfx::window::Base THIS;

GLFWwindow* THIS::first_window_ = NULL;

THIS::Base():
	x_(1200),
	y_(0),
	w_(600),
	h_(600),
	window_(NULL)
{
}
THIS::~Base()
{
}
void			THIS::init(parent_t * const & p)
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);

	if(p == NULL) return;

	setParent(p);
	
	auto app = get_fnd_app();

	if(!app->flag_.any(neb::fnd::app::util::flag::INIT_GLFW))
	{
		printv(WARNING, "glfw not initializaed\n");
		return;
	}
	
	auto g = std::dynamic_pointer_cast<neb::gfx::app::Base>(app->G::get_object());

	//auto self = std::dynamic_pointer_cast<THIS>(shared_from_this());
	
	if(window_) return;

	// create window
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	window_ = glfwCreateWindow(
			w_,
			h_,
			title_.c_str(),
			NULL,
			first_window_
			);

	if(first_window_ == NULL) {
		first_window_ = window_;
	}

	if(window_ == NULL) {
		glfwTerminate();
		printv(DEBUG, "glfwCreateWindow failed\n");
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(window_, x_, y_);

	glfwMakeContextCurrent(window_);

	glfwSetWindowPosCallback(
			window_,
			neb::gfx::app::glfw::static_window_pos_fun);
	glfwSetWindowSizeCallback(
			window_,
			neb::gfx::app::glfw::static_window_size_fun);
	glfwSetWindowCloseCallback(
			window_,
			neb::gfx::app::glfw::static_window_close_fun);
	glfwSetWindowRefreshCallback(
			window_,
			neb::gfx::app::glfw::static_window_refresh_fun);
	glfwSetKeyCallback(
			window_,
			neb::gfx::app::glfw::static_key_fun);
	glfwSetMouseButtonCallback(
			window_,
			neb::gfx::app::glfw::static_mouse_button_fun);
	glfwSetCharCallback(
			window_,
			neb::gfx::app::glfw::staticCharFun);

	// add window to app's window map
	g->windows_glfw_[window_] = p->is_fnd_window_base();

	//if(all(neb::app::base::option::SHADERS)) create_programs();

	g->init_glew();

	g->create_programs();

	//printf("%s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

	//Check for necessary extensions
	if(!GL_ARB_depth_texture || !GL_ARB_shadow)
	{
		printv(CRITICAL, "I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Shading states
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states

	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	checkerror("unknown");
}
void		THIS::release()
{
	printv_func(DEBUG);

	glfwDestroyWindow(window_);
}
void		THIS::render()
{
	printv_func(DEBUG);

	assert(window_ != NULL);
	glfwMakeContextCurrent(window_);

	/** @todo rendering multiple contexts in a window */

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	typedef neb::fnd::context::util::Parent C;
	typedef neb::fnd::environ::util::Parent E;

	auto lamb1 = [] (C::map_type::pointer p)
	{
		if(p->E::front()->is_fnd_environ_three()) {
			p->render();
		}
	};

	getParent()->C::for_each(lamb1);

	auto lamb2 = [] (C::map_type::pointer p)
	{
		if(p->E::front()->is_fnd_environ_two()) {
			p->render();
		}
	};

	getParent()->C::for_each(lamb2);






	glFinish();
	glfwSwapBuffers(window_);

	// screen print every frame (use for video?)
	//save_png("test.png",w_,h_);
}
void			THIS::callback_window_refresh_fun(GLFWwindow*)
{
}
void			THIS::step(gal::etc::timestep const & ts)
{
	printv_func(DEBUG);

	/// @ TODO move to fnd
	/*
	   contexts::step(ts);

	   if(glfwWindowShouldClose(window_))
	   {
	   getParent()->erase(_M_index);
	   return;
	   }
	   */
}
void			THIS::callback_window_size_fun(GLFWwindow* window, int w, int h)
{
	printv_func(DEBUG);

	w_ = w;
	h_ = h;

	resize();

	callback_window_refresh_fun(window);
}
void			THIS::callback_window_pos_fun(GLFWwindow* window, int x, int y)
{
	printv_func(DEBUG);

	x_ = x;
	y_ = y;

	callback_window_refresh_fun(window);
}
void			THIS::callback_window_close_fun(GLFWwindow* window)
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);
}
void			THIS::resize()
{
	printv(DEBUG, "%s\n", __PRETTY_FUNCTION__);

	glViewport(0, 0, w_, h_);

	typedef neb::fnd::context::util::Parent C;

	auto lamb = [&] (C::map_type::pointer p)
	{
		//auto context = std::dynamic_pointer_cast<neb::gfx::context::base>(p);
		//assert(context);
		//context->resize(w_, h_);

		p->resize(w_, h_);
	};

	getParent()->C::for_each(lamb);

}
void			THIS::makeCurrent()
{
	assert(window_ != NULL);
	glfwMakeContextCurrent(window_);
}
glm::vec2		THIS::getCursorPosNDC()
{
	return glm::vec2();
}
void			THIS::printScreen()
{
	if(screenBuffer_.capacity() < (w_ * h_ * 3u)) screenBuffer_.reserve(w_*h_*3);

	glReadPixels(
			0,
			0,
			w_,
			h_,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			(GLvoid *)&screenBuffer_[0]
		    );


	// invert pixels (stolen from SOILs source code)
	/*
	   for (int j = 0; j * 2 < h_; ++j) {
	   int x = j * w_ * 3;
	   int y = (h_ - 1 - j) * w_ * 3;
	   for (int i = w_ * 3; i > 0; --i) {
	   uint8_t tmp = screenBuffer_[x];
	   screenBuffer_[x] = screenBuffer_[y];
	   screenBuffer_[y] = tmp;
	   ++x;
	   ++y;
	   }
	   }
	   */

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"screenshot_%Y-%m-%d_%H:%M:%S.png",timeinfo);

	save_png_libpng(buffer, &screenBuffer_[0], w_, h_);
}
int		THIS::get_width()
{
	return w_;
}
int		THIS::get_height()
{
	return h_;
}


