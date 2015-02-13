#include <neb/gfx/core/light/util/Cast.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/directional.hpp>

typedef neb::gfx::core::light::util::Cast THIS;

typedef neb::gfx::core::light::base		B;
typedef neb::gfx::core::light::spot		S;
typedef neb::gfx::core::light::point		P;
typedef neb::gfx::core::light::directional	D;

std::shared_ptr<B>	THIS::is_gfx_light_base()
{
	auto l = std::dynamic_pointer_cast<B>(shared_from_this());
}
std::shared_ptr<S>	THIS::is_gfx_light_spot()
{
	auto l = std::dynamic_pointer_cast<S>(shared_from_this());
}
std::shared_ptr<P>	THIS::is_gfx_light_point()
{
	auto l = std::dynamic_pointer_cast<P>(shared_from_this());
}
std::shared_ptr<D>	THIS::is_gfx_light_directional()
{
	auto l = std::dynamic_pointer_cast<D>(shared_from_this());
}

