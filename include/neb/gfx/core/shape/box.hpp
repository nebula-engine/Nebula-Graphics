#ifndef NEBULA_GFX_SHAPE_BOX_HH
#define NEBULA_GFX_SHAPE_BOX_HH

#include <neb/gfx/core/shape/base.hpp>

namespace neb { namespace gfx { namespace core { namespace shape {
	class box:
		virtual public neb::gfx::core::shape::base
	{
		public:
			box();
			virtual void			init(parent_t * const & p);
			virtual void			createMesh();
			void				create_mesh_instance();
			void				create_mesh_standalone();
			virtual void			draw_legacy(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			virtual void			step(gal::etc::timestep const & ts);
		/*
			virtual void			v_set_pose_data(
					FND * const & ptr,
					gal::math::pose const & global_pose);
					*/
/*			virtual void			model_load(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
*/
	};
}}}}

#endif
