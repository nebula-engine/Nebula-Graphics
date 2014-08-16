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
#include <neb/gfx/glsl/program.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>

neb::gfx::mesh::mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
neb::gfx::mesh::~mesh() {
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::gfx::mesh::construct(math::geo::polyhedron* poly) {

	auto tris = poly->triangles();
	
	printf("%s\n",__PRETTY_FUNCTION__);
	
	LOG(lg, neb::gfx::sl, info) << "tris: " << tris.size();


	
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

	LOG(lg, neb::gfx::sl, info) << "vertices: " << vertices_.size();
	LOG(lg, neb::gfx::sl, info) << "indices:  " << indices_.size();


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
		shared_ptr<neb::gfx::context::base> context,
		shared_ptr<neb::glsl::program> p)
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

	auto bufs(sp::make_shared<neb::gfx::core::buffer>());
	context_[context.get()] = bufs;

	// image
	//if(0)//if(flag_.all(neb::core::core::shape::flag::e::IMAGE))
	//if(texture_)
	//{
	//	texture_->init_buffer(bufs);
	//}


	glGenBuffers(1, &bufs->indices_);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);

	// vertices

	glGenBuffers(1, &bufs->vbo_);
	//glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(neb::vertex));
	checkerror("glGenBuffers");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	

	vertexAttribPointer(bufs, p);

	buffer_data(bufs);
}
void			neb::gfx::mesh::vertexAttribPointer(
		shared_ptr<neb::gfx::core::buffer> buf,
		shared_ptr<neb::glsl::program> p)
{

	static math::geo::vertex v;
	static long off_position = (long)&(v.p[0])  - (long)&v;
	static long off_normal =   (long)&(v.n[0])  - (long)&v;
	static long off_texcoor =  (long)&(v.tc[0]) - (long)&v;
	static long off_tangent =  (long)&(v.tangent[0]) - (long)&v;
	static long off_binormal = (long)&(v.binormal[0]) - (long)&v;

	glBindBuffer(GL_ARRAY_BUFFER, buf->vbo_);
	
	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_position);
	checkerror("glVertexAttribPointer position");

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_normal);
	checkerror("glVertexAttribPointer normal");

	if(texture_ || normal_map_) {
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(math::geo::vertex),
				(void*)off_texcoor);
		checkerror("glVertexAttribPointer texcoor");
	}
	if(normal_map_) {
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::TANGENT)->o_,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(math::geo::vertex),
				(void*)off_tangent);
		checkerror("glVertexAttribPointer tangent");
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::BINORMAL)->o_,
				3,
				GL_FLOAT,
				GL_FALSE,
				sizeof(math::geo::vertex),
				(void*)off_binormal);
		checkerror("glVertexAttribPointer binormal");
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void			neb::gfx::mesh::buffer_data(std::shared_ptr<neb::gfx::core::buffer> buf) {

	int size_i = indices_.size() * sizeof(GLushort);
	int size_v = vertices_.size() * sizeof(math::geo::vertex);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->indices_);
	glBindBuffer(GL_ARRAY_BUFFER, buf->vbo_);

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

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
void			neb::gfx::mesh::draw_elements(
		std::shared_ptr<neb::gfx::context::base> context,
		std::shared_ptr<neb::glsl::program> p,
		neb::core::pose const & pose,
		glm::vec3 scale)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(context);

	// initialize buffers if not already
	if(!context_[context.get()])
	{	
		init_buffer(context, p);
	}
	auto bufs = context_[context.get()];

	vertexAttribPointer(bufs, p);

	if(!bufs) return;

	// attribs
	p->get_attrib(neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->enable();
	if(texture_ || normal_map_)
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	if(normal_map_) {
		p->get_attrib(neb::attrib_name::e::TANGENT)->enable();
		p->get_attrib(neb::attrib_name::e::BINORMAL)->enable();
	}
	// material
	material_front_.load();

	// texture
	if(normal_map_) {
		LOG(lg, neb::gfx::sl, debug) << "activate normal map";
		glActiveTexture(GL_TEXTURE0);//checkerror("glActiveTexture");
		normal_map_->bind(context);
		p->get_uniform_scalar("normal_map")->load(0);
	}
	if(texture_) {
		LOG(lg, neb::gfx::sl, debug) << "activate texture";
		glActiveTexture(GL_TEXTURE1);//checkerror("glActiveTexture");
		texture_->bind(context);
		p->get_uniform_scalar("image")->load(1);
	}


	// load modelview matrix
	LOG(lg, neb::gfx::sl, debug) << "load modelview matrix";
	mat4 space = pose.mat4_cast() * glm::scale(scale);
	p->get_uniform_scalar("model")->load(space);

	// bind
	LOG(lg, neb::gfx::sl, debug) << "bind vbo";
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);//checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	checkerror("glBindBuffer");

	// draw
	LOG(lg, neb::gfx::sl, debug) << "draw";
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, 0);

	// unbind
	LOG(lg, neb::gfx::sl, debug) << "unbind vbo";
	glBindBuffer(GL_ARRAY_BUFFER, 0);//checkerror("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	checkerror("glBindBuffer 0");

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
