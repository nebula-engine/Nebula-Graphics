
#include <neb/gfx/glsl/uniform/array.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/uniform/scalar.hpp>

void		neb::gfx::glsl::uniform::light_locations::init(std::shared_ptr<neb::gfx::glsl::program::threed> program) {
	location[0] = program->get_uniform_vector("light_position")->o_[0];
	location[1] = program->get_uniform_vector("light_ambient")->o_[0];
	location[2] = program->get_uniform_vector("light_diffuse")->o_[0];
	location[3] = program->get_uniform_vector("light_specular")->o_[0];
	location[4] = program->get_uniform_vector("light_atten_const")->o_[0];
	location[5] = program->get_uniform_vector("light_atten_linear")->o_[0];
	location[6] = program->get_uniform_vector("light_atten_quad")->o_[0];
	location[7] = program->get_uniform_vector("light_spot_direction")->o_[0];
	location[8] = program->get_uniform_vector("light_spot_cutoff")->o_[0];
	location[9] = program->get_uniform_vector("light_spot_exponent")->o_[0];
	location[10] = program->get_uniform_vector("light_type")->o_[0];
	location[11] = program->get_uniform_vector("light_closed")->o_[0];
	location[12] = program->get_uniform_scalar("light_count")->o_;
}


