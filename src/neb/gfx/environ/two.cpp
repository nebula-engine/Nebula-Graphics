#include <neb/fnd/glsl/program/Base.hpp>
#include <neb/fnd/plug/gfx/app/Base.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/environ/two.hpp>
//#include <neb/gfx/glsl/program/base.hpp> removed by c_header_checker
#include <neb/fnd/RenderDesc.hpp>

void			neb::gfx::environ::Two::render(
		neb::fnd::context::Base * const & context)
{
	printv_func(DEBUG);

	/**
	 * prepare rendering environment and then call the drawable
	 */

	//GLUTPP_DEBUG_1_FUNCTION;
	
	auto drawable = getParent()->drawable_.lock();

	assert(drawable);
	//if(!drawable) return;

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::glsl::global().lock();
	auto app = get_fnd_app()->G::get_object();

	/** wrong for color maybe! */	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);

	
	// get program choice from drawable
	/** @todo replace with 'environ' which determines program and camera types and accepts certian types of drawables */
	
	//app->get_program_text()->use();
	
	//drawable->draw(context, app->program_text_, 0);
	drawable->draw(neb::fnd::RenderDesc());
}		





