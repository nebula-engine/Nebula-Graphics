#ifndef __GRU_WINDOW___BASE_H__
#define __GRU_WINDOW___BASE_H__

#include <gal/stl/child.hpp>

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx { namespace window {

	class __base:
		virtual public neb::core::itf::shared
	{
		public:
			virtual void		render() = 0;
	};

}}}


#endif










