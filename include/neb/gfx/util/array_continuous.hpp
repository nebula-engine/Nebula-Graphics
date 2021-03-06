#ifndef NEB_GFX_ARRAY_CONTINUOUS_HPP
#define NEB_GFX_ARRAY_CONTINUOUS_HPP

#include <iostream>
#include <vector>
#include <memory>

#include <gal/stl/verbosity.hpp>

#include <neb/gfx/util/array_basic_double_buffered.hpp>
#include <neb/gfx/util/slot.hpp>

namespace neb { namespace gfx {

	template<class... T>
	class array_continuous:
		public gal::tmp::Verbosity< neb::gfx::array_continuous<T...> >,
		public std::enable_shared_from_this< array_continuous<T...> >,
		public array_basic_double_buffered<T...>
	{
		public:
			using gal::tmp::Verbosity< neb::gfx::array_continuous<T...> >::printv;
			typedef std::enable_shared_from_this< array_continuous<T...> > esft;

			typedef typename gens<sizeof...(T)>::type seq_type;

			typedef slot< array_continuous< T... > >	slot_type;
			typedef std::shared_ptr<slot_type>		slot_shared;
		public:
			
			array_continuous():
				update_begin_(0),
				update_end_(0) {}
			void					alloc(int n) {
				array_basic_double_buffered<T...>::alloc(n);

				reset_update();
			}
			slot_shared			reg(T... value)
			{
				printv_func(DEBUG);

				int index = array_basic_double_buffered<T...>::next();

				slot_shared s(
						new slot_type(
							esft::shared_from_this(),
							index)
						);

				printv(DEBUG, "index = %i\n", index);
				printv(DEBUG, "size  = %i\n", size());

				array_basic_double_buffered<T...>::set(index, value...);

				slots_.push_back(s);

				mark_update(index);

				return s;
			}
			void					mark_update(int index) {
				update_begin_ = std::min(update_begin_, index);
				update_end_ = std::max(update_end_, index);
			}
			void					mark_update_all() {
				update_begin_ = 0;
				update_end_ = size() - 1;
			}
			void					reset_update() {
				update_begin_ = size_array();
				update_end_ = 0;
			}
			void					update_slots()
			{
				printv_func(DEBUG);

				// remove expired instanced
				bool update = false;

				auto it = slots_.begin();

				while(it != slots_.end())
				{
					if(it->expired())
					{
						printv(DEBUG, "erased\n");
						it = slots_.erase(it);
						update = true;
					} else {
						it++;
					}
				}

				// if instances were removed, copy remaining data to back buffer
				if(update) swap();

				mark_update_all();
			}
			void					swap()
			{
				printv_func(DEBUG);

				int nsize = 0;
				//array_basic_double_buffered<T...>::size_ = 0;

				auto it = slots_.begin();
				while(it != slots_.end()) {
					auto s = it->lock();

					array_basic_double_buffered<T...>::copy_data(s->index_, nsize); //array_basic_double_buffered<T...>::size_);

					s->index_ = nsize; //array_basic_double_buffered<T...>::size_;

					//array_basic_double_buffered<T...>::size_++;
					nsize++;
					it++;
				}

				array_basic_double_buffered<T...>::swap_buffers();
				array_basic_double_buffered<T...>::set_size(nsize);

				printv(DEBUG, "size = %i %i\n", nsize, size());

			}
			template<int I, typename U> U*		get() {
				return array_basic_double_buffered<T...>::template get<I,U>();
			}
			template<int I, typename U> void	set(int i, U const & u) {
				array_basic_double_buffered<T...>::template set<I>(i,u);

				mark_update(i);
			}
			GLsizei					size()
			{
				auto s = array_basic_double_buffered<T...>::size();
				
				printv_func(DEBUG);
				printv(DEBUG, "size = \n", s);

				return s;
			}
			GLsizei					size_array() {
				return array_basic_double_buffered<T...>::size_array();
			}
		public:
			std::vector< std::weak_ptr<slot_type> >		slots_;
			int						update_begin_;
			int						update_end_;
	};
}}

#endif
