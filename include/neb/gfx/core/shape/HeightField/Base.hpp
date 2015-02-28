#ifndef NEB_GFX_SHAPE_HEIGHT_FIELD_HH
#define NEB_GFX_SHAPE_HEIGHT_FIELD_HH

#include <neb/fnd/core/shape/HeightField.hpp>
#include <neb/fnd/math/geo/util/decl.hpp>

#include <neb/gfx/core/shape/base.hpp>

namespace neb { namespace gfx { namespace core { namespace shape { namespace HeightField {
	class Base:
		virtual public neb::fnd::core::shape::HeightField::Base,
		virtual public neb::gfx::core::shape::base
	{
		public:
			typedef neb::fnd::core::shape::util::parent parent_t;
			Base();
			virtual void				init(parent_t * const & p) = 0;
			virtual void				release() = 0;
			virtual void				step(gal::etc::timestep  const & ts) = 0;
			// dont render normally. function is empty
			virtual void				draw(
							neb::gfx::glsl::program::Base const * const & p,
							gal::math::pose const & pose);
			virtual void				drawHF(
						FND * const & ptr,
						neb::gfx::glsl::program::Base const * const & p,
							gal::math::pose const & pose);
			//virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			//virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;

			void		mesh_from_heightfield(neb::fnd::math::HeightField::Base*, float, float);
	};
}}}}}

#endif
