#include <stdio.h>
#include <assert.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/decl.hpp>
#include <neb/core/util/log.hpp>
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/shape/base.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>


neb::gfx::core::light::base::base(std::shared_ptr<neb::core::core::light::util::parent> parent, int type):
	neb::core::core::light::base(parent),
	ambient_(0.1,0.1,0.1,1.0),
	diffuse_(neb::core::color::color::white()),
	specular_(neb::core::color::color::white()),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0),
	type_(type)
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
neb::gfx::core::light::base::~base() {}
void			neb::gfx::core::light::base::init() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;

	// register in light_array
	light_array_ = 0;
	light_array_slot_ = getScene().lock()->light_array_[light_array_].reg(
			pos_,
			ambient_,
			diffuse_,
			specular_,
			atten_const_,
			atten_linear_,
			atten_quad_,
			spot_direction_,
			spot_cutoff_,
			spot_exponent_,
			glm::mat4(),
			glm::mat4(),
			glm::mat4(),
			glm::mat4(),
			glm::mat4(),
			glm::mat4(),
			glm::vec3(-1.0),
			glm::vec3(-1.0),
			type_
			);
}
void			neb::gfx::core::light::base::setPose(neb::core::pose const & pose) {
	pos_ = pose.pos_;
	
	auto parent = getScene().lock();
	
	parent->light_array_[light_array_].set_pos(light_array_slot_, pose.pos_);
	parent->light_array_[light_array_].set_spot_direction(light_array_slot_, pose.rot_ * spot_direction_);
}
void			neb::gfx::core::light::base::release() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::light::base::cleanup() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::light::base::dim() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*	
	//printf("diffuse\n");
	//diffuse_.print();

	glLightfv(o_, GL_POSITION, camera_.eye_);
	glLightfv(o_, GL_AMBIENT, ambient_);
	glLightfv(o_, GL_DIFFUSE, diffuse_ * 0.2f);
	glLightfv(o_, GL_SPECULAR, math::black);checkerror(__PRETTY_FUNCTION__);
	*/
	printf("UNSUPPORTED\n");
	exit(0);
}
void		neb::gfx::core::light::base::step(gal::etc::timestep const & ts) {

}
void	neb::gfx::core::light::base::draw() {	
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
}
neb::core::pose		neb::gfx::core::light::base::getPose() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	
	auto parent(parent_.lock());
	assert(parent);
	
	auto p = parent->getPoseGlobal();
	
	return p;
}
void			neb::gfx::core::light::base::load(int o, neb::core::pose const & pose) {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	
	/** @todo way to ditinguish lights in shader */
/*	
	auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();
	
	vec3 pos = pos_;
	
	pos += vec3(pose.pos_);
	
	
	p->get_uniform_vector(light_type_string_ + ".position")->load(o, pos);
	
	
	p->get_uniform_vector(light_type_string_ + ".ambient")->load(o, (glm::vec4)ambient_);
	p->get_uniform_vector(light_type_string_ + ".diffuse")->load(o, (glm::vec4)diffuse_);
	p->get_uniform_vector(light_type_string_ + ".specular")->load(o, (glm::vec4)specular_);
*/

}
void	neb::gfx::core::light::base::load_shadow() {
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*	auto p = neb::master::Global()->current_program();

		math::mat44 biasMatrix(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);

		math::mat44 textureMatrix = biasMatrix * camera_.proj() * camera_.view();

		uniform_matrix_shadow_.load_matrix4fv(textureMatrix);

	// texture
	glActiveTexture(GL_TEXTURE1);
	texture_shadow_map_.bind();
	uniform_tex_shadow_.load_1i(1);
	*/
}
void	neb::gfx::core::light::base::RenderLightPOV()
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	/*
	   std::shared_ptr<scene> scene = scene_.lock();

	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	camera_.load_shader();
	*/	/*
		   glMatrixMode(GL_PROJECTION);
		   glLoadMatrixf(camera_.proj());

		   glMatrixMode(GL_MODELVIEW);
		   glLoadMatrixf(camera_.view());

		   glViewport(0, 0, texture_shadow_map_.w_, texture_shadow_map_.h_);
		   */

	//window_->lights_updateGL();

	// Use viewport the same size as the shadow map

	// Draw back faces into the shadow map
	/*	glCullFace(GL_FRONT);

	// Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);

	//Draw the scene
	scene->draw_shader();

	//Read the depth buffer into the shadow map texture
	texture_shadow_map_.bind();

	glCopyTexSubImage2D(
	GL_TEXTURE_2D,
	0, 0, 0, 0, 0,
	texture_shadow_map_.w_, texture_shadow_map_.h_);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);
	*/
	checkerror("unknown");
}
void	neb::gfx::core::light::base::RenderShadowPost()
{
	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	glDisable(GL_ALPHA_TEST);
	checkerror(__PRETTY_FUNCTION__);
}
std::weak_ptr<neb::gfx::core::scene::base>	neb::gfx::core::light::base::getScene() {
	auto parent = parent_.lock();
	assert(parent);

	auto p2 = std::dynamic_pointer_cast<neb::gfx::core::scene::base>(
			parent->getScene().lock());
	assert(p2);
	return p2;
}






