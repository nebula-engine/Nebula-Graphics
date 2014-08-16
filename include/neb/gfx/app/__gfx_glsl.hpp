#ifndef __NEBULA_APP___GFX_GLSL_H__
#define __NEBULA_APP___GFX_GLSL_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gal/itf/shared.hpp>

#include <neb/core/util/decl.hpp>
#include <neb/core/app/__base.hpp>
#include <neb/gfx/util/decl.hpp>

using namespace std;

namespace neb {
	namespace app {
		class __gfx_glsl: virtual public neb::core::app::__base {
			public:
				typedef ::std::map<int, std::shared_ptr<neb::glsl::program> >		map_program_type;
				friend class neb::gfx::environ::base;
				friend class neb::gfx::environ::two;
				friend class neb::gfx::environ::three;
				static weak_ptr<neb::app::__gfx_glsl>			global();
			protected:
				void							__init();
				shared_ptr<neb::glsl::program>				use_program(neb::program_name::e);
				shared_ptr<neb::glsl::program>				get_program(neb::program_name::e);
			public:
				shared_ptr<neb::glsl::program>				current_program();
				void							create_programs();
				map_program_type					programs_;
				std::shared_ptr<neb::glsl::program>			current_;
		};
	}
}
#endif





