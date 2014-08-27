
#include <neb/gfx/environ/shadow_directional.hpp>
#include <neb/gfx/camera/view/shadow_directional.hpp>
#include <neb/gfx/core/light/directional.hpp>

neb::gfx::camera::view::shadow_directional::shadow_directional(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::view::base(parent)
{
	assert(parent);

	
	//light_ = light;
	
}
glm::mat4				neb::gfx::camera::view::shadow_directional::view() {
	
	auto parent = parent_.lock();
	assert(parent);

	auto p2 = std::dynamic_pointer_cast<neb::gfx::environ::shadow_directional>(parent);
	assert(p2);

	auto light = p2->light_.lock();
	assert(light);


	//auto light = light_.lock();
	//assert(light);
	
	glm::vec3 eye;
	glm::vec3 center = light->spot_direction_ + eye;
	glm::vec3 up(0,0,1);
	
	return glm::lookAt(eye, center, up);
		
}
void					neb::gfx::camera::view::shadow_directional::step(gal::etc::timestep const & ts) {
}




