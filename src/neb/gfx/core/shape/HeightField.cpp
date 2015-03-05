
#include <neb/fnd/math/HeightField.hpp>

#include <neb/gfx/core/shape/HeightField/Base.hpp>

typedef neb::gfx::core::shape::HeightField::Base THIS;

THIS::Base()
{}
void			THIS::mesh_from_heightfield(neb::fnd::math::HeightField::Base* hf, float rowScale, float colScale)
{
	auto parent = dynamic_cast<neb::fnd::core::shape::HeightField::Base*>(getParent());
	assert(parent);

	unsigned int r = hf->_M_r;
	unsigned int c = hf->_M_c;
	unsigned int nbVerts = r * c;


	unsigned int nbTriangles = (r - 1) * (c - 1) * 2;
	unsigned int nbIndices = nbTriangles * 3;

	std::vector<neb::fnd::math::geo::vertex> vertices(nbVerts);
	std::vector<unsigned short> indices(nbIndices);
	

	parent->min_y_ = hf->min();
	parent->max_y_ = hf->max();
	
	hf->slope(rowScale, colScale);

	for(unsigned int i = 0; i < r; i++)
	{
		for(unsigned int j = 0; j < c; j++)
		{
			int ind = hf->at(i,j);

			if(1) {
				vertices[hf->at(i,j)].p = glm::vec3(
						(float)i * rowScale,
						(float)j * colScale,
						hf->get(i,j)
						);

				vertices[ind].tc = glm::vec2(
						(float)i / (float)(r-1),
						(float)j / (float)(c-1)
						);

				vertices[hf->at(i,j)].n = glm::vec3(
						-hf->_M_dzdx[hf->at(i,j)],
						-hf->_M_dzdy[hf->at(i,j)],
						2.0 * rowScale
						);
			} else {
				vertices[hf->at(i,j)].p = glm::vec3(
						(float)i * rowScale,
						hf->get(i,j),
						(float)j * colScale
						);

				vertices[ind].tc = glm::vec2(
						(float)i / (float)(r-1),
						(float)j / (float)(c-1)
						);

				vertices[hf->at(i,j)].n = glm::vec3(
						hf->_M_dzdx[hf->at(i,j)],
						2.0 * rowScale,
						hf->_M_dzdy[hf->at(i,j)]
						);
			}
		}
	}


	for(unsigned int i = 0; i < (r-1); i++)
	{
		for(unsigned int j = 0; j < (c-1); j++)
		{
			unsigned int d = (i * (c-1) + j) * 6;

			assert((d+5) < nbIndices);

			if(1) {
				indices[d+0] = hf->at(i    , j    );
				indices[d+1] = hf->at(i + 1, j    );
				indices[d+2] = hf->at(i    , j + 1);

				indices[d+3] = hf->at(i + 1, j    );
				indices[d+4] = hf->at(i + 1, j + 1);
				indices[d+5] = hf->at(i    , j + 1);
			} else {
				// reversed
				indices[d+0] = hf->at(i    , j    );
				indices[d+1] = hf->at(i    , j + 1);
				indices[d+2] = hf->at(i + 1, j    );

				indices[d+3] = hf->at(i + 1, j    );
				indices[d+4] = hf->at(i    , j + 1);
				indices[d+5] = hf->at(i + 1, j + 1);
			}
		}
	}

	mesh_.reset(new neb::gfx::mesh::tri1);

	mesh_->setVerts(vertices);
	mesh_->setIndices(indices);

	// testing generated normal map
	//mesh_->normal_map_ = neb::gfx::texture::makePNG("test.png");

}
void			THIS::draw(
		neb::gfx::glsl::program::Base const * const & p,
		gal::math::pose const & pose)
{}
void			THIS::drawHF(
		FND * const & ptr,
		neb::gfx::glsl::program::Base const * const & p,
		gal::math::pose const & pose)
{
	auto parent = dynamic_cast<neb::fnd::core::shape::HeightField::Base*>(getParent());
	assert(parent);

	auto npose = pose * parent->pose_;

	p->use();

	// load texture height range
	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MIN], parent->min_y_);
	neb::gfx::ogl::glUniform(p->uniform_table_[neb::gfx::glsl::uniforms::HF_MAX], parent->max_y_);


	draw_elements(ptr, p, npose);


}

