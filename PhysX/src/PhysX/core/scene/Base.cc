#include <stdio.h>

#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>


#include <Nebula/Scene/Base.hh>
#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Actor/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>

//#include <math/free.hpp>

#include <Nebula/Actor/Util/Type.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Message/Actor/Create.hh>
#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/network/message.hh>
//#include <Nebula/Util/Typed.hh>
#include <Nebula/Memory/smart_ptr.hh>

#include <Nebula/config.hh> // nebula/config.hpp.in
#include <Nebula/App/Base.hh>
#include <Nebula/Physics.hh>
#include <Nebula/simulation_callback.hh>
//#include <Nebula/actor/free.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>
#include <Nebula/Actor/Controller/Base.hh>
//#include <Nebula/actor/vehicle.hh>
#include <Nebula/Actor/empty.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/timer/Types.hh>
#include <Nebula/timer/Actor/Release.hpp>

neb::Scene::Base::Base(sp::shared_ptr<neb::Scene::Util::Parent> parent):
	parent_(parent),
	user_type_(0),
	px_filter_shader_(NULL),
	simulation_callback_(NULL),
	px_scene_(NULL),
	last_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
neb::Scene::Base::~Base() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void neb::Scene::Base::init() {
	GLUTPP_DEBUG_0_FUNCTION;
	
	create_physics();
}
void neb::Scene::Base::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
physx::PxMat44		neb::Scene::Base::get_pose() {
	return physx::PxMat44();
}
void neb::Scene::Base::render(double time,
		std::shared_ptr<neb::gfx::Camera::View::Base> view,
		std::shared_ptr<neb::gfx::Camera::Projection::Base> proj,
		sp::shared_ptr<neb::gfx::Window::Base> window) {

	GLUTPP_DEBUG_1_FUNCTION;

	assert(view);
	assert(proj);

	auto p = neb::App::Base::globalBase()->use_program(neb::program_name::e::LIGHT);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	view->load();
	proj->load();

	int i = 0;
	
	typedef neb::Util::Parent<neb::Actor::Base> A;
	
	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->load_lights(i, physx::PxMat44());
	});

	p->get_uniform_scalar("light_count")->load(i);

	//printf("%i\n",i);

	draw(window);
}
void neb::Scene::Base::draw(sp::shared_ptr<neb::gfx::Window::Base> window) {
	GLUTPP_DEBUG_1_FUNCTION;

	typedef neb::Util::Parent<neb::Actor::Base> A;
	
	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->draw(window, physx::PxTransform());
	});

}
void neb::Scene::Base::resize(int w, int h) {
}



physx::PxTransform				neb::Scene::Base::getPose() {
	return physx::PxTransform();
}
physx::PxTransform				neb::Scene::Base::getPoseGlobal() {
	return physx::PxTransform();
}
/*neb::weak_ptr<neb::Actor::Base>		neb::Scene::Base::get_actor(int i) {
	auto it = actors_.find(i);
	std::shared_ptr<neb::Actor::Base> a;
	if(it == actors_.end())
	{
		return a;
	} else {
		a = boost::dynamic_pointer_cast<neb::Actor::Base>(it->second);
		assert(a);
		return a;
	}
}*/
/*neb::weak_ptr<neb::Actor::Base>		neb::Scene::Base::get_actor(neb::Actor::addr> addr) {
	
	std::deque<int> vec = addr->vec_;
	assert(vec);
	
	assert(!vec.empty());
	//if(vec.empty()) return actor;
	
	int i = vec.front();
	vec.pop_front();
	
	auto actor = get_actor(i);
	
	//if(!actor) return actor;
	
	
	if(!vec.empty())
	{
		return actor->get_actor(addr);
	}
	
	return actor;
}*/
/*void neb::Scene::Base::create_actors(std::shared_ptr<glutpp::scene::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	assert(desc);
	
	for(auto it = desc->actors_.cbegin(); it != desc->actors_.cend(); ++it) {
		auto ad = *it;

		switch(ad->raw_wrapper_.ptr_->mode_create_) {
			case glutpp::actor::mode_create::NOW:
				printf("NOW\n");
				create_actor_local(ad);
				break;
			case glutpp::actor::mode_create::DEFERRED:
				printf("DEFERRED\n");
				add_deferred(ad);
				break;
			default:
				printf("invalid mode\n");
				abort();
		}
	}
}*/
void		neb::Scene::Base::add_deferred(sp::shared_ptr<neb::Actor::Base> actor) {
	//NEBULA_DEBUG_0_FUNCTION;

	actors_deferred_[actor->name_] = actor;
}
/*std::shared_ptr<neb::Actor::Base>	neb::Scene::Base::create_actor(std::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;
	
	auto me = boost::dynamic_pointer_cast<neb::Scene::Base>(shared_from_this());

	long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;
	neb::unique_ptr<neb::Actor::Base> actor((neb::Actor::Base*)neb::Factory<glutpp::actor::actor>::global()->alloc(hash_code));
	
	actor->init(desc);
	
	return std::shared_ptr<neb::Actor::Base>();
}
neb::weak_ptr<neb::Actor::Base>			neb::Scene::Base::create_actor_local(std::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto actor = create_actor(desc);

	actors_.push_back(actor);

	// network
	
	auto app = get_app();

	std::shared_ptr<gal::network::omessage> msg(new gal::network::omessage);

	int type = glutpp::network::type::ACTOR_CREATE;
	msg->write(&type, sizeof(int));
	
	//std::shared_ptr<glutpp::network::actor::create> actor_create(new glutpp::network::actor::create);
	
	glutpp::network::actor::create actor_create;

	actor_create.load(actor);
	
	msg->ar_ << actor_create;
	
	//actor_create->write(msg);

	app->send_server(msg);

	return actor;	
}
neb::weak_ptr<neb::Actor::Base>			neb::Scene::Base::create_actor_remote(std::shared_ptr<glutpp::actor::addr> addr, std::shared_ptr<glutpp::actor::desc> desc) {
	NEBULA_DEBUG_0_FUNCTION;

	auto parent = get_actor(addr);

	neb::weak_ptr<neb::Actor::Base> weak;
	
	if(parent) {
		weak = parent->create_actor_remote(addr, desc);
	} else {
		int i = desc->i_;
		//actor = create_actor(desc);


		auto me = boost::dynamic_pointer_cast<neb::Scene::Base>(shared_from_this());

		long int hash_code = desc->raw_wrapper_.ptr_->type_.val_;

		neb::unique_ptr<neb::Actor::Base> actor((neb::Actor::Base*)neb::Factory<glutpp::actor::actor>::global()->alloc(hash_code));
		
		actor->init(desc);
		
		neb::Map<glutpp::actor::actor>::value_type p;
		p.first = i;
		p.second.swap(actor);

		actors_.map_.insert(p);
		
		weak = actor;
	}

	return actor;
}*/
/*

 */
/*
   neb::Scene::Base::rigid_static_t neb::scene::scene::Create_Rigid_Static_Plane(
   glutpp::actor::desc* ad,
   neb::Scene::Base::base_t) {

   printf("%s\n", __PRETTY_FUNCTION__);

// create
std::shared_ptr<neb::Actor::Rigid_Static> actor(new neb::actor::Rigid_Static);

// PxMaterial
physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);


actor->pose_ = ad->raw_.pose_.to_math();

physx::PxPlane p(
ad->raw_.n_.to_math(),
ad->raw_.d_);

// PxActor
physx::PxRigidStatic* px_rigid_static = PxCreatePlane(*(neb::__physics.px_physics_), p, *px_mat);

if (!px_rigid_static)
{
printf("create shape failed!");
exit(1);
}

actor->px_actor_ = px_rigid_static;

// userData
px_rigid_static->userData = actor.get();

//printf("box=%p\n",box);


// add PxActor to PxScene
px_scene_->addActor(*px_rigid_static);

add_actor(actor);

return actor;
}

neb::Scene::Base::controller_t neb::scene::scene::Create_Controller(neb::Actor::desc* ad) {
printf("%s\n",__FUNCTION__);

//jess::scoped_ostream( &jess::clog, neb_FUNCSIG );
// create
std::shared_ptr<neb::Actor::Controller> actor(new neb::actor::Controller);

physx::PxMaterial* px_mat = neb::__physics.px_physics_->createMaterial(1,1,1);

// description
math::vec3 p = ad->raw_.pose_.p.to_math();

physx::PxExtendedVec3 position(p.x, p.y, p.z);

physx::PxCapsuleControllerDesc desc;

desc.position = position;
desc.height = 1.0;
desc.radius = 0.5;
desc.scaleCoeff = 1.0;
desc.volumeGrowth = 2.0;
desc.density = 1000.0;
desc.slopeLimit = 0.707;
desc.stepOffset = 1.0;
desc.contactOffset = 1.0;
desc.material = px_mat;
desc.climbingMode = physx::PxCapsuleClimbingMode::eEASY;
desc.userData = actor.get();


actor->px_controller_ = neb::__physics.px_character_controller_manager_->createController(
		*neb::__physics.px_physics_, px_scene_, desc );

return actor;
}
neb::Scene::Base::vehicle_t neb::scene::scene::create_vehicle() {

	neb::Actor::desc* desc = new neb::actor::desc;
	//desc.raw_.reset();

	glutpp::shape::desc* sd = NULL;

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(3,1,6));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);

	sd = new glutpp::shape::desc;
	sd->raw_.box(math::vec3(0.5,1,1));
	desc->shapes_.push_back(sd);


	neb::Scene::Base::vehicle_t vehicle;

	vehicle = vehicle_manager_.create_vehicle(
			neb::__physics.px_physics_,
			px_scene_,
			desc);


	add_actor(vehicle);

	return vehicle;
}
*/
void neb::Scene::Base::create_physics() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	auto pxphysics = neb::Physics::global()->px_physics_;
	
	physx::PxSceneDesc scene_desc(pxphysics->getTolerancesScale());

	scene_desc.gravity = gravity_;

	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

	int m_nbThreads = 1;

	// cpu dispatcher
	printf("cpu dispatcher\n");
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher =
			::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );

		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	printf("filter shader\n");
	if(!scene_desc.filterShader)
	{
		if(px_filter_shader_)
		{
			scene_desc.filterShader = px_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
	printf("gpu dispatcher\n");
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif
	assert( scene_desc.isValid() );

	px_scene_ = pxphysics->createScene(scene_desc);
	assert(px_scene_);

	// simulation callback
	neb::simulation_callback* sec = new neb::simulation_callback;
	simulation_callback_ = sec;
	px_scene_->setSimulationEventCallback(sec);
}
void		neb::Scene::Base::step(double const & time, double const & dt) {
	//NEBULA_DEBUG_1_FUNCTION;

	typedef neb::Util::Parent<neb::Actor::Base> A;

	A::map_.for_each([&] (A::map_type::const_iterator it) {
		it->second.ptr_->step(time, dt);
	});
	
	// extras
	//printf("desc size = %i\n", (int)desc_size());
}
void neb::Scene::Base::send_actor_update() {
	//printf("DEBUG: message ACTOR_UPDATE sent\n");
	
	
	//int type = glutpp::network::type::ACTOR_UPDATE;
	//msg->write(&type, sizeof(int));
	
	sp::shared_ptr<neb::Message::Actor::OUpdate> message(new neb::Message::Actor::OUpdate);
	
	typedef neb::Util::Parent<neb::Actor::Base> A;

	A::map_.for_each([&] (A::map_type::const_iterator it) {
			if(it->second.ptr_->flag_.any(neb::Actor::Util::Flag::SHOULD_UPDATE)) {
			message->actors_.push_back(it->second.ptr_);
			}
			});


	neb::App::Base::globalBase()->sendServer(message);
}





