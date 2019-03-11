#ifndef GL_SHADER__H
#define GL_SHADER__H

#include <string>

#include "svq/types.h"
#include "svq/gfx/shader.h"

namespace svq{ namespace gfx{

struct ShaderSources {
	std::string vertexSource;
	std::string fragmentSource;
};

struct GLShaderErrorInfo {
	uint shader;
	std::string message[2];
	uint line[2];
};

class GL_Shader : public Shader{
	public:
		GL_Shader(const std::string& name, const std::string& unifiedSource);
		GL_Shader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		~GL_Shader();

		void init();
		void shutdown();
		void bind() const override;
		void unbind() const override;

		inline const std::string& getName() const override { return m_Name; }
		inline const std::string& getFilePath() const override { return m_Path; }

	public:
		const void setUnifromMatrix4fv(const std::string &uniform_name, const void *value) const override;

	private:
		friend class Shader;
		friend class ShaderManager;

	private:
		static uint compile(ShaderSources sources, GLShaderErrorInfo error);
		static ShaderSources parseSources(const std::string& shaderSourcePath);



	private:
		uint m_Handle;
		std::string m_Name, m_Path;
		ShaderSources m_Sources; // vertex and program shader sources

		//ShaderUniformBufferList m_VSUniformBuffers;
		//ShaderUniformBufferList m_PSUniformBuffers;
		//GL_ShaderUniformBufferDeclaration* m_VSUserUniformBuffer;
		//GL_ShaderUniformBufferDeclaration* m_PSUserUniformBuffer;
		//ShaderResourceList m_Resources;
		//ShaderStructList m_Structs;
	};

}}

#endif // GL_SHADER__H