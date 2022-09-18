#include <GL/glew.h>
#include <fstream>
#include <string>

#include <scene/Scene.h>
#include <scene/importer/Importer.h>
#include <vector>
#include <debug/Debug.h>

static void createShader(const char* shaderFile);
static void getCompileStatus(int shaderID);
static void createProgram();

static Shader shader;
static std::vector<Shader> shaders = std::vector<Shader>();

Shader Scene::Importer::loadShader(const char* vertexShader, const char* fragmentShader) 
{
	shader = Shader();

	createShader(vertexShader);
	createShader(fragmentShader);
	createProgram();

	shaders.emplace_back(shader);
	return shader;
}

static void createProgram() 
{
	shader.shaderID = glCreateProgram();
	if (shader.vertexStageID != -1)glAttachShader(shader.shaderID, shader.vertexStageID);
	if (shader.geometryStageID != -1) glAttachShader(shader.shaderID, shader.geometryStageID);
	if (shader.fragmentStageID != -1)glAttachShader(shader.shaderID, shader.fragmentStageID);
	glLinkProgram(shader.shaderID);
	glValidateProgram(shader.shaderID);
}

static void getCompileStatus(int shaderID) 
{
	int status;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (!status) 
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		Debug::log("ERROR: Shader Compilation Failed:\n\n");
		Debug::log(infoLog);
	}
}

static void createShader(const char* shaderFile) 
{
	std::ifstream fileStream;
	fileStream.open(shaderFile);

	std::string src;
	std::string line;
	while (std::getline(fileStream, line))
	{
		src.append(line + "\n");
	}

	fileStream.close();
	const char* cSrc = src.c_str();

	std::string path = std::string(shaderFile);
	int identifier = path.find("Vertex.glsl");
	if (identifier != std::string::npos) 
	{
		shader.vertexStageID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader.vertexStageID, 1, &cSrc, nullptr);
		glCompileShader(shader.vertexStageID);
		getCompileStatus(shader.vertexStageID);
	}
	identifier = path.find("Geometry.glsl");
	if (identifier != std::string::npos)
	{
		shader.geometryStageID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shader.geometryStageID, 1, &cSrc, nullptr);
		glCompileShader(shader.geometryStageID);
		getCompileStatus(shader.geometryStageID);
	}
	identifier = path.find("Fragment.glsl");
	if (identifier != std::string::npos)
	{
		shader.fragmentStageID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader.fragmentStageID, 1, &cSrc, nullptr);
		glCompileShader(shader.fragmentStageID);
		getCompileStatus(shader.fragmentStageID);
	}
}

void Scene::Importer::deleteShaderRegistry() 
{
	for (int i = 0; i < shaders.size(); i++) 
	{
		glDeleteProgram(shaders[i].shaderID);
		if (shaders[i].vertexStageID != -1) glDeleteShader(shaders[i].vertexStageID);
		if (shaders[i].geometryStageID != -1) glDeleteShader(shaders[i].geometryStageID);
		if (shaders[i].fragmentStageID != -1) glDeleteShader(shaders[i].fragmentStageID);
	}
}