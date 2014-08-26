#ifndef GRU_FREE_HPP
#define GRU_FREE_HPP

#include <memory>
#include <sstream>

#include <gal/stl/helper.hpp>

#include <neb/core/color/Color.hh>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>


namespace neb {
	void	draw_quad(
			std::shared_ptr<neb::gfx::glsl::program::base> p,
			float,
			float,
			float,
			float,
			neb::core::color::color);
	void	draw_text(
			std::shared_ptr<neb::gfx::glsl::program::base> p,
			float,
			float,
			float,
			float,
			neb::core::color::color,
			std::string,
			std::string::size_type pos = std::string::npos);
}

void	checkerror(std::string);

template<typename... T> void	checkerror(T... t) {
	std::stringstream ss;
	pass((ss << t)...);
	checkerror(ss.str());
}

bool	isGLError();

template<class A> A*	new_copy(std::shared_ptr<A> a) {
	if(a) {
		return new A(*a);
	}
	return NULL;
}

#endif

