#pragma once

#include <utils/collection/Buffer.h>
#include <utils/collection/Color.h>
#include <utils/math/Vector.h>
#include <utils/math/Matrix.h>

namespace Scene 
{
	struct VertexArray;
	struct ElementBuffer;
	struct Mesh;
	struct VertexBuffer;
	struct Shader;
	struct Image;
	struct Texture;
	struct Node;
	struct DirectionalLight;
	struct PointLight;
	struct AreaLight;
	struct SpotLight;
	struct AmbientLight;
	struct Model;
	struct Camera;
	struct Material;

	extern Camera activeCamera;
	extern ArrayList<DirectionalLight> directionalLights;
	extern ArrayList<PointLight> pointLights;
	extern ArrayList<AreaLight> areaLights;
	extern ArrayList<SpotLight> spotLights;
	extern ArrayList<AmbientLight> ambientLights;

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
		ArrayList<VertexBuffer> vbos = ArrayList<VertexBuffer>();
		ElementBuffer elementBuffer;
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

	enum NodeType
	{
		MESH = 0,
		DIRECTIONAL_LIGHT = 1,
		POINT_LIGHT = 2,
		AREA_LIGHT = 3,
		SPOT_LIGHT = 4,
		AMBIENT_LIGHT = 5,
		CAMERA = 6
	};

	struct Node 
	{
	public:
		const char* name;

		int type;
		int ID;

		Matrix4x4 offsetTransform;
		Matrix4x4 transform;
	};

	struct Mesh : Node
	{
	public:
		ArrayList<float> positions = ArrayList<float>(1000);
		ArrayList<float> textureCoords = ArrayList<float>(1000);
		ArrayList<float> normals = ArrayList<float>(1000);
		ArrayList<float> colors = ArrayList<float>(1000);
		ArrayList<float> tangents = ArrayList<float>(1000);
		ArrayList<int> indices = ArrayList<int>(1000);

		VertexArray vertexArray;
		int materialID;
	};

	struct DirectionalLight : Node
	{
	public:
		Vector3 direction;

		Color3 ambientColor;
		Color3 diffuseColor;
		Color3 specularColor;
	};

	struct PointLight : Node
	{
	public:
		Vector3 position;

		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

		Color3 ambientColor;
		Color3 diffuseColor;
		Color3 specularColor;
	};

	struct AreaLight : Node
	{
	public:
		Vector3 position;
		Vector3 direction;

		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

		float areaWidth;
		float areaHeight;

		Color3 ambientColor;
		Color3 diffuseColor;
		Color3 specularColor;
	};

	struct SpotLight : Node
	{
	public:
		Vector3 position;
		Vector3 direction;

		float innerConeAngle;
		float outerConeAngle;

		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;

		Color3 ambientColor;
		Color3 diffuseColor;
		Color3 specularColor;
	};

	struct AmbientLight : Node
	{
	public:
		Color3 ambientColor;
		Color3 diffuseColor;
		Color3 specularColor;
	};

	struct Camera : Node
	{
	public:
		Matrix4x4 cameraMatrix;
		
		Vector3 position;
		Vector3 lookDirection;
		Vector3 orientation;

		float nearPlane = 0;
		float farPlane = 0;

		float aspectRatio = 0;
		float fovX = 0;
	};

	struct Material 
	{
	public:
		Shader shader;

		const char* name;

		ArrayList<Texture> baseColorTextures;
		ArrayList<Texture> ambientTextures;
		ArrayList<Texture> diffuseTextures;
		ArrayList<Texture> ambientOcclusionTextures;
		ArrayList<Texture> clearCoatTextures;
		ArrayList<Texture> diffuseRoughnessTextures;
		ArrayList<Texture> displacementTextures;
		ArrayList<Texture> emissionColorTextures;
		ArrayList<Texture> emissiveTextures;
		ArrayList<Texture> lightMapTextures;
		ArrayList<Texture> metalnessTextures;
		ArrayList<Texture> normalTextures;
		ArrayList<Texture> opacityTextures;
		ArrayList<Texture> reflectionTextures;
		ArrayList<Texture> sheenTextures;
		ArrayList<Texture> shininessTextures;
		ArrayList<Texture> transmissionTextures;
		ArrayList<Texture> specularTextures;

		Color3 baseColor;
		Color3 diffuseColor;
		Color3 specularColor;
		Color3 reflectiveColor;
		Color3 ambientColor;
		Color3 emissiveColor;
		Color3 transparentColor;

		bool wireframe;
		bool twoSided;

		float reflectivity;
		float specularFactor;
		float sheenColorFactor;
		float sheenRoughnessFactor;
		float roughnessFactor;
		float metallicFactor;
		float glossinessFactor;
		float emissiveIntensity;
		float anisotrophyFactor;
		float clearcoatFactor;
		float clearcoatRoughnessFactor;
		float opacity;
		float shininess;
		float shininessStrength;
		float refracti;
	};

	struct Model
	{
	public:
		ArrayList<Mesh> meshes;

		ArrayList<DirectionalLight> directionalLights;
		ArrayList<PointLight> pointLights;
		ArrayList<AreaLight> areaLights;
		ArrayList<SpotLight> spotLights;
		ArrayList<AmbientLight> ambientLights;
		ArrayList<Material> materials;

		ArrayList<Camera> cameras;
	};
}

using namespace Scene;