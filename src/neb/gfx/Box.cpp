#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>

#include <neb/core/glsl/util/decl.hpp>
#include <neb/core/glsl/program/Base.hpp>
#include <neb/core/core/shape/base.hpp>
#include <neb/core/plug/gfx/core/shape/Base.hpp>

#include <neb/gfx/opengl/uniform.hpp>

#include <neb/plug/gfx1/core/shape/Box.hpp>


typedef neb::fnd::plug::gfx::core::shape::Base		T0;
typedef neb::plug::gfx1::core::shape::Box		T1;

extern "C" T0*	shape_create()
{
	printf("%s\n", __PRETTY_FUNCTION__);
	return new T1;
}
extern "C" void	shape_destroy(T0* t)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	delete t;
}

typedef T1 THIS;

void			THIS::init(parent_t * const & p)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	T0::init(p);
}
void			THIS::draw(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	//printf("%s\n", __PRETTY_FUNCTION__);

	model_load(ptr, p, pose);
	
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

}
void			THIS::step(gal::etc::timestep const & ts)
{
	T0::step(ts);
}
void			THIS::v_set_pose_data(
		FND * const & p,
		neb::fnd::math::pose const & global_pose)
{

}
void			THIS::model_load(
		FND * const & ptr,
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	printf("%s\n", __PRETTY_FUNCTION__);

	assert(ptr);

	printf("pos = %16f %16f %16f\n",
			pose.pos_.x,
			pose.pos_.y,
			pose.pos_.z);

	glm::mat4 space = pose.mat4_cast() * glm::scale(ptr->scale_);

	auto v = p->get_uniform_table_value(neb::gfx::glsl::uniforms::MODEL);

	assert(v != -1);

	neb::gfx::ogl::glUniform(v, space);
}

