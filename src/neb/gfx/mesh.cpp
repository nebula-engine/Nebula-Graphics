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

neb::gfx::mesh::mesh() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::~mesh() {
	//printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::construct(math::geo::polyhedron* poly) {

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
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_iarchive & ar, unsigned int const & version) {
	
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
void		neb::gfx::mesh::serialize(boost::archive::polymorphic_oarchive & ar, unsigned int const & version) {

	printf("%s\n",__PRETTY_FUNCTION__);
	
	ar & vertices_;
	ar & indices_;
	
	
	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();

}
void		neb::gfx::mesh::print(int sl) {
	LOG(lg, neb::gfx::sl, (severity_level)sl) << "mesh";

	for(auto v : vertices_) {
		v.print(sl);
	}	
}
void			neb::gfx::mesh::init_buffer(
		shared_ptr<neb::gfx::glsl::program::threed> p)
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

	auto bufs(std::make_shared<neb::gfx::glsl::buffer::mesh>());
	buffers_[p.get()] = bufs;

	bufs->init(p);

	buffer_data(bufs);
}
void			neb::gfx::mesh::buffer_data(std::shared_ptr<neb::gfx::glsl::buffer::mesh> buf) {
	
	assert(!indices_.empty());
	assert(!vertices_.empty());

	int size_i = indices_.size() * sizeof(GLushort);
	int size_v = vertices_.size() * sizeof(math::geo::vertex);
	
	buf->bind();


	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size_i,
			&indices_[0],
			GL_STATIC_DRAW);

	glBufferData(
			GL_ARRAY_BUFFER,
			size_v,
			&vertices_[0],
			GL_STATIC_DRAW);

	buf->unbind();

}
void			neb::gfx::mesh::draw_elements(
		std::shared_ptr<neb::gfx::glsl::program::threed> p,
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
void			neb::gfx::mesh::draw_elements(
		std::shared_ptr<neb::gfx::glsl::program::threed>	p,
		std::shared_ptr<neb::gfx::glsl::buffer::mesh>		buf,
		neb::core::pose const & pose,
		glm::vec3 scale)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	buf->vertexAttribPointer(p);

	// attribs
	p->get_attrib(neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->enable();
	p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	p->get_attrib(neb::attrib_name::e::TANGENT)->enable();
	p->get_attrib(neb::attrib_name::e::BINORMAL)->enable();

	// Uniforms
	// ========
	// material
	material_front_.load(p);

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
	p->get_attrib(neb::attrib_name::e::POSITION)->disable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->disable();
	if(texture_ || normal_map_)
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->disable();
	if(normal_map_) {
		p->get_attrib(neb::attrib_name::e::TANGENT)->disable();
		p->get_attrib(neb::attrib_name::e::BINORMAL)->disable();
	}

}
