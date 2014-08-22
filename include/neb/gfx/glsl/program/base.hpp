#ifndef __DRAW_H__
#define __DRAW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <neb/core/util/decl.hpp>
#include <neb/core/util/typedef.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	class base: public std::enable_shared_from_this<base> {
		public:
			typedef std::map< std::string, std::shared_ptr<neb::gfx::glsl::Uniform::Scalar::base> > uniform_s_map;
			typedef std::map< std::string, std::shared_ptr<neb::gfx::glsl::Uniform::Vector::base> > uniform_v_map;

			base(neb::program_name::e name);
			virtual ~base() {}

			void	init();
			void	add_shader(char const *, GLenum);
			void	add_shaders(::std::vector<neb::gfx::glsl::shader>);
			void	compile();
			void	use();
			void	locate();
			void	scanUniforms();

			void	add_attrib(neb::attrib_name::e, char const *, GLuint);
			void	add_uniform_scalar(::std::string, GLenum);
			void	add_uniform_vector(::std::string, ::std::string, GLenum);

			std::shared_ptr<neb::gfx::glsl::attrib>					get_attrib(int);
			std::shared_ptr<neb::gfx::glsl::Uniform::Scalar::base>			get_uniform_scalar(std::string);
			std::shared_ptr<neb::gfx::glsl::Uniform::Vector::base>			get_uniform_vector(std::string);


			GLuint							o_;

			uniform_s_map						uniform_scalar_;
			uniform_v_map						uniform_vector_;

			std::map<int, std::shared_ptr<neb::gfx::glsl::attrib> >			attrib_;

			neb::program_name::e						name_;
	};
}}}}

#endif
