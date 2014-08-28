
#include <neb/gfx/environ/shadow_directional.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
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

	std::shared_ptr<neb::gfx::core::light::directional> light;

	auto p2 = std::dynamic_pointer_cast<neb::gfx::environ::shadow_directional>(parent);
	auto p3 = std::dynamic_pointer_cast<neb::gfx::environ::vis_depth>(parent);
	if(p2) {
		light = p2->light_.lock();
		assert(light);
	} else if(p3) {
		light = p3->light_.lock();
		assert(light);
	}

	assert(light);


	//auto light = light_.lock();
	//assert(light);
	
	glm::vec3 eye(22.5, -30, 30);
	//glm::vec3 eye(5.0, 30, -30);
	//glm::vec3 eye(0.0, 0, 0);
	glm::vec3 center = light->pos_ + eye;
	glm::vec3 up(0,1,0);
	
	return glm::lookAt(eye, center, up);

}
void					neb::gfx::camera::view::shadow_directional::step(gal::etc::timestep const & ts) {
}




