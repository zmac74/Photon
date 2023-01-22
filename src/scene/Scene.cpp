#include <scene/scene.h>

Camera Scene::activeCamera = Camera();

ArrayList<DirectionalLight> Scene::directionalLights = ArrayList<DirectionalLight>();
ArrayList<PointLight> Scene::pointLights = ArrayList<PointLight>();
ArrayList<AreaLight> Scene::areaLights = ArrayList<AreaLight>();
ArrayList<SpotLight> Scene::spotLights = ArrayList<SpotLight>();
ArrayList<AmbientLight> Scene::ambientLights = ArrayList<AmbientLight>();