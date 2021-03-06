
#include <neb/fnd/core/light/util/parent.hpp>
#include <neb/fnd/window/Base.hpp>
#include <neb/fnd/context/FBO.hpp>
#include <neb/fnd/environ/shadow/Directional.hpp>

#include <neb/gfx/core/light/Directional.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/app/base.hpp>
#include <neb/gfx/core/light/Base.hpp>
#include <neb/gfx/window/Base.hpp>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hpp>
#include <neb/gfx/context/fbo.hpp>
//#include <neb/gfx/util/log.hpp> removed by c_header_checker
#include <neb/gfx/core/scene/base.hpp>

typedef neb::gfx::core::light::Directional THIS;

THIS::Directional()
{

}
neb::gfx::core::light::type::e		THIS::getType()
{
	return neb::gfx::core::light::type::DIRECTIONAL;
}
void					THIS::init(parent_t * const & p)
{
	setParent(p);
	
	neb::gfx::core::light::Base::init(p);
	

	/* shadow stuff
	auto scene = std::dynamic_pointer_cast<neb::gfx::core::scene::base>(getScene()->shared_from_this());

	auto self = std::dynamic_pointer_cast<neb::gfx::core::light::directional>(shared_from_this());
	
	auto app = get_fnd_app();

	
	//auto window = app->neb::gfx::window::util::parent::create<neb::gfx::window::base>().lock();
	auto window = app->createWindow().lock();
	//neb::gfx::window::util::parent::create<neb::gfx::window::base>().lock();

	auto context = window->createContextFBO().lock();
	
	auto environ = context->createEnvironShadowDirectional().lock();
	
	environ->set_drawable(scene);
	
	context->setTexture(scene->tex_shadow_map_);

	environ->setLight(self);

	setShadowEnviron(environ);
	*/
}
void					THIS::v_set_pose_data(
		FND * const & fnd,
		gal::math::pose const & gpose)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::light::sl, debug) << gpose.mat4_cast();
	
	//auto scene = getScene();
	
	//scene->light_array_[light_array_].set_pos(light_array_slot_, gpose.pos_);
}
void					THIS::setShadowEnviron(std::shared_ptr<neb::fnd::environ::Base> environ)
{
	abort();
	/*
	assert(environ);
	
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::directional>(environ);

	shadow_environ_ = e;
	
	assert(e);
	
	auto proj = e->proj_->proj();
	auto view = e->view_->view();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	glm::mat4 vpb = bias * proj * view;
	
	// request texture layers
	auto scene = dynamic_cast<neb::gfx::core::scene::base*>(getScene());

	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(1);

	shadow_sampler_[0].x = texture_layers_->operator[](0);

	shadow_vpb_[0] = vpb;
	
	// light array
	
	light_array_slot_->set<10>(shadow_vpb_[0]);
			
	light_array_slot_->set<16>(shadow_sampler_[0]);
	*/
}
void					THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::fnd::core::light::base);
}
void		THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	//BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::fnd::core::light::base);
}



