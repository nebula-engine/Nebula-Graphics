#ifndef __GRU_WINDOW_H__
#define __GRU_WINDOW_H__

#include <functional>
#include <vector>
#include <map>

#include <gal/etc/timestep.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/core/scene/util/decl.hpp>

#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/glsl/program.hpp>
#include <neb/gfx/glsl/shader.hh>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/window/__base.hpp>
#include <neb/gfx/window/util/Flag.hh>
#include <neb/gfx/window/util/Cast.hh>
#include <neb/gfx/window/util/signals.hpp>

namespace neb { namespace gfx { namespace window {
			class base:
				virtual public neb::gfx::window::__base,
				virtual public neb::gfx::context::util::parent,
				virtual public neb::gfx::window::util::cast
			{
				public:
					base();
					base(std::shared_ptr<neb::gfx::window::util::parent> parent);
					virtual ~base();
				
				public:
					virtual void				init();
					virtual void				release();
	
					/** @name Main Loop @{ */
					void					render();
					void					step(gal::etc::timestep const & ts);
					/** @} */
					void					resize();
	
					void					callback_window_pos_fun(GLFWwindow*,int,int);
					void					callback_window_size_fun(GLFWwindow*,int,int);
					void					callback_window_close_fun(GLFWwindow*);
					void					callback_window_refresh_fun(GLFWwindow*);
					void					callback_mouse_button_fun(GLFWwindow*,int,int,int);
					void					callback_key_fun(GLFWwindow*,int,int,int,int);
					void					callbackCharFun(GLFWwindow*,unsigned int);
					weak_ptr<neb::gfx::context::window>	createContextTwo();
					weak_ptr<neb::gfx::context::window>	createContextThree();
				public:
					std::shared_ptr<neb::gfx::window::util::parent>			parent_;
					/** @brief self
					 *
					 * avoid casting shared_from_this
					 */
					std::shared_ptr<neb::gfx::window::base>		self_;

					// input signals
					struct
					{
						neb::gfx::window::signals::KeyFun		key_fun_;
						neb::gfx::window::signals::MouseButtonFun	mouse_button_fun_;
						neb::gfx::window::signals::CharFun		charFun_;
					} sig_;


					
					
	
					neb::gfx::window::util::Flag	flag_;
					int					x_;
					int					y_;
					int					w_;
					int					h_;
					::std::string				title_;
					
					
					GLFWwindow*		window_;
					
					//int			windowID;
	
				public:

			};
		}
	}
}


#endif








