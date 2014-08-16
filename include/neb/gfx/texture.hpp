#ifndef __GRU_TEXTURE_H__
#define __GRU_TEXTURE_H__

#include <functional>
#include <map>

#define PNG_SKIP_SETJMP_CHECK
#include <png.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <neb/gfx/util/decl.hpp>

using namespace std;

namespace neb { namespace gfx {
	class texture {
		public:
			//typedef std::shared_ptr<WINDOW>		WINDOW_S;
			//typedef std::weak_ptr<WINDOW>		WINDOW_W;

			typedef map< neb::gfx::context::base*, GLuint >		map_t;

			texture();
			~texture();
			//void			init(WINDOW_S);
			void			init_shadow(int,int, shared_ptr<neb::gfx::context::base> context);

			int			load_png(char const *);

			GLuint			init_buffer(shared_ptr<neb::gfx::context::base> context);
			GLuint			genAndBind(shared_ptr<neb::gfx::context::base> context);


			void			bind(shared_ptr<neb::gfx::context::base> context);

			png_uint_32		w_;
			png_uint_32		h_;

			png_byte*		png_image_data_;

			map_t			buffers_;
	};
}}

#endif








