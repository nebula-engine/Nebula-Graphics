#ifndef NEB_GFX_GLSL_UNIFORM_ARRAY_HPP
#define NEB_GFX_GLSL_UNIFORM_ARRAY_HPP

#include <stdio.h>
#include <tuple>
#include <memory>
#include <iostream>
#include <iomanip>
#include <map>

#include <gal/stl/helper.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/opengl/uniform.hpp>
#include <neb/gfx/glsl/util/decl.hpp>
#include <neb/gfx/util/log.hpp>

#include <neb/gfx/util/array.hpp>
#include <neb/gfx/util/slot.hpp>

#include <neb/gfx/glsl/program/base.hpp>

namespace neb { namespace gfx { namespace glsl { namespace uniform {
	typedef neb::fnd::glsl::program::Base P;
	template<int I, typename D> class locations;
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
	template<typename LOC_DER, class... T>
	class array:
		public gal::tmp::Verbosity< array< LOC_DER, T... > >,
		public std::enable_shared_from_this< array< LOC_DER, T... > >,
		public neb::gfx::array<T...>
	{
		public:
			using gal::tmp::Verbosity< array< LOC_DER, T... > >::printv;
			typedef locations<sizeof...(T), LOC_DER>				loc_type;
			typedef typename gens<sizeof...(T)>::type				seq_type;
			typedef std::map<P*, loc_type>						loc_map;
			typedef std::enable_shared_from_this< array< LOC_DER, T... > >		esft;
			typedef slot< array< LOC_DER, T... > >					slot_type;
			typedef std::shared_ptr<slot_type>					slot_shared;
		public:

			using neb::gfx::array<T...>::size;
			using neb::gfx::array<T...>::getClosed;
			using neb::gfx::array<T...>::isClosed;
			using neb::gfx::array<T...>::isOpen;

			virtual slot_shared			reg(T... initial)
			{
				printv_func(DEBUG);

				int i = neb::gfx::array<T...>::reg_array(initial...);

				slot_shared s(
						new slot_type(
							esft::shared_from_this(),
							i
							)
					     );

				markLoadAll();				

				return s;
			}
			void					markLoadAll()
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.markLoadAll();
				}
			}
			void					markLoadClosed()
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.load_closed = 1;
					p.second.load_any = 1;
				}
			}
			void					markLoad(int i)
			{
				for(typename loc_map::value_type& p: _M_locations)
				{
					p.second.load[i] = 1;
					p.second.load_any = 1;
				}
			}
			void					unreg(int i)
			{
				printv_func(DEBUG);

				neb::gfx::array<T...>::unreg_array(i);

				markLoadClosed();
			}
			template<int I, typename U> void	set(int i, U const & u) {
				neb::gfx::array<T...>::template set_array<I>(i, u);

				markLoad(I);
			}
			void					load_uniform(P* p)
			{
				loc_type& loc = _M_locations[p];
				loc.init(p);
				load_uniform(loc);
			}
		private:
			void					load_uniform(loc_type& loc) {
				if(loc.load_any == 1) {
					load_uniform(seq_type(), loc);

					if(loc.load_closed == 1) {

						neb::gfx::ogl::glUniformv(
								loc.location[sizeof...(T)],
								size(),
								getClosed());

						loc.load_closed = 0;
					}

					neb::gfx::ogl::glUniform(
							loc.location[sizeof...(T)+1],
							(int)size());

					printv(DEBUG, "load_uniform size = %i\n", size());

					loc.load_any = 0;
				}
			}
			template<int... S> void			load_uniform(seq<S...>, loc_type& loc) {
				//pass((std::cout << S << std::endl)...);
				pass(load_uniform__<S,T>(loc)...);
			}
			template<int I, typename U> int		load_uniform__(loc_type& loc) {

				if(loc.load[I] == 1)
				{
					printv(DEBUG, "load_uniform__ I=%i loc=%i", I, loc.location[I]);

					for(int i = 0; i < size(); i++)
					{
						//std::get<I>(neb::gfx::array_basic<T...>::data_)[i]
						//neb::gfx::array_basic<T...>::get<I,U>(i)

						//printv(DEBUG, neb::gfx::array_basic<T...>::template get<I,U>(i));
						printv(DEBUG, "closed=%i\n", isClosed(i));
					}

					neb::gfx::ogl::glUniformv(
							loc.location[I],
							size(),
							neb::gfx::array_basic<T...>::template get<I,U>());

					loc.load[I] = 0;
				}
				return 0;
			}
			loc_map		_M_locations;
	};
	template<int I, typename D>
	class locations:
		public gal::tmp::Verbosity< neb::gfx::glsl::uniform::locations< I, D > >
	{
		public:
			using gal::tmp::Verbosity< neb::gfx::glsl::uniform::locations< I, D > >::printv;
			enum {
				N = I + 2
			};

			locations(): _M_initialized(false), load_any(1), load_closed(1) {}

			void					markLoadAll()
			{
				for(int j = 0; j < N; j++) {
					load[j] = 1;
				}
				load_closed = 1;
				load_any = 1;
			}
			void					init(P* p)
			{
				if(_M_initialized) return;

				for(unsigned int i = 0; i < N; i++) location[i] = -1;

				for(int j = 0; j < N; j++) load[j] = 1;

				for(unsigned int i = 0; i < N; i++)
				{
					location[i] = p->get_uniform_table_value(D::names_[i]);
					printv(DEBUG, "location[% 4i] = %4i\n", i, location[i]);
				}

				_M_initialized = true;
			}
			bool					_M_initialized;
			GLint					location[I+2];
			int					load[I+2];
			int					load_any;
			int					load_closed;
	};
}}}}



#endif

