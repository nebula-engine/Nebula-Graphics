#ifndef __NEBULA_UI_OBJECT_BASE_HPP__
#define __NEBULA_UI_OBJECT_BASE_HPP__

#include <memory>

#include <boost/signals2.hpp>

#include <neb/core/itf/shared.hpp>
#include <neb/core/color/Color.hh>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/gui/object/util/parent.hpp>
#include <neb/gfx/gui/object/util/flag.hpp>

namespace neb {
	namespace gfx {
		namespace gui {
			namespace object {
				class base: virtual public neb::itf::shared {
					public:
						base();
						virtual ~base() {}

						virtual void			init();
						//std::shared_ptr<window::window>		get_window();
						virtual void			draw(std::shared_ptr<neb::gfx::glsl::program::base> p) = 0;

						virtual int			key_fun(
								std::shared_ptr<neb::gfx::window::base> const & window, int, int, int, int) = 0;
						virtual int			mouse_button_fun(
								std::shared_ptr<neb::gfx::window::base> const & window, int, int, int);
						virtual int			charFun(
								std::shared_ptr<neb::gfx::window::base> const & window,
								unsigned int codepoint) {return 0;}

						//virtual void			connect();
						bool				active_;


						template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
							ar & boost::serialization::make_nvp("x",x_);
							ar & boost::serialization::make_nvp("y",y_);
							ar & boost::serialization::make_nvp("w",w_);
							ar & boost::serialization::make_nvp("h",h_);
							ar & boost::serialization::make_nvp("font_color",font_color_);
							ar & boost::serialization::make_nvp("bg_color",bg_color_);
							ar & boost::serialization::make_nvp("label",label_);

						}
					public:
						std::shared_ptr<neb::gfx::gui::object::util::parent>	parent_;
						
						neb::gfx::gui::object::util::flag			flag_;

						float							x_;
						float							y_;
						float							w_;
						float							h_;

						neb::Color::color<float>				font_color_;
						neb::Color::color<float>				bg_color_;

						::std::string						label_;
						// connections
						struct
						{
							boost::signals2::connection		mouse_button_fun_;
							boost::signals2::connection		key_fun_;
						} conns_;



				};
			}
		}
	}
}
#endif









