#ifndef BUFFER_LAYOUT__H
#define BUFFER_LAYOUT__H

#include <assert.h>
#include <string>
#include <vector>

#ifdef _SVQ_OPENGL
#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>
#endif

#include "svq/api.h"
#include "svq/types.h"
#include "svq/math/vec2.h"
#include "svq/math/vec3.h"
#include "svq/math/vec4.h"

namespace svq {
namespace gfx {

struct SVQ_API BufferElement {
		std::string name;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

class SVQ_API BufferLayout {
	public:
		BufferLayout();

		template<typename T>
		void push(const std::string& name, uint count = 1, bool normalized = false) {
			assert(false); //unknown type
		}

		inline const std::vector<BufferElement>& getLayout() const { return m_Layout; }
		inline uint getStride() const { return m_Size; }

	private:
		void push(const std::string& name, uint type, uint size, uint count, bool normalized);

	private:
		uint m_Size;
		std::vector<BufferElement> m_Layout;

};
/*
template<>
void BufferLayout::push<float>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_FLOAT, sizeof(float), count, normalized);
	#else
	//push(name, DX_TYPE_R32_FLOAT, sizeof(float), count, normalized);
	#endif
}

template<>
void BufferLayout::push<uint>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
	#else
	//push(name, DX_TYPE_R32_UINT, sizeof(uint), count, normalized);
	#endif
}

template<>
void BufferLayout::push<byte>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
	#else
	//push(name, DX_TYPE_R8G8B8A8_UNORM, sizeof(byte) * 4, 1, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec2f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_FLOAT, sizeof(float), 2, normalized);
	#else
	//push(name, DX_TYPE_R32G32_FLOAT, sizeof(maths::vec2), count, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec3f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_FLOAT, sizeof(float), 3, normalized);
	#else
	//push(name, DX_TYPE_R32G32B32_FLOAT, sizeof(maths::vec3), count, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec4f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	push(name, GL_FLOAT, sizeof(float), 4, normalized);
	#else
	//push(name, DX_TYPE_R32G32B32A32_FLOAT, sizeof(maths::vec4), count, normalized);
	#endif
}
*/

}
}

#endif // BUFFER_LAYOUT__H