#include <gal/log/log.hpp>

#include <glm/gtx/transform.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/math/geo/polyhedron.hpp>

#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/shape/box.hpp>

typedef neb::gfx::core::shape::box THIS;

THIS::box()
{
	printv_func(INFO);
}
void			THIS::init(parent_t * const & p)
{
	printv_func(INFO);
	setParent(p);
}
void			THIS::step(gal::etc::timestep const & ts)
{
}
void			THIS::createMesh()
{
	printv_func(DEBUG);

	if(0) {
		create_mesh_instance();
	} else if(0) {
		create_mesh_standalone();
	}
}
void	THIS::create_mesh_instance()
{
	printv_func(DEBUG);

	/// @TODO fix this
	//if(!hasScene()) return;

	auto p = getParent();

	auto scene = dynamic_cast<neb::gfx::core::scene::base*>(p->getScene());
	
	if(!mesh_slot_)
	{
		//LOG(lg, neb::gfx::sl, debug) << "mesh registered";


		auto model = p->getPoseGlobal().mat4_cast() * glm::scale(p->scale_);

		auto dif = neb::fnd::math::color::ucolor8888::rand();
		auto amb = neb::fnd::math::color::color::gray(0.2);
		auto spc = neb::fnd::math::color::color::white();
		auto emi = neb::fnd::math::color::color::black();

		/*		
		LOG(lg, neb::gfx::sl, debug) << "diffuse   " << std::hex << dif;
		LOG(lg, neb::gfx::sl, debug) << "diffuse r " << std::hex << (unsigned int)dif.r;
		LOG(lg, neb::gfx::sl, debug) << "diffuse g " << std::hex << (unsigned int)dif.g;
		LOG(lg, neb::gfx::sl, debug) << "diffuse b " << std::hex << (unsigned int)dif.b;
		LOG(lg, neb::gfx::sl, debug) << "diffuse a " << std::hex << (unsigned int)dif.a;
		//dif.print();
		LOG(lg, neb::gfx::sl, debug) << "ambient";
		//amb.print();
		LOG(lg, neb::gfx::sl, debug) << "specular";
		//spc.print();
		LOG(lg, neb::gfx::sl, debug) << "emission";
		//emi.print();
		*/

		scene->initMeshes();
		assert(scene->meshes_.cuboid_);

		mesh_slot_ = scene->meshes_.cuboid_->instances_->reg(
				model,
				glm::vec4(-1.0,-1.0,-1.0,-1.0),
				(unsigned int)dif,
				amb,
				spc,
				emi,
				100.0
				);
	}
}
void	THIS::create_mesh_standalone()
{
	neb::fnd::math::geo::cuboid cube(1.0,1.0,1.0);

	mesh_.reset(new neb::gfx::mesh::tri1);
	mesh_->construct(&cube);
}
void			THIS::draw_legacy(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		gal::math::pose const & pose)
{
	printv_func(DEBUG);

	// load model matrix
	//LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
	model_load(ptr, p, pose);

	printv(DEBUG, pose);

	//material_.load(p);
	
	//glUseProgram(0);
	//glPushMatrix();
	//glTranslatef(pose.pos_.x, pose.pos_.y, pose.pos_.z);

	//LOG(lg, neb::gfx::sl, debug) << scale_.x << " " << scale_.y << " " << scale_.z;
	//LOG(lg, neb::gfx::sl, debug) << pose.pos_.x << " " << pose.pos_.y << " " << pose.pos_.z;


	// draw
	glBegin(GL_TRIANGLES);
	{
		// front faces
		glNormal3f(0,0,1);
		// face v0-v0.5-v2
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glColor3f(0.5,0.5,0);
		glVertex3f(-0.5,0.5,0.5);
		glColor3f(0.5,0,0);
		glVertex3f(-0.5,-0.5,0.5);
		// face v2-v3-v0
		glColor3f(0.5,0,0);
		glVertex3f(-0.5,-0.5,0.5);
		glColor3f(0.5,0,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);

		// right faces
		glNormal3f(1,0,0);
		// face v0-v3-v4
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glColor3f(0.5,0,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glColor3f(0,0,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		// face v4-v5-v0
		glColor3f(0,0,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glColor3f(0,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);

		// top faces
		glNormal3f(0,1,0);
		// face v0-v5-v6
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glColor3f(0,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glColor3f(0,0.5,0);
		glVertex3f(-0.5,0.5,-0.5);
		// face v6-v0.5-v0
		glColor3f(0,0.5,0);
		glVertex3f(-0.5,0.5,-0.5);
		glColor3f(0.5,0.5,0);
		glVertex3f(-0.5,0.5,0.5);
		glColor3f(0.5,0.5,0.5);
		glVertex3f(0.5,0.5,0.5);

		// left faces
		glNormal3f(-1,0,0);
		// face  v0.5-v6-v7
		glColor3f(0.5,0.5,0);
		glVertex3f(-0.5,0.5,0.5);
		glColor3f(0,0.5,0);
		glVertex3f(-0.5,0.5,-0.5);
		glColor3f(0,0,0);
		glVertex3f(-0.5,-0.5,-0.5);
		// face v7-v2-v0.5
		glColor3f(0,0,0);
		glVertex3f(-0.5,-0.5,-0.5);
		glColor3f(0.5,0,0);
		glVertex3f(-0.5,-0.5,0.5);
		glColor3f(0.5,0.5,0);
		glVertex3f(-0.5,0.5,0.5);

		// bottom faces
		glNormal3f(0,-1,0);
		// face v7-v4-v3
		glColor3f(0,0,0);
		glVertex3f(-0.5,-0.5,-0.5);
		glColor3f(0,0,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glColor3f(0.5,0,0.5);
		glVertex3f(0.5,-0.5,0.5);
		// face v3-v2-v7
		glColor3f(0.5,0,0.5);
		glVertex3f(0.5,-0.5,0.5);
		glColor3f(0.5,0,0);
		glVertex3f(-0.5,-0.5,0.5);
		glColor3f(0,0,0);
		glVertex3f(-0.5,-0.5,-0.5);

		// back faces
		glNormal3f(0,0,-1);
		// face v4-v7-v6
		glColor3f(0,0,0.5);
		glVertex3f(0.5,-0.5,-0.5);
		glColor3f(0,0,0);
		glVertex3f(-0.5,-0.5,-0.5);
		glColor3f(0,0.5,0);
		glVertex3f(-0.5,0.5,-0.5);
		// face v6-v5-v4
		glColor3f(0,0.5,0);
		glVertex3f(-0.5,0.5,-0.5);
		glColor3f(0,0.5,0.5);
		glVertex3f(0.5,0.5,-0.5);
		glColor3f(0,0,0.5);
		glVertex3f(0.5,-0.5,-0.5);
	}
	glEnd();

	//glPopMatrix();

}






