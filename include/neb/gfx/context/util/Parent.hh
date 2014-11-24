#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <neb/core/util/parent.hpp>
#include <neb/gfx/window/util/Cast.hh>
#include <neb/gfx/context/Base.hh>
#include <neb/gfx/context/util/decl.hpp>

namespace neb { namespace gfx { namespace context { namespace util {

	class parent:
		virtual public neb::core::util::parent<neb::gfx::context::base, parent>,
		virtual public neb::gfx::window::util::cast
	{
		public:
			typedef neb::gfx::context::window C_W;

		public:

			//virtual void			init();
			//virtual void			release();
			//virtual void			step(gal::etc::timestep const & ts);
			virtual void			render();

			virtual std::weak_ptr<neb::gfx::context::fbo>		createContextFBO() = 0;
			virtual std::weak_ptr<neb::gfx::context::fbo_multi>	createContextFBOMulti() = 0;
			virtual std::weak_ptr<C_W>				createContextWindow() = 0;
			virtual std::weak_ptr<C_W>				createContextVisDepth() = 0;
	};
}}}}

#endif





