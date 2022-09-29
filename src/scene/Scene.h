#pragma once

#include <vector>

#include <utils/collection/Buffer.h>
#include <utils/math/Vector.h>
#include <utils/math/Matrix.h>

namespace Scene 
{
	struct VertexArray;
	struct ElementBuffer;
	struct Mesh;
	struct VertexBuffer;
	struct Shader;

	struct VertexBuffer
	{
		unsigned int vboID = 0;
		int attributeIndex = -1;
		int vectorSize = 0;
	};

	struct ElementBuffer
	{
	public:
		unsigned int eboID = 0;
		int indexCount = 0;
	};

	struct VertexArray
	{
	public:
		unsigned int vaoID = 0;
		unsigned int vertexCount = 0;
		std::vector<VertexBuffer> vbos = std::vector<VertexBuffer>();
		ElementBuffer elementBuffer;
	};

	struct Mesh
	{
	public:
		VertexArray vertexArray;
	};

	struct Shader
	{
	public:
		unsigned int shaderID;

		int vertexStageID = -1;
		int geometryStageID = -1;
		int fragmentStageID = -1;

		void Start();
		void Stop();

		void SetFloat(const char* varName, float value);
		void SetInt(const char* varName, int value);
		
		void SetVector2(const char* varName, Vector2 value);
		void SetVector3(const char* varName, Vector3 value);
		void SetVector4(const char* varName, Vector4 value);

		void SetMatrix4x4(const char* varName, Matrix4x4 value);
	};

	struct Image 
	{
	public:
		Image(int width, int height, int channels, unsigned char* pixels) : width(width), height(height), channels(channels), pixels(pixels) {};

		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
		inline int GetChannels() const { return channels; }
		inline unsigned char* GetPixels() const { return pixels; }

	private:
		int width;
		int height;
		int channels;

		unsigned char* pixels;
	};

	struct Texture 
	{
	public:	
		Texture() = default;
		Texture(unsigned int textureID) : textureID(textureID) {}

		inline unsigned int GetTextureID() const { return textureID; }

	private:
		unsigned int textureID = 0;
	};
}

using namespace Scene;