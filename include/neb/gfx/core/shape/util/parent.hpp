#ifndef NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP
#define NEBULA_GFX_CORE_SHAPE_UTIL_PARENT_HPP

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/itf/shared.hpp>

#include <gal/math/pose.hpp>
#include <neb/fnd/util/parent.hpp>
#include <neb/fnd/core/actor/util/decl.hpp>
#include <neb/fnd/core/actor/util/Cast.hpp>
#include <neb/fnd/core/shape/util/cast.hpp>
#include <neb/fnd/core/shape/util/parent.hpp>

namespace neb { namespace gfx { namespace core { namespace shape { namespace util {
	/** @brief @parent
	 * abstract class for parent of a shape
	 *
	 * @note inheritance of neb::util::parent is non-virtual
	 */
	class parent :
		virtual public neb::fnd::core::shape::util::parent
	{
		public:
			virtual ~parent() {}
	};


}}}}}

#endif
