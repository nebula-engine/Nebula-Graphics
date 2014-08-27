#include <iostream>
#include <iomanip>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <glm/gtx/transform.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>
#include <neb/core/util/debug.hpp>

#include <neb/gfx/free.hpp>
#include <neb/gfx/core/mesh.hh>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::mesh::tri1::tri1() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::tri1::~tri1() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::tri1::construct(math::geo::polyhedron* poly) {

	auto tris = poly->triangles();
	
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::sl, debug) << "tris: " << tris.size();


	
	for(size_t i = 0; i < (3 * tris.size()); ++i) {
		indices_.push_back(i);
	}
	
	
	for(auto t : tris) {
		assert(t);
		for(int i = 0; i < 3; ++i) {
			assert(t->v_[i]);
			vertices_.push_back(*(t->v_[i]));
		}
	}

	LOG(lg, neb::gfx::sl, debug) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, debug) << "indices:  " << indices_.size();


}
void		neb::gfx::mesh::tri1::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	/*std::string filename = std::string(GLUTPP_OBJECT_DIR) + "/" + name;
	
	FILE * fp;
	
	std::cout << "load file " << filename << std::endl;

	fp = fopen(filename.c_str(), "rb");

	if (fp <= 0) {
		perror("fopen");
		abort();
	}*/
	
	ar & vertices_;
	ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::tri1::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	ar & vertices_;
	ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::tri1::print(int sl) {
	LOG(lg, neb::gfx::sl, (severity_level)sl) << "mesh";

	for(auto v : vertices_) {
		v.print(sl);
	}	
}
void			neb::gfx::mesh::tri1::init_buffer(
		program_shared p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//glEnable(GL_TEXTURE_2D);

	if(indices_.empty()) {
		printf("not initialized\n");
		//assert(0);
		// return instead of abort so shape::base objects for making lights can pass through
		/// @todo need better system for this (like seperate mesh objects that implement this function!!
		return;
	}

	checkerror("unknown");

	auto bufs(std::make_shared<neb::gfx::glsl::buffer::tri1>());
	buffers_[p.get()] = bufs;

	bufs->init(p);

	bufferData(bufs);
}

void			neb::gfx::mesh::tri1::draw_elements(
		program_shared p,
		neb::core::pose const & pose,
		glm::vec3 scale)
{

	// initialize buffers if not already
	if(!buffers_[p.get()])
	{	
		init_buffer(p);
	}
	auto buf = buffers_[p.get()];

	if(!buf) return;

	draw_elements(p, buf, pose, scale);

}
void			neb::gfx::mesh::tri1::draw_elements(
		program_shared						p,
		std::shared_ptr<neb::gfx::glsl::buffer::tri1>		buf,
		neb::core::pose const & pose,
		glm::vec3 scale)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	buf->vertexAttribPointer();

	// attribs
/*	p->get_attrib(neb::gfx::glsl::attribs::POSITION)->enable();
	p->get_attrib(neb::gfx::glsl::attribs::NORMAL)->enable();
	p->get_attrib(neb::gfx::glsl::attribs::TEXCOOR)->enable();
	p->get_attrib(neb::gfx::glsl::attribs::TANGENT)->enable();
	p->get_attrib(neb::gfx::glsl::attribs::BINORMAL)->enable();
*/
	// Uniforms
	// ========
	// material
	//material_front_.load(p);

	/*	// texture
		if(normal_map_) {
		LOG(lg, neb::gfx::sl, debug) << "activate normal map";
		glActiveTexture(GL_TEXTURE0);//checkerror("glActiveTexture");
		normal_map_->bind(context);
		p->get_uniform_scalar("normal_map")->load(0);

		p->get_uniform_scalar("has_normal_map")->load_b(true);
		} else {
		p->get_uniform_scalar("has_normal_map")->load_b(false);
		}

		if(texture_) {
		LOG(lg, neb::gfx::sl, debug) << "activate texture";
		glActiveTexture(GL_TEXTURE1);//checkerror("glActiveTexture");
		texture_->bind(context);
		p->get_uniform_scalar("texture")->load(1);

		p->get_uniform_scalar("has_texture")->load_b(true);
		} else {
		p->get_uniform_scalar("has_texture")->load_b(false);
		}
		*/
/*
	// load modelview matrix
	LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
	mat4 space = pose.mat4_cast() * glm::scale(scale);
	p->get_uniform_scalar("model")->load(space);

	// bind
	LOG(lg, neb::gfx::sl, debug) << "bind vbo";
	buf->bind();

	// draw
	LOG(lg, neb::gfx::sl, debug) << "draw";
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, 0);

	// unbind
	LOG(lg, neb::gfx::sl, debug) << "unbind vbo";
	buf->unbind();

	// attribs
	p->get_attrib(neb::gfx::glsl::attribs::POSITION)->disable();
	p->get_attrib(neb::gfx::glsl::attribs::NORMAL)->disable();
	if(texture_ || normal_map_)
		p->get_attrib(neb::gfx::glsl::attribs::TEXCOOR)->disable();
	if(normal_map_) {
		p->get_attrib(neb::gfx::glsl::attribs::TANGENT)->disable();
		p->get_attrib(neb::gfx::glsl::attribs::BINORMAL)->disable();
	}
*/
}
