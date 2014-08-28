#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>

#include <gal/stl/helper.hpp>

#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/util/io.hpp>
#include <neb/gfx/glsl/util/decl.hpp>



namespace neb { namespace gfx {
	template<class... T> class array_basic {
		public:
			typedef typename gens<sizeof...(T)>::type	seq_type;

			template<int... S> void			alloc(seq<S...>, int n) {
				pass((std::get<S>(data_) = new T[n])...);
			}
			void					set(int i, T... value) {
				set(seq_type(), i, value...);
			}
			template<int... S> void			set(seq<S...>, int i, T... value) {
				pass((std::get<S>(data_)[i] = value)...);
			}
			template<int I, typename U> void	set(int i, U const & u) {
				std::get<I>(data_)[i] = u;
			}
		
			std::tuple<T*...>			data_;
	};
	template<class... T> class array: public array_basic<T...> {
		public:
			typedef typename gens<sizeof...(T)>::type	seq_type;
			void				alloc(int n) {
				array_basic<T...>::alloc(seq_type(), n);

				closed = new int[n];

				for(int i = 0; i < n; i++) {
					closed[i] = 0;
				}

				size = 0;
			}
			int				reg_array(T... initial) {
				// search for empty slot
				int i = 0;
				while(closed[i]) i++;

				// mark slot as filled
				closed[i] = 1;

				// update size
				if((i+1) > size) size = i + 1;

				// initial values
				array_basic<T...>::set(i, initial...);

				// return position to object so it can access it later
				return i;
			}
			void					unreg_array(int i) {
				closed[i] = 0;

				if((i+1) == size) {
					while(!closed[size-1]) size--;
				}
			}
			template<int I, typename U> void	set_array(int i, U const & u) {
				array_basic<T...>::template set<I>(i,u);
			}
		protected:
			int*					closed;
			GLsizei					size;

	};
}}

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
				pass(load_uniform__<S>(location)...);
			}
			template<int I> int			load_uniform__(GLint* location) {


				if(load[I] == 1) {

					std::cout << "load_uniform__ I=" << I << " loc=" << location[I] << std::endl;
					for(int i = 0; i < neb::gfx::array<T...>::size; i++) {
						std::cout << std::setw(32) << std::get<I>(neb::gfx::array_basic<T...>::data_)[i] << std::endl;
					}

					neb::gfx::ogl::glUniformv(
							location[I],
							neb::gfx::array<T...>::size,
							std::get<I>(neb::gfx::array_basic<T...>::data_));
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
	class light_array: public array<
			   glm::vec3,	// 0position
			   glm::vec4,	// 1ambient
			   glm::vec4,	// 2diffuse
			   glm::vec4,	// 3specular
			   float,	// 4atten const
			   float,	// 5atten linear
			   float,	// 6atten quad
			   glm::vec3,	// 7spot direction
			   float,	// 8spot cutoff
			   float,	// 9spot exponent
			   glm::mat4,	// 0shadow vpb matrix 0
			   glm::mat4,	// 1shadow vpb matrix 1
			   glm::mat4,	// 2shadow vpb matrix 2
			   glm::mat4,	// 3shadow vpb matrix 3
			   glm::mat4,	// 4shadow vpb matrix 4
			   glm::mat4,	// 5shadow vpb matrix 5
			   glm::vec3,	// 6shadow sampler 0
			   glm::vec3,	// 7shadow sampler 1
			   int		// 8type
					       >
	{
		public:
			light_array() {}
			void		set_pos(int i, glm::vec3 const & pos) {
				set<0>(i, pos);
			}
			void		set_spot_direction(int i, glm::vec3 const & pos) {
				set<7>(i, pos);
			}
			void		set_shadow_vpb_0(int i, glm::mat4 const & v) {
				set<10>(i, v);
			}
			void		set_shadow_sampler_0(int i, glm::vec3 const & v) {
				set<16>(i, v);
			}
	};
	class light_locations: public light_array::loc_type {
		public:
			void		init(std::shared_ptr<neb::gfx::glsl::program::threed> program);
	};
}}}}



#endif

