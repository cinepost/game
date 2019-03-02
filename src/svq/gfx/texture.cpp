#include "svq/gfx/texture.h"

namespace svq{ namespace gfx{

TextureWrap Texture::s_WrapMode = TextureWrap::CLAMP;
TextureFilter Texture::s_FilterMode = TextureFilter::LINEAR;

byte Texture::getStrideFromFormat(TextureFormat format)
{
	switch (format)
	{
		case TextureFormat::NONE:	return 0;
		case TextureFormat::LUMINANCE: return 1;
		case TextureFormat::RGB: return 3;
		case TextureFormat::RGBA:	return 4;
		case TextureFormat::LUMINANCE_ALPHA: return 4;
	}
	return 0;
}

}}