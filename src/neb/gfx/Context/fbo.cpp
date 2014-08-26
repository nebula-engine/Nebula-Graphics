
#include <GL/glew.h>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/environ/base.hpp>

void		neb::gfx::context::fbo::init() {
	
	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	GLuint framebuffer_ = 0;
	glGenFramebuffers(1, &framebuffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);


	texture_ = std::make_shared<neb::gfx::texture>();
	texture_->init_shadow(1024, 1024, self);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->o_, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "error with framebuffer" << std::endl;
		abort();
	}
}
void		neb::gfx::context::fbo::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	if(!environ_) return;

	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	// Not sure, but I think these three lines should be called each time the scene is rendered
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_->o_, 0);
	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

	environ_->render(self);
}


