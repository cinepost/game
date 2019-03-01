#include "sp/sp.h"
#include "svq/gfx/ogl/gl_frame_buffer.h"

#include "sp/system/Memory.h"
#include "sp/utils/Log.h"

namespace svq{namespace gfx{

GL_Framebuffer::GL_Framebuffer(uint width, uint height) {
	m_Width = width; m_Height = height;
	init();
}

GL_Framebuffer::~GL_Framebuffer() {
	glDeleteFramebuffers(1, &m_FramebufferHandle);
}

void GL_Framebuffer::init() {
	glGenFramebuffers(1, &m_FramebufferHandle);
	glGenRenderbuffers(1, &m_DepthbufferHandle);

	TextureParameters params(TextureFormat::RGBA, TextureFilter::LINEAR, TextureWrap::CLAMP);
	m_Texture = spnew GLTexture2D(m_Width, m_Height, params);

	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthbufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->GetHandle(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthbufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL_Framebuffer::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle);
	glViewport(0, 0, m_Width, m_Height);
}

void GL_Framebuffer::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL_Framebuffer::Clear() {
	glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}}