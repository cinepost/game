#ifndef BBOX2__H
#define BBOX2__H

#include "svq/math/vec2.h"

namespace svq { 
namespace math {

template <class T>
class Bbox2 {
	public:
		Vec2<T> pos, size;
		
		Bbox2() {}
		Bbox2(const Vec2<T>& v_pos, const Vec2<T>& v_size) : pos(v_pos), size(v_size) {}
		
		Bbox2& operator=(const Bbox2& b) {
			pos = b.pos;
			size = b.size;
			return *this;
		}
	
};

typedef Bbox2<int> Bbox2i;
typedef Bbox2<float> Bbox2f;
typedef Bbox2<double> Bbox2d;

}
}

#endif // BBOX2__H