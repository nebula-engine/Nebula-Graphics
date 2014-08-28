#ifndef NEBULA_GRAPHICS_CONTEXT_FBO_HH
#define NEBULA_GRAPHICS_CONTEXT_FBO_HH

#include <memory>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/Context/Window.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			/** @brief Context
			 *
			 * A context with an OpenGL FBO as target.
			 *
			 * @todo allow for manual ordering of context objects in parent's context map
			 * such that things like layouts are render ON TOP of existing scene.'
			 */
			class fbo:
				public neb::gfx::context::window
			{
				public:
					fbo(std::shared_ptr<neb::gfx::window::base> parent);
					virtual void				init();
					virtual void				render();

					
					GLuint					framebuffer_;

					std::shared_ptr<neb::gfx::texture>	texture_;
			};
		}
	}
}
#endif

