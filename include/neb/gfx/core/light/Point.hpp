#ifndef NEBULA_GFX_LIGHT_SPOT_HH
#define NEBULA_GFX_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/fnd/util/config.hpp>
#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/itf/shared.hpp>
#include <neb/fnd/math/serialization/glm.hpp>
#include <neb/fnd/environ/util/decl.hpp>
#include <neb/fnd/core/light/util/light_count.hpp>

#include <neb/gfx/texture/Base.hpp>
#include <neb/gfx/core/light/Base.hpp>

namespace neb { namespace gfx { namespace core { namespace light {
	class Point:
		virtual public neb::gfx::core::light::Base
	{
		public:
			Point();
			virtual type::e		getType();
			virtual void		init(parent_t * const & p);
			virtual void		v_set_pose_data(
					FND * const & ptr,
					gal::math::pose const & global_pose);
			virtual void		initShadow(std::shared_ptr<neb::gfx::environ::SceneDefault>);
			virtual void		load(
					neb::fnd::core::light::util::count & light_count,
					gal::math::pose const & pose);
			virtual void		setShadowEnviron(
					std::shared_ptr<neb::fnd::environ::Base> environ);

			virtual void	load(boost::archive::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(boost::archive::polymorphic_oarchive & ar, unsigned int const &) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
	};
}}}}

#endif
