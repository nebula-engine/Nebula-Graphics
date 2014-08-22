
#include <neb/gfx/glsl/array.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>

void		neb::gfx::glsl::uniform::light_locations::init(std::shared_ptr<neb::gfx::glsl::program::threed> program) {
	location[0] = program->get_uniform_vector("light_position[0]")->o_[0];
	location[1] = program->get_uniform_vector("light_ambient[0]")->o_[0];
	location[2] = program->get_uniform_vector("light_diffuse[0]")->o_[0];
	location[3] = program->get_uniform_vector("light_specular[0]")->o_[0];
	location[4] = program->get_uniform_vector("light_atten_const[0]")->o_[0];
	location[5] = program->get_uniform_vector("light_atten_linear[0]")->o_[0];
	location[6] = program->get_uniform_vector("light_atten_quad[0]")->o_[0];
	location[7] = program->get_uniform_vector("light_spot_direction[0]")->o_[0];
	location[8] = program->get_uniform_vector("light_spot_cutoff[0]")->o_[0];
	location[9] = program->get_uniform_vector("light_spot_exponent[0]")->o_[0];
	location[10] = program->get_uniform_vector("light_spot_light_cos_cutoff[0]")->o_[0];
	location[11] = program->get_uniform_vector("light_type[0]")->o_[0];
}


