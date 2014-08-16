#ifndef NEBULA_CORE_ACTOR_GFX_BASE_HH
#define NEBULA_CORE_ACTOR_GFX_BASE_HH

#include <memory>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/signals2.hpp>

#include <neb/core/math/Serialization/glm.hpp>
#include <neb/core/core/actor/base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/shape/util/parent.hpp>

#include <neb/gfx/Context/Util/decl.hpp>
#include <neb/gfx/util/decl.hpp>

using namespace std;

namespace neb {
	namespace gfx {
		namespace core {
			namespace actor {
				/** @brief %base
				 * 
				 * graphics data for actors.
				 * no need to derive this class for different actor types.
				 */
				class base:
					virtual public neb::core::core::actor::base
				{
					public:
						/** @brief default constructor */
						//base();
						/** @brief constructor */
						base(std::shared_ptr<neb::core::core::actor::util::parent> parent);
						virtual ~base();
					public:
						virtual void					init();
						virtual void					release();
						virtual void					step(gal::etc::timestep const & ts);
					public:
						void						draw(
								std::shared_ptr<neb::gfx::context::base> context,
								std::shared_ptr<neb::glsl::program> p,
								neb::core::pose const & pose);

						void						load_lights(
								neb::core::core::light::util::count& light_count,
								neb::core::pose const &);
						//virtual weak_ptr<neb::core::shape::base>	createShapeBase();
						//virtual weak_ptr<neb::core::shape::base>	createShapeBox(glm::vec3 size);
						//virtual weak_ptr<neb::core::shape::base>	createShapeCube(double size);
				};
			}
		}
	}
}

#endif








