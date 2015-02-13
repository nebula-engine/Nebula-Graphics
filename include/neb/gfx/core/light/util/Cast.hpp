#ifndef NEB_GFX_CORE_LIGHT_UTIL_CAST_HPP
#define NEB_GFX_CORE_LIGHT_UTIL_CAST_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/core/light/util/decl.hpp>

namespace neb { namespace gfx { namespace core { namespace light { namespace util {
	class Cast:
		virtual public neb::fnd::itf::shared
	{
		public:
			typedef neb::gfx::core::light::base		B;
			typedef neb::gfx::core::light::spot		S;
			typedef neb::gfx::core::light::point		P;
			typedef neb::gfx::core::light::directional	D;
			std::shared_ptr<B>	is_gfx_light_base();
			std::shared_ptr<S>	is_gfx_light_spot();
			std::shared_ptr<P>	is_gfx_light_point();
			std::shared_ptr<D>	is_gfx_light_directional();
	};
}}}}}

#endif
