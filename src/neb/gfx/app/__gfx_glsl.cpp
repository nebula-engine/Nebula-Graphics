
#include <neb/core/math/geo/polyhedron.hpp>

#include <neb/gfx/util/config.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/mesh/instanced.hpp>

typedef neb::gfx::app::glsl THIS;

/*
std::weak_ptr<neb::gfx::app::glsl>		::global()
{
	auto app(std::dynamic_pointer_cast<neb::gfx::app::__gfx_glsl>(g_app_));
	assert(app);
	return app;
}
*/
void		THIS::__init()
{
}
void		THIS::create_programs()
{
	printf("%s\n", __PRETTY_FUNCTION__);

	std::shared_ptr<neb::gfx::glsl::program::Base> p;

	program_text_.reset(new neb::gfx::glsl::program::Base("text"));
	program_text_->init();

	program_tex_.reset(new neb::gfx::glsl::program::Base("tex"));
	program_tex_->init();

	program_simple3_.reset(new neb::gfx::glsl::program::Base("simple3"));
	program_simple3_->init();

}
/*std::shared_ptr<neb::gfx::glsl::program::Base>		neb::gfx::app::__gfx_glsl::use_program(neb::program_name::e name){
	auto p = get_program(name);

	p->use();

	current_ = p;

	return p;
}
std::shared_ptr<neb::gfx::glsl::program::Base>		neb::gfx::app::__gfx_glsl::current_program(){
	assert(current_);

	return current_;
}*/
/*std::shared_ptr<neb::gfx::glsl::program::Base>		neb::gfx::app::__gfx_glsl::get_program(neb::program_name::e name){
	auto it = programs_.find(name);

	if(it == programs_.end())
	{
		printf("program '%i' not found\n", name);
		exit(0);
	}

	auto p = (*it).second;

	assert(p);

	return p;
	}*/
std::shared_ptr<neb::fnd::glsl::program::Base>		THIS::get_program_text()
{
	return program_text_;
}
std::shared_ptr<neb::fnd::glsl::program::Base>		THIS::get_program_tex()
{
	return program_tex_;
}
std::shared_ptr<neb::fnd::glsl::program::Base>		THIS::get_program_simple3()
{
	return program_simple3_;
}



