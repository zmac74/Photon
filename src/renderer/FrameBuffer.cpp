#include <gl/glew.h>

#include <renderer/FrameBuffer.h>
#include <scene/importer/Importer.h>
#include <scene/Scene.h>

void Renderer::FrameBuffer::Start() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);
}

void Renderer::FrameBuffer::Stop() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::FrameBuffer::AddAttachment(FrameBufferAttachmentProperties attachmentProperties) 
{
	Texture texture = Importer::LoadFrameBufferTexture(width, height, attachmentProperties.textureProperties, attachments.GetLength());
	attachments.Add(FrameBufferAttachment(texture, attachmentProperties));
}