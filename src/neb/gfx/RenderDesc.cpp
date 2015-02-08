#include <neb/gfx/RenderDesc.hpp>

typedef neb::gfx::RenderDesc THIS;

THIS::RenderDesc():
	v(0),
	p(0),
	d3(0),
	d3_inst(0)
{
}
THIS::RenderDesc(
		camera::view::Base* nv,
		camera::proj::Base* np,
		glsl::program::Base* nd3,
		glsl::program::Base* nd3_HF,
		glsl::program::Base* nd3_inst):
	v(nv),
	p(np),
	d3(nd3),
	d3_HF(nd3_HF),
	d3_inst(nd3_inst)
{
}

