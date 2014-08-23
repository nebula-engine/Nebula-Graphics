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
					index_(index) {}
				template<int I, typename U> void	set(U const & u) {
					auto arr = array_.lock();
					if(arr) {
						std::cout << __PRETTY_FUNCTION__ << " index=" << index_ << std::endl;
						arr->set<I>(index_, u);
					}
				}
				std::weak_ptr< neb::gfx::array_continuous<T...> >	array_;
				int							index_;
			};
		public:
			std::shared_ptr<slot>			reg(T... value) {
				auto s = std::make_shared<slot>(
						std::enable_shared_from_this< array_continuous<T...> >::shared_from_this(),
						array_basic_double_buffered<T...>::size_);

				array_basic_double_buffered<T...>::size_++;

				array_basic_double_buffered<T...>::set(s->index_, value...);

				slots_.push_back(s);

				return s;
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
				if(update) {

					array_basic_double_buffered<T...>::size_ = 0;

					it = slots_.begin();
					while(it != slots_.end()) {
						auto s = it->lock();

						array_basic_double_buffered<T...>::copy_data(s->index_, array_basic_double_buffered<T...>::size_);

						s->index_ = array_basic_double_buffered<T...>::size_;

						array_basic_double_buffered<T...>::size_++;

						it++;
					}

					array_basic_double_buffered<T...>::swap_buffers();

				}
			}
			template<int I, typename U> U*		get() {
				return std::get<I>(*array_basic_double_buffered<T...>::front_);
			}
			template<int I, typename U> void	set(int i, U const & u) {
				array_basic_double_buffered<T...>::template set<I>(i,u);
			}
			GLsizei					size() {
				return array_basic_double_buffered<T...>::size_;
			}
			GLsizei					size_array() {
				return array_basic_double_buffered<T...>::size_array_;
			}
		public:
			std::vector<std::weak_ptr<slot>>	slots_;
	};
}}

#endif
