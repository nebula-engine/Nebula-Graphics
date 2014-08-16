#ifndef __GLUTPP_GFX_CORE_SCENE_H__
#define __GLUTPP_GFX_CORE_SCENE_H__

#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/drawable/base.hpp>

namespace neb {
	namespace gfx {
		namespace core {
			namespace scene {


				/** 
				 * @ingroup group_core
				 * @brief Base
				 */
				class base:
					virtual public neb::core::core::scene::base,
					virtual public neb::gfx::drawable::base
				{
					public:
						base(std::shared_ptr<neb::core::core::scene::util::parent>);
						virtual ~base();
						virtual void				init();
						virtual void				release();
						virtual void				step(gal::etc::timestep const & ts);

						void					resize(int w, int h);
						void					load_lights(std::shared_ptr<neb::glsl::program> p);
						void					draw(std::shared_ptr<neb::gfx::context::base> context, std::shared_ptr<neb::glsl::program> p);

						/** @brief create empty actor
						 *
						 * @warning this function allocates object
						 */		
						//virtual std::weak_ptr<neb::core::core::actor::base>			createActorBase(neb::core::pose const & pose);
						/** @brief create empty actor with point light
						 *
						 * @warning this function allocates object
						 */
						virtual weak_ptr<neb::core::core::actor::base>			createActorLightPoint(glm::vec3 p);

				};




			}
		}
	}
}

#endif





