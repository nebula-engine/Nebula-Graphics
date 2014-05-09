#ifndef __NEBULA_DESC_LIGHT_H__
#define __NEBULA_DESC_LIGHT_H__

#include <tinyxml2.h>

/*
//#include <math/raw/raw.h>
#include <math/vec3.hpp>
#include <math/vec4.hpp>
#include <math/color.hpp>
*/
//#include <galaxy/network/serial.hpp>

#include <Nebula/config.hpp>
#include <Nebula/Graphics/light/raw.hpp>

namespace Neb {
	namespace light {
		class desc {
			public:
				desc();
				void					load(Neb::light::light_w);
				
				template<class Archive> void		serialize(Archive & ar, unsigned int const & version) {
					ar & boost::serialization::make_nvp("i",i_);
					ar & boost::serialization::make_nvp("raw",raw_);
				}
				
				
				int					i_;
				raw					raw_;
				
		};
	}
}

#endif

