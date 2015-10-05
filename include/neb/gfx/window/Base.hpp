#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <gal/etc/timestep.hpp>
#include <gal/stl/verbosity.hpp>

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/core/scene/util/decl.hpp>
#include <neb/fnd/plug/gfx/window/Base.hpp>

#include <neb/gfx/app/util/decl.hpp>
#include <neb/gfx/tmp/Child.hpp>
#include <neb/gfx/context/Base.hpp>
#include <neb/gfx/context/util/Parent.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture/Base.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/window/util/Flag.hpp>
#include <neb/gfx/window/util/Cast.hpp>

namespace neb { namespace gfx { namespace window {
	class Base:
		public gal::tmp::Verbosity<neb::gfx::window::Base>,
		virtual public gal::enable_shared_from_this<neb::gfx::window::Base>,
		virtual public neb::fnd::plug::gfx::window::Base,
		virtual public neb::gfx::window::util::cast
	{
		public:
			friend class neb::gfx::app::glfw;
			using gal::enable_shared_from_this<neb::gfx::window::Base>::shared_from_this;
			//typedef neb::gfx::window::util::parent parent_t;
			//typedef neb::fnd::util::parent<neb::fnd::context::Base, neb::fnd::context::util::Parent> contexts;
			Base();
			virtual ~Base();
			virtual void				init(parent_t * const & p);
			virtual void				release();
			virtual glm::vec2			getCursorPosNDC();
			virtual void				render();
			virtual void				step(gal::etc::timestep const & ts);
			void					resize();
			void					callback_window_pos_fun(GLFWwindow*,int,int);
			void					callback_window_size_fun(GLFWwindow*,int,int);
			void					callback_window_close_fun(GLFWwindow*);
			void					callback_window_refresh_fun(GLFWwindow*);
			void					callback_mouse_button_fun(GLFWwindow*,int,int,int);
			void					callback_key_fun(GLFWwindow*,int,int,int,int);
			void					callbackCharFun(GLFWwindow*,unsigned int);
			virtual int				get_width();
			virtual int				get_height();
			virtual void				makeCurrent();
			void					printScreen();
			static GLFWwindow*			first_window_;
			neb::gfx::window::util::Flag		flag_;
			int					x_;
			int					y_;
			int					w_;
			int					h_;
			::std::string				title_;


			GLFWwindow*		window_;

			//int			windowID;

			// persistent buffer for screen print
			std::vector<unsigned char>		screenBuffer_;

		public:

	};
}}}

#endif
