#include <glm/gtc/matrix_transform.hpp>

#include <neb/app/Base.hh>
#include <neb/fnd/actor/base.hpp>
#include <neb/util/wrapper.hpp>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/GUI/Object/terminal.hh>
#include <neb/fnd/light/Spot.hh>
#include <neb/fnd/scene/Local.hh>
#include <neb/fnd/shape/Box.hh>
#include <neb/fnd/shape/empty.hpp>
#include <neb/fnd/actor/RigidDynamic/Local.hh>
#include <neb/game/map/base.hpp>
#include <neb/ext/maze/game/map/maze2.hpp>
#include <neb/util/command.hpp>
#include <neb/util/command_set.hpp>

std::shared_ptr<neb::gfx::context::window>		create_context_two(std::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	
	window->insert(context);

	context->environ_ = sp::make_shared<neb::gfx::environ::two>(/*context*/);

	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, std::shared_ptr<neb::gfx::window::base> >(window);
	
	
	

	return context;
}
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

	auto app = neb::app::base::global();
	
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
std::shared_ptr<neb::fnd::actor::rigiddynamic::local>		create_actor(std::shared_ptr<neb::fnd::scene::local> scene) {

	auto actor = scene->cii<neb::fnd::actor::rigiddynamic::local, std::shared_ptr<neb::fnd::scene::local>>(scene);

	// shape	
	auto shape = sp::make_shared<neb::fnd::shape::box>(actor);
	
	
	actor->neb::fnd::shape::util::parent::insert(shape);
	//actor->insert(shape);
	
	
	shape->init();
	
	return actor;	
}
std::shared_ptr<neb::fnd::actor::rigiddynamic::local>		create_actor2(std::shared_ptr<neb::fnd::scene::local> scene) {
	auto actor = sp::make_shared<neb::fnd::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);
	
	actor->init();
	
	// shape	
	/*
	auto shape = sp::make_shared<neb::fnd::shape::empty>(actor);
	
	actor->neb::fnd::shape::util::parent::insert(shape);
	
	shape->init();
	*/
	auto shape = actor->neb::fnd::shape::util::parent::cii< neb::fnd::shape::empty, std::shared_ptr<neb::fnd::actor::rigiddynamic::local> >(actor);
	
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
}
std::shared_ptr<neb::fnd::scene::local>			create_scene(
		std::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = neb::app::base::global();
	assert(app);
	
	auto scene = sp::make_shared<neb::fnd::scene::local>(app);
	assert(scene);	
	
	app->neb::fnd::scene::util::parent::insert(scene);
	
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



	auto actor2 = create_actor2(scene);




	
	context->environ_->drawable_ = scene;

	return scene;
}
std::shared_ptr<neb::game::map::base>			create_map(
		std::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = neb::app::base::global();
	
	auto map = sp::make_shared<neb::game::map::base>(app);
	
	app->neb::fnd::scene::util::parent::insert(map);
	
	map->init();
	
	// actors
	auto actor = create_actor(map);
	actor->pose_.pos_ += vec4(0,0,-5,0);
	
	actor = create_actor(map);
	actor->pose_.pos_ += vec4(0,0,5,0);
	
	actor = create_actor(map);
	actor->pose_.pos_ += vec4(0,-5,0,0);

	actor = create_actor(map);
	actor->pose_.pos_ += vec4(0,5,0,0);

	actor = create_actor(map);
	actor->pose_.pos_ += vec4(-5,0,0,0);

	actor = create_actor(map);
	actor->pose_.pos_ += vec4(5,0,0,0);



	auto actor2 = create_actor2(map);




	
	context->environ_->drawable_ = map;

	return map;
}
std::shared_ptr<neb::game::map::base>			create_maze(
		std::shared_ptr<neb::gfx::context::window> context) {
	
	auto app = neb::app::base::global();
	
	auto map = sp::make_shared<neb::ext::maze::game::map::maze2>(app, ivec2(15,15));
	
	app->neb::fnd::scene::util::parent::insert(map);
	
	map->init();

	auto actor2 = create_actor2(map);
	
	context->environ_->drawable_ = map;

	return map;
}
int main() {

	neb::init();

	auto app = neb::app::base::global();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context_three(window);
	auto context2 = create_context_two(window);

	// drawable
	// scene
	
	
	std::shared_ptr<neb::game::map::base> map;

	// command
	// create scene
	auto cmd_create_scene = sp::make_shared<neb::util::command>();

	cmd_create_scene->func_ = [&] (std::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		(*term) << "creating scene...";
		map = create_maze(context1);
	};
	
	app->command_set_->map_["sc"] = cmd_create_scene;
	
	// destroy scene
	auto cmd_destroy_scene = sp::make_shared<neb::util::command>();
	
	cmd_destroy_scene->func_ = [&] (std::shared_ptr<neb::util::terminal> term, bpo::variables_map vm) {
		(*term) << "destroying scene...";
		if(map) {
			map->parent_->erase(map->i_);
			map.reset();
		}
		std::stringstream ss;
		ss << "use count " << map.use_count();
		(*term) << ss.str();
	};
	
	app->command_set_->map_["sd"] = cmd_destroy_scene;
	
	//auto scene = create_scene(context1);
	//auto map = create_map(context1);
	//auto map = create_maze(context1);


	auto layout = create_layout(window, context2);

	// loop

	app->loop();

}



