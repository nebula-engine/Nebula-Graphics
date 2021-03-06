
#include <GL/glew.h>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/texture/Base.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/window/Base.hpp>

typedef neb::gfx::context::fbo_multi THIS;

THIS::fbo_multi():
	framebuffer_(0)
{
	layer_ = 0;
	layer_count_ = 6;
}
void		neb::gfx::context::fbo_multi::init(parent_t * const & p)
{
	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	checkerror("unknown");

	glGenFramebuffers(1, &framebuffer_);
	checkerror("glGenFramebuffers");
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
	checkerror("glBindFramebuffer");


	//texture_ = std::make_shared<neb::gfx::texture>();
	//texture_->init_shadow(2048, 2048, self);

	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->o_, 0); checkerror("glFramebufferTexture");
	

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.
	checkerror("");

/*	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "error with framebuffer" << std::endl;
		abort();
	}*/

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkerror("");

}
void		neb::gfx::context::fbo_multi::render()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	auto tex = texture_.lock();
	assert(tex);

	auto env = getParent()->neb::fnd::environ::util::Parent::front();

	if(!env) {
		LOG(lg, neb::gfx::sl, warning) << "context has no environ";
		return;
	}
	checkerror("unknown");

	//if(!env->shouldRender()) return;

	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(env);
	assert(e);

	//assert(environ_->program_);
	//environ_->program_->use();

	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	for(unsigned int c = 0; c < layer_count_; c++) {

		if(!e->shouldRender(c)) return;
	

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
		checkerror("glBindFramebuffer\n");

		glBindTexture(GL_TEXTURE_2D_ARRAY, tex->o_);
		checkerror("glBindTexture\n");

		glFramebufferTextureLayer(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				tex->o_,
				0,
				c);
		checkerror("glFramebufferTexture\n");

		glDrawBuffer(GL_NONE);
		checkerror("glDrawBuffer");

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "error with framebuffer" << std::endl;
			abort();
		}

		glViewport(0, 0, tex->w_, tex->h_);

		e->render(self,c);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkerror("glBindFramebuffer");
}
void			THIS::setTexture(std::shared_ptr<neb::fnd::itf::shared> texture)
{
	auto t = std::dynamic_pointer_cast<neb::gfx::texture::Base>(texture);
	assert(t);
	texture_ = t;
}

