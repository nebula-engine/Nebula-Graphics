#include <stdio.h>

#include <Galaxy-Log/log.hpp>

//#include <neb/gfx/window/Base.hh>
//#include <neb/gfx/Context/Base.hh>

#include <neb/core/debug.hh>
#include <neb/core/util/config.hpp>
#include <neb/core/light/base.hpp>
#include <neb/core/actor/util/Type.hh>

#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/glsl/program.hpp>
#include <neb/gfx/Camera/Projection/Perspective.hh>



#include <neb/gfx/core/shape/base.hpp>
#include <neb/timer/Types.hh>
#include <neb/timer/Actor/Release.hpp>
#include <neb/gfx/glsl/Uniform/scalar.hpp>
#include <neb/core/light/util/light_count.hpp>

using namespace std;

neb::gfx::core::scene::base::base(sp::shared_ptr<neb::core::core::scene::util::parent> parent):
	neb::core::core::scene::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
neb::gfx::core::scene::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::scene::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
}
void			neb::gfx::core::scene::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;
	
	neb::core::core::scene::base::release();
}
void			neb::gfx::core::scene::base::draw(
		sp::shared_ptr<neb::gfx::context::base> context,
		sp::shared_ptr<neb::glsl::program> p) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core scene", debug) << __PRETTY_FUNCTION__;



	neb::core::light::util::count light_count;

	typedef neb::core::actor::util::parent A;

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::gfx::core::actor::base>(it->ptr_);
			assert(actor);
			actor->load_lights(light_count, neb::core::pose());
			});

	p->get_uniform_scalar("light_count_point")->load(light_count.point);
	p->get_uniform_scalar("light_count_spot")->load(light_count.spot);
	p->get_uniform_scalar("light_count_directional")->load(light_count.directional);

	//printf("%i\n",i);


	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = sp::dynamic_pointer_cast<neb::gfx::core::actor::base>(it->ptr_);
			assert(actor);
			actor->draw(context, p, neb::core::pose());
			});

}
void						neb::gfx::core::scene::base::resize(int w, int h) {
}
void						neb::gfx::core::scene::base::step(gal::std::timestep const & ts) {
}
/*weak_ptr<neb::core::actor::base>		neb::gfx::core::scene::base::createActorBase(neb::core::pose const & pose) {
	auto actor(make_shared<neb::gfx::core::actor::base>(isSceneBase()));
	insert(actor);
	return actor;
}*/
weak_ptr<neb::core::actor::base>		neb::gfx::core::scene::base::createActorLightPoint(vec3 p) {

	neb::core::pose pose(p);
	
	auto actor = createActorBase(pose).lock();
	
	insert(actor);

	auto shape = actor->createShapeBase(neb::core::pose()).lock();

	shape->createLightPoint();

	return actor;
}



