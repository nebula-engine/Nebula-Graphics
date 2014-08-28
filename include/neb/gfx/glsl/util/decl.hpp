#ifndef NEB_GFX_GLSL_UTIL_DECL_HPP
#define NEB_GFX_GLSL_UTIL_DECL_HPP

namespace neb { namespace gfx {

	namespace glsl {

		struct attribs {
			enum {
				COOR,
				TEX,
				POSITION,
				NORMAL,
				TEXCOOR,
				TANGENT,
				BINORMAL,
				INSTANCE_MODEL0,
				INSTANCE_MODEL1,
				INSTANCE_MODEL2,
				INSTANCE_MODEL3,
				INSTANCE_SAMPLER,
				INSTANCE_DIFFUSE,
				INSTANCE_AMBIENT,
				INSTANCE_SPECULAR,
				INSTANCE_EMISSION,
				INSTANCE_SHININESS,
				COUNT
			};
		};

		struct uniforms {
			enum {
				VIEW,
				PROJ,
				TEX_IMAGE,
				TEX_NORMAL_MAP,
				TEX_SHADOW_MAP,
				COUNT
			};
		};

		namespace program {
			class base;
			class text;
			class tex;
			class threed;
			class shadow_directional;
		}

		/** @brief uniforms */
		namespace uniform {

			static constexpr char const * uniform_string_[attribs::COUNT] = {
				"view",
				"proj",
				"image",
				"normal_map",
				"shadow_map"
			};

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

		namespace buffer {
			class tri1;
			class instanced;
		}
	}

}}

#endif
