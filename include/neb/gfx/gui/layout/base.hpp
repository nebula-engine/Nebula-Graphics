#ifndef __NEBULA_UI_LAYOUT_BASE_HPP__
#define __NEBULA_UI_LAYOUT_BASE_HPP__

#include <map>

#include <glm/glm.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/gui/object/Base.hh>
#include <neb/gfx/gui/object/util/parent.hpp>
#include <neb/gfx/drawable/base.hpp>
//#include <neb/gfx/window/Base.hh>

namespace neb {namespace gfx {namespace gui {namespace layout {
	/** @brief %Base */
	class base:
		virtual public neb::itf::shared,
		virtual public neb::gfx::drawable::base,
		virtual public neb::gfx::gui::object::util::parent
	{
		public:
			//base();
			base(std::shared_ptr<neb::gfx::gui::layout::util::parent> parent);

			virtual void				init();
			virtual void				release() {}


			/** @brief Main Loop @{ */
			virtual void					step(gal::etc::timestep const & ts);
			virtual void					draw(
					std::shared_ptr<neb::gfx::context::base> context,
					std::shared_ptr<neb::gfx::glsl::program::base> p);
			/** @} */

			void						connect(
					std::shared_ptr<neb::gfx::window::base> const & window);
			int						search(
					std::shared_ptr<neb::gfx::window::base> const & ,int button, int action, int mods);
			int						mouse_button_fun(
					std::shared_ptr<neb::gfx::window::base> const & ,int button, int action, int mods);
			int						key_fun(
					std::shared_ptr<neb::gfx::window::base> const & ,int,int,int,int);
			int						charFun(
					std::shared_ptr<neb::gfx::window::base> const & window,
					unsigned int codepoint);
			std::weak_ptr<neb::gfx::gui::object::terminal>	createObjectTerminal();
		public:
			glm::mat4x4					ortho_;


			std::shared_ptr<neb::gfx::gui::layout::util::parent>	parent_;
			// connections
			struct
			{
				boost::signals2::connection		mouse_button_fun_;
				boost::signals2::connection		key_fun_;
				boost::signals2::connection		charFun_;
			} conns_;


	};
}}}}

#endif



