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

#ifndef NEB_PLUG_GFX1_CORE_SHAPE_BOX_HPP
#define NEB_PLUG_GFX1_CORE_SHAPE_BOX_HPP

#include <neb/fnd/plug/gfx/core/shape/Base.hpp>

namespace neb { namespace plug { namespace gfx1 { namespace core { namespace shape {
	/** @brief Base
	 */
	class Box:
		virtual public neb::fnd::plug::gfx::core::shape::Base
	{
		public:
			virtual void			init(parent_t * const & p);
			virtual void			draw(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & program,
					neb::fnd::math::pose const & pose);
			virtual void			step(gal::etc::timestep const & ts);
			virtual void			v_set_pose_data(
					FND * const & ptr,
					neb::fnd::math::pose const & global_pose);
			virtual void			model_load(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					neb::fnd::math::pose const & pose);
	};
}}}}}

#endif
