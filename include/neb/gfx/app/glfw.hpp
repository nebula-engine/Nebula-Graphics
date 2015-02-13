#ifndef __NEBULA_APP_GFX_WINDOW_H__
#define __NEBULA_APP_GFX_WINDOW_H__

#include <fstream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <gal/itf/shared.hpp>

#include <neb/core/except/base.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/app/Base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/gui/layout/util/parent.hpp>
#include <neb/gfx/window/util/Parent.hpp>
#include <neb/gfx/context/util/Parent.hpp>
#include <neb/gfx/JoystickState.hpp>

namespace neb { namespace gfx { namespace app {
	/** @brief gfx
	 * 
	 * graphics and window handling
	 */
	class glfw:
		virtual public neb::fnd::app::Base,
		virtual public neb::gfx::window::util::parent
	{
		public:
			typedef std::map< GLFWwindow*, std::shared_ptr<neb::gfx::window::Base> >	glfwwindow_map_type;
			typedef std::weak_ptr<neb::fnd::window::Base>					window_w;
			static void					static_error_fun(int,char const *);
			static void					static_window_pos_fun(GLFWwindow*,int,int);
			static void					static_window_size_fun(GLFWwindow*,int,int);
			static void					static_window_close_fun(GLFWwindow*);
			static void					static_window_refresh_fun(GLFWwindow*);
			//static void					static_window_focus_fun(GLFWwindow*,int);
			//static void					static_window_iconify_fun(GLFWwindow*,int);
			//static void					static_window_buffer_size_fun(GLFWwindow*,int,int);
			static void					static_mouse_button_fun(GLFWwindow*,int,int,int);
			static void					static_key_fun(GLFWwindow*,int,int,int,int);
			static void					staticCharFun(GLFWwindow*,unsigned int);
		private:
			/**
			 * @warn do not use in python or mods
			 */
			static neb::gfx::app::glfw*			get_gfx_app_glfw();
		public:
			void						__init();
			void						init_glew();
			void						release();
			void						step(gal::etc::timestep const & ts);
			void						render();
			/*
			 * called after the first OpenGL context is created
			 */
			void						onFirstContext();
			//virtual window_w				createWindow()
			//{ throw neb::fnd::except::NotImplemented(); return window_w(); }
			window_w					get_window(GLFWwindow*);
			void						update_joysticks();
		public:
			//GLFWwindow*					currentIdleWindow_;
			glfwwindow_map_type				windows_glfw_;
			neb::gfx::JoystickState				_M_joystick_state[16];
	};
}}}

#endif
