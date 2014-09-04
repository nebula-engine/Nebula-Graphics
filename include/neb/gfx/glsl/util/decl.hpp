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
				FLAG,
				VIEW,
				PROJ,
				TEX_IMAGE,
				TEX_NORMAL_MAP,
				TEX_SHADOW_MAP,
				LIGHT_POSITION,
				LIGHT_AMBIENT,
				LIGHT_DIFFUSE,
				LIGHT_SPECULAR,
				LIGHT_ATTEN_CONST,
				LIGHT_ATTEN_LINEAR,
				LIGHT_ATTEN_QUAD,
				LIGHT_SPOT_DIRECTION,
				LIGHT_SPOT_CUTOFF,
				LIGHT_SPOT_EXPONENT,
				LIGHT_SHADOW_VPB_0,
				LIGHT_SHADOW_VPB_1,
				LIGHT_SHADOW_VPB_2,
				LIGHT_SHADOW_VPB_3,
				LIGHT_SHADOW_VPB_4,
				LIGHT_SHADOW_VPB_5,
				LIGHT_SHADOW_SAMPLER_0,
				LIGHT_SHADOW_SAMPLER_1,
				LIGHT_TYPE,
				LIGHT_CLOSED,
				LIGHT_COUNT,
				COUNT
			};
		};

		namespace program {
			class base;
			class text;
			class tex;
			class threed;
			class shadow;
		}

		/** @brief uniforms */
		namespace uniform {

			static constexpr char const * uniform_string_[uniforms::COUNT] = {
				"flag",
				"view",
				"proj",
				"image",
				"normal_map",
				"shadow_map",
				"light_position",
				"light_ambient",
				"light_diffuse",
				"light_specular",
				"light_atten_const",
				"light_atten_linear",
				"light_atten_quad",
				"light_spot_direction",
				"light_spot_cutoff",
				"light_spot_exponent",
				"light_shadow_vpb_0",
				"light_shadow_vpb_1",
				"light_shadow_vpb_2",
				"light_shadow_vpb_3",
				"light_shadow_vpb_4",
				"light_shadow_vpb_5",
				"light_shadow_sampler_0",
				"light_shadow_sampler_1",
				"light_type",
				"light_closed",
				"light_count"
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
