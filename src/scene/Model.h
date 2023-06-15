#pragma once

#include <utils/collection/Buffer.h>

#include <scene/Mesh.h>
#include <scene/Light.h>
#include <scene/Material.h>
#include <scene/Camera.h>

namespace Scene 
{
	extern LinkedList<Model> models;
	
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