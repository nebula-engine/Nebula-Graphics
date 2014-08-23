#ifndef __GLUTPP_GFX_CORE_SHAPE_H__
#define __GLUTPP_GFX_CORE_SHAPE_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gal/etc/timestep.hpp>

#include <neb/core/core/shape/base.hpp>
#include <neb/core/core/light/util/light_count.hpp>

#include <neb/gfx/core/light/util/parent.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/material.hpp>
#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/core/mesh_instanced.hpp>

namespace neb {
	namespace gfx {
		namespace context {
			class base;
		}

		namespace core { namespace shape {
			class base:
				virtual public neb::core::core::shape::base,
				virtual public neb::gfx::core::light::util::parent
			{
				public:
					
					base(std::shared_ptr<neb::core::core::shape::util::parent> parent);
					virtual ~base();

					void			init();
					void			release();
					void			step(gal::etc::timestep const & ts);
					virtual void		callbackPose(neb::core::pose const & pose_global);
					virtual weak_ptr<neb::core::core::light::base>		createLightPoint();


					void							setPose(neb::core::pose const & pose);
					virtual void						createMesh();


					/** @name Rendering @{ */
					//void						load_lights(
					//		neb::core::core::light::util::count& light_count,
					//		neb::core::pose const & pose);
					void						model_load(
							std::shared_ptr<neb::gfx::glsl::program::threed> p,
							neb::core::pose const & pose);
					void						init_buffer(
							std::shared_ptr<neb::gfx::context::base> context,
							std::shared_ptr<neb::gfx::glsl::program::base> p);
					void						draw(
							std::shared_ptr<neb::gfx::context::base>,
							std::shared_ptr<neb::gfx::glsl::program::threed> p,
							neb::core::pose const & pose);
					virtual void					draw_elements(
							std::shared_ptr<neb::gfx::context::base> context,
							std::shared_ptr<neb::gfx::glsl::program::threed> p,
							neb::core::pose const & pose);
					/** @} */
				public:
					template<class Archive>	void	serialize(Archive & ar, unsigned int const & version) {
						ar & boost::serialization::make_nvp("flag",flag_);
						ar & boost::serialization::make_nvp("pose",pose_);
						ar & boost::serialization::make_nvp("s",s_);
						ar & boost::serialization::make_nvp("image",image_);
						ar & boost::serialization::make_nvp("normal",normal_);
						ar & boost::serialization::make_nvp("material",material_);
					}

				public:
					weak_ptr<neb::core::core::shape::util::parent>		parent_;

				public:
					/** @brief Material. */
					neb::material::raw					material_;
				public:

					// draw data
					/** @brief ID */
					std::shared_ptr<neb::gfx::mesh>				mesh_;
					//neb::program_name::e					program_;
					/** @brief Parent */
					
					std::shared_ptr<neb::gfx::mesh_instanced::slot_type>	mesh_slot_;
			};
		}}
	}
}


#endif





