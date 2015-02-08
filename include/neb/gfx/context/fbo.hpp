#ifndef NEBULA_GRAPHICS_CONTEXT_FBO_HH
#define NEBULA_GRAPHICS_CONTEXT_FBO_HH

#include <memory>

#include <neb/core/context/FBO.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/context/Window.hpp>

namespace neb { namespace gfx { namespace context {
	/** @brief Context
	 *
	 * A context with an OpenGL FBO as target.
	 *
	 * @todo allow for manual ordering of context objects in parent's context map
	 * such that things like layouts are render ON TOP of existing scene.'
	 */
	class fbo:
		virtual public neb::fnd::context::FBO,
		virtual public neb::gfx::context::Window
	{
		public:
			fbo();
			virtual void				init(parent_t * const & p);
			virtual void				render();

			/**
			 * implemented by neb::fin::environ::util::Parent
			 */
			virtual std::weak_ptr<neb::fnd::environ::shadow::Directional>		createEnvironShadowDirectional() = 0;

			GLuint					framebuffer_;

			std::weak_ptr<neb::gfx::texture>	texture_;
			GLint					layer_;
	};
}}}

#endif

