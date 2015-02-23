#ifndef NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH
#define NEBULA_CORE_LIGHT_GFX_UTIL_PARENT_HH

#include <neb/fnd/core/light/util/light_count.hpp>
#include <neb/fnd/core/light/util/parent.hpp>

namespace neb { namespace gfx { namespace core { namespace light { namespace util {

	class parent:
		virtual public neb::fnd::core::light::util::parent
	{
		public:
			virtual ~parent() {}
			void			setPose(
					neb::fnd::math::pose const & pose);
			void			load_lights(
					neb::fnd::core::light::util::count & light_count,
					neb::fnd::math::pose const & pose);
	};

}}}}}

#endif

