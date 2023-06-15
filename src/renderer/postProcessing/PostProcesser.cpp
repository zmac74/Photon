#include <gl/glew.h>

#include <utils/collection/Buffer.h>
#include <utils/collection/Color.h>
#include <utils/math/Intersect.h>

#include <renderer/postProcessing/PostProcessStack.h>
#include <renderer/postProcessing/PostProcesser.h>
#include <renderer/FrameBuffer.h>
#include <renderer/Renderer.h>

#include <scene/importer/Importer.h>
#include <scene/Scene.h>

static void runPostProcessStack(const PostProcessStack& postProcessStack, bool lastStack);
static void runPostProcess(const FrameBuffer* input, const FrameBuffer* output, const Shader& shader);
static void intersectPostProcessVolumes(ArrayList<PostProcessVolume*>& intersectedVolumes);
static void setFrameBufferTextures(const FrameBuffer& frameBuffer);
static void unbindFrameBufferTextures();
static void renderPostProcessQuad();

static VertexArray quadVertexArray;

static FrameBuffer oddFrameBuffer;
static FrameBuffer evenFrameBuffer;
static int currentProcessCount = 0;

void Renderer::PostProcessing::InitPostProcesser(int width, int height) 
{
	oddFrameBuffer = LoadFrameBuffer(width, height, { {"COLOR"} });
	evenFrameBuffer = LoadFrameBuffer(width, height, { {"COLOR"} });

	float verticesArray[] = { -1, -1, 0, -1,  1, 0, 1,  1, 0, 1, -1, 0 }; 
	float texturesArray[] = { 0, 0, 0, 1, 1, 1, 1, 0 };
	int indicesArray[] = { 0, 1, 3, 1, 2, 3 };

	ArrayList<float> positions = ArrayList<float>(verticesArray, 12, 1);
	ArrayList<float> texturesCoords = ArrayList<float>(texturesArray, 8, 1);
	ArrayList<int> indices = ArrayList<int>(indicesArray, 6, 1);

	quadVertexArray = LoadVertexArray(positions, texturesCoords, ArrayList<float>(), ArrayList<float>(), ArrayList<float>(), indices);
	
	PostProcessStack postProcessStack;
	postProcessStack.AddLayer(LoadShader("Shader Library/postProcessing/chromaticAberration/Vertex.glsl", "Shader Library/postProcessing/chromaticAberration/Fragment.glsl"));
	postProcessStack.AddLayer(LoadShader("Shader Library/postProcessing/vignette/Vertex.glsl", "Shader Library/postProcessing/vignette/Fragment.glsl"));

	CreatePostProcessVolume(AABB(Vector3(0, 0, 0), 5), true, 0, postProcessStack);
}

void Renderer::PostProcessing::SetPostProcessFrameBufferSize(int width, int height)
{
	oddFrameBuffer = LoadFrameBuffer(width, height, { {"COLOR"} });
	evenFrameBuffer = LoadFrameBuffer(width, height, { {"COLOR"} });
}

void Renderer::PostProcessing::RunPostProcessPipeline()
{
	ArrayList<PostProcessVolume*> intersectedVolumes = ArrayList<PostProcessVolume*>(Scene::postProcessVolumes.GetLength() + 1);
	intersectPostProcessVolumes(intersectedVolumes);
	
	if (intersectedVolumes.GetLength() == 0) 
	{
		Renderer::ClearFrame(Color3(0, 1, 0));
		CopyFrameBuffer(sceneFrameBuffer, 0);
		return;
	};

	CopyFrameBuffer(sceneFrameBuffer, 0, evenFrameBuffer, 0);
	currentProcessCount = 0;

	for (int i = 0; i < intersectedVolumes.GetLength(); i++) runPostProcessStack(intersectedVolumes[i]->postProcessStack, i == intersectedVolumes.GetLength() - 1);
}

static void intersectPostProcessVolumes(ArrayList<PostProcessVolume*>& intersectedVolumes) 
{
	for (int i = 0; i < Scene::postProcessVolumes.GetLength(); i++) 
	{
		if (IntersectPointToAABB(Scene::activeCamera.position, Scene::postProcessVolumes[i].aabb) || Scene::postProcessVolumes[i].boundless)
			if (Scene::postProcessVolumes[i].postProcessStack.layers.GetLength() != 0) intersectedVolumes.Add(&Scene::postProcessVolumes[i]);
	}
}

static void runPostProcessStack(const PostProcessStack& postProcessStack, bool lastStack) 
{
	bool lastLayer = false;
	for (int i = 0; i < postProcessStack.layers.GetLength(); i++)
	{
		PostProcessLayer& layer = postProcessStack.layers[i];
		if (i == postProcessStack.layers.GetLength() - 1 && lastStack) lastLayer = true;

		for (int j = 0; j < layer.GetShaders().GetLength(); j++)
		{
			Shader& shader = layer.GetShaders()[j];
			if (currentProcessCount % 2 == 0)
			{
				runPostProcess(&evenFrameBuffer, &oddFrameBuffer, shader);
				if (lastLayer && j == layer.GetShaders().GetLength() - 1) runPostProcess(&evenFrameBuffer, nullptr, shader);
			}
			else if (currentProcessCount % 2 == 1)
			{
				runPostProcess(&oddFrameBuffer, &evenFrameBuffer, shader);
				if (lastLayer && j == layer.GetShaders().GetLength() - 1) runPostProcess(&oddFrameBuffer, nullptr, shader);
			}
			currentProcessCount++;
		}
	}
}

static void runPostProcess(const FrameBuffer* input, const FrameBuffer* output, const Shader& shader)
{
	if (output != nullptr) output->Start();
	Renderer::ClearFrame(Color3(0, 1, 0));
	shader.Start();

	setFrameBufferTextures(*input);
	renderPostProcessQuad();
	unbindFrameBufferTextures();

	shader.Stop();
	if (output != nullptr) output->Stop();
}

static void renderPostProcessQuad() 
{
	glBindVertexArray(quadVertexArray.vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, quadVertexArray.elementBuffer.indexCount, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

static void setFrameBufferTextures(const FrameBuffer& frameBuffer)
{
	for (int i = 0; i < sceneFrameBuffer.attachments.GetLength(); i++) 
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, sceneFrameBuffer.attachments[i].textureAttachment.GetTextureID());
	}
	
	glActiveTexture(GL_TEXTURE0 + sceneFrameBuffer.attachments.GetLength());
	glBindTexture(GL_TEXTURE_2D, frameBuffer.attachments[0].textureAttachment.GetTextureID());
}

static void unbindFrameBufferTextures() 
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
}
