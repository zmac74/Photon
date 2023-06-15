#include <scene/scene.h>

Camera Scene::activeCamera = Camera();

ArrayList<PostProcessVolume> Scene::postProcessVolumes = ArrayList<PostProcessVolume>();
ArrayList<DirectionalLight> Scene::directionalLights = ArrayList<DirectionalLight>();
ArrayList<PointLight> Scene::pointLights = ArrayList<PointLight>();
ArrayList<AreaLight> Scene::areaLights = ArrayList<AreaLight>();
ArrayList<SpotLight> Scene::spotLights = ArrayList<SpotLight>();
ArrayList<AmbientLight> Scene::ambientLights = ArrayList<AmbientLight>();
LinkedList<Model> Scene::models = LinkedList<Model>();

PostProcessVolume* Scene::CreatePostProcessVolume(AABB aabb, bool boundless, int priority, PostProcessStack postProcessStack) 
{
	postProcessVolumes.Add(PostProcessVolume(aabb, boundless, postProcessVolumes.GetLength(), postProcessStack));
	return &postProcessVolumes.GetLastElement();
}

DirectionalLight* Scene::CreateDirectionalLight(DirectionalLight light)
{
	directionalLights.Add(light);
	return &directionalLights.GetLastElement();
}

PointLight* Scene::CreatePointLight(PointLight light) 
{
	pointLights.Add(light);
	return &pointLights.GetLastElement();
}

AreaLight* Scene::CreateAreaLight(AreaLight light) 
{
	areaLights.Add(light);
	return &areaLights.GetLastElement();
}

SpotLight* Scene::CreateSpotLight(SpotLight light) 
{
	spotLights.Add(light);
	return &spotLights.GetLastElement();
}

AmbientLight* Scene::CreateAmbientLight(AmbientLight light) 
{
	ambientLights.Add(light);
	return &ambientLights.GetLastElement();
}