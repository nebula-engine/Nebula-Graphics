#ifndef NEBULA_GFX_LIGHT_SPOT_HH
#define NEBULA_GFX_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/util/config.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/itf/shared.hpp>
#include <neb/core/math/serialization/glm.hpp>
#include <neb/core/environ/util/decl.hpp>

#include <neb/gfx/texture.hpp>
#include <neb/gfx/core/light/base.hpp>

namespace neb { namespace gfx { namespace core { namespace light {
	class point:
		virtual public neb::gfx::core::light::base
	{
		public:
			point();
			virtual type::e		getType();
			virtual void		init(neb::fnd::core::light::util::parent * const & p);
			virtual void		callbackPose(neb::fnd::math::pose const &);
			virtual void		initShadow(std::shared_ptr<neb::gfx::environ::SceneDefault>);
			virtual void		load(
					neb::fnd::core::light::util::count & light_count,
					neb::fnd::math::pose const & pose);
			virtual void		setShadowEnviron(
					std::shared_ptr<neb::fnd::environ::Base> environ);

			virtual void	load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void	save(ba::polymorphic_oarchive & ar, unsigned int const &) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
	};
}}}}

#endif
