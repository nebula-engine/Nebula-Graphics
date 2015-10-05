#include <neb/gfx/core/light/util/Cast.hpp>
#include <neb/gfx/core/light/Base.hpp>
#include <neb/gfx/core/light/Spot.hpp>
#include <neb/gfx/core/light/Point.hpp>
#include <neb/gfx/core/light/Directional.hpp>

typedef neb::gfx::core::light::util::Cast THIS;

typedef neb::gfx::core::light::Base		B;
typedef neb::gfx::core::light::Spot		S;
typedef neb::gfx::core::light::Point		P;
typedef neb::gfx::core::light::Directional	D;

std::shared_ptr<B>	THIS::is_gfx_light_base()
{
	auto l = std::dynamic_pointer_cast<B>(shared_from_this());
	return l;
}
std::shared_ptr<S>	THIS::is_gfx_light_spot()
{
	auto l = std::dynamic_pointer_cast<S>(shared_from_this());
	return l;
}
std::shared_ptr<P>	THIS::is_gfx_light_point()
{
	auto l = std::dynamic_pointer_cast<P>(shared_from_this());
	return l;
}
std::shared_ptr<D>	THIS::is_gfx_light_directional()
{
	auto l = std::dynamic_pointer_cast<D>(shared_from_this());
	return l;
}

