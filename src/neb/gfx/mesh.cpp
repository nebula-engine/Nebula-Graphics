#include <iostream>
#include <iomanip>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <glm/gtx/transform.hpp>

#include <gal/log/log.hpp>

#include <neb/core/math/geo/polyhedron.hh>
#include <neb/core/util/debug.hpp>

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
void		neb::gfx::mesh::draw_elements(
		sp::shared_ptr<neb::gfx::context::base> context,
		sp::shared_ptr<neb::glsl::program> p,
		neb::core::pose const & pose,
		glm::vec3 scale)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	//mesh_.print(debug);

	assert(context);

	/** @todo could switching programs here leave view and proj unset? */

	// initialize buffers if not already
	//	if(!context_[window.get()])
	{	
		init_buffer(context, p);
	}
	auto bufs = context_[context.get()];

	//assert(bufs);
	if(!bufs) return;
	
	//checkerror("unknown");

	// attribs
	p->get_attrib(neb::attrib_name::e::POSITION)->enable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->enable();

	if(0) //if(flag_.all(neb::core::core::shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->enable();
	}

	// material
	//printf("load material\n");
	material_front_.load();

	// texture
	if(0) //if(flag_.all(neb::core::core::shape::flag::e::IMAGE))
	{
		glActiveTexture(GL_TEXTURE0);
		//checkerror("glActiveTexture");
		bufs->texture_.image_->bind();
		p->get_uniform_scalar("image")->load(0);
	}

	//printf("bind vbo\n");
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
	//checkerror("glBindBuffer");
	//printf("bind elements\n");// indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	//checkerror("glBindBuffer");

	// load modelview matrix
	mat4 space = pose.mat4_cast() * glm::scale(scale);
	
	p->get_uniform_scalar("model")->load(space);
	
	
	// draw
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, 0);
	//checkerror("glDrawElements");

	//glDrawElements(GL_LINES, mesh_.indices_.size(), GL_UNSIGNED_SHORT, 0);
	//checkerror("glDrawElements");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//checkerror("glBindBuffer");

	p->get_attrib(neb::attrib_name::e::POSITION)->disable();
	p->get_attrib(neb::attrib_name::e::NORMAL)->disable();

	if(0) //if(flag_.all(neb::core::core::shape::flag::e::IMAGE))
	{
		p->get_attrib(neb::attrib_name::e::TEXCOOR)->disable();
	}
}
void			neb::gfx::mesh::init_buffer(sp::shared_ptr<neb::gfx::context::base> context, sp::shared_ptr<neb::glsl::program> p) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	glEnable(GL_TEXTURE_2D);

	if(indices_.empty()) {
		printf("not initialized\n");
		//assert(0);
		// return instead of abort so shape::base objects for making lights can pass through
		/// @todo need better system for this (like seperate mesh objects that implement this function!!
		return;
	}

	//checkerror("unknown");

	auto bufs(sp::make_shared<neb::gfx::core::buffer>());
	context_[context.get()] = bufs;

	// image
	if(0)//if(flag_.all(neb::core::core::shape::flag::e::IMAGE))
	{
		bufs->texture_.image_.reset(new neb::texture);

		//bufs->texture_.image_->load_png(raw_.image_);
	}

	// indices
	int size = indices_.size() * sizeof(GLushort);

	glGenBuffers(1, &bufs->indices_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->indices_);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			size,
			&indices_[0],
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	// vertices

	glGenBuffers(1, &bufs->vbo_);

	//int baseOffset = 0;
	glBindBuffer(GL_ARRAY_BUFFER, bufs->vbo_);
	//glBindVertexBuffer(0, vbo_, baseOffset, sizeof(neb::vertex));

	math::geo::vertex v;
	long off_position = (long)&(v.p[0])  - (long)&v;
	long off_normal =   (long)&(v.n[0])  - (long)&v;
	long off_texcoor =  (long)&(v.tc[0]) - (long)&v;

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::POSITION)->o_,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_position);
	//checkerror("glVertexAttribPointer");

	glVertexAttribPointer(
			p->get_attrib(neb::attrib_name::e::NORMAL)->o_,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(math::geo::vertex),
			(void*)off_normal);
	//checkerror("glVertexAttribPointer normal");

	if(0) {//if(flag_.all(neb::core::core::shape::flag::e::IMAGE)) 
		glVertexAttribPointer(
				p->get_attrib(neb::attrib_name::e::TEXCOOR)->o_,
				2,
				GL_FLOAT,
				GL_FALSE,
				sizeof(math::geo::vertex),
				(void*)off_texcoor);
		//checkerror("glVertexAttribPointer texcoor");
	}

	size = vertices_.size() * sizeof(math::geo::vertex);
	glBufferData(
			GL_ARRAY_BUFFER,
			size,
			&vertices_[0],
			GL_STATIC_DRAW);

	//checkerror("glBufferData");

	//glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}



