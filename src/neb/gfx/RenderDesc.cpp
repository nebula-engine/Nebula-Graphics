#include <neb/fnd/RenderDesc.hpp>

typedef neb::fnd::RenderDesc THIS;

THIS::RenderDesc():
	v(0),
	p(0),
	d3(0),
	d3_inst(0)
{
}
THIS::RenderDesc(
		neb::fnd::camera::view::Base* nv,
		neb::fnd::camera::proj::Base* np,
		neb::fnd::glsl::program::Base* nd3,
		neb::fnd::glsl::program::Base* nd3_HF,
		neb::fnd::glsl::program::Base* nd3_inst):
	v(nv),
	p(np),
	d3(nd3),
	d3_HF(nd3_HF),
	d3_inst(nd3_inst)
{
}

