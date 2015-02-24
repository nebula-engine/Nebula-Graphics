
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <gal/log/log.hpp>

//#include <neb/fnd/util/debug.hpp> removed by c_header_checker
//#include <neb/fnd/input/source.hpp>

//#include <neb/gfx/window/Base.hpp> removed by c_header_checker
#include <neb/gfx/camera/view/Manual.hpp>
#include <neb/gfx/util/log.hpp>

typedef neb::gfx::camera::view::manual THIS;

THIS::manual():
	eye_(0, 0, 30),
	center_(0, 0, 0),
	up_(0, 1, 0)
{
}
void			THIS::init(parent_t * const & p)
{
	setParent(p);
}
void			THIS::step(gal::etc::timestep const & ts)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
glm::mat4		THIS::view()
{
	//printf("%s\n", __FUNCTION__);

	glm::mat4 ret = glm::lookAt(eye_, center_, up_);

	return ret;
}


