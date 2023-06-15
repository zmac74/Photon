#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <scene/importer/Importer.h>

#include <debug/Debug.h>

#include <utils/collection/Buffer.h>
#include <utils/collection/Color.h>
#include <utils/math/Arithmetic.h>
#include <utils/math/Vector.h>
#include <utils/math/Matrix.h>

#include <scene/Scene.h>

const int Scene::Importer::POSTPROCESS_TARGET_REALTIME_FAST = aiProcessPreset_TargetRealtime_Fast;
const int Scene::Importer::POSTPROCESS_TARGET_REALTIME_QUALITY = aiProcessPreset_TargetRealtime_Quality;
const int Scene::Importer::POSTPROCESS_TARGET_REALTIME_MAX_QUALITY = aiProcessPreset_TargetRealtime_MaxQuality;

const int Scene::Importer::POSTPROCESS_CALC_TANGENT_SPACE = aiProcess_CalcTangentSpace;
const int Scene::Importer::POSTPROCESS_CONVERT_TO_LEFT_HANDED = aiProcess_ConvertToLeftHanded;
const int Scene::Importer::POSTPROCESS_DEBONE = aiProcess_Debone;
const int Scene::Importer::POSTPROCESS_DROP_NORMALS = aiProcess_DropNormals;
const int Scene::Importer::POSTPROCESS_EMBED_TEXTURES = aiProcess_EmbedTextures;
const int Scene::Importer::POSTPROCESS_FIND_DEGENERATES = aiProcess_FindDegenerates;
const int Scene::Importer::POSTPROCESS_FIND_INSTANCES = aiProcess_FindInstances;
const int Scene::Importer::POSTPROCESS_FIND_INVALID_DATA = aiProcess_FindInvalidData;
const int Scene::Importer::POSTPROCESS_FIX_INFACING_NORMALS = aiProcess_FixInfacingNormals;
const int Scene::Importer::POSTPROCESS_FLIP_UV = aiProcess_FlipUVs;
const int Scene::Importer::POSTPROCESS_FLIP_WINDING_ORDER = aiProcess_FlipWindingOrder;
const int Scene::Importer::POSTPROCESS_FORCE_GEN_NORMALS = aiProcess_ForceGenNormals;
const int Scene::Importer::POSTPROCESS_GEN_BOUNDS_BOXES = aiProcess_GenBoundingBoxes;
const int Scene::Importer::POSTPROCESS_GEN_NORMALS = aiProcess_GenNormals;
const int Scene::Importer::POSTPROCESS_GEN_SMOOTH_NORMALS = aiProcess_GenSmoothNormals;
const int Scene::Importer::POSTPROCESS_GEN_UV_COORDS = aiProcess_GenUVCoords;
const int Scene::Importer::POSTPROCESS_GLOBAL_SCALE = aiProcess_GlobalScale;
const int Scene::Importer::POSTPROCESS_IMPROVE_CACHE_LOCALITY = aiProcess_ImproveCacheLocality;
const int Scene::Importer::POSTPROCESS_JOIN_IDENTICAL_VERTICES = aiProcess_JoinIdenticalVertices;
const int Scene::Importer::POSTPROCESS_LIMIT_BONE_WEIGHTS = aiProcess_LimitBoneWeights;
const int Scene::Importer::POSTPROCESS_MAKE_LEFT_HANDED = aiProcess_MakeLeftHanded;
const int Scene::Importer::POSTPROCESS_OPTIMIZE_GRAPH = aiProcess_OptimizeGraph;
const int Scene::Importer::POSTPROCESS_OPTIMIZE_MESHES = aiProcess_OptimizeMeshes;
const int Scene::Importer::POSTPROCESS_POPULATE_ARMATURE_DATA = aiProcess_PopulateArmatureData;
const int Scene::Importer::POSTPROCESS_PRE_TRANSFORM_VERTICES = aiProcess_PreTransformVertices;
const int Scene::Importer::POSTPROCESS_REMOVE_COMPONENT = aiProcess_RemoveComponent;
const int Scene::Importer::POSTPROCESS_REMOVE_REDUNDANT_MATERIALS = aiProcess_RemoveRedundantMaterials;
const int Scene::Importer::POSTPROCESS_SORT_BY_P_TYPE = aiProcess_SortByPType;
const int Scene::Importer::POSTPROCESS_SPLIT_BY_BONE_COUNT = aiProcess_SplitByBoneCount;
const int Scene::Importer::POSTPROCESS_SPLIT_LARGE_MESHES = aiProcess_SplitLargeMeshes;
const int Scene::Importer::POSTPROCESS_TRANSFORM_UV_COORDS = aiProcess_TransformUVCoords;
const int Scene::Importer::POSTPROCESS_TRIANGULATE = aiProcess_Triangulate;
const int Scene::Importer::POSTPROCESS_VALIDATE_DATA_STRUCTURE = aiProcess_ValidateDataStructure;

static int MESH_NAMING_OFFSET = 0;
static int LIGHT_NAMING_OFFSET = 0;
static int CAMERA_NAMING_OFFSET = 0;

static void calculateModelDirectory(const char* path);
static void calculateNodeNamingOffset(const char* path);
static void processScene(const aiScene* scene);
static void processMesh(const aiMesh* srcMesh, const aiScene* srcScene);
static void processLight(const aiLight* srcLight);
static void processCamera(const aiCamera* srcCamera);
static void processMaterial(const aiMaterial* srcMaterial, const aiScene* srcScene);
static ArrayList<Texture> processTexture(const aiMaterial* srcMaterial, aiTextureType type, const aiScene* srcScene);
static void processNodeData(aiString name, Node& nodeData, NodeType type, int namingOffset);
static void processTransform(const aiNode* node, Matrix4x4* transform);

static void processMeshPositions(const aiMesh* mesh, ArrayList<float>& positions);
static void processMeshTextureCoords(const aiMesh* mesh, ArrayList<float>& textureCoords);
static void processMeshNormals(const aiMesh* mesh, ArrayList<float>& normals);
static void processMeshColors(const aiMesh* mesh, ArrayList<float>& colors);
static void processMeshTangents(const aiMesh* mesh, ArrayList<float>& tangents);
static void processMeshIndices(const aiMesh* mesh, ArrayList<int>& indices);

static void processDirectionalLight(const aiLight* srcLight);
static void processPointLight(const aiLight* srcLight);
static void processAreaLight(const aiLight* srcLight);
static void processSpotLight(const aiLight* srcLight);
static void processAmbientLight(const aiLight* srcLight);

static Color3 to01Range(const Color3& color);
static Matrix4x4 convertMatrixFormat(const aiMatrix4x4& srcMatrix);

static std::string directory;
static Model model;
static aiNode* rootNode = nullptr;
static aiMaterial** materials = nullptr;

Model* Scene::Importer::LoadModel(const char* path, unsigned int flags) 
{
	model = Model();
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, flags);
	if (scene == nullptr) Debug::Assert("Error: Could not load model.");
	materials = scene->mMaterials;

	calculateModelDirectory(path);
	calculateNodeNamingOffset(path);
	processScene(scene);
	models.Add(model);
	
	importer.FreeScene();
	return &models.GetLastElement();
}

Model* Scene::Importer::LoadModel(const char* path)
{
	return LoadModel(path, POSTPROCESS_TRIANGULATE | POSTPROCESS_PRE_TRANSFORM_VERTICES);
}

static void calculateModelDirectory(const char* path) 
{
	std::string str = std::string(path);
	directory = str.substr(0, str.find_last_of("/") + 1);
}

static void calculateNodeNamingOffset(const char* path) 
{
	std::string fileExt = std::string(path);
	fileExt = fileExt.substr(fileExt.find(".") + 1, std::string::npos);

	if (fileExt == "obj") 
	{
		MESH_NAMING_OFFSET = 0;
		LIGHT_NAMING_OFFSET = 0;
		CAMERA_NAMING_OFFSET = 0;
	}
	else if (fileExt == "dae") 
	{
		MESH_NAMING_OFFSET = -5;
		LIGHT_NAMING_OFFSET = -6;
		CAMERA_NAMING_OFFSET = -7;
	} 
}

static void processScene(const aiScene* scene) 
{
	rootNode = scene->mRootNode;
	if (scene->HasMeshes()) for (int i = 0; i < scene->mNumMeshes; i++)	processMesh(scene->mMeshes[i], scene);
	if (scene->HasLights()) for (int i = 0; i < scene->mNumLights; i++) processLight(scene->mLights[i]);
	if (scene->HasCameras()) for (int i = 0; i < scene->mNumCameras; i++) processCamera(scene->mCameras[i]);
}

static void processNodeData(aiString name, Node& nodeData, NodeType type, int namingOffset)
{
	std::string str = std::string(name.C_Str()).substr(0, name.length + namingOffset);
	nodeData.name = str.c_str();
	nodeData.type = type;
	nodeData.ID = 0;//model.meshes.GetLength() - 1;

	aiNode* node = rootNode->FindNode(nodeData.name);
	//nodeData.offsetTransform = convertMatrixFormat(node->mTransformation);
	//processTransform(node, &nodeData.transform);
}

static void processTransform(const aiNode* node, Matrix4x4* transform) 
{
	Matrix4x4 matrix = convertMatrixFormat(node->mTransformation) * *transform;
	*transform = matrix;

	if (node->mParent == nullptr) return;
	processTransform(node->mParent, transform);
}

static void processMesh(const aiMesh* srcMesh, const aiScene* srcScene)
{
	model.meshes.Add(Mesh());
	Mesh& mesh = model.meshes.GetLastElement();

	processNodeData(srcMesh->mName, mesh, NodeType::MESH, MESH_NAMING_OFFSET);
	
	if (srcMesh->HasPositions()) processMeshPositions(srcMesh, mesh.positions);
	if (srcMesh->HasTextureCoords(0)) processMeshTextureCoords(srcMesh, mesh.textureCoords);
	if (srcMesh->HasNormals()) processMeshNormals(srcMesh, mesh.normals);
	if (srcMesh->HasVertexColors(0)) processMeshColors(srcMesh, mesh.colors);
	if (srcMesh->HasTangentsAndBitangents()) processMeshTangents(srcMesh, mesh.tangents);
	if (srcMesh->HasFaces()) processMeshIndices(srcMesh, mesh.indices);

	mesh.vertexArray = LoadVertexArray(mesh.positions, mesh.textureCoords, mesh.normals, mesh.colors, mesh.tangents, mesh.indices);

	mesh.materialID = model.materials.GetLength();
	processMaterial(materials[srcMesh->mMaterialIndex], srcScene);
}

static void processMeshPositions(const aiMesh* mesh, ArrayList<float>& positions)
{
	const unsigned int positionCount = mesh->mNumVertices;

	for (int i = 0; i < positionCount; i++)
	{
		const aiVector3D vector = mesh->mVertices[i];
		positions.Add(vector.x);
		positions.Add(vector.y);
		positions.Add(vector.z);
	}
}

static void processMeshTextureCoords(const aiMesh* mesh, ArrayList<float>& textureCoords)
{
	const unsigned int textureCoordCount = mesh->mNumVertices;

	for (int i = 0; i < textureCoordCount; i++)
	{
		const aiVector3D vector = mesh->mTextureCoords[0][i];
		textureCoords.Add(vector.x);
		textureCoords.Add(vector.y);
	}
}

static void processMeshNormals(const aiMesh* mesh, ArrayList<float>& normals)
{
	const unsigned int normalCount = mesh->mNumVertices;

	for (int i = 0; i < normalCount; i++)
	{
		const aiVector3D vector = mesh->mNormals[i];
		normals.Add(vector.x);
		normals.Add(vector.y);
		normals.Add(vector.z);
	}
}

static void processMeshColors(const aiMesh* mesh, ArrayList<float>& colors)
{
	const unsigned int colorCount = mesh->mNumVertices;

	for (int i = 0; i < colorCount; i++)
	{
		const aiColor4D vector = mesh->mColors[0][i];
		colors.Add(vector.r);
		colors.Add(vector.g);
		colors.Add(vector.b);
		colors.Add(vector.a);
	}
}

static void processMeshTangents(const aiMesh* mesh, ArrayList<float>& tangents)
{
	const unsigned int tangentCount = mesh->mNumVertices;

	for (int i = 0; i < tangentCount; i++)
	{
		const aiVector3D vector = mesh->mTangents[i];
		tangents.Add(vector.x);
		tangents.Add(vector.y);
		tangents.Add(vector.z);
	}
}

static void processMeshIndices(const aiMesh* mesh, ArrayList<int>& indices)
{
	const unsigned int faceCount = mesh->mNumFaces;

	for (int i = 0; i < faceCount; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.Add(face.mIndices[j]);
		}
	}
}

static void processLight(const aiLight* light) 
{
	aiLightSourceType lightType = light->mType;

	if (lightType == aiLightSource_DIRECTIONAL) processDirectionalLight(light);
	else if (lightType == aiLightSource_POINT) processPointLight(light);
	else if (lightType == aiLightSource_AREA) processAreaLight(light);
	else if (lightType == aiLightSource_SPOT) processSpotLight(light);
	else if (lightType == aiLightSource_AMBIENT) processAmbientLight(light);
}

static void processDirectionalLight(const aiLight* srcLight) 
{
	model.directionalLights.Add(DirectionalLight());
	DirectionalLight& light = model.directionalLights.GetLastElement();

	processNodeData(srcLight->mName, light, NodeType::DIRECTIONAL_LIGHT, LIGHT_NAMING_OFFSET);

	light.direction = Vector3(srcLight->mDirection.x, srcLight->mDirection.y, srcLight->mDirection.z);

	light.ambientColor = Color3(to01Range(Color3(srcLight->mColorAmbient.r, srcLight->mColorAmbient.g, srcLight->mColorAmbient.b)));
	light.diffuseColor = Color3(to01Range(Color3(srcLight->mColorDiffuse.r, srcLight->mColorDiffuse.g, srcLight->mColorDiffuse.b)));
	light.specularColor = Color3(to01Range(Color3(srcLight->mColorSpecular.r, srcLight->mColorSpecular.g, srcLight->mColorSpecular.b)));

	Scene::directionalLights.Add(light);
}

static void processPointLight(const aiLight* srcLight) 
{
	model.pointLights.Add(PointLight());
	PointLight& light = model.pointLights.GetLastElement();

	processNodeData(srcLight->mName, light, NodeType::POINT_LIGHT, LIGHT_NAMING_OFFSET);

	light.position = Vector3(srcLight->mPosition.x, srcLight->mPosition.y, srcLight->mPosition.z);

	light.constantAttenuation = srcLight->mAttenuationConstant;
	light.linearAttenuation = srcLight->mAttenuationLinear;
	light.quadraticAttenuation = srcLight->mAttenuationQuadratic;

	light.ambientColor = Color3(to01Range(Color3(srcLight->mColorAmbient.r, srcLight->mColorAmbient.g, srcLight->mColorAmbient.b)));
	light.diffuseColor = Color3(to01Range(Color3(srcLight->mColorDiffuse.r, srcLight->mColorDiffuse.g, srcLight->mColorDiffuse.b)));
	light.specularColor = Color3(to01Range(Color3(srcLight->mColorSpecular.r, srcLight->mColorSpecular.g, srcLight->mColorSpecular.b)));

	Scene::pointLights.Add(light);
}

static void processAreaLight(const aiLight* srcLight) 
{
	model.areaLights.Add(AreaLight());
	AreaLight& light = model.areaLights.GetLastElement();

	processNodeData(srcLight->mName, light, NodeType::AREA_LIGHT, LIGHT_NAMING_OFFSET);

	light.position = Vector3(srcLight->mPosition.x, srcLight->mPosition.y, srcLight->mPosition.z);
	light.direction = Vector3(srcLight->mDirection.x, srcLight->mDirection.y, srcLight->mDirection.z);
	
	light.constantAttenuation = srcLight->mAttenuationConstant;
	light.linearAttenuation = srcLight->mAttenuationLinear;
	light.quadraticAttenuation = srcLight->mAttenuationQuadratic;

	light.areaWidth = srcLight->mSize.x;
	light.areaHeight = srcLight->mSize.y;

	light.ambientColor = Color3(to01Range(Color3(srcLight->mColorAmbient.r, srcLight->mColorAmbient.g, srcLight->mColorAmbient.b)));
	light.diffuseColor = Color3(to01Range(Color3(srcLight->mColorDiffuse.r, srcLight->mColorDiffuse.g, srcLight->mColorDiffuse.b)));
	light.specularColor = Color3(to01Range(Color3(srcLight->mColorSpecular.r, srcLight->mColorSpecular.g, srcLight->mColorSpecular.b)));
	
	Scene::areaLights.Add(light);
}

static void processSpotLight(const aiLight* srcLight) 
{
	model.spotLights.Add(SpotLight());
	SpotLight& light = model.spotLights.GetLastElement();

	processNodeData(srcLight->mName, light, NodeType::SPOT_LIGHT, LIGHT_NAMING_OFFSET);
	
	light.position = Vector3(srcLight->mPosition.x, srcLight->mPosition.y, srcLight->mPosition.z);
	light.direction = Vector3(srcLight->mDirection.x, srcLight->mDirection.y, srcLight->mDirection.z);

	light.innerConeAngle = srcLight->mAngleInnerCone;
	light.outerConeAngle = srcLight->mAngleOuterCone;

	light.constantAttenuation = srcLight->mAttenuationConstant;
	light.linearAttenuation = srcLight->mAttenuationLinear;
	light.quadraticAttenuation = srcLight->mAttenuationQuadratic;

	light.ambientColor = Color3(to01Range(Color3(srcLight->mColorAmbient.r, srcLight->mColorAmbient.g, srcLight->mColorAmbient.b)));
	light.diffuseColor = Color3(to01Range(Color3(srcLight->mColorDiffuse.r, srcLight->mColorDiffuse.g, srcLight->mColorDiffuse.b)));
	light.specularColor = Color3(to01Range(Color3(srcLight->mColorSpecular.r, srcLight->mColorSpecular.g, srcLight->mColorSpecular.b)));
	
	Scene::spotLights.Add(light);
}

static void processAmbientLight(const aiLight* srcLight) 
{
	model.ambientLights.Add(AmbientLight());
	AmbientLight& light = model.ambientLights.GetLastElement();

	processNodeData(srcLight->mName, light, NodeType::AMBIENT_LIGHT, LIGHT_NAMING_OFFSET);

	light.ambientColor = Color3(to01Range(Color3(srcLight->mColorAmbient.r, srcLight->mColorAmbient.g, srcLight->mColorAmbient.b)));
	light.diffuseColor = Color3(to01Range(Color3(srcLight->mColorDiffuse.r, srcLight->mColorDiffuse.g, srcLight->mColorDiffuse.b)));
	light.specularColor = Color3(to01Range(Color3(srcLight->mColorSpecular.r, srcLight->mColorSpecular.g, srcLight->mColorSpecular.b)));

	Scene::ambientLights.Add(light);
}

static void processCamera(const aiCamera* srcCamera) 
{
	model.cameras.Add(Camera());
	Camera& camera = model.cameras.GetLastElement();

	processNodeData(srcCamera->mName, camera, NodeType::CAMERA, CAMERA_NAMING_OFFSET);

	camera.aspectRatio = srcCamera->mAspect;
	camera.fovX = srcCamera->mHorizontalFOV;
	camera.nearPlane = srcCamera->mClipPlaneNear;
	camera.farPlane = srcCamera->mClipPlaneFar;
	
	aiMatrix4x4 matrix;
	srcCamera->GetCameraMatrix(matrix);
	camera.cameraMatrix = convertMatrixFormat(matrix);
}

static void processMaterial(const aiMaterial* srcMaterial, const aiScene* srcScene)
{
	model.materials.Add(Material());
	Material& material = model.materials.GetLastElement();

	material.shader = LoadShader("Shader Library/albedo/Vertex.glsl", "Shader Library/albedo/Fragment.glsl");

	material.shader.Start();
	material.shader.SetInt("materialTextures.baseColorMap", 0);
	material.shader.SetInt("materialTextures.normalMap", 1);
	material.shader.SetInt("materialTextures.diffuseRoughnessMap", 2);
	material.shader.SetInt("materialTextures.clearCoatMap", 3);
	material.shader.SetInt("materialTextures.ambientOcclusionMap", 4);
	material.shader.SetInt("materialTextures.opacityTextures", 5);
	material.shader.SetInt("materialTextures.reflectionMap", 6);
	material.shader.SetInt("materialTextures.sheenMap", 7);
	material.shader.SetInt("materialTextures.shininessMap", 8);
	material.shader.SetInt("materialTextures.transmissionMap", 9);
	material.shader.SetInt("materialTextures.specularMap", 10);
	material.shader.SetInt("materialTextures.metalnessMap", 11);
	material.shader.SetInt("materialTextures.displacementMap", 12);
	material.shader.SetInt("materialTextures.emissionColorMap", 13);
	material.shader.SetInt("materialTextures.emissiveMap", 14);
	material.shader.Stop();

	aiString name;
	srcMaterial->Get(AI_MATKEY_NAME, name);
	material.name = name.C_Str();

	aiColor3D baseColor;
	srcMaterial->Get(AI_MATKEY_BASE_COLOR, baseColor);
	material.baseColor = Color3(baseColor.r, baseColor.g, baseColor.b);

	aiColor3D diffuseColor;
	srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, material.diffuseColor);
	material.baseColor = Color3(diffuseColor.r, diffuseColor.g, diffuseColor.b);

	aiColor3D emissiveColor;
	srcMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, material.emissiveColor);
	material.baseColor = Color3(emissiveColor.r, emissiveColor.g, emissiveColor.b);

	aiColor3D ambientColor;
	srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, material.ambientColor);
	material.baseColor = Color3(ambientColor.r, ambientColor.g, ambientColor.b);

	aiColor3D reflectiveColor;
	srcMaterial->Get(AI_MATKEY_COLOR_REFLECTIVE, material.reflectiveColor);
	material.baseColor = Color3(reflectiveColor.r, reflectiveColor.g, reflectiveColor.b);

	aiColor3D specularColor;
	srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, material.specularColor);
	material.baseColor = Color3(specularColor.r, specularColor.g, specularColor.b);

	aiColor3D transparentColor;
	srcMaterial->Get(AI_MATKEY_COLOR_TRANSPARENT, material.transparentColor);
	material.baseColor = Color3(transparentColor.r, transparentColor.g, transparentColor.b);

	srcMaterial->Get(AI_MATKEY_REFLECTIVITY, material.reflectivity);
	srcMaterial->Get(AI_MATKEY_ROUGHNESS_FACTOR, material.roughnessFactor);
	srcMaterial->Get(AI_MATKEY_SHEEN_COLOR_FACTOR, material.sheenColorFactor);
	srcMaterial->Get(AI_MATKEY_SHEEN_ROUGHNESS_FACTOR, material.sheenRoughnessFactor);
	srcMaterial->Get(AI_MATKEY_SPECULAR_FACTOR, material.specularFactor);
	srcMaterial->Get(AI_MATKEY_ANISOTROPY_FACTOR, material.anisotrophyFactor);
	srcMaterial->Get(AI_MATKEY_CLEARCOAT_FACTOR, material.clearcoatFactor);
	srcMaterial->Get(AI_MATKEY_CLEARCOAT_ROUGHNESS_FACTOR, material.clearcoatRoughnessFactor);
	srcMaterial->Get(AI_MATKEY_EMISSIVE_INTENSITY, material.emissiveIntensity);
	srcMaterial->Get(AI_MATKEY_GLOSSINESS_FACTOR, material.glossinessFactor);
	srcMaterial->Get(AI_MATKEY_METALLIC_FACTOR, material.metallicFactor);
	srcMaterial->Get(AI_MATKEY_OPACITY, material.opacity);
	srcMaterial->Get(AI_MATKEY_SHININESS, material.shininess);
	srcMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, material.shininessStrength);
	srcMaterial->Get(AI_MATKEY_REFRACTI, material.refracti);

	srcMaterial->Get(AI_MATKEY_ENABLE_WIREFRAME, material.wireframe);
	srcMaterial->Get(AI_MATKEY_TWOSIDED, material.twoSided);

	material.baseColorTextures = processTexture(srcMaterial, aiTextureType_BASE_COLOR, srcScene);
	material.ambientTextures = processTexture(srcMaterial, aiTextureType_DIFFUSE, srcScene);
	material.diffuseTextures = processTexture(srcMaterial, aiTextureType_AMBIENT, srcScene);
	material.ambientOcclusionTextures = processTexture(srcMaterial, aiTextureType_AMBIENT_OCCLUSION, srcScene);
	material.clearCoatTextures = processTexture(srcMaterial, aiTextureType_CLEARCOAT, srcScene);
	material.diffuseRoughnessTextures = processTexture(srcMaterial, aiTextureType_DIFFUSE_ROUGHNESS, srcScene);
	material.displacementTextures = processTexture(srcMaterial, aiTextureType_DISPLACEMENT, srcScene);
	material.emissionColorTextures = processTexture(srcMaterial, aiTextureType_EMISSION_COLOR, srcScene);
	material.emissiveTextures = processTexture(srcMaterial, aiTextureType_EMISSIVE, srcScene);
	material.lightMapTextures = processTexture(srcMaterial, aiTextureType_LIGHTMAP, srcScene);
	material.metalnessTextures = processTexture(srcMaterial, aiTextureType_METALNESS, srcScene);
	material.normalTextures = processTexture(srcMaterial, aiTextureType_NORMALS, srcScene);
	material.opacityTextures = processTexture(srcMaterial, aiTextureType_OPACITY, srcScene);
	material.reflectionTextures = processTexture(srcMaterial, aiTextureType_REFLECTION, srcScene);
	material.sheenTextures = processTexture(srcMaterial, aiTextureType_SHEEN, srcScene);
	material.shininessTextures = processTexture(srcMaterial, aiTextureType_SHININESS, srcScene);
	material.transmissionTextures = processTexture(srcMaterial, aiTextureType_TRANSMISSION, srcScene);
	material.specularTextures = processTexture(srcMaterial, aiTextureType_SPECULAR, srcScene);
}

static ArrayList<Texture> processTexture(const aiMaterial* srcMaterial, aiTextureType type, const aiScene* srcScene)
{
	const unsigned int textureAmount = srcMaterial->GetTextureCount(type);
	ArrayList<Texture> textures = ArrayList<Texture>();
	
	for (int i = 0; i < textureAmount; i++) 
	{
		aiString path;
		srcMaterial->GetTexture(type, i, &path);
		if (const aiTexture* texture = srcScene->GetEmbeddedTexture(path.C_Str())) 
		{
			const int textureLength = texture->mWidth * texture->mHeight;
			unsigned char* texels = new unsigned char[textureLength * 4];
			
			for (int i = 0; i < textureLength; i++) 
			{
				texels[(i * 4)] = texture->pcData[i].r;
				texels[(i * 4) + 1] = texture->pcData[i].g;
				texels[(i * 4) + 2] = texture->pcData[i].b;
				texels[(i * 4) + 3] = texture->pcData[i].a;
			}

			textures.Add(LoadTexture(texels, texture->mWidth, texture->mHeight, 4));
		}
		else 
		{
			textures.Add(LoadTexture((directory + std::string(path.C_Str())).c_str()));
		}
	}

	return textures;
}

static Color3 to01Range(const Color3& color) 
{
	float firtsMax = Math::Max(color.r, color.g);
	float max = Math::Max(firtsMax, color.b);

	return Color3(color.r / max, color.g / max, color.b / max);
}

static Matrix4x4 convertMatrixFormat(const aiMatrix4x4& srcMatrix) 
{
	Matrix4x4 matrix;

	matrix.Set00(srcMatrix.a1); matrix.Set10(srcMatrix.a2); matrix.Set20(srcMatrix.a3); matrix.Set30(srcMatrix.a4);
	matrix.Set01(srcMatrix.b1); matrix.Set11(srcMatrix.b2); matrix.Set21(srcMatrix.b3); matrix.Set31(srcMatrix.b4);
	matrix.Set02(srcMatrix.c1); matrix.Set12(srcMatrix.c2); matrix.Set22(srcMatrix.c3); matrix.Set32(srcMatrix.c4);
	matrix.Set03(srcMatrix.d1); matrix.Set13(srcMatrix.d2); matrix.Set23(srcMatrix.d3); matrix.Set33(srcMatrix.d4);

	return matrix;
}