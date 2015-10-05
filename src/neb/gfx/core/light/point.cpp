#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/window/Base.hpp>
//#include <neb/fnd/core/light/util/parent.hpp>
//#include <neb/fnd/context/FBOM.hpp> removed by c_header_checker
#include <neb/fnd/environ/shadow/Point.hpp>
#include <neb/fnd/environ/shadow/Directional.hpp>
#include <neb/fnd/camera/proj/Base.hpp>

#include <neb/gfx/app/base.hpp>
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/core/light/Point.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/texture/Base.hpp>
#include <neb/gfx/core/scene/base.hpp>

typedef neb::gfx::core::light::Point THIS;

THIS::Point()
{
}
neb::gfx::core::light::type::e		THIS::getType()
{
	return neb::gfx::core::light::type::POINT;
}
void	THIS::load(neb::fnd::core::light::util::count & light_count, gal::math::pose const & pose)
{
	printv_func(DEBUG);
	
	abort();
	/*        
		  neb::gfx::core::light::base::load(light_count.point, pose);

		  auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();


		  p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
		  p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
		  p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
		  light_count.point++;
		  */
}
void			THIS::init(parent_t * const & p)
{
	printv_func(DEBUG);

	setParent(p);

	neb::gfx::core::light::Base::init(p);
}	
void			THIS::v_set_pose_data(
		FND * const & fnd,
		gal::math::pose const & gpose)
{
	printv_func(DEBUG);
	//printv(DEBUG, gpose.mat4_cast());
	
	light_array_slot_->set<0>(gpose.pos_);
}
void			THIS::initShadow(
		std::shared_ptr<neb::gfx::environ::SceneDefault> e3)
{
	printv_func(DEBUG);
	// scene

	/*
	auto scene = std::dynamic_pointer_cast<neb::gfx::core::scene::base>(getScene()->shared_from_this());
	
	auto self = std::dynamic_pointer_cast<THIS>(shared_from_this());
	
	auto app = get_fnd_app();

	//typedef neb::gfx::window::base Window;
	//auto window = app->neb::gfx::window::util::parent::create<Window>().lock();
	auto window = app->createWindow().lock(); //neb::gfx::window::util::parent::create<Window>().lock();
	
	auto context = window->createContextFBOMulti().lock();

	auto environ = context->createEnvironShadowPoint().lock();

	environ->set_drawable(scene);

	context->G::get_object()->setTexture(scene->tex_shadow_map_);

	environ->setLight(self);

	setShadowEnviron(environ);

	// where shadows are rendered
	//environ->setSceneEnviron(e3);
	*/
	abort();
}
void			THIS::setShadowEnviron(
		std::shared_ptr<neb::fnd::environ::Base> environ)
{
	printv_func(DEBUG);

	assert(environ);

	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(environ);
	assert(e);

	shadow_environ_ = e;

	//auto proj = e->getParent()->proj_->proj();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	//glm::mat4 pb = bias * proj;
	glm::mat4 vpb;

	/*
	for(GLint layer = 0; layer < 6; layer++) {

		auto view = e->view_[layer]->view();

		vpb = pb * view;
		shadow_vpb_[layer] = vpb;
	}
	*/
	abort();

	/*
	auto scene = dynamic_cast<neb::gfx::core::scene::base*>(getScene());//getScene();

	// request texture layers
	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(6);

	shadow_sampler_[0].x = texture_layers_->operator[](0);
	shadow_sampler_[0].y = texture_layers_->operator[](1);
	shadow_sampler_[0].z = texture_layers_->operator[](2);
	shadow_sampler_[1].x = texture_layers_->operator[](3);
	shadow_sampler_[1].y = texture_layers_->operator[](4);
	shadow_sampler_[1].z = texture_layers_->operator[](5);

	light_array_slot_->set<10>(shadow_vpb_[0]);
	light_array_slot_->set<11>(shadow_vpb_[1]);
	light_array_slot_->set<12>(shadow_vpb_[2]);
	light_array_slot_->set<13>(shadow_vpb_[3]);
	light_array_slot_->set<14>(shadow_vpb_[4]);
	light_array_slot_->set<15>(shadow_vpb_[5]);

	light_array_slot_->set<16>(shadow_sampler_[0]);
	light_array_slot_->set<17>(shadow_sampler_[1]);
	*/
}
void		THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	printv_func(DEBUG);

	gal::itf::shared::serialize(ar, v);
	neb::gfx::core::light::Base::load(ar, v);
}
void		THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	printv_func(DEBUG);

	const_cast<THIS*>(this)->gal::itf::shared::serialize(ar, v);
	//neb::fnd::core::light::base::save(ar, v);
	neb::gfx::core::light::Base::save(ar, v);
}



