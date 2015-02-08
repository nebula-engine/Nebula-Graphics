#include <glm/gtc/matrix_transform.hpp>


#include <neb/core/free.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>

#include <neb/gfx/app/base.hpp>

#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/GUI/Object/terminal.hh>
#include <neb/gfx/camera/view/Base.hh>

/*#include <neb/core/light/Spot.hh>
#include <neb/core/scene/Local.hh>
#include <neb/core/shape/empty.hpp>*/
#include <neb/gfx/core/shape/box.hpp>
#include <neb/core/actor/base.hpp>
/*#include <neb/game/map/base.hpp>
#include <neb/ext/maze/game/map/maze2.hpp>
#include <neb/util/command.hpp>
#include <neb/util/command_set.hpp>

*/


std::shared_ptr<neb::gfx::context::window>		create_context_three(std::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	
	window->insert(context);
	


	auto environ = sp::make_shared<neb::gfx::environ::three>(/*context*/);
	environ->init();

	context->environ_ = environ;




	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, std::shared_ptr<neb::gfx::window::base> >(window);
	
	
	environ->view_->connect(window);

	return context;
}

std::shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		std::shared_ptr<neb::gfx::window::base> window,
		std::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::app::__gfx::global().lock();
	
	//auto layout = app->neb::gfx::gui::layout::util::parent::cii<neb::gfx::gui::layout::base, neb::app::base>(app);


	auto layout = sp::make_shared<neb::gfx::gui::layout::base>(app);

	app->neb::gfx::gui::layout::util::parent::insert(layout);

	
	context->environ_->drawable_ = layout;

	layout->connect(window);

	// object
	auto term = sp::make_shared<neb::gfx::gui::object::terminal>();

	layout->insert(term);

	term->init();

	return layout;
}
std::shared_ptr<neb::fnd::actor::base>		create_actor(std::shared_ptr<neb::fnd::core::scene::base> scene) {

	auto actor = scene->cii<neb::gfx::core::actor::base, std::shared_ptr<neb::fnd::core::scene::base>>(scene);
	
	// shape	
	auto shape = sp::make_shared<neb::gfx::core::shape::box>(actor);
	
	
	actor->neb::fnd::shape::util::parent::insert(shape);
	//actor->insert(shape);
	
	
	shape->init();
	
	return actor;	
}
/*std::shared_ptr<neb::fnd::actor::base>		create_actor2(std::shared_ptr<neb::fnd::core::scene::base> scene) {
	auto actor = sp::make_shared<neb::gfx::core::actor::base>(scene);
	
	scene->insert(actor);
	
	actor->init();
	
	// shape	
	
	//auto shape = sp::make_shared<neb::fnd::shape::empty>(actor);
	
	//actor->neb::fnd::shape::util::parent::insert(shape);
	
	//shape->init();
	
	auto shape = actor->neb::fnd::shape::util::parent::cii< neb::fnd::shape::empty, std::shared_ptr<neb::fnd::actor::base> >(actor);
	
	// light
	auto light = sp::make_shared<neb::fnd::light::Point>(shape);
	
	shape->neb::fnd::light::util::parent::insert(light);
	
	light->init();
	
	// another light
	
	light = sp::make_shared<neb::fnd::light::Point>(shape);
	
	shape->neb::fnd::light::util::parent::insert(light);
	
	light->init();

	light->pos_ = vec3(10,0,0);

	return actor;	
}*/
std::shared_ptr<neb::fnd::core::scene::base>			create_scene(
		std::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = neb::app::__core::global().lock();
	
	auto scene = sp::make_shared<neb::gfx::core::scene::base>(app);
	assert(scene);	
	
	app->neb::fnd::core::scene::util::parent::insert(scene);
	
	scene->init();
	
	// actors
	auto actor = create_actor(scene);
	actor->pose_.pos_ += vec4(0,0,-5,0);
	
	actor = create_actor(scene);
	actor->pose_.pos_ += vec4(0,0,5,0);
	
	actor = create_actor(scene);
	actor->pose_.pos_ += vec4(0,-5,0,0);

	actor = create_actor(scene);
	actor->pose_.pos_ += vec4(0,5,0,0);

	actor = create_actor(scene);
	actor->pose_.pos_ += vec4(-5,0,0,0);

	actor = create_actor(scene);
	actor->pose_.pos_ += vec4(5,0,0,0);



	//auto actor2 = create_actor2(scene);

	
	context->environ_->drawable_ = scene;

	return scene;
}

int main() {
	
	auto app = neb::gfx::app::base::initialize().lock();
	
	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context_three(window);
	//auto context2 = create_context_two(window);

	auto scene = create_scene(context1);

	// layout
	//auto layout = create_layout(window, context2);

	// loop

	app->loop();

}



