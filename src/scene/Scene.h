#pragma once

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
	struct PostProcessVolume;
	struct AABB;
}

using namespace Scene;

#include <scene/BoundingVolume.h>
#include <scene/PostProcessVolume.h>
#include <scene/Texture.h>
#include <scene/Image.h>
#include <scene/Camera.h>
#include <scene/Light.h>
#include <scene/Node.h>
#include <scene/Shader.h>
#include <scene/Material.h>
#include <scene/Mesh.h>
#include <scene/Model.h>