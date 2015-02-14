#include <neb/gfx/gui/layout/util/parent.hpp>

typedef neb::gfx::gui::layout::util::parent THIS;

neb::fnd::app::Base*		neb::gfx::gui::layout::util::parent::get_fnd_app()
{
	auto a = dynamic_cast<neb::fnd::app::Base*>(this);
	assert(a);
	return a;
}

