#ifndef NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP
#define NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/std/shared.hpp>

#include <neb/core/Pose.hh>
#include <neb/core/util/parent.hpp>
#include <neb/core/actor/util/Types.hh>
#include <neb/core/actor/util/Cast.hh>
#include <neb/core/shape/util/Cast.hh>

namespace neb {
	namespace gfx {
		namespace core {
			namespace shape {
				namespace util {
					/** @brief @parent
					 * abstract class for parent of a shape
					 *
					 * @note inheritance of neb::util::parent is non-virtual
					 */
					class parent :
						virtual public neb::util::parent<neb::core::shape::base>,
						virtual public neb::core::actor::util::cast,
						virtual public neb::core::shape::util::cast,
						virtual public neb::core::Pose
					{
					public:
						virtual ~parent() {}
					};


				}
			}
		}
	}
}


#endif






