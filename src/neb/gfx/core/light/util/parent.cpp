#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/gfx/core/light/Base.hpp>
#include <neb/gfx/core/light/util/Parent.hpp>

typedef neb::gfx::core::light::util::parent THIS;

/*std::weak_ptr<neb::gfx::core::scene::base>		neb::gfx::core::light::util::parent::getScene() {
	auto shape = isShapeBase();
	assert(shape);

	auto scene1 = shape->getScene();

	return scene1;
}*/
THIS::~parent()
{
}
void			THIS::setPose(gal::math::pose const & pose)
{
	printv_func(DEBUG);
	
	auto lambda_light = [&] (map_type::pointer p) {
		
		auto light = std::dynamic_pointer_cast<neb::gfx::core::light::Base>(p);
		assert(light);
		
		//if(i == neb::fnd::light::light_max) return L::map_type::BREAK;
		
		light->setPose(pose);
		
	};

	for_each(lambda_light);

}
void			neb::gfx::core::light::util::parent::load_lights(
		neb::fnd::core::light::util::count & light_count,
		gal::math::pose const & pose)
{
	printv_func(DEBUG);

	assert(0);

	auto lambda_light = [&] (map_type::pointer p) {

		auto light = std::dynamic_pointer_cast<neb::gfx::core::light::Base>(p);
		assert(light);

		//if(i == neb::fnd::light::light_max) return L::map_type::BREAK;

		//light->load(light_count, pose);

	};

	for_each(lambda_light);

}

