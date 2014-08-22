#ifndef NEB_GFX_GLSL_UTIL_DECL_HPP
#define NEB_GFX_GLSL_UTIL_DECL_HPP

namespace neb { namespace gfx {

	namespace glsl {

		namespace program {
			class base;
			class threed;
		}

		/** @brief uniforms */
		namespace Uniform {
			/** @brief Scalar GLSL Uniforms */
			namespace Scalar {
				class base;
			}
			/** @brief Vector GLSL Uniforms */
			namespace Vector {
				class base;
			}
		}

		class shader;
		class attrib;
	}

}}

#endif
