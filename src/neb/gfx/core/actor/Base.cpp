#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/util/config.hpp>
#include <neb/fnd/core/scene/Base.hpp>
#include <neb/fnd/timer/actor/Base.hpp>
#include <neb/fnd/plug/gfx/core/shape/Base.hpp>
#include <neb/fnd/core/actor/Base.hpp>

#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/window/Base.hpp>

//neb::gfx::core::actor::base::base()

/*neb::gfx::core::actor::base::base(std::shared_ptr<neb::fnd::core::actor::util::parent> parent):
	gal::stl::child<neb::fnd::core::actor::base
	neb::fnd::core::actor::base(parent)
{
	LOG(lg, neb::fnd::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}*/

typedef neb::gfx::core::actor::base THIS;

THIS::~base()
{
	printv_func(DEBUG);
}
void			THIS::init(parent_t * const & p)
{
	setParent(p);
}
void			THIS::step(gal::etc::timestep const & ts)
{
}
void			THIS::draw(
		neb::fnd::glsl::program::Base const * const & program,
		gal::math::pose const & pose)
{
	printv_func(DEBUG);

	auto parent = getParent();

	auto npose = pose * parent->pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	auto lambda_actor = [=] (A::S const & p)
	{
		auto actor = std::dynamic_pointer_cast<THIS>(p);
		assert(actor);
		actor->draw(program, npose);
	};

	auto lambda_shape = [=] (S::S const & p)
	{
		//auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
		//assert(shape);
		//shape->draw(program, npose);

		//if(p->G::has_object()) {
		auto pose3 = npose * p->pose_;
		p->G::get_object()->draw(p.get(), program, pose3);
		//}

	};

	parent->A::for_each(lambda_actor);
	parent->S::for_each(lambda_shape);
}
void				THIS::drawDebug(
		neb::fnd::glsl::program::Base const * const & program,
		gal::math::pose const & pose)
{
	printv_func(DEBUG);

	auto parent = getParent();

	auto npose = pose * parent->pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	parent->A::for_each([&] (A::S const & p) {
			auto actor = std::dynamic_pointer_cast<THIS>(p);
			assert(actor);
			actor->drawDebug(program, npose);
			});

	parent->S::for_each([&] (S::S const & p) {
			/// @TODO fix this
			//auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
			//assert(shape);
			//shape->drawDebug(program, npose);
			});


}
void				THIS::drawHF(
		neb::fnd::glsl::program::Base const * const & program,
		gal::math::pose const & pose)
{
	printv_func(DEBUG);

	auto parent = getParent();

	auto npose = pose * parent->pose_;

	typedef neb::fnd::core::actor::util::parent A;
	typedef neb::fnd::core::shape::util::parent S;

	parent->A::for_each([&] (A::S const & p) {
			auto actor = std::dynamic_pointer_cast<THIS>(p);
			assert(actor);
			actor->drawHF(program, npose);
			});

	parent->S::for_each([&] (S::S const & p) {
			//auto shape = std::dynamic_pointer_cast<neb::gfx::core::shape::base>(p);
			//assert(shape);
			//shape->drawHF(program, npose);
			});


}




