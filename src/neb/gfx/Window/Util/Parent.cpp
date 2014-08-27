#include <neb/gfx/util/log.hpp>
#include <neb/gfx/window/util/Parent.hh>

void		neb::gfx::window::util::parent::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto lamb = [&] (iterator<0> it) {
		it->ptr_->render();
	};

	map_.template for_each<0>(lamb);

}

