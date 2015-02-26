#include <neb/fnd/camera/view/Base.hpp>
#include <neb/fnd/camera/view/shadow/Directional.hpp>

#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/camera/view/shadow/directional.hpp>
#include <neb/gfx/core/light/directional.hpp>

typedef neb::gfx::camera::view::shadow::Directional THIS;

THIS::Directional()
{
}
glm::mat4				neb::gfx::camera::view::shadow::Directional::view()
{
	/*
	auto parent = getParent()->is_fnd_camera_view_shadow_directional();
	assert(parent);

	std::shared_ptr<neb::fnd::core::light::directional> light = parent->get_light();

	auto p2 = std::dynamic_pointer_cast<neb::gfx::environ::shadow::directional>(parent);
	auto p3 = std::dynamic_pointer_cast<neb::gfx::environ::vis_depth>(parent);
	if(p2) {
		light = p2->light_.lock();
		assert(light);
	} else if(p3) {
		light = std::dynamic_pointer_cast<neb::gfx::core::light::directional>(p3->light_.lock());
		assert(light);
	}

	assert(light);


	//auto light = light_.lock();
	//assert(light);
	
	//glm::vec3 look = light->pos_;
	glm::vec3 look = -light->pose_.pos_;
	
	glm::vec3 scene_center(22.5,0,0);
	
	glm::vec3 eye = scene_center - look * 30.0f;
	//glm::vec3 eye(22.5, -30, 30);
	
	//glm::vec3 eye(5.0, 30, -30);
	//glm::vec3 eye(0.0, 0, 0);
	
	glm::vec3 center = look + eye;
	glm::vec3 up(0,1,0);
	
	return glm::lookAt(eye, center, up);
	*/
	abort();
	return glm::mat4();
}
void					neb::gfx::camera::view::shadow::Directional::step(gal::etc::timestep const & ts)
{
}




