#ifndef NEBULA_GFX_SHAPE_BOX_HH
#define NEBULA_GFX_SHAPE_BOX_HH

#include <neb/gfx/core/shape/base.hpp>

namespace neb { namespace gfx { namespace core { namespace shape {
	class box:
		virtual public neb::gfx::core::shape::base
	{
		public:
			box();
			virtual void			createMesh();
			void				create_mesh_instance();
			void				create_mesh_standalone();
			virtual void			draw_legacy(
					neb::fnd::glsl::program::Base const * const & p,
					neb::fnd::math::pose const & pose);
	};
}}}}

#endif
