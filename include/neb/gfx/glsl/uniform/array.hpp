#ifndef NEB_GFX_GLSL_UNIFORM_ARRAY_HPP
#define NEB_GFX_GLSL_UNIFORM_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>

#include <gal/stl/helper.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array.hpp>


namespace neb { namespace gfx { namespace glsl { namespace uniform {
	template<int I> class locations;

	/** @brief array
	 * abstract class for managing sequential data arrays.
	 * So data for arrays of uniforms can be loaded faster.
	 *
	 * For example, an array is used for light positions.
	 * The core light object is stored elsewhere and registers for a slot in the array.
	 *
	 * Used by:
	 * lights
	 *
	 */
	template<class... T> class array: public neb::gfx::array<T...> {
		public:
			typedef locations<sizeof...(T)+2>		loc_type;
			typedef typename gens<sizeof...(T)>::type	seq_type;
		public:
			virtual int				reg(T... initial) {
				int i = neb::gfx::array<T...>::reg_array(initial...);
				
				// mark for load
				for(int j = 0; j < sizeof...(T); j++) {
					load[j] = 1;
				}
				load_closed = 1;
				load_any = 1;

				return i;
			}
			void					unreg(int i) {
				neb::gfx::array<T...>::unreg_array(i);

				load_closed = 1;
				load_any = 1;
			}
			template<int I, typename U> void	set(int i, U const & u) {
				neb::gfx::array<T...>::template set_array<I>(i, u);

				load[I] = 1;
				load_any = 1;
			}
			void					load_uniform(GLint* location) {
				if(load_any == 1) {
					load_uniform(seq_type(), location);

					if(load_closed == 1) {

						neb::gfx::ogl::glUniformv(
								location[sizeof...(T)],
								neb::gfx::array<T...>::size,
								neb::gfx::array<T...>::closed);

						load_closed = 0;
					}

					neb::gfx::ogl::glUniform(
							location[sizeof...(T)+1],
							(int)neb::gfx::array<T...>::size);

					std::cout << "load_uniform size=" << neb::gfx::array<T...>::size << std::endl;

					load_any = 0;
				}
			}
			template<int... S> void			load_uniform(seq<S...>, GLint* location) {
				//pass((std::cout << S << std::endl)...);
				pass(load_uniform__<S,T>(location)...);
			}
			template<int I, typename U> int		load_uniform__(GLint* location) {


				if(load[I] == 1) {

					std::cout << "load_uniform__ I=" << I << " loc=" << location[I] << std::endl;
					for(int i = 0; i < neb::gfx::array<T...>::size; i++) {

						//std::get<I>(neb::gfx::array_basic<T...>::data_)[i]
						//neb::gfx::array_basic<T...>::get<I,U>(i)

						std::cout << std::setw(32) << neb::gfx::array_basic<T...>::template get<I,U>(i) << std::endl;
					}

					neb::gfx::ogl::glUniformv(
							location[I],
							neb::gfx::array<T...>::size,
							neb::gfx::array_basic<T...>::template get<I,U>());
					load[I] = 0;
				}
				return 0;
			}
		public:
			int					load[sizeof...(T)];
			int					load_any;
			int					load_closed;
	};
	template<int I> class locations {
		public:
			GLint					location[I];
	};
}}}}



#endif

