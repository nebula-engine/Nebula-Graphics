#include <glm/gtc/matrix_transform.hpp>


#include <neb/core/free.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/core/actor/base.hpp>
#include <neb/core/util/wrapper.hpp>

#include <neb/gfx/app/base.hpp>

#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/three.hpp>
#include <neb/gfx/GUI/Object/terminal.hh>
/*#include <neb/core/light/Spot.hh>
#include <neb/core/scene/Local.hh>
#include <neb/core/shape/Box.hh>
#include <neb/core/shape/empty.hpp>
#include <neb/core/actor/RigidDynamic/Local.hh>
#include <neb/game/map/base.hpp>
#include <neb/ext/maze/game/map/maze2.hpp>
#include <neb/util/command.hpp>
#include <neb/util/command_set.hpp>

*/
int main() {
	
	auto app = neb::gfx::app::base::initialize().lock();
	
	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	//auto context1 = create_context_three(window);
	//auto context2 = create_context_two(window);

	// layout
	//auto layout = create_layout(window, context2);

	// loop

	app->loop();

}



