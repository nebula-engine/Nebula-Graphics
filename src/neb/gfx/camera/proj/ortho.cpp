#include <glm/gtc/matrix_transform.hpp>

#include <neb/gfx/camera/proj/ortho.hpp>

typedef neb::gfx::camera::proj::Ortho THIS;

THIS::Ortho():
	left_(-30),
	right_(30),
	bottom_(-30),
	top_(30),
	near_(0),
	far_(100)
{
}
glm::mat4&			neb::gfx::camera::proj::Ortho::proj() {
	return _M_matrix;
}
void				neb::gfx::camera::proj::Ortho::set(
		float l,
		float r,
		float b,
		float t,
		float n,
		float f
		)
{
	left_ = l;
	right_ = r;
	bottom_ = b;
	top_ = t;
	near_ = n;
	far_ = f;

	calculate();
}
void				neb::gfx::camera::proj::Ortho::calculate()
{
	_M_matrix = glm::ortho(left_, right_, bottom_, top_, near_, far_);

	calculate_geometry();
}
void				neb::gfx::camera::proj::Ortho::step(gal::etc::timestep const & ts) {
	
}

