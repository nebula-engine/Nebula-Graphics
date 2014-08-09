#ifndef NEB_GFX_APP_BASE_HPP
#define NEB_GFX_APP_BASE_HPP

#include <neb/core/app/__core.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>

using namespace std;

namespace neb {
	namespace gfx {
		namespace app {
			class base:
				virtual public neb::app::__core,
				virtual public neb::app::__gfx,
				virtual public neb::app::__gfx_glsl
			{
				public:
					static weak_ptr<neb::gfx::app::base>		initialize();

					virtual void					init();
					virtual void					release();
					virtual void					step(gal::std::timestep const & ts);

					void						loop();
			};
		}
	}
}

#endif
