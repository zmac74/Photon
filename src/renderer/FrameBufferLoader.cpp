#include <gl/glew.h>
#include <debug/Debug.h>

#include <scene/importer/Importer.h>
#include <renderer/FrameBuffer.h>
#include <utils/collection/Buffer.h>

static ArrayList<unsigned int> frameBuffers = ArrayList<unsigned int>();

FrameBuffer Renderer::LoadFrameBuffer(int width, int height, const InitializerList<FrameBufferAttachmentProperties>& attachmentsProperties)
{
	unsigned int fboID;
	glGenFramebuffers(1, &fboID);
	frameBuffers.Add(fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, fboID);

	ArrayList<FrameBufferAttachment> attachments = ArrayList<FrameBufferAttachment>();
	const FrameBufferAttachmentProperties* attachmentPropertiesBuffer = attachmentsProperties.begin();
	for (int i = 0; i < attachmentsProperties.size(); i++)
	{
		Texture texture = Importer::LoadFrameBufferTexture(width, height, attachmentPropertiesBuffer[i].textureProperties, i);
		attachments.Add(FrameBufferAttachment(texture, attachmentPropertiesBuffer[i]));
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return FrameBuffer{ width, height, fboID, attachments };
}

void Renderer::DeleteFrameBufferRegistry() 
{
	for (int i = 0; i < frameBuffers.GetLength(); i++) glDeleteFramebuffers(1, &frameBuffers[i]);
}

void Renderer::CopyFrameBuffer(const FrameBuffer& input, int readAttachmentIndex, FrameBuffer& output, int writeAttachmentIndex)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, input.fboID);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + readAttachmentIndex);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.fboID);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + writeAttachmentIndex);
	
	glBlitFramebuffer(0, 0, input.width, input.height, 0, 0, output.width, output.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Renderer::CopyFrameBuffer(const FrameBuffer& input, FrameBuffer& output)
{
	CopyFrameBuffer(input, 0, output, 0);
}

void Renderer::CopyFrameBuffer(const FrameBuffer& input, int readAttachmentIndex)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, input.fboID);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + readAttachmentIndex);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBlitFramebuffer(0, 0, input.width, input.height, 0, 0, input.width, input.height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Renderer::CopyFrameBuffer(const FrameBuffer& input)
{
	CopyFrameBuffer(input, 0);
}