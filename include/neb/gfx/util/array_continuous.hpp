#ifndef NEB_GFX_ARRAY_CONTINUOUS_HPP
#define NEB_GFX_ARRAY_CONTINUOUS_HPP

#include <iostream>
#include <vector>
#include <memory>

#include <neb/gfx/util/array_basic_double_buffered.hpp>

namespace neb { namespace gfx {
	template<class... T> class array_continuous:
		public std::enable_shared_from_this< array_continuous<T...> >,
		public array_basic_double_buffered<T...>
	{
		public:
			typedef typename gens<sizeof...(T)>::type seq_type;
			struct slot {
				slot(std::shared_ptr< neb::gfx::array_continuous<T...> > array, int index):
					array_(array),
					index_(index),
					count_(0) {}
				template<int I, typename U> void	set(U const & u) {
					auto arr = array_.lock();
					if(arr) {
						//std::cout << __PRETTY_FUNCTION__ << " index=" << index_ << std::endl;
						arr->set<I>(index_, u);
						count_++;
					}
				}
				std::weak_ptr< neb::gfx::array_continuous<T...> >	array_;
				int							index_;
				int							count_;
			};
		public:
			array_continuous():
				update_begin_(0),
				update_end_(0) {}
			void					alloc(int n) {
				array_basic_double_buffered<T...>::alloc(n);
				
				reset_update();
			}
			std::shared_ptr<slot>			reg(T... value) {

				int index = array_basic_double_buffered<T...>::next();
				
				auto s = std::make_shared<slot>(
						std::enable_shared_from_this< array_continuous<T...> >::shared_from_this(),
						index);


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
				update_end_ = size();
			}
			void					reset_update() {
				update_begin_ = size_array();
				update_end_ = 0;
			}
			void					update_slots() {
				// remove expired instanced
				bool update = false;

				auto it = slots_.begin();
				while(it != slots_.end()) {
					if(it->expired()) {
						it = slots_.erase(it);
						update = true;
					} else {
						it++;
					}
				}

				// if instances were removed, copy remaining data to back buffer
				if(update) swap();
			}
			void					swap() {

				int size = 0;
				//array_basic_double_buffered<T...>::size_ = 0;

				auto it = slots_.begin();
				while(it != slots_.end()) {
					auto s = it->lock();

					array_basic_double_buffered<T...>::copy_data(s->index_, size); //array_basic_double_buffered<T...>::size_);

					s->index_ = size; //array_basic_double_buffered<T...>::size_;

					//array_basic_double_buffered<T...>::size_++;
					size++;
					it++;
				}

				array_basic_double_buffered<T...>::swap_buffers();
				array_basic_double_buffered<T...>::set_size(size);


			}
			template<int I, typename U> U*		get() {
				return array_basic_double_buffered<T...>::template get<I,U>();
			}
			template<int I, typename U> void	set(int i, U const & u) {
				array_basic_double_buffered<T...>::template set<I>(i,u);

				mark_update(i);
			}
			GLsizei					size() {
				return array_basic_double_buffered<T...>::size();
			}
			GLsizei					size_array() {
				return array_basic_double_buffered<T...>::size_array();
			}
		public:
			std::vector<std::weak_ptr<slot>>	slots_;
			int					update_begin_;
			int					update_end_;
	};
}}

#endif
