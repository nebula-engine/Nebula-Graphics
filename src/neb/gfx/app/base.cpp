#include <neb/core/except/base.hpp>
#include <neb/gfx/app/base.hpp>

std::weak_ptr<neb::gfx::app::base>		neb::gfx::app::base::initialize()
{
	assert(!g_app_);

	
/*
	typedef neb::gfx::app::base T;

	auto app = std::shared_ptr<T>(new T());

	g_app_ = app;


	//app->neb::app::__core::init();
	
	app->neb::gfx::app::__gfx::init();
	app->neb::gfx::app::__gfx_glsl::__init();

	return app;
	*/

	throw neb::core::except::NotImplemented();

	return std::weak_ptr<neb::gfx::app::base>();
}
void					neb::gfx::app::base::__init() {
}
void					neb::gfx::app::base::release() {
	nc::app::__core::release();
	
	neb::gfx::app::__gfx::release();
	//neb::gfx::app::__gfx_glsl::release();
}
void					neb::gfx::app::base::step(gal::etc::timestep const & ts) {

	//neb::core::app::__base::step(ts);
	nc::app::__core::__step(ts);
	
	neb::gfx::app::__gfx::step(ts);
	//neb::gfx::app::__gfx_glsl::step(ts);
}
void					neb::gfx::app::base::loop() {
	while(!flag_.any(neb::core::app::util::flag::E::SHOULD_RELEASE)) {
		::std::cout << "loop1" << ::std::endl;
		ts_.step(glfwGetTime());
		step(ts_);
	}
}




