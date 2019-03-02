#include "svq/gfx/ogl/gl_frame_buffer.h"

//#include "sp/system/Memory.h"
//#include "sp/utils/Log.h"

namespace svq{namespace gfx{

GL_FrameBuffer::GL_FrameBuffer(uint width, uint height) {
	m_Width = width; m_Height = height;
	init();
}

GL_FrameBuffer::~GL_FrameBuffer() {
	glDeleteFramebuffers(1, &m_FramebufferHandle);
}

void GL_FrameBuffer::init() {
	glGenFramebuffers(1, &m_FramebufferHandle);
	glGenRenderbuffers(1, &m_DepthbufferHandle);

	TextureParameters params(TextureFormat::RGBA, TextureFilter::LINEAR, TextureWrap::CLAMP);
	m_Texture = new GL_Texture(m_Width, m_Height, params);

	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthbufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->getHandle(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthbufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL_FrameBuffer::bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferHandle);
	glViewport(0, 0, m_Width, m_Height);
}

void GL_FrameBuffer::unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL_FrameBuffer::clear() {
	glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}}