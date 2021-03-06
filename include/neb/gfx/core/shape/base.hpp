#ifndef __GLUTPP_GFX_CORE_SHAPE_H__
#define __GLUTPP_GFX_CORE_SHAPE_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/etc/timestep.hpp>

#include <neb/fnd/core/shape/base.hpp>
#include <neb/fnd/core/light/util/light_count.hpp>
#include <neb/fnd/plug/gfx/core/shape/Base.hpp>

#include <neb/gfx/core/light/util/Parent.hpp>
#include <neb/gfx/texture/Base.hpp>
#include <neb/gfx/material.hpp>
#include <neb/gfx/mesh/tri1.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/mesh/instanced.hpp>

#include <neb/gfx/util/log.hpp>

namespace neb { namespace gfx { namespace core { namespace shape {
	class base:
		public gal::tmp::Verbosity<neb::gfx::core::shape::base>,
		virtual public neb::fnd::plug::gfx::core::shape::Base
		//virtual public neb::gfx::core::light::util::parent
	{
		public:
			using gal::tmp::Verbosity<neb::gfx::core::shape::base>::printv;
			typedef neb::fnd::core::light::base L;
			base();
			virtual ~base();
			void					init(parent_t * const & p);
			void					release();
			void					step(gal::etc::timestep const & ts);
			/*
			 * overrides neb::fnd::core::shape::Base::v_set_pose_data
			 */
			virtual void				v_set_pose_data(
					FND * const & ptr,
					gal::math::pose const & global_pose);
			//virtual std::weak_ptr<L>		createLightPoint();
			//virtual std::weak_ptr<L>		createLightSpot(glm::vec3);
			//virtual std::weak_ptr<L>		createLightDirectional(glm::vec3);
			void					setPose(gal::math::pose const & pose);
			virtual void				createMesh();
			/** @name Rendering @{ */
			//void						load_lights(
			//		neb::fnd::core::light::util::count& light_count,
			//		gal::math::pose const & pose);
			void					model_load(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			void					init_buffer(
					neb::gfx::glsl::program::Base const * const & p);
			virtual void				draw(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			virtual void				drawHF(
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			virtual void				drawDebug(
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			virtual void				draw_elements(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			virtual void				draw_legacy(
					FND * const & ptr,
					neb::fnd::glsl::program::Base const * const & p,
					gal::math::pose const & pose);
			/** @} */
		public:
			/*
			template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
				LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;

				ar & boost::serialization::make_nvp("flag",flag_);
				ar & boost::serialization::make_nvp("pose",pose_);
				ar & boost::serialization::make_nvp("scale",scale_);
				ar & boost::serialization::make_nvp("image",image_);
				ar & boost::serialization::make_nvp("normal",normal_);
				ar & boost::serialization::make_nvp("material",material_);
			}
			*/
		public:
			/** @brief Material. */
			neb::gfx::material::raw					material_;
			// draw data
			/** @brief ID */
			std::shared_ptr<neb::gfx::mesh::tri1>			mesh_;
			//neb::program_name::e					program_;
			/** @brief Parent */
			std::shared_ptr<neb::gfx::mesh::instanced::slot_type>		mesh_slot_;
	};
}}}}

#endif
