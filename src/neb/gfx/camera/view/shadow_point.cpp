#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/core/light/Point.hpp>

typedef neb::gfx::camera::view::shadow::Point THIS;

THIS::Point()
{
	//light_ = light;
}
/*
void			THIS::init(parent_t * const & p)
{
	setParent(p);
}
*/
glm::mat4		THIS::view()
{
/*
	auto parent = getParent();

	std::shared_ptr<neb::gfx::core::light::point> light;

	auto p2 = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(parent);
	auto p3 = std::dynamic_pointer_cast<neb::gfx::environ::vis_depth>(parent);
	if(p2) {
		light = p2->light_.lock();
		assert(light);
	} else if(p3) {
		light = std::dynamic_pointer_cast<neb::gfx::core::light::point>(p3->light_.lock());
		assert(light);
	}

	assert(light);
	
	glm::vec3 eye = light->getPoseGlobal().pos_;

	return glm::lookAt(eye, eye + look_, up_);
*/
	abort();
	return glm::mat4();
}
void			THIS::step(gal::etc::timestep const & ts)
{
}




