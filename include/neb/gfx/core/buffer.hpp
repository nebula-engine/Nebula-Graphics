#ifndef __GLUTPP_GFX_CORE_BUFFER_H__
#define __GLUTPP_GFX_CORE_BUFFER_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/std/timestep.hpp>

#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>

#include <neb/gfx/core/light/util/parent.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/material.hpp>
#include <neb/gfx/core/mesh.hh>

namespace neb { namespace gfx { namespace core {
	class buffer {
		public:
			GLuint		vbo_;
			GLuint		indices_;

			struct
			{
				sp::shared_ptr<neb::texture>	image_;
			} texture_;
	};
}}}

#endif

