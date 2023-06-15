#pragma once

#include <utils/collection/Buffer.h>
#include <utils/collection/Color.h>

#include <scene/Shader.h>

namespace Scene 
{
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
}

using namespace Scene;