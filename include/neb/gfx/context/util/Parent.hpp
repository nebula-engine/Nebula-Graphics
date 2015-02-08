#ifndef NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH
#define NEBULA_GRAPHICS_CONTEXT_UTIL_PARENT_HH

#include <neb/core/context/util/decl.hpp>
#include <neb/core/context/util/Parent.hpp>

#include <neb/gfx/window/util/Cast.hpp>
#include <neb/gfx/context/Base.hpp>
#include <neb/gfx/context/util/decl.hpp>

namespace neb { namespace gfx { namespace context { namespace util {

	class parent:
		virtual public neb::fnd::context::util::Parent,
		virtual public neb::gfx::window::util::cast
	{
		public:
			typedef neb::fnd::context::Window C_W;

		public:
			//virtual void			init();
			//virtual void			release();
			//virtual void			step(gal::etc::timestep const & ts);
			virtual void			render();

			/**
			 *
			 * implemented by neb::fin::context::util::Parent
			 */
			virtual std::weak_ptr<neb::fnd::context::FBO>		createContextFBO() = 0;
			virtual std::weak_ptr<neb::fnd::context::FBOM>		createContextFBOMulti() = 0;
			virtual std::weak_ptr<C_W>				createContextWindow() = 0;
			virtual std::weak_ptr<C_W>				createContextVisDepth() = 0;

			virtual std::weak_ptr<C_W>				createContextTwo();
			virtual std::weak_ptr<C_W>				createContextThree();
			virtual std::weak_ptr<C_W>				createContextNormalMap();
	};
}}}}

#endif





