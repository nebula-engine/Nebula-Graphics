
#include <neb/gfx/app/base.hpp>

weak_ptr<neb::gfx::app::base>		neb::gfx::app::base::initialize() {
	assert(!g_app_);
	
	auto app(make_shared<neb::gfx::app::base>());

	g_app_ = app;

	app->init();

	return app;
}
void					neb::gfx::app::base::init() {
	neb::app::__core::init();
	
	neb::app::__gfx::init();
	neb::app::__gfx_glsl::init();
}
void					neb::gfx::app::base::release() {
	neb::app::__core::release();
	
	neb::app::__gfx::release();
	//neb::app::__gfx_glsl::release();
}
void					neb::gfx::app::base::step(gal::std::timestep const & ts) {

	//neb::core::app::__base::step(ts);
	neb::app::__core::step(ts);
	
	neb::app::__gfx::step(ts);
	//neb::app::__gfx_glsl::step(ts);
}
void					neb::gfx::app::base::loop() {
	while(!flag_.any(neb::core::app::util::flag::E::SHOULD_RELEASE)) {
		::std::cout << "loop1" << ::std::endl;
		ts_.step(glfwGetTime());
		step(ts_);
	}
}




