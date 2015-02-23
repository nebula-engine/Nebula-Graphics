#ifndef NEBULA_GRAPHICS_TYPES_HH
#define NEBULA_GRAPHICS_TYPES_HH

#include <memory>

namespace neb {

	struct program_name {
		enum e {
			TEXT,
			LIGHT,
			IMAGE,
			NORM,
			NORM_IMAGE,
			THREED
		};
	};

	/** @brief %Graphics */
	namespace gfx {
		namespace window {
			namespace util {
				class parent;
			}

			class Base;
		}

		namespace mesh {
			//template<typename BUFFER> class base;
			class tri1;
			class instanced;
		}

		/** @brief Graphical User Interface */
		namespace gui {
			/** @brief %Layout */
			namespace layout {
				class base;

				/** @brief %utilities */
				namespace util {
					class parent;
				}


			}


		}

		/**@brief %Context */
		namespace context {
			/** @brief %utilities */
			namespace util {
				class parent;
			}
			class base;
			class Window;
			class fbo;
		}

		/**@brief %environ */
		namespace environ {
			class base;
			class two;
			class three;
			class SceneDefault;
		}

		/**@brief %environ */
		namespace drawable {
			class base;
			class two;
			class three;
		}
	}
}

#endif
