#ifndef __GLUTPP_GFX_LIGHT_H__
#define __GLUTPP_GFX_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/etc/slots.hpp>

#include <neb/core/core/light/base.hpp>
#include <neb/core/environ/util/decl.hpp>
#include <neb/core/math/serialization/glm.hpp>
#include <neb/core/math/color/color.hpp>
#include <neb/core/util/decl.hpp>

#include <neb/gfx/glsl/uniform/light_array.hpp>
#include <neb/gfx/core/scene/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/texture/util/decl.hpp>
#include <neb/gfx/tmp/Child.hpp>

namespace neb { namespace gfx { namespace core { namespace light {

	struct type {
		enum e {
			POINT = 0,
			SPOT = 1,
			DIRECTIONAL = 2
		};
	};

	class base:
		public neb::fnd::itf::verbosity<neb::gfx::core::light::base>,
		virtual public neb::fnd::core::light::base,
		virtual public neb::gfx::tmp::Child<neb::fnd::core::light::util::parent>
	{
		public:
			using neb::fnd::itf::verbosity<neb::gfx::core::light::base>::printv;
			base();
			~base() = 0;
			virtual void					init(neb::fnd::core::light::util::parent * const & p);
			virtual type::e					getType() = 0;
			virtual void					release();
			virtual void					cleanup();
			virtual void					step(gal::etc::timestep const & ts);
			//virtual void					load(neb::fnd::core::light::util::count & light_count, neb::fnd::math::pose const & pose) = 0;
			void						load(int o, neb::fnd::math::pose const & pose);
			void						load_shadow();
			void						draw();
			void						dim();
			void						RenderShadowPost();
			void						RenderLightPOV();
			neb::fnd::math::pose				getPose();
			glm::vec4					getPos();
			void						setPose(neb::fnd::math::pose const & pose);
			virtual void					setShadowEnviron(std::shared_ptr<neb::fnd::environ::Base> environ);
			//virtual void					setSceneEnviron(std::shared_ptr<neb::fnd::environ::base> environ);
		protected:
			template<class Archive> void			__serialize(Archive & ar, unsigned int const & version)
			{
				ar & boost::serialization::make_nvp("ambient",ambient_);
				ar & boost::serialization::make_nvp("diffuse",diffuse_);
				ar & boost::serialization::make_nvp("specular",specular_);
				ar & boost::serialization::make_nvp("atten_const",atten_const_);
				ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
				ar & boost::serialization::make_nvp("atten_quad",atten_quad_);
			}
		public:
			virtual void					load(ba::polymorphic_iarchive & ar, unsigned int const &);
			virtual void					save(ba::polymorphic_oarchive & ar, unsigned int const &) const;
			BOOST_SERIALIZATION_SPLIT_MEMBER();
		public:
			std::string					light_type_string_;
			// data
			neb::fnd::math::color::color			ambient_;
			neb::fnd::math::color::color			diffuse_;
			neb::fnd::math::color::color			specular_;
			float						atten_const_;
			float						atten_linear_;
			float						atten_quad_;
			glm::vec3					spot_direction_;
			float						spot_cutoff_;
			float						spot_exponent_;
			float						spot_light_cos_cutoff_;
			glm::mat4					shadow_vpb_[6];
			glm::vec3					shadow_sampler_[2];
			// shadows
			//std::shared_ptr<neb::gfx::window::base>	shadow_environ_;
			std::shared_ptr<neb::gfx::environ::base>	shadow_environ_;				
			// other properties
			int							light_array_;
			neb::gfx::glsl::uniform::light_array::slot_shared	light_array_slot_;
			std::shared_ptr<gal::etc::slots::ticket>		texture_layers_;
			std::shared_ptr<neb::gfx::texture::Base>		texture_shadow_map_;
	};

}}}}

#endif
