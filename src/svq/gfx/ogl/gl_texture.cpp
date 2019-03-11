#include "svq/gfx/ogl/gl_common.h"
#include "svq/gfx/ogl/gl_texture.h"

//#include <GL/glew.h>
//#include <FreeImage.h>

//#include "sp/utils/ImageLoad.h"
//#include "sp/platform/opengl/GLShader.h"
//#include "sp/system/Memory.h"

namespace svq{ namespace gfx{

GL_Texture::GL_Texture(uint width, uint height, TextureParameters parameters, TextureLoadOptions loadOptions) {
	m_FileName = "NULL";
	m_Width = width;
	m_Height = height;
	m_Parameters = parameters;
	m_LoadOptions = loadOptions;
	m_Handle = load();
}

GL_Texture::GL_Texture(uint width, uint height, uint color, TextureParameters parameters, TextureLoadOptions loadOptions) {
	m_FileName = "NULL";
	m_Width = width;
	m_Height = height;
	m_Parameters = parameters;
	m_LoadOptions = loadOptions;
	m_Handle = load();

	setData(color);
}

GL_Texture::GL_Texture(const std::string& name, const std::string& filename, TextureParameters parameters, TextureLoadOptions loadOptions) {
	m_FileName = filename;
	m_Name = name;
	m_Parameters = parameters;
	m_LoadOptions = loadOptions;
	m_Handle = load();
}

GL_Texture::~GL_Texture() {
	glDeleteTextures(1, &m_Handle);
}

uint GL_Texture::load() {
	// TODO: Split this up into loading from file vs. generating from data
	byte* pixels = nullptr;

	if (m_FileName != "NULL") {
		uint bits;
		SDL_Surface *surface = IMG_Load(m_FileName.c_str());
		
		if (surface) {
			m_Width = surface->w;
			m_Height = surface->h;
			bits = surface->format->BitsPerPixel;
			memcpy(pixels, surface->pixels, surface->format->BitsPerPixel * m_Width * m_Height);
			
			if (bits != 24 && bits != 32)
				printf("Unsupported image bit depth");

			m_Parameters.format = bits == 24 ? TextureFormat::RGB : TextureFormat::RGBA;

			delete surface;
		} else {
			printf("Unable to load texture %s", m_FileName.c_str());
		}
	}
	
	uint handle;
	GL_CALL(glGenTextures(1, &handle));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, handle));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Parameters.filter == TextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToGL(s_WrapMode)));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToGL(s_WrapMode)));

	GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, textureFormatToGL(m_Parameters.format), m_Width, m_Height, 0, textureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels));
	GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (pixels != nullptr)
		delete[] pixels;

	return handle;
}

void GL_Texture::setData(const void* pixels) {
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_Handle));
	GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, textureFormatToGL(m_Parameters.format), GL_UNSIGNED_BYTE, pixels));
}

void GL_Texture::setData(uint color) {
	assert(false); // not working
	uint stride = m_Parameters.format == TextureFormat::RGB ? 3 : 4;
	uint size = m_Width * m_Height * stride;
	byte* data = new byte[size];
	for (uint i = 0; i < size; i += stride) {
		data[i + 0] = (color & 0xff);
		data[i + 1] = (color & 0xff00) >> 8;
		data[i + 2] = (color & 0xff0000) >> 16;
		if (stride == 4)
			data[i + 3] = (color & 0xff000000) >> 24;
	}

	setData(data);
	delete[] data;
}

void GL_Texture::bind(uint slot) const {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, m_Handle));
}

void GL_Texture::unbind(uint slot) const {
	GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

uint GL_Texture::textureFormatToGL(TextureFormat format) {
	switch (format) {
		case TextureFormat::NONE: // default to GL_RGBA
		case TextureFormat::RGBA:				return GL_RGBA;
		case TextureFormat::RGB:				return GL_RGB;
		case TextureFormat::LUMINANCE:			return GL_LUMINANCE;
		case TextureFormat::LUMINANCE_ALPHA:	return GL_LUMINANCE_ALPHA;
	}
	return 0;
}

uint GL_Texture::textureWrapToGL(TextureWrap wrap) {
	switch (wrap) {
		case TextureWrap::NONE: // default to GL_CLAMP	
		case TextureWrap::CLAMP:			return GL_CLAMP;
		case TextureWrap::CLAMP_TO_BORDER:	return GL_CLAMP_TO_BORDER;
		case TextureWrap::CLAMP_TO_EDGE:	return GL_CLAMP_TO_EDGE;
		case TextureWrap::REPEAT:			return GL_REPEAT;
		case TextureWrap::MIRRORED_REPEAT:	return GL_MIRRORED_REPEAT;
	}
	return 0;
}

}}