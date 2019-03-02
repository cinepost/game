#ifndef TEXTURE__H
#define TEXTURE__H

#include <string>

#include "svq/api.h"
#include "svq/types.h"

namespace svq{ namespace gfx{

enum class SVQ_API TextureWrap {
	NONE = 0,
	REPEAT,
	CLAMP,
	MIRRORED_REPEAT,
	CLAMP_TO_EDGE,
	CLAMP_TO_BORDER
};

enum class SVQ_API TextureFilter {
	NONE = 0,
	LINEAR,
	NEAREST
};

enum class SVQ_API TextureFormat {
	NONE = 0,
	RGB,
	RGBA,
	LUMINANCE,
	LUMINANCE_ALPHA
};

struct SVQ_API TextureParameters {
	TextureFormat format;
	TextureFilter filter;
	TextureWrap wrap;

	TextureParameters() {
		format = TextureFormat::RGBA;
		filter = TextureFilter::LINEAR;
		wrap = TextureWrap::CLAMP;
	}

	TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap)
		: format(format), filter(filter), wrap(wrap) {
	}

	TextureParameters(TextureFilter filter)
		: format(TextureFormat::RGBA), filter(filter), wrap(TextureWrap::CLAMP) {
	}

	TextureParameters(TextureFilter filter, TextureWrap wrap)
		: format(TextureFormat::RGBA), filter(filter), wrap(wrap) {
	}
};

struct SVQ_API TextureLoadOptions {
	bool flipX;
	bool flipY;

	TextureLoadOptions() {
		flipX = false;
		flipY = false;
	}

	TextureLoadOptions(bool flipX, bool flipY) : flipX(flipX), flipY(flipY) { }
};

class SVQ_API Texture {
	public:
		virtual ~Texture() {}

		virtual void bind(uint slot = 0) const = 0;
		virtual void unbind(uint slot = 0) const = 0;

		virtual void setData(const void* pixels) = 0;
		virtual void setData(uint color) = 0;

		virtual const std::string& getName() const = 0;
		virtual const std::string& getFilepath() const = 0;

	public:
		inline static void setWrap(TextureWrap mode) { s_WrapMode = mode; }
		inline static void setFilter(TextureFilter mode) { s_FilterMode = mode; }

	public:
		static byte getStrideFromFormat(TextureFormat format);

	protected:
		static TextureWrap s_WrapMode;
		static TextureFilter s_FilterMode;
};

}}

#endif // TEXTURE__H