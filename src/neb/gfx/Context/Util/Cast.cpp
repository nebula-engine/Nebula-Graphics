#include <neb/gfx/Context/Util/Cast.hh>
#include <neb/gfx/Context/Base.hh>

std::shared_ptr<neb::gfx::context::base>		neb::gfx::context::util::cast::isContextBase() {
	return std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
}

