
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/Context/fbo.hpp>

typedef neb::gfx::context::fbo C;

void					neb::gfx::context::util::parent::render() {

	auto lamb = [&] (iterator<0> it) {
		it->ptr_->render();
	};

	map_.template for_each<0>(lamb);

}
std::weak_ptr<neb::gfx::context::fbo>	neb::gfx::context::util::parent::createContextFBO() {


	auto self(std::dynamic_pointer_cast<neb::gfx::context::util::parent>(shared_from_this()));
	
	std::shared_ptr<C> context(new C(self));
	
	insert(context);

	context->init();

	return context;
}

