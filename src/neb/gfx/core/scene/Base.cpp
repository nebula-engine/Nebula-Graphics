
#include <neb/gfx/core/scene/base.hpp>

void			neb::gfx::core::scene::base::__init(parent_t * const & p)
{
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	// graphics

	// use _M_programs._M_d3 as completion flag
	if(!_M_programs._M_d3)
	{
		// programs
		_M_programs._M_d3.reset(new P3("3d"));
		_M_programs._M_d3->init();

		_M_programs._M_d3_HF.reset(new P3("3d_HF"));
		_M_programs._M_d3_HF->init();

		_M_programs._M_d3_inst.reset(new P3("3d_inst"));
		_M_programs._M_d3_inst->init();

		init_light();

		// meshes
		math::geo::cuboid cube(1.0,1.0,1.0);

		meshes_.cuboid_.reset(new neb::gfx::mesh::instanced);
		meshes_.cuboid_->mesh_.construct(&cube);

		meshes_.cuboid_->instances_.reset(new neb::gfx::mesh::instanced::instances_type);
		meshes_.cuboid_->instances_->alloc(2048);

		unsigned int shadow_tex_size = 512;

		tex_shadow_map_ = std::make_shared<neb::gfx::texture>();
		tex_shadow_map_->init_shadow(
				shadow_tex_size,
				shadow_tex_size,
				std::shared_ptr<neb::gfx::context::base>());
	}
}


