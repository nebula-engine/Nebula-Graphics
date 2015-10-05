#ifndef NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH

#include <gal/stl/verbosity.hpp>

#include <neb/fnd/core/light/util/light_count.hpp>
#include <neb/fnd/core/light/util/parent.hpp>

namespace neb { namespace gfx { namespace core { namespace light { namespace util {
	class parent:
		public gal::tmp::Verbosity<neb::gfx::core::light::util::parent>,
		virtual public neb::fnd::core::light::util::parent
	{
		public:
			using gal::tmp::Verbosity<neb::gfx::core::light::util::parent>::printv;
			virtual ~parent();
			void			setPose(
					gal::math::pose const & pose);
			void			load_lights(
					neb::fnd::core::light::util::count & light_count,
					gal::math::pose const & pose);
	};
}}}}}

#endif

