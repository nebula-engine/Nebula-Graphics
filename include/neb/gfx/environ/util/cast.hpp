#ifndef NEBULA_GFX_ENVIRON_UTIL_CAST_HPP
#define NEBULA_GFX_ENVIRON_UTIL_CAST_HPP

#include <neb/fnd/itf/shared.hpp>

#include <neb/gfx/environ/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx { namespace environ { namespace util {

	class cast:
		virtual public neb::fnd::itf::shared
	{
		public:
			std::shared_ptr<neb::gfx::environ::Two>		isEnvironTwo();
			std::shared_ptr<neb::gfx::environ::three>	isEnvironThree();
	};

}}}}

#endif
