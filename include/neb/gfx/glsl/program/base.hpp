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
			typedef std::shared_ptr<neb::gfx::glsl::Uniform::Scalar::base>		single_shared;
			typedef std::shared_ptr<neb::gfx::glsl::Uniform::Vector::base>		array_shared;
			typedef std::shared_ptr<neb::gfx::glsl::attrib>				attrib_shared;
			typedef std::map<std::string, single_shared>				uniform_s_map;
			typedef std::map<std::string, array_shared>				uniform_a_map;
			typedef std::map<int, std::shared_ptr<neb::gfx::glsl::attrib> >		attrib_map;
			
			enum {
				VERT = 0,
				FRAG = 1
			};

			base();
			virtual ~base() = 0;
			
			virtual void		init();
			void			add_shader(char const *, GLenum);
			void			add_shaders(std::vector<neb::gfx::glsl::shader>);
			void			compile();
			void			use();
			void			locate();
			void			scanUniforms();

			//void			add_attrib(neb::gfx::glsl::attribs, char const *, GLuint);
			void			add_uniform_scalar(std::string, GLenum);
			void			add_uniform_vector(std::string, GLenum);

			//attrib_shared		get_attrib(int);
			single_shared		get_uniform_scalar(std::string);
			array_shared		get_uniform_vector(std::string);

			GLuint			o_;

			uniform_s_map		uniform_scalar_;
			uniform_a_map		uniform_vector_;

			attrib_map		attrib_;
			
			int			shader_[2];

			GLint			attrib_table_[neb::gfx::glsl::attribs::COUNT];
	};
}}}}

#endif
