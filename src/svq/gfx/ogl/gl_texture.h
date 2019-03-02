#ifndef GL_TEXTURE__H
#define GL_TEXTURE__H

#define GL_GLEXT_PROTOTYPES
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "svq/gfx/texture.h"

namespace svq{ namespace gfx{

class GL_Texture : public Texture {
	public:
		GL_Texture(uint width, uint height, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GL_Texture(uint width, uint height, uint color, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());
		GL_Texture(const std::string& name, const std::string& filename, TextureParameters parameters = TextureParameters(), TextureLoadOptions loadOptions = TextureLoadOptions());

		~GL_Texture();

		void bind(uint slot = 0) const override;
		void unbind(uint slot = 0) const override;

		virtual void setData(const void* pixels) override;
		virtual void setData(uint color) override;

		uint getHandle() const { return m_Handle; }

		inline uint getWidth() const { return m_Width; }
		inline uint getHeight() const { return m_Height; }

		inline const std::string& getName() const override { return m_Name; }
		inline const std::string& getFilepath() const override { return m_FileName; }

	public:
		static uint textureFormatToGL(TextureFormat format);
		static uint textureWrapToGL(TextureWrap wrap);

	private:
		uint load();

	private:
		std::string m_Name;
		std::string m_FileName;
		uint m_Handle;
		uint m_Width, m_Height;
		TextureParameters m_Parameters;
		TextureLoadOptions m_LoadOptions;
	};


}}

#endif // GL_TEXTURE__H