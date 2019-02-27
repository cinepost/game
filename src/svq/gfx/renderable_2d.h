#ifndef RENDERABLE__H
#define RENDERABLE__H

#include "svq/math/vec2.h"
#include "svq/math/vec3.h"
#include "svq/math/vec4.h"


namespace svq { namespace gfx {


struct VertexData {
    math::Vec3f vertex;
    math::Vec4f color;
};


class Renderable_2D { 
    public:


    protected:
        math::Vec3f = m_Position;
        math::Vec2f = m_Size;
        math::Vec4f = m_Color;

};
    
} }

#endif // RENDERABLE__H