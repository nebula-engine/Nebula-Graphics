#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/actor/base.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/Camera/View/ridealong.hh>

neb::gfx::Camera::View::Ridealong::Ridealong(std::shared_ptr<neb::gfx::environ::base> parent, weak_ptr<neb::core::core::actor::base> actor):
	neb::gfx::Camera::View::base(parent),
	actor_(actor)
{
}
mat4		neb::gfx::Camera::View::Ridealong::view() {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	
	auto actor = actor_.lock();
	if(!actor) return mat4();

	//auto pose = actor_->pose_;
	
	vec3 translate_vec(actor->pose_.pos_);

	//mat4 translate(mat4(-pose.p));
	//translate.SetTranslation(-pose.p);

	quat rotation(actor->pose_.rot_);
	
	//mat4 m(pose);
	//pose.Invert();


	// offset vector relative to object
	vec3 offset_vec(0.0,-1.0,-4.0);

	// transform offset vector to object space
	//rotate.rotate(offset_v);
	offset_vec = rotation * offset_vec;
	
	
	
	// create matrix from offset vector
	//mat4 offset_m = glm::translate(offset_vec);
	//offset_m.SetTranslation(offset_v);
	
	
	mat4 ret = glm::affineInverse(actor->pose_.mat4_cast());
	
	ret = glm::translate(ret, offset_vec);
	
	//math::mat44 ret = pose * offset_m;
	//math::mat44 ret = offset_m * pose.GetInverse();
	//math::mat44 ret = translate;//.GetInverse();

	//ret.SetTranslation(math::vec3(0.0,0.0,-5.0));
	
	/*
	std::cout << "inverse" << std::endl;
	//mInv.print();

	std::cout << "det(m) = " << m.det() << std::endl;

	std::cout << "view" << std::endl;
	//ret.print();
	*/
	return mat4(ret);
}
void neb::gfx::Camera::View::Ridealong::step(gal::etc::timestep const & ts) {
	
}




