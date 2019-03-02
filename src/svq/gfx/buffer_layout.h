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

namespace svq{ namespace gfx{

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
		void _push(const std::string& name, uint type, uint size, uint count, bool normalized);

	private:
		uint m_Size;
		std::vector<BufferElement> m_Layout;

};

}}


#endif // BUFFER_LAYOUT__H