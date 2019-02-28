#include "svq/gfx/buffer_layout.h"

namespace svq {
namespace gfx {

BufferLayout::BufferLayout()
	: m_Size(0)
{
}

void BufferLayout::push(const std::string& name, uint type, uint size, uint count, bool normalized)
{
	m_Layout.push_back({ name, type, size, count, m_Size, normalized });
	m_Size += size * count;
}

}
}
