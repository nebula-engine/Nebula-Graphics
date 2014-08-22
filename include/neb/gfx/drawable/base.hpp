#ifndef NEBULA_GRAPHICS_DRAWABLE_BASE_HPP
#define NEBULA_GRAPHICS_DRAWABLE_BASE_HPP

#include <neb/core/itf/shared.hpp>

#include <neb/gfx/glsl/util/decl.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			class base;
		}
		namespace drawable {
			/** @brief %drawable
			 * 
			 * Contains content to draw in a context (scene, layout, etc.).
			 */
			class base: virtual public neb::itf::shared {
				public:
					virtual void			init() = 0;
					/** @brief draw
					 *
					 * @param context context in which we are drawing. used by shape to keep track of vertex buffers for various contexts.
					 *
					 * draw into prepared rendering context
					 */
					virtual void			draw(
							std::shared_ptr<neb::gfx::context::base> context,
							std::shared_ptr<neb::gfx::glsl::program::base> p) = 0;
			};
			class two: virtual public neb::gfx::drawable::base {
				public:
					virtual void			init() {}
			};
		}
	}
}

#endif
