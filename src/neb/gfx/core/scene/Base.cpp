
#include <neb/fnd/math/geo/polyhedron.hpp>
#include <neb/fnd/RenderDesc.hpp>
#include <neb/fnd/DebugBuffer.hpp>
#include <neb/fnd/camera/proj/Base.hpp>
#include <neb/fnd/camera/view/Base.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hpp>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/texture/Base.hpp>
//#include <neb/gfx/util/log.hpp> removed by c_header_checker

typedef neb::gfx::core::scene::base THIS;

typedef neb::fnd::core::actor::util::parent A;
typedef neb::fnd::glsl::program::Base P;

THIS::base()
{}
THIS::~base()
{}
void			THIS::__init(parent_t * const & p)
{
	LOG(lg, neb::gfx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	// graphics

	// use _M_programs._M_d3 as completion flag
	if(!_M_programs._M_d3)
	{
		// programs
		_M_programs._M_d3.reset(new neb::gfx::glsl::program::threed("3d"));
		_M_programs._M_d3->init();

		_M_programs._M_d3_HF.reset(new neb::gfx::glsl::program::threed("3d_HF"));
		_M_programs._M_d3_HF->init();

		_M_programs._M_d3_inst.reset(new neb::gfx::glsl::program::threed("3d_inst"));
		_M_programs._M_d3_inst->init();

		init_light();
		
		initMeshes();

		unsigned int shadow_tex_size = 512;

		tex_shadow_map_.reset(new neb::gfx::texture::Base());

		tex_shadow_map_->init_shadow(
				shadow_tex_size,
				shadow_tex_size,
				std::shared_ptr<neb::gfx::context::base>());
	}
}
void			THIS::initMeshes()
{
	if(!meshes_.cuboid_)
	{
		// meshes
		neb::fnd::math::geo::cuboid cube(1.0,1.0,1.0);

		meshes_.cuboid_.reset(new neb::gfx::mesh::instanced);
		meshes_.cuboid_->mesh_.construct(&cube);

		meshes_.cuboid_->instances_.reset(new neb::gfx::mesh::instanced::instances_type);
		meshes_.cuboid_->instances_->alloc(2048);
	}
}
void			THIS::init_light()
{
	LOG(lg, neb::gfx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	if(!light_array_[0])
	{
		// light arrays
		light_array_[0].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[0]->alloc(32);

		light_array_[1].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[1]->alloc(32);
	}
}
void			THIS::draw(neb::fnd::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(desc.p);
	assert(desc.v);

	drawMesh(desc);
	drawMeshHF(desc);
	drawMeshInst(desc);
}
void			THIS::drawMesh(neb::fnd::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.

	P* d3;

	if(desc.d3) {
		d3 = desc.d3;
	} else {
		assert(_M_programs._M_d3);
		d3 = _M_programs._M_d3.get();
	}

	assert(d3);

	d3->use();

	desc.p->load(d3);
	desc.v->load(d3);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3);

	assert(light_array_[0]->size() > 0);

	// individual meshes
	auto la = [&] (A::map_type::pointer p)
	{
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
		assert(actor);
		actor->draw(d3, neb::fnd::math::pose());
	};

	A::map_.for_each(la);
}
void			THIS::drawMeshHF(neb::fnd::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.

	P* p;

	if(desc.d3_HF) {
		p = desc.d3_HF;
	} else {
		assert(_M_programs._M_d3_HF);
		p = _M_programs._M_d3_HF.get();
	}

	assert(p);

	p->use();

	desc.p->load(p);
	desc.v->load(p);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(p);

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawHF(p, neb::fnd::math::pose());
	};

	A::map_.for_each(la);

}
void			THIS::drawMeshInst(neb::fnd::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	P* d3_inst;

	if(desc.d3_inst) {
		d3_inst = desc.d3_inst;
	} else {
		assert(_M_programs._M_d3);
		d3_inst = _M_programs._M_d3_inst.get();
	}

	assert(d3_inst);

	d3_inst->use();

	desc.p->load(d3_inst);
	desc.v->load(d3_inst);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3_inst);

	if(tex_shadow_map_) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(tex_shadow_map_->target_, tex_shadow_map_->o_);

		GLint loc = d3_inst->get_uniform_table_value(neb::gfx::glsl::uniforms::TEX_SHADOW_MAP);
		neb::gfx::ogl::glUniform(loc, 0);
	}

	// meshes
	assert(meshes_.cuboid_);
	meshes_.cuboid_->draw(d3_inst);

}
void			THIS::drawDebug(
		neb::fnd::RenderDesc const & desc)
{
	//auto app(neb::gfx::app::glsl::global().lock());
	auto app = get_fnd_app();

	auto g = app->_M_graphics_object;
	assert(g);
	auto p = g->get_program_simple3();
	p->use();

	desc.p->load(p.get());
	desc.v->load(p.get());

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawDebug(p.get(), neb::fnd::math::pose());
	};

	A::map_.for_each(la);

}
void			THIS::resize(int w, int h)
{
}
void			THIS::draw_debug_buffer(
		neb::fnd::RenderDesc const & desc,
		neb::fnd::DebugBuffer const & db)
{
	auto g = get_fnd_app()->_M_graphics_object;
	assert(g);

	auto p = g->get_program_simple3();
	p->use();

	desc.p->load(p.get());
	desc.v->load(p.get());

	glClear(GL_DEPTH_BUFFER_BIT);


	/*
	LOG(lg, neb::phx::core::scene::sl, debug) << "Debug visualization";
	LOG(lg, neb::phx::core::scene::sl, debug) << "number of points    " << rb.getNbPoints();
	LOG(lg, neb::phx::core::scene::sl, debug) << "number of lines     " << nblines;
	LOG(lg, neb::phx::core::scene::sl, debug) << "number of triangles " << nbtriangles;
	*/

	GLint i_color = p->get_attrib_table_value(neb::gfx::glsl::attribs::COLOR);

	glEnableVertexAttribArray(p->get_attrib_table_value(neb::gfx::glsl::attribs::POSITION));
	if(i_color > -1)
		glEnableVertexAttribArray(i_color);

	GLuint buf;
	glGenBuffers(1, &buf);
	glBindBuffer(GL_ARRAY_BUFFER, buf);


	// lines
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(neb::fnd::DebugLine) * db.nblines,
			db.lines,
			GL_STREAM_DRAW
		    );

	glVertexAttribPointer(
			p->get_attrib_table_value(neb::gfx::glsl::attribs::POSITION),
			3,
			GL_FLOAT,
			GL_FALSE,
			16,
			0);


	if(i_color > -1)
		glVertexAttribIPointer(
				p->get_attrib_table_value(neb::gfx::glsl::attribs::COLOR),
				1,
				GL_UNSIGNED_INT,
				16,
				(GLvoid*)12);

	glDrawArrays(GL_LINES, 0, db.nblines * 2);

	checkerror("");

	// triangles
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(neb::fnd::DebugTriangle) * db.nbtriangles,
			db.triangles,
			GL_STREAM_DRAW
		    );

	glVertexAttribPointer(
			p->get_attrib_table_value(neb::gfx::glsl::attribs::POSITION),
			3,
			GL_FLOAT,
			GL_FALSE,
			16,
			0);


	if(i_color > -1)
		glVertexAttribIPointer(
				p->get_attrib_table_value(neb::gfx::glsl::attribs::COLOR),
				1,
				GL_UNSIGNED_INT,
				16,
				(GLvoid*)12);

	glDrawArrays(GL_TRIANGLES, 0, db.nbtriangles * 3);

	checkerror("");

	// cleanup
	glDisableVertexAttribArray(p->get_attrib_table_value(neb::gfx::glsl::attribs::POSITION));
	if(i_color > -1)
		glDisableVertexAttribArray(p->get_attrib_table_value(neb::gfx::glsl::attribs::COLOR));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


