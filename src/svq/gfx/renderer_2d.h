#ifndef RENDERER__H
#define RENDERER__H

#include "svq/gfx/renderable_2d.h"

namespace svq { namespace gfx {

class Renderer_2D { 
    public:
    	virtual void push(const Renderable2D* renderable) = 0;
    	virtual void flush() = 0;
};
    
} }

#endif // RENDERER__H