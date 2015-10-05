#include <neb/gfx/texture/util/Parent.hpp>
#include <neb/gfx/core/light/util/Parent.hpp>
#include <neb/gfx/core/light/Base.hpp>

typedef neb::gfx::texture::util::Parent THIS;

neb::fnd::app::Base*		THIS::get_fnd_app()
{
	auto l = is_gfx_light_base();
	assert(l);
	return l->get_fnd_app();
}

