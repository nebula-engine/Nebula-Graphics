#include <Galaxy-Log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/debug.hh>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/glsl/Uniform/vector.hpp>
#include <neb/gfx/glsl/program.hpp>

neb::gfx::core::light::point::point(sp::shared_ptr<neb::core::light::util::parent> parent):
        neb::core::light::base(parent),
        neb::gfx::core::light::base(parent, "lights_point"),
        atten_const_(1.0),
        atten_linear_(0.0),
        atten_quad_(0.0)
{}
void	neb::gfx::core::light::point::load(neb::core::light::util::count & light_count, neb::core::pose const & pose) {

        if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
        
        neb::gfx::core::light::base::load(light_count.point, pose);
        
        auto p = neb::app::__gfx_glsl::global().lock()->current_program();
        
        
        p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
        p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
        p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
        light_count.point++;
}

