#ifndef NEB_GFX_TEXTURE_UTIL_PARENT_HPP
#define NEB_GFX_TEXTURE_UTIL_PARENT_HPP

#include <neb/gfx/core/light/util/Cast.hpp>

namespace neb { namespace gfx { namespace texture { namespace util {
	class Parent:
		virtual public neb::gfx::core::light::util::Cast
	{
		public:
			neb::fnd::app::Base*		get_fnd_app();
	};
}}}}

#endif
