#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/Ridealong.hpp>



neb::gfx::camera::view::ridealong::ridealong(
		std::shared_ptr<neb::gfx::environ::base> parent,
		weak_ptr<neb::fnd::core::actor::base> actor):
	neb::gfx::camera::view::base(parent),
	actor_(actor)
{
}
glm::mat4		neb::gfx::camera::view::ridealong::view()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	auto actor = actor_.lock();
	if(!actor) return glm::mat4();

	glm::vec3 translate_vec(actor->pose_.pos_);
	glm::quat rotation(actor->pose_.rot_);


	glm::vec3 offset_vec(0.0,-1.0,-4.0);

	offset_vec = rotation * offset_vec;


	glm::mat4 ret = glm::affineInverse(actor->pose_.mat4_cast());
	
	ret = glm::translate(ret, offset_vec);
	
	return glm::mat4(ret);
}
void neb::gfx::camera::view::ridealong::step(gal::etc::timestep const & ts)
{	
}

