#pragma once

#include <utils/collection/Buffer.h>
#include <scene/Scene.h>

namespace Renderer 
{
	struct FrameBufferAttachmentProperties
	{
	public:
		FrameBufferAttachmentProperties() : name("name") {}
		FrameBufferAttachmentProperties(const char* name) : name(name) {}
		FrameBufferAttachmentProperties(const char* name, TextureProperties textureProperties) : name(name), textureProperties(textureProperties) {}

		TextureProperties textureProperties;
		const char* name;
	};

	struct FrameBufferAttachment
	{
	public:
		FrameBufferAttachment() = default;
		FrameBufferAttachment(Texture textureAttachment, FrameBufferAttachmentProperties attachmentProperties)
			: textureAttachment(textureAttachment), attachmentProperties(attachmentProperties) {}

		FrameBufferAttachmentProperties attachmentProperties;
		Texture textureAttachment;
	};
	
	class FrameBuffer 
	{
	public:
		int width;
		int height;
		
		unsigned int fboID;

		ArrayList<FrameBufferAttachment> attachments;

		void Start() const;
		void Stop() const;

		void AddAttachment(FrameBufferAttachmentProperties attachmentProperties);
	};

	FrameBuffer LoadFrameBuffer(int width, int height, const InitializerList<FrameBufferAttachmentProperties>& attachmentsProperties);
	void DeleteFrameBufferRegistry();

	void CopyFrameBuffer(const FrameBuffer& input, FrameBuffer& output);
	void CopyFrameBuffer(const FrameBuffer& input, int readAttachmentIndex, FrameBuffer& output, int writeAttachmentIndex);
	void CopyFrameBuffer(const FrameBuffer& input);
	void CopyFrameBuffer(const FrameBuffer& input, int readAttachmentIndex);
}

using namespace Renderer;