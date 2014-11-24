#ifndef NEB_GFX_CAMERA_PROJ_UTIL_CAST_HPP
#define NEB_GFX_CAMERA_PROJ_UTIL_CAST_HPP

#include <gal/itf/shared.hpp>

#include <neb/gfx/camera/util/decl.hpp>

namespace neb { namespace gfx { namespace camera { namespace proj { namespace util {
	/***/
	class cast:
		virtual public gal::itf::shared
	{
		public:
			std::shared_ptr<neb::gfx::camera::proj::perspective>	isPerspective();
			std::shared_ptr<neb::gfx::camera::proj::ortho>		isOrtho();
	};
}}}}}

#endif
