#ifndef __GLUTPP_GFX_LIGHT_H__
#define __GLUTPP_GFX_LIGHT_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>
#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/core/light/base.hpp>
#include <neb/core/color/Color.hh>


#include <neb/gfx/core/scene/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>

namespace neb { namespace gfx { namespace core { namespace light {

		class base: virtual public neb::core::core::light::base {
			public:
				base(std::shared_ptr<neb::core::core::light::util::parent> parent, int type);
				
				void				init();
				
				virtual void			release();
				virtual void			cleanup();
				virtual void			step(gal::etc::timestep const & ts);

				virtual void			load(neb::core::core::light::util::count & light_count, neb::core::pose const & pose) = 0;
				void				load(int o, neb::core::pose const & pose);

				void				load_shadow();
				void				draw();
				void				dim();
				void				RenderShadowPost();
				void				RenderLightPOV();


				std::weak_ptr<neb::gfx::core::scene::base>	getScene();
				neb::core::pose					getPose();
				vec4						getPos();
				void						setPose(neb::core::pose const & pose);
			private:
				template<class Archive> void		serializeTemplate(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("ambient",ambient_);
					ar & boost::serialization::make_nvp("diffuse",diffuse_);
					ar & boost::serialization::make_nvp("specular",specular_);
/*					ar & boost::serialization::make_nvp("atten_const",atten_const_);
					ar & boost::serialization::make_nvp("atten_linear",atten_linear_);
					ar & boost::serialization::make_nvp("atten_quad",atten_quad_);*/
				}
			public:
				virtual void				serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
				virtual void				serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {
					serializeTemplate(ar, version);
				}
			public:
			
				std::string					light_type_string_;

				// data
				neb::core::color::color			ambient_;
				neb::core::color::color			diffuse_;
				neb::core::color::color			specular_;
				float						atten_const_;
				float						atten_linear_;
				float						atten_quad_;
				vec3						spot_direction_;
				float						spot_cutoff_;
				float						spot_exponent_;
				float						spot_light_cos_cutoff_;

				int						type_;
				
				
				// other properties

				int						light_array_;
				int						light_array_slot_;
				
				std::shared_ptr<neb::gfx::texture>		texture_shadow_map_;



		};

}}}}

#endif
