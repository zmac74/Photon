#pragma once

#include <utils/collection/Color.h>
#include <utils/math/Vector.h>

#include <scene/Node.h>

namespace Scene
{
	extern ArrayList<DirectionalLight> directionalLights;
	extern ArrayList<PointLight> pointLights;
	extern ArrayList<AreaLight> areaLights;
	extern ArrayList<SpotLight> spotLights;
	extern ArrayList<AmbientLight> ambientLights;

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

	DirectionalLight* CreateDirectionalLight(DirectionalLight light);
	PointLight* CreatePointLight(PointLight light);
	AreaLight* CreateAreaLight(AreaLight light);
	SpotLight* CreateSpotLight(SpotLight light);
	AmbientLight* CreateAmbientLight(AmbientLight light);
}

using namespace Scene;