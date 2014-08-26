
#include <glm/gtc/matrix_transform.hpp>

#include <neb/gfx/camera/proj/ortho.hpp>


neb::gfx::camera::proj::ortho::ortho(std::shared_ptr<neb::gfx::environ::base> parent):
	neb::gfx::camera::proj::base(parent),
	left_(0),
	right_(10),
	bottom_(0),
	top_(10),
	near_(1),
	far_(1000)
{

}
glm::mat4			neb::gfx::camera::proj::ortho::proj() {
	return glm::ortho(left_, right_, bottom_, top_, near_, far_);
}
void				neb::gfx::camera::proj::ortho::step(gal::etc::timestep const & ts) {
	
}

