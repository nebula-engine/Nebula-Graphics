#ifndef NEB_GFX_CORE_SCENE_BASE_HPP
#define NEB_GFX_CORE_SCENE_BASE_HPP


#include <vector>

#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

#include <gal/etc/flag.hpp>
#include <gal/stl/map.hpp>

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/math/serialization/glm.hpp>
#include <neb/fnd/core/actor/util/parent.hpp>
#include <neb/fnd/core/scene/base.hpp>
#include <neb/fnd/plug/gfx/core/scene/Base.hpp>
#include <neb/fnd/plug/Object.hpp>

#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/glsl/uniform/light_array.hpp>
#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/texture/util/decl.hpp>

typedef std::weak_ptr<neb::fnd::core::actor::base> wbase;

namespace neb { namespace gfx { namespace core { namespace scene {
	/** 
	 * @ingroup group_core
	 * @brief base
	 */
	class base:
		virtual public neb::gfx::drawable::base,
		virtual public neb::fnd::plug::gfx::core::scene::Base
	{
		public:
			using CHILD::get_fnd_app;
			base();
			virtual ~base();
		protected:
			void					init(parent_t * const & p);
		public:
			void					init_light();
			void					initMeshes();
			virtual void				release();
			virtual void				step(gal::etc::timestep const & ts);
			void					resize(int w, int h);
			void					draw(neb::fnd::RenderDesc const &);
			void					drawMesh(neb::fnd::RenderDesc const &);
			void					drawMeshHF(neb::fnd::RenderDesc const &);
			void					drawMeshInst(neb::fnd::RenderDesc const &);
			//virtual void				drawPhysxVisualization(neb::fnd::RenderDesc const &) = 0;
			void					drawDebug(neb::fnd::RenderDesc const &);
			void					draw_debug_buffer(
					neb::fnd::RenderDesc const & desc,
					neb::fnd::DebugBuffer const & db);
			//virtual void				load(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) = 0;
			//virtual void				save(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) const = 0;
			//BOOST_SERIALIZATION_SPLIT_MEMBER();
			/** @name convenience functions
			 * @{
			 */
			/** @brief create rigiddynamic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			//virtual weak_ptr<neb::fnd::core::actor::base>		createActorRigidStaticUninitialized() = 0;
			/** @brief create rigidstatic
			 *
			 * @note typeof returned actor will be determined by final implementation of this
			 *
			 * @warning return actor is not initialized
			 */
			//virtual weak_ptr<neb::fnd::core::actor::base>		createActorRigidDynamicUninitialized() = 0;
			/** @} */
			// rendering data
			struct
			{
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_HF;
				std::shared_ptr<neb::gfx::glsl::program::threed>	_M_d3_inst;
			} _M_programs;

			// one for static, one for dynamic
			std::shared_ptr<neb::gfx::glsl::uniform::light_array>		light_array_[2];

			std::shared_ptr<neb::gfx::texture::Base>			tex_shadow_map_;

			// standard meshes
			struct {
				std::shared_ptr<neb::gfx::mesh::instanced>		cuboid_;
			} meshes_;



	};
}}}}

#endif

