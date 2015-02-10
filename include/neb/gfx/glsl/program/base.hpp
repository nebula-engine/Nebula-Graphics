#ifndef NEB_GFX_GLSL_PROGRAM_BASE_HPP
#define NEB_GFX_GLSL_PROGRAM_BASE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <vector>

#include <neb/core/util/decl.hpp>
#include <neb/core/glsl/program/Base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/glsl/program/util/flag.hpp>

namespace neb { namespace gfx { namespace glsl { namespace program {
	/**/
	class Base:
		virtual public neb::fnd::glsl::program::Base
	{
		public:
			enum {
				VERT = 0,
				FRAG = 1
			};
			Base(std::string);
			virtual ~Base();
			virtual void		init();
			void			restoreDefaultShaderFlags();
			void			add_shader(std::string, GLenum);
			void			add_shaders(std::vector<neb::gfx::glsl::shader>);
			void			compile();
			void			use() const;
			void			locate();
			void			scanUniforms();
			virtual int		get_attrib_table_value(int key) const;
			virtual int		get_uniform_table_value(int key) const;

			GLuint			o_;
			std::string		name_;


			int			shader_[2];

			GLint			attrib_table_[neb::gfx::glsl::attribs::COUNT];
			GLint			uniform_table_[neb::gfx::glsl::uniforms::COUNT];

			neb::gfx::glsl::program::util::flag_shader	flag_shader_;
			neb::gfx::glsl::program::util::flag_shader	flag_shader_def_;
	};
}}}}

#endif
