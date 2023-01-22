#version 460 core

in vec4 color;
in vec3 normal;
in vec3 worldPos;
in vec2 textureCoord;

out vec4 fragColor;

struct Camera
{	
	vec3 position;
	vec3 lookDirection;
	vec3 orientation;

	float nearPlane;
	float farPlane;

	float aspectRatio;
	float fovX;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct PointLight 
{    
    vec3 position;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
};  

struct AreaLight
{
	vec3 position;
	vec3 direction;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	float areaWidth;
	float areaHeight;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;

	float innerConeAngle;
	float outerConeAngle;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct AmbientLight
{
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
};

struct MaterialProperties
{
    vec3 baseColor;
    vec3 diffuseColor;
    vec3 specularColor;
	vec3 reflectiveColor;
	vec3 emissiveColor;
	vec3 transparentColor;

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

struct MaterialTextures
{
	sampler2D baseColorMap;
    sampler2D normalMap;
    sampler2D diffuseRoughnessMap;
    sampler2D clearCoatMap;
    sampler2D ambientOcclusionMap;
    sampler2D opacityTextures;
    sampler2D reflectionMap;
    sampler2D sheenMap;
    sampler2D shininessMap;
    sampler2D transmissionMap;
    sampler2D specularMap;
    sampler2D metalnessMap;
    sampler2D displacementMap;
    sampler2D emissionColorMap;
    sampler2D emissiveMap;
};

#define LIGHT_CAPACITY 10

uniform Camera cameraData;

uniform DirectionalLight directionalLights[LIGHT_CAPACITY];
uniform PointLight pointLights[LIGHT_CAPACITY];
uniform AreaLight areaLights[LIGHT_CAPACITY];
uniform SpotLight spotLights[LIGHT_CAPACITY];
uniform AmbientLight ambientLights[LIGHT_CAPACITY];

uniform int directionalLightCount;
uniform int pointLightCount;
uniform int areaLightCount;
uniform int spotLightCount;
uniform int ambientLightCount;

uniform MaterialProperties materialProperties;
uniform MaterialTextures materialTextures;

vec3 processPhongLighting();

vec3 processDirectionalLight(int index);
vec3 processPointLight(int index);
vec3 processSpotLight(int index);

void main()
{
	vec4 objectColor = texture(materialTextures.baseColorMap, textureCoord);
	float alpha = objectColor.w;

	vec3 phongLighting = processPhongLighting();

	fragColor = vec4(phongLighting * objectColor.xyz, alpha);
}

vec3 processPhongLighting()
{
	vec3 lighting = vec3(0, 0, 0);

	for (int i = 0; i < directionalLightCount; i++) lighting += processDirectionalLight(i);
	for (int i = 0; i < pointLightCount; i++) lighting += processPointLight(i);
	for (int i = 0; i < spotLightCount; i++) lighting += processSpotLight(i);

	return lighting + vec3(0.1, 0.1, 0.1);
}

vec3 processDirectionalLight(int index)
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * directionalLights[index].diffuseColor;

	vec3 diffuse = max(dot(normalize(normal), -directionalLights[index].direction), 0.0) * directionalLights[index].diffuseColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraData.position - worldPos);
	vec3 reflectDir = reflect(directionalLights[index].direction, normalize(normal));
	vec3 specular = specularStrength * (pow(max(dot(viewDir, reflectDir), 0.0), 32)) * directionalLights[index].diffuseColor;

	return (diffuse + specular);
}

vec3 processPointLight(int index)
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * pointLights[index].diffuseColor;
	
	vec3 lightDir = normalize(pointLights[index].position - worldPos);
	vec3 diffuse = max(dot(normalize(normal), lightDir), 0.0) * pointLights[index].diffuseColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraData.position - worldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	vec3 specular = specularStrength * (pow(max(dot(viewDir, reflectDir), 0.0), 32)) * pointLights[index].diffuseColor;

	float dist = length(pointLights[index].position - worldPos);
	float attenuation = 1.0 / (pointLights[index].constantAttenuation + pointLights[index].linearAttenuation * dist + pointLights[index].quadraticAttenuation * (dist * dist));
	diffuse *= attenuation;
	specular *= attenuation;

	return (diffuse + specular);
}

vec3 processSpotLight(int index)
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * spotLights[index].diffuseColor;

	vec3 lightDir = normalize(spotLights[index].position - worldPos);
	vec3 diffuse = max(dot(normalize(normal), lightDir), 0.0) * spotLights[index].diffuseColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraData.position - worldPos);
	vec3 reflectDir = reflect(-lightDir, normalize(normal));
	vec3 specular = specularStrength * (pow(max(dot(viewDir, reflectDir), 0.0), 32)) * spotLights[index].diffuseColor;

	float theta = dot(lightDir, normalize(-spotLights[index].direction));
	float epsilon = spotLights[index].innerConeAngle - spotLights[index].outerConeAngle;
	float intensity = smoothstep(0.0, 1.0, (theta - spotLights[index].outerConeAngle) / epsilon);
	diffuse *= intensity;
	specular *= intensity;

	float dist = length(spotLights[index].position - worldPos);
	float attenuation = 1.0 / (spotLights[index].constantAttenuation + spotLights[index].linearAttenuation * dist + spotLights[index].quadraticAttenuation * (dist * dist));
	diffuse *= attenuation;
	specular *= attenuation;

	return (diffuse + specular);
}