#ifndef NEB_GFX_TMP_CHILD_HPP
#define NEB_GFX_TMP_CHILD_HPP

#include <neb/core/tmp/Child.hpp>

#include <neb/gfx/app/util/decl.hpp>

namespace neb { namespace gfx { namespace tmp {
	template<class T> class Child:
		virtual public neb::fnd::tmp::Child<T>
	{
		public:
		neb::gfx::app::Base* const	get_gfx_app()
		{
			auto a = neb::fnd::tmp::Child<T>::get_fnd_app();
			auto g = dynamic_cast<neb::gfx::app::Base*>(a);
			assert(g);
			return g;
		}
	};
}}}

#endif
