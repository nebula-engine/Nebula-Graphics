#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <boost/mutex.hpp>

#include <boost/serialization/map.hpp>

#include <Nebula/Util/WrapperTyped.hh>

namespace Neb {
	template <class T> class Map {
		public:
			typedef int							__index_type;
			typedef std::shared_ptr<T>					shared_type;
			
			typedef Neb::WrapperTyped<T>					mapped_type;

			typedef std::weak_ptr< Neb::Factory<T> >			factory_weak;
			
			typedef std::map<__index_type,mapped_type>			__map_type;


			typedef typename __map_type::iterator			iterator;
			typedef typename __map_type::const_iterator		const_iterator;

			typedef typename __map_type::value_type			value_type_const;
			typedef std::pair<__index_type,mapped_type>		value_type;
			
			/** @brief Constructor */
			Map() {}
			Map(factory_weak factory): factory_(factory) {}
			/*void		add(value_type& p) {
			  p.first = next_++;
			  map_.insert(p);
			  }*/
			/** */
			template<class Archive> void	serialize(Archive & ar, unsigned int const & version) {
				ar & boost::serialization::make_nvp("map",map_);
			}
			void				push_back(shared_type& u) {
				assert(u);
				
				mapped_type m(u);
				
				map_.emplace(u->i_, m);
			}
			void				for_each(std::function<void(const_iterator)> const & f) {
				boost::lock_guard(mutex_);

				for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
					f(it);
				}
			}
			/** */
			iterator			find(__index_type i) {
				auto it = map_.find(i);
				return it;
			}
			/** */
			void				clear() {
				map_.clear();
			}
			/** */
			iterator			begin() {
				return map_.begin();
			}
			/** */
			iterator			end() {
				return map_.end();
			}
			/** */
			iterator			erase(iterator it) {
				boost::lock_guard(mutex_);

				it = map_.erase(it);
				return it;
			}
		private:
			factory_weak			factory_;
			__map_type			map_;
			boost::mutex			mutex_;
	};	
}

#endif





