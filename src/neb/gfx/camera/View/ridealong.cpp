#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

//#include <gal/log/log.hpp> removed by c_header_checker

//#include <neb/fnd/util/debug.hpp> removed by c_header_checker
#include <neb/fnd/core/actor/base.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/Ridealong.hpp>

typedef neb::gfx::camera::view::Ridealong THIS;

THIS::Ridealong()
{
}
/*
void			THIS::init(parent_t * const & p)
{
	setParent(p);
}
*/
glm::mat4		THIS::view()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto cam = getParent()->is_fnd_camera_view_ridealong();
	assert(cam);

	auto actor = cam->actor_.lock();
	if(!actor) return glm::mat4();

	glm::vec3 translate_vec(actor->pose_.pos_);
	glm::quat rotation(actor->pose_.rot_);


	glm::vec3 offset_vec(0.0,-1.0,-4.0);

	offset_vec = rotation * offset_vec;


	glm::mat4 ret = glm::affineInverse(actor->pose_.mat4_cast());
	
	ret = glm::translate(ret, offset_vec);
	
	return glm::mat4(ret);
}
void			THIS::step(gal::etc::timestep const & ts)
{	
}

