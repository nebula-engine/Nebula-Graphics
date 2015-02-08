
#include <neb/gfx/camera/proj/util/cast.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/proj/ortho.hpp>

typedef neb::gfx::camera::proj::util::cast THIS;

std::shared_ptr<neb::gfx::camera::proj::Perspective>	THIS::isPerspective()
{
	return std::dynamic_pointer_cast<neb::gfx::camera::proj::Perspective>(shared_from_this());
}
std::shared_ptr<neb::gfx::camera::proj::Ortho>		THIS::isOrtho()
{
	return std::dynamic_pointer_cast<neb::gfx::camera::proj::Ortho>(shared_from_this());
}

