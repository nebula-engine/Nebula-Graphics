#ifndef NEBULA_CORE_ACTOR_GFX_BASE_HH
#define NEBULA_CORE_ACTOR_GFX_BASE_HH

#include <memory>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/signals2.hpp>

#include <neb/fnd/math/serialization/glm.hpp>
#include <neb/fnd/core/actor/base.hpp>
#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/core/shape/util/parent.hpp>
#include <neb/fnd/glsl/program/util/decl.hpp>

#include <neb/gfx/context/util/decl.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace core { namespace actor {
	/** @brief %base
	 * 
	 * graphics data for actors.
	 * no need to derive this class for different actor types.
	 */
	class base:
		virtual public neb::fnd::core::actor::base
	{
		public:
			/** @brief default constructor */
			//base();
			/** @brief constructor */
			//base(std::shared_ptr<neb::fnd::core::actor::util::parent> parent);
			virtual ~base();
		public:
			//virtual void					init(neb::fnd::core::actor::util::parent * const & p) = 0;
			//virtual void					release() = 0;
			//virtual void					step(gal::etc::timestep const & ts);
		public:
			void						draw(
					neb::fnd::glsl::program::Base const * const & p,
					neb::fnd::math::pose const & pose);
			void						drawDebug(
					neb::fnd::glsl::program::Base const * const & p,
					neb::fnd::math::pose const & pose);
			void						drawHF(
					neb::fnd::glsl::program::Base const * const & p,
					neb::fnd::math::pose const & pose);

	};
}}}}

#endif
