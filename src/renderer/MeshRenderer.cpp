#include <gl/glew.h>
#include <string>

#include <scene/Scene.h>
#include <renderer/Renderer.h>
#include <utils/math/Arithmetic.h>

static void setCamera(const Model& model, int i);
static void setLights(const Model& model, int i);
static void setTextures(const Model& model, int i);
static void setMaterialProperties(const Model& model, int i);

void Renderer::Render(Model model)
{
	for (int i = 0; i < model.meshes.GetLength(); i++) 
	{
		Shader shader = model.materials[model.meshes[i].materialID].shader;
		shader.Start();

		shader.SetMatrix4x4("camera", Scene::activeCamera.cameraMatrix);
		shader.SetMatrix4x4("transform", model.meshes[i].transform);
		const VertexArray& vertexArray = model.meshes[i].vertexArray;

		glBindVertexArray(vertexArray.vaoID);
		for (int i = 0; i < vertexArray.vbos.GetLength(); i++) glEnableVertexAttribArray(vertexArray.vbos[i].attributeIndex);

		setCamera(model, i);
		setLights(model, i);
		setMaterialProperties(model, i);
		setTextures(model, i);

		glDrawElements(GL_TRIANGLES, vertexArray.elementBuffer.indexCount, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, 0);

		for (int i = 0; i < vertexArray.vbos.GetLength(); i++) glDisableVertexAttribArray(vertexArray.vbos[i].attributeIndex);
		glBindVertexArray(0);

		shader.Stop();
	}
}

static void setCamera(const Model& model, int i) 
{
	Shader& shader = model.materials[model.meshes[i].materialID].shader;

	shader.SetVector3("cameraData.position", Scene::activeCamera.position);
	shader.SetVector3("cameraData.lookDirection", Scene::activeCamera.lookDirection);
	shader.SetVector3("cameraData.orientation", Scene::activeCamera.orientation);
	shader.SetFloat("cameraData.nearPlane", Scene::activeCamera.nearPlane);
	shader.SetFloat("cameraData.farPlane", Scene::activeCamera.farPlane);
	shader.SetFloat("cameraData.aspectRatio", Scene::activeCamera.aspectRatio);
	shader.SetFloat("cameraData.fovX", Scene::activeCamera.fovX);
}

static void setLights(const Model& model, int i) 
{
	Shader& shader = model.materials[model.meshes[i].materialID].shader;

	//shader.SetVector3("pointLight.position", Vector3(0, 1.5, 0));
	//shader.SetVector3("pointLight.diffuseColor", Vector3(1, 1, 1));
	//shader.SetFloat("pointLight.constantAttenuation", 1.0f);
	//shader.SetFloat("pointLight.linearAttenuation", 0.045f);
	//shader.SetFloat("pointLight.quadraticAttenuation", 0.0075f);

	/*shader.SetVector3("spotLight.position", Scene::activeCamera.position);
	shader.SetVector3("spotLight.direction", Scene::activeCamera.lookDirection);
	shader.SetFloat("spotLight.innerConeAngle", Math::Cos(Math::ToRadians(25.0f)));
	shader.SetFloat("spotLight.outerConeAngle", Math::Cos(Math::ToRadians(40.0f)));
	shader.SetVector3("spotLight.diffuseColor", Vector3(1, 1, 1));
	shader.SetFloat("spotLight.constantAttenuation", 1.0f);
	shader.SetFloat("spotLight.linearAttenuation", 0.0045f);
	shader.SetFloat("spotLight.quadraticAttenuation", 0.00075f);*/

	shader.SetInt("directionalLightCount", Scene::directionalLights.GetLength());
	for (int i = 0; i < Scene::directionalLights.GetLength(); i++) 
	{
		DirectionalLight& light = Scene::directionalLights[i];
		std::string index = std::to_string(i);

		shader.SetVector3(("directionalLights[" + index + "].direction").c_str(), light.direction);
		shader.SetVector3(("directionalLights[" + index + "].diffuseColor").c_str(), Vector3(light.diffuseColor.r, light.diffuseColor.g, light.diffuseColor.b));
		shader.SetVector3(("directionalLights[" + index + "].specularColor").c_str(), Vector3(light.specularColor.r, light.specularColor.g, light.specularColor.b));
		shader.SetVector3(("directionalLights[" + index + "].ambientColor").c_str(), Vector3(light.ambientColor.r, light.ambientColor.g, light.ambientColor.b));
	}

	shader.SetInt("pointLightCount", Scene::pointLights.GetLength());
	for (int i = 0; i < Scene::pointLights.GetLength(); i++)
	{
		PointLight& light = Scene::pointLights[i];
		std::string index = std::to_string(i);

		shader.SetVector3(("pointLights[" + index + "].position").c_str(), light.position);
		shader.SetVector3(("pointLights[" + index + "].diffuseColor").c_str(), Vector3(light.diffuseColor.r, light.diffuseColor.g, light.diffuseColor.b));
		shader.SetVector3(("pointLights[" + index + "].specularColor").c_str(), Vector3(light.specularColor.r, light.specularColor.g, light.specularColor.b));
		shader.SetVector3(("pointLights[" + index + "].ambientColor").c_str(), Vector3(light.ambientColor.r, light.ambientColor.g, light.ambientColor.b));
		shader.SetFloat(("pointLights[" + index + "].constantAttenuation").c_str(), light.constantAttenuation);
		shader.SetFloat(("pointLights[" + index + "].linearAttenuation").c_str(), light.linearAttenuation);
		shader.SetFloat(("pointLights[" + index + "].quadraticAttenuation").c_str(), light.quadraticAttenuation);
	}

	shader.SetInt("spotLightCount", Scene::spotLights.GetLength());
	for (int i = 0; i < Scene::spotLights.GetLength(); i++)
	{
		SpotLight& light = Scene::spotLights[i];
		std::string index = std::to_string(i);

		shader.SetVector3(("spotLights[" + index + "].position").c_str(), light.position);
		shader.SetVector3(("spotLights[" + index + "].direction").c_str(), light.direction);
		shader.SetFloat(("spotLights[" + index + "].innerConeAngle").c_str(), Math::Cos(light.innerConeAngle));
		shader.SetFloat(("spotLights[" + index + "].outerConeAngle").c_str(), Math::Cos(light.outerConeAngle));
		shader.SetVector3(("spotLights[" + index + "].diffuseColor").c_str(), Vector3(light.diffuseColor.r, light.diffuseColor.g, light.diffuseColor.b));
		shader.SetVector3(("spotLights[" + index + "].specularColor").c_str(), Vector3(light.specularColor.r, light.specularColor.g, light.specularColor.b));
		shader.SetVector3(("spotLights[" + index + "].ambientColor").c_str(), Vector3(light.ambientColor.r, light.ambientColor.g, light.ambientColor.b));
		shader.SetFloat(("spotLights[" + index + "].constantAttenuation").c_str(), light.constantAttenuation);
		shader.SetFloat(("spotLights[" + index + "].linearAttenuation").c_str(), light.linearAttenuation);
		shader.SetFloat(("spotLights[" + index + "].quadraticAttenuation").c_str(), light.quadraticAttenuation);
	}
}

static void setMaterialProperties(const Model& model, int i)
{
	Material& material = model.materials[model.meshes[i].materialID];

	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.baseColor", Vector3(material.baseColor.r, material.baseColor.g, material.baseColor.b));
	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.diffuseColor", Vector3(material.diffuseColor.r, material.diffuseColor.g, material.diffuseColor.b));
	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.specularColor", Vector3(material.specularColor.r, material.specularColor.g, material.specularColor.b));
	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.reflectiveColor", Vector3(material.reflectiveColor.r, material.reflectiveColor.g, material.reflectiveColor.b));
	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.emissiveColor", Vector3(material.emissiveColor.r, material.emissiveColor.g, material.emissiveColor.b));
	model.materials[model.meshes[i].materialID].shader.SetVector3("materialProperties.transparentColor", Vector3(material.transparentColor.r, material.transparentColor.g, material.transparentColor.b));

	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.reflectivity", material.reflectivity);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.specularFactor", material.specularFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.sheenColorFactor", material.sheenColorFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.sheenRoughnessFactor", material.sheenRoughnessFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.roughnessFactor", material.roughnessFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.metallicFactor", material.metallicFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.glossinessFactor", material.glossinessFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.emissiveIntensity", material.emissiveIntensity);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.anisotrophyFactor", material.anisotrophyFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.clearcoatFactor", material.clearcoatFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.clearcoatRoughnessFactor", material.clearcoatRoughnessFactor);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.opacity", material.opacity);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.shininess", material.shininess);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.shininessStrength", material.shininessStrength);
	model.materials[model.meshes[i].materialID].shader.SetFloat("materialProperties.refracti", material.refracti);
}

static void setTextures(const Model& model, int i)
{
	glActiveTexture(GL_TEXTURE0);
	if (model.materials[model.meshes[i].materialID].diffuseTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].diffuseTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE1);
	if (model.materials[model.meshes[i].materialID].normalTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].normalTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE2);
	if (model.materials[model.meshes[i].materialID].diffuseRoughnessTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].diffuseRoughnessTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE3);
	if (model.materials[model.meshes[i].materialID].clearCoatTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].clearCoatTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE4);
	if (model.materials[model.meshes[i].materialID].ambientOcclusionTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].ambientOcclusionTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE5);
	if (model.materials[model.meshes[i].materialID].opacityTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].opacityTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE6);
	if (model.materials[model.meshes[i].materialID].reflectionTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].reflectionTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE7);
	if (model.materials[model.meshes[i].materialID].sheenTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].sheenTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE8);
	if (model.materials[model.meshes[i].materialID].shininessTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].shininessTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE9);
	if (model.materials[model.meshes[i].materialID].transmissionTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].transmissionTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE10);
	if (model.materials[model.meshes[i].materialID].specularTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].specularTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE11);
	if (model.materials[model.meshes[i].materialID].metalnessTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].metalnessTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE12);
	if (model.materials[model.meshes[i].materialID].displacementTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].displacementTextures[0].GetTextureID());

	glActiveTexture(GL_TEXTURE13);
	if (model.materials[model.meshes[i].materialID].emissionColorTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].emissionColorTextures[0].GetTextureID());
	
	glActiveTexture(GL_TEXTURE14);
	if (model.materials[model.meshes[i].materialID].emissiveTextures.GetLength() > 0)
		glBindTexture(GL_TEXTURE_2D, model.materials[model.meshes[i].materialID].emissiveTextures[0].GetTextureID());
}