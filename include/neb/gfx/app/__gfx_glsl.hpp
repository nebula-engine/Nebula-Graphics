#ifndef __NEBULA_APP___GFX_GLSL_H__
#define __NEBULA_APP___GFX_GLSL_H__

#include <fstream>

#include <boost/asio/io_service.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <gal/itf/shared.hpp>

#include <neb/fnd/util/decl.hpp>
#include <neb/fnd/app/Base.hpp>
#include <neb/fnd/plug/gfx/app/Base.hpp>

#include <neb/gfx/util/decl.hpp>
#include <neb/gfx/glsl/util/decl.hpp>

namespace neb { namespace gfx { namespace app {
	class glsl:
		virtual public neb::fnd::plug::gfx::app::Base
	{
		public:
			//typedef std::map<int, std::shared_ptr<neb::gfx::glsl::program::Base> >		map_program_type;
			friend class neb::gfx::environ::base;
			friend class neb::gfx::environ::two;
			friend class neb::gfx::environ::three;
		protected:
			void								__init();
			//std::shared_ptr<neb::gfx::glsl::program::Base>		use_program(neb::program_name::e);
			//std::shared_ptr<neb::gfx::glsl::program::Base>		get_program(neb::program_name::e);
		public:
			//std::shared_ptr<neb::gfx::glsl::program::Base>		current_program();
			void								create_programs();
			virtual std::shared_ptr<neb::fnd::glsl::program::Base>		get_program_text();
			virtual std::shared_ptr<neb::fnd::glsl::program::Base>		get_program_tex();
			virtual std::shared_ptr<neb::fnd::glsl::program::Base>		get_program_simple3();
			//map_program_type					programs_;
			//std::shared_ptr<neb::gfx::glsl::program::Base>		current_;
			std::shared_ptr<neb::gfx::glsl::program::Base>			program_text_;
			std::shared_ptr<neb::gfx::glsl::program::Base>			program_tex_;
			std::shared_ptr<neb::gfx::glsl::program::Base>			program_simple3_;

	};
}}}

#endif





