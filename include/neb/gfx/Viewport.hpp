#ifndef NEBULA_GRAPHICS_VIEWPORT_HPP
#define NEBULA_GRAPHICS_VIEWPORT_HPP

#include <GL/glew.h>

#include <gal/stl/verbosity.hpp>

namespace neb { namespace gfx {
	class Viewport:
		public gal::tmp::Verbosity<neb::gfx::Viewport>
	{
		public:
			using gal::tmp::Verbosity<neb::gfx::Viewport>::printv;
			Viewport();
			virtual void		load();
			virtual void		resize(int w, int h);
			GLuint			x_, y_, w_, h_;
			GLfloat			aspect_;
	};
}}

#endif
