
#include <neb/core/context/Base.hpp>

#include <neb/gfx/context/util/Parent.hh>
#include <neb/gfx/context/fbo.hpp>
#include <neb/gfx/context/fbo_multi.hpp>
#include <neb/gfx/environ/vis_depth.hpp>

typedef neb::fnd::context::FBO		C_FBO;
typedef neb::fnd::context::FBOM	C_FBOM;
typedef neb::fnd::context::Window	C_W;

typedef neb::gfx::context::util::parent THIS;

void				THIS::render()
{
	auto lamb = [&] (pointer p) {
		p->render();
	};

	map_.for_each(lamb);

}
std::weak_ptr<C_W>		THIS::createContextTwo() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<C_W> w;
	{
		auto context = createContextWindow().lock();
		//auto context(make_shared<>(self));
		//assert(context);
		//insert(context);

		auto environ = context->createEnvironTwo().lock();

		context->init(this);

		w = context;
	}
	assert(!w.expired());
	return w;
}
std::weak_ptr<C_W>		THIS::createContextThree() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<C_W> w;
	{
		auto context = createContextWindow().lock();
		//	auto context = std::make_shared<neb::gfx::context::window>(self);
		//	assert(context);
		//	insert(context);

		auto environ = context->createEnvironSceneDefault().lock();

		context->init(this);

		//assert(environ->view_);
		//environ->view_->connect(self);

		w = context;
	}
	assert(!w.expired());
	return w;
}
std::weak_ptr<C_W>		THIS::createContextNormalMap() {

	auto self = isWindowBase();
	assert(self);

	std::weak_ptr<C_W> w;
	{
		auto context = createContextWindow().lock();
		//	auto context = std::make_shared<neb::gfx::context::window>(self);
		//	assert(context);
		//	insert(context);

		auto environ = context->createEnvironVisualizationNormal().lock();

		context->init(this);

		//assert(environ->view_);
		//environ->view_->connect(self);

		w = context;
	}
	assert(!w.expired());
	return w;
}


