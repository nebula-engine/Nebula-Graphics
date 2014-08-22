#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

#include <tuple>
#include <memory>

#include <gal/stl/helper.hpp>

#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

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
	template<class... T> class array {
		public:
			typedef locations<sizeof...(T)>		loc_type;
		public:
			void				alloc(int n) {
				alloc(typename gens<sizeof...(T)>::type(), n);

				closed = new int[n];

				for(int i = 0; i < n; i++) {
					closed[i] = 0;
				}
			}
			template<int... S> void		alloc(seq<S...>, int n) {
				pass((std::get<S>(data) = new T[n])...);
			}
			int				reg(T... initial) {
				// search for empty slot
				int i = 0;
				while(closed[i]) i++;

				// mark slot as filled
				closed[i] = 1;

				// update size
				if((i+1) > size) size = i + 1;

				// initial values
				set_initial(typename gens<sizeof...(T)>::type(), i, initial...);

				// mark for load
				for(int j = 0; j < sizeof...(T); j++) {
					load[j] = 1;
				}
				load_any = 1;

				// return position to object so it can access it later
				return i;
			}
			template<int... S> void			set_initial(seq<S...>, int i, T... initial) {
				pass((std::get<S>(data)[i] = initial)...);
			}
			void					unreg(int i) {
				closed[i] = 0;

				if((i+1) == size) {
					while(!closed[size-1]) size--;
				}

				load_closed = 1;
				load_any = 1;
			}
			template<int I, typename U> void	set(int i, U const & u) {
				std::get<I>(data)[i] = u;
				load[I] = 1;
				load_any = 1;
			}
			void					load_uniform(GLint* location) {
				if(load_any == 1) {
					load_uniform(typename gens<sizeof...(T)>::type(), location);
					load_any = 0;
				}
			}
			template<int... S> void			load_uniform(seq<S...>, GLint* location) {
				pass(load_uniform__<S>(location)...);
			}
			template<int I> int			load_uniform__(GLint* location) {
				if(load[I] == 1) {
					neb::gfx::ogl::glUniformv(location[I], size, std::get<I>(data)[0]);
					load[I] = 0;
				}
				return 0;
			}
		public:
			int					load[sizeof...(T)];
			int					load_any;
			int					load_closed;
		private:
			std::tuple<T*...>			data;
			int*					closed;
			GLsizei					size;
	};
	template<int I> class locations {
		public:
			GLint					location[I];
	};
	class light_array: public array<
			   glm::vec3,	// position
			   glm::vec4,	// ambient
			   glm::vec4,	// diffuse
			   glm::vec4,	// specular
			   float,	// atten const
			   float,	// atten linear
			   float,	// atten quad
			   glm::vec3,	// spot direction
			   float,	// spot cutoff
			   float,	// spot exponent
			   float,	// spot cos cutoff
			   int		// type
					       >
	{
		public:
			light_array() {}
			void		set_pos(int i, glm::vec3 const & pos) {
				set<0>(i, pos);
			}
			void		set_spot_direction(int i, glm::vec3 const & pos) {
				set<0>(i, pos);
			}
	};
	class light_locations: public light_array::loc_type {
		public:
			void		init(std::shared_ptr<neb::gfx::glsl::program::threed> program);
	};
}}}}



#endif

