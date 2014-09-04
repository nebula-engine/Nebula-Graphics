#ifndef NEB_GFX_GLSL_ARRAY_HPP
#define NEB_GFX_GLSL_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>

#include <gal/stl/helper.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/array_basic.hpp>

namespace neb { namespace gfx {

	template<class... T> class array: public array_basic<T...> {
		public:
			typedef typename gens<sizeof...(T)>::type	seq_type;
			void				alloc(int n) {
				array_basic<T...>::alloc(n);

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

#endif
