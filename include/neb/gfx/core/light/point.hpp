#ifndef NEBULA_GFX_LIGHT_SPOT_HH
#define NEBULA_GFX_LIGHT_SPOT_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/util/config.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/util/shared.hpp>
#include <neb/core/math/Serialization/glm.hpp>

#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/texture.hh>
#include <neb/gfx/core/light/base.hpp>


namespace neb { namespace gfx { namespace core { namespace light {


	class point:
		virtual public neb::gfx::core::light::base
	{
		public:
			point(sp::shared_ptr<neb::core::light::util::parent> parent);

			virtual void	load(neb::core::light::util::count & light_count, neb::core::pose const & pose);



			float	atten_const_;
			float	atten_linear_;
			float	atten_quad_;


	};



}}}}

#endif
