#ifndef NEBULA_GRAPHICS_CONTEXT_FBO_MULTI_HPP
#define NEBULA_GRAPHICS_CONTEXT_FBO_MULTI_HPP

#include <memory>

#include <neb/fnd/context/FBOM.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture/util/decl.hpp>
#include <neb/gfx/context/Window.hpp>

namespace neb { namespace gfx { namespace context {
	/** @brief Context
	 *
	 * A context with an OpenGL FBO as target.
	 *
	 * @todo allow for manual ordering of context objects in parent's context map
	 * such that things like layouts are render ON TOP of existing scene.'
	 */
	class fbo_multi:
		//virtual public neb::fnd::context::FBOM,
		virtual public neb::gfx::context::Window
	{
		public:
			fbo_multi();
			virtual void				init(parent_t * const & p);
			virtual void				render();

			virtual std::weak_ptr<neb::fnd::environ::shadow::Directional>		createEnvironShadowDirectional() = 0;

			virtual void				setTexture(std::shared_ptr<neb::fnd::itf::shared> texture);

			GLuint					framebuffer_;

			std::weak_ptr<neb::gfx::texture::Base>	texture_;
			GLint*					layer_;
			GLuint					layer_count_;
	};
}}}

#endif
