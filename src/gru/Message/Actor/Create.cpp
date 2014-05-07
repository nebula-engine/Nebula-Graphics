
#include <gru/actor/addr.hpp>
#include <gru/actor/actor.hpp>
#include <gru/Message/Actor/Create.hpp>

void		glutpp::network::actor::create::load(Neb::unique_ptr<glutpp::actor::actor> actor) {
	assert(actor);
	
	addr_.load_parent(actor);

	desc_.load(actor);
	
}









