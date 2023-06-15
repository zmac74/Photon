#include <renderer/postProcessing/PostProcessStack.h>
#include <renderer/Renderer.h>

void Renderer::PostProcessing::PostProcessStack::AddLayer(PostProcessLayer layer) 
{
	for (int i = 0; i < layer.GetShaders().GetLength(); i++) 
	{
		Shader& shader = layer.GetShaders()[i];

		shader.Start();
		for (int j = 0; j < sceneFrameBuffer.attachments.GetLength(); j++) 
		{
			shader.SetInt(sceneFrameBuffer.attachments[j].attachmentProperties.name, j);
		}
		shader.SetInt("COLOR", sceneFrameBuffer.attachments.GetLength());
		shader.Stop();

		layers.Add(layer);
	}
}

void Renderer::PostProcessing::PostProcessStack::AddLayer(Shader shader) 
{
	shader.Start();
	for (int i = 0; i < sceneFrameBuffer.attachments.GetLength(); i++)
	{
		shader.SetInt(sceneFrameBuffer.attachments[i].attachmentProperties.name, i);
	}
	shader.SetInt("COLOR", sceneFrameBuffer.attachments.GetLength());
	shader.Stop();

	layers.Add(PostProcessLayer(shader));
}

void Renderer::PostProcessing::PostProcessStack::Refresh() 
{
	for (int i = 0; i < layers.GetLength(); i++) 
	{
		PostProcessLayer& layer = layers[i];

		for (int j = 0; j < layer.GetShaders().GetLength(); j++)
		{
			Shader& shader = layer.GetShaders()[j];

			shader.Start();
			for (int k = 0; k < sceneFrameBuffer.attachments.GetLength(); k++)
			{
				shader.SetInt(sceneFrameBuffer.attachments[k].attachmentProperties.name, k);
			}
			shader.SetInt("COLOR", sceneFrameBuffer.attachments.GetLength());
			shader.Stop();
		}
	}
}