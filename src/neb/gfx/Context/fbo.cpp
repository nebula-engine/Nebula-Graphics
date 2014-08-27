
#include <GL/glew.h>

#include <neb/gfx/free.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/texture.hpp>

neb::gfx::context::fbo::fbo(std::shared_ptr<neb::gfx::context::util::parent> parent):
	neb::gfx::context::base(parent),
	framebuffer_(0)
{}
void		neb::gfx::context::fbo::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	checkerror("unknown");

	glGenFramebuffers(1, &framebuffer_);
	checkerror("glGenFramebuffers");
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
	checkerror("glBindFramebuffer");


	texture_ = std::make_shared<neb::gfx::texture>();
	texture_->init_shadow(1024, 1024, self);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->o_, 0); checkerror("glFramebufferTexture");
	

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.
	checkerror("");

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "error with framebuffer" << std::endl;
		abort();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkerror("");

}
void		neb::gfx::context::fbo::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	assert(texture_);
	
	if(!environ_) {
		LOG(lg, neb::gfx::sl, warning) << "context has no environ";
		return;
	}
	checkerror("unknown");

	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	// Not sure, but I think these three lines should be called each time the scene is rendered
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_); checkerror("glBindFramebuffer");
	
	glBindTexture(GL_TEXTURE_2D, texture_->o_); checkerror("glBindTexture");
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->o_, 0); checkerror("glFramebufferTexture");
	

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.
	checkerror("glDrawBuffer");

	environ_->render(self);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	checkerror("glBindFramebuffer");
}


