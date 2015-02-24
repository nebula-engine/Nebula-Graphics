#ifndef __NEBULA_APP_GFX_H__
#define __NEBULA_APP_GFX_H__

#include <fstream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/plug/gfx/app/Base.hpp>
#include <neb/fnd/math/color/color.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace app {
	/** @brief gfx
	 * 
	 * graphics and window handling
	 */
	class draw:
		virtual public neb::fnd::plug::gfx::app::Base
	{
		public:
			void			__init();
			void			release();
			void			step(gal::etc::timestep const & ts);
			//void			render();
			void			draw_quad(
					float x,
					float y,
					float w,
					float h,
					neb::fnd::math::color::color color);
			void			draw_text(
					float x,
					float y,
					float sx,
					float sy,
					neb::fnd::math::color::color color,
					std::string text,
					std::string::size_type cursor_pos);
			// replaced with gal::parent::create()
			//		std::weak_ptr<neb::gfx::gui::layout::base>	createLayout();
			//		std::weak_ptr<neb::gfx::window::base>		createWindow();
		public:
			//GLFWwindow*								currentIdleWindow_;
			FT_Library								ft_;
			FT_Face									face_;
	};
}}}

#endif
