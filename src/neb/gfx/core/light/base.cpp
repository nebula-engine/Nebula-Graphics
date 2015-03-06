#include <stdio.h>
#include <assert.h>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/core/scene/Base.hpp>
#include <neb/fnd/core/shape/base.hpp>

//#include <neb/gfx/app/__gfx_glsl.hpp> removed by c_header_checker
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/camera/proj/base.hpp>
//#include <neb/gfx/camera/view/Base.hpp> removed by c_header_checker
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/light/Base.hpp>

typedef neb::gfx::core::light::Base THIS;

THIS::Base():
	ambient_(0.2,0.2,0.2,1.0),
	diffuse_(neb::fnd::math::color::color::white()),
	specular_(neb::fnd::math::color::color::white()),
	atten_const_(1.0),
	atten_linear_(0.5),
	atten_quad_(0.0),
	spot_direction_(glm::vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(1.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0)
{
	printv_func(DEBUG);

	shadow_sampler_[0] = glm::vec3(-1);
	shadow_sampler_[1] = glm::vec3(-1);

}
THIS::~Base()
{
}
void			THIS::init(parent_t * const & p)
{
	printv_func(DEBUG);

	setParent(p);

	// check if detached
	/*
	if(!hasScene()) {
		std::cout << "skip initialization" << std::endl;
		return;
	}
	*/
	
	auto scene_fnd = dynamic_cast<neb::fnd::core::scene::base*>(getParent()->getScene());
	assert(scene_fnd);
	auto scene = dynamic_cast<neb::gfx::core::scene::base*>(scene_fnd->G::get_object().get());
	
	auto pose = getParent()->getPoseGlobal();

	// register in light_array
	light_array_ = 0;

	if(!light_array_slot_)
	{
		if(!scene->light_array_[light_array_]) scene->init_light();

		assert(scene->light_array_[light_array_]);
		assert(scene->light_array_[light_array_]->size_array() != 0);

		printv(debug,
				"pose     %12f %12f %12f\n",
				pose.pos_.x,
				pose.pos_.y,
				pose.pos_.z);
		printv(debug,
				"type     %i\n",
				(int)getType());
		printv(debug,
				"ambient  %12f %12f %12f %12f\n",
				ambient_.r,
				ambient_.g,
				ambient_.b,
				ambient_.a);
		printv(debug,
				"diffuse  %12f %12f %12f %12f\n",
				diffuse_.r,
				diffuse_.g,
				diffuse_.b,
				diffuse_.a);
		printv(debug,
				"specular %12f %12f %12f %12f\n",
				specular_.r,
				specular_.g,
				specular_.b,
				specular_.a);

		light_array_slot_ = scene->light_array_[light_array_]->reg(
				pose.pos_,
				ambient_,
				diffuse_,
				specular_,
				atten_const_,
				atten_linear_,
				atten_quad_,
				pose.rot_ * spot_direction_,
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
				(int)getType()
				);
	}
}
void			THIS::setPose(gal::math::pose const & npose)
{
	getParent()->pose_ = npose;

	auto pose = getParent()->getPoseGlobal();

	light_array_slot_->set<0>(pose.pos_);
	light_array_slot_->set<7>(pose.rot_ * spot_direction_);
}
void			THIS::release()
{
	printv_func(DEBUG);
}
void			THIS::cleanup()
{
	printv_func(DEBUG);
}
void			THIS::dim()
{
	printv_func(DEBUG);
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
void			THIS::step(gal::etc::timestep const & ts)
{
	/*
	   if(shadow_environ_) {

	   auto e = std::dynamic_pointer_cast<>

	   }
	   */
}
void			THIS::draw()
{
	printv_func(DEBUG);
}
gal::math::pose		THIS::getPose()
{
	printv_func(DEBUG);

	auto p = getParent()->getPoseGlobal();

	return p;
}
void			THIS::load(int o, gal::math::pose const & pose)
{
	printv_func(DEBUG);

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
void			THIS::load_shadow()
{
	printv_func(DEBUG);
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
void			THIS::RenderLightPOV()
{
	printv_func(DEBUG);
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
void	THIS::RenderShadowPost()
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
void	THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	__serialize(ar,v);
}
void	THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	const_cast<THIS*>(this)->__serialize(ar,v);
}
void	THIS::setShadowEnviron(std::shared_ptr<neb::fnd::environ::Base> environ)
{
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::base>(environ);
	assert(e);
	shadow_environ_ = e;
}


