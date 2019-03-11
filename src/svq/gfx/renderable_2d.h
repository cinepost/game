#ifndef RENDERABLE_2D__H
#define RENDERABLE_2D__H

#include <vector>

#include "svq/api.h"
#include "svq/types.h"

#include "svq/math/vec2.h"
#include "svq/math/vec3.h"
#include "svq/math/vec4.h"
#include "svq/math/bbox2.h"

#include "svq/gfx/texture.h"
#include "svq/gfx/vertex_array.h"
#include "svq/gfx/index_buffer.h"


namespace svq {
namespace gfx {

class Renderer_2D;

struct VertexData {
    math::Vec3f vertex;
    math::Vec2f uv;
    float texture_id;
    math::Vec4f color;
    //unsigned char shader_id;
};

#define RENDERER_VERTEX_SIZE    sizeof(VertexData)

class Renderable_2D { 
    public:
        Renderable_2D(math::Vec3f pos, math::Vec2f size, math::Vec4f color);
        virtual ~Renderable_2D();

        virtual void submit(Renderer_2D* renderer) const;

        inline const std::vector<math::Vec2f>& getUVs() const { return m_UVs; }
        inline const math::Vec4f getColor() const { return m_Color; }
        inline Texture* getTexture() const { return m_Texture; }
        inline bool isVisible() const { return m_Visible; }

        void setColor(const math::Vec4f& color);
        static const std::vector<math::Vec2f>& getDefaultUVs();

    protected:
        Renderable_2D();

    protected:
        math::Bbox2f m_Bounds;
        math::Vec4f m_Color;
        std::vector<math::Vec2f> m_UVs;
        Texture* m_Texture;
        bool m_Visible;
};
    
} 
}

#endif // RENDERABLE_2D__H