#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

#include <gal/stl/helper.hpp>

namespace neb { namespace gfx { namespace glsl { namespace uniform {
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
			void				alloc(int n) {
				alloc(gens<sizeof...(T)>::type(), n);
				
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
				set_initial(gens<sizeof...(T)>::type(), i, initial...);

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
			}
		public:
			int					load[sizeof...(T)];
			int					load_any;
			int					load_closed;
		private:
			std::tuple<T*...>			data;
			int*					closed;
			int					size;
		private:
			GLuint					location[sizeof...(T)];
	};

	class light_array: public array<glm::vec3, glm::vec4, glm::vec4, glm::vec4, float, float, float, glm::vec3, float, float> {
		public:
			light_array() {}
			void		set_pos(int i, glm::vec3 const & pos) {
				set<0>(i, pos);
			}
	};
}}}}



#endif

