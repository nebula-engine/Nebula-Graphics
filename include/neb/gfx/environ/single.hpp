#ifndef NEBULA_GFX_ENVIRON_SINGLE_HPP
#define NEBULA_GFX_ENVIRON_SINGLE_HPP

#include <neb/gfx/environ/base.hpp>

namespace neb { namespace gfx { namespace environ {
	/***/
	template<typename VIEW> class single:
		virtual public neb::gfx::environ::base
	{
		public:
			//std::shared_ptr<VIEW>		view_;
	};
	/***/
	template<typename VIEW> class multiple:
		virtual public neb::gfx::environ::base
	{
		public:
			//std::shared_ptr<VIEW>		view_[6];
	};
}}}


#endif
