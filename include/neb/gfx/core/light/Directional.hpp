#ifndef NEBULA_LIGHT_DIRECTIONAL_HH
#define NEBULA_LIGHT_DIRECTIONAL_HH

#include <neb/fnd/environ/util/decl.hpp>
#include <neb/gfx/core/light/Base.hpp>

namespace neb { namespace gfx { namespace core { namespace light {
	/** @brief
	 */
	class Directional:
		virtual public neb::gfx::core::light::Base
	{
		public:
			Directional();
			virtual void		init(parent_t * const & p);
			virtual void		v_set_pose_data(
					FND * const & ptr,
					gal::math::pose const & global_pose);
			virtual type::e		getType();
			virtual void		setShadowEnviron(std::shared_ptr<neb::fnd::environ::Base> environ);
			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
	};
}}}}

#endif
