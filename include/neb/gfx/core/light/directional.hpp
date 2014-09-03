#ifndef NEBULA_LIGHT_DIRECTIONAL_HH
#define NEBULA_LIGHT_DIRECTIONAL_HH


#include <neb/gfx/core/light/base.hpp>

namespace neb { namespace gfx { namespace core { namespace light {

	class directional: virtual public neb::gfx::core::light::base {
		public:
			directional(std::shared_ptr<neb::core::core::light::util::parent> parent);
			virtual void	init();
			virtual void	setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ);

	};


}}}}

#endif
