#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <neb/core/util/parent.hpp>
#include <neb/gfx/window/util/Cast.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			namespace util {
				class parent:
					virtual public neb::util::parent<neb::gfx::context::base>,
					virtual public neb::gfx::window::util::cast
				{
					public:
						virtual void			__init() {}
						virtual void			release() {}
						virtual void			step(gal::etc::timestep const & ts) { neb::util::parent< neb::gfx::context::base >::step(ts); }
						virtual void			render();
						
						std::weak_ptr<neb::gfx::context::fbo>	createContextFBO();
				};
			}
		}
	}
}

#endif





