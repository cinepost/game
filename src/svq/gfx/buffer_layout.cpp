#include "svq/gfx/buffer_layout.h"

namespace svq{ namespace gfx{

BufferLayout::BufferLayout(): m_Size(0) { }

template<>
void BufferLayout::push<float>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_FLOAT, sizeof(float), count, normalized);
	#else
	//push(name, DX_TYPE_R32_FLOAT, sizeof(float), count, normalized);
	#endif
}
	
template<>
void BufferLayout::push<uint>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
	#else
	//push(name, DX_TYPE_R32_UINT, sizeof(uint), count, normalized);
	#endif
}

template<>
void BufferLayout::push<byte>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
	#else
	//push(name, DX_TYPE_R8G8B8A8_UNORM, sizeof(byte) * 4, 1, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec2f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_FLOAT, sizeof(float), 2, normalized);
	#else
	//push(name, DX_TYPE_R32G32_FLOAT, sizeof(maths::vec2), count, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec3f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_FLOAT, sizeof(float), 3, normalized);
	#else
	//push(name, DX_TYPE_R32G32B32_FLOAT, sizeof(maths::vec3), count, normalized);
	#endif
}

template<>
void BufferLayout::push<math::Vec4f>(const std::string& name, uint count, bool normalized) {
	#ifdef _SVQ_OPENGL
	_push(name, GL_FLOAT, sizeof(float), 4, normalized);
	#else
	//push(name, DX_TYPE_R32G32B32A32_FLOAT, sizeof(maths::vec4), count, normalized);
	#endif
}

void BufferLayout::_push(const std::string& name, uint type, uint size, uint count, bool normalized)
{
	m_Layout.push_back({ name, type, size, count, m_Size, normalized });
	m_Size += size * count;
}

}}
