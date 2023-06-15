#include <GL/glew.h>
#include <fstream>
#include <string>

#include <utils/math/Vector.h>
#include <utils/math/Matrix.h>
#include <utils/math/Arithmetic.h>

#include <scene/Scene.h>
#include <scene/importer/Importer.h>
#include <utils/collection/Buffer.h>
#include <debug/Debug.h>

static void createShader(const char* shaderFile);

static void readUniforms(const std::string& src);
static void findUniformStruct(const std::string& src, const std::string& varType, const std::string& varName,
	TupleList<std::string, std::string>& varList);
static void findTypeUniformStruct(const std::string& src, const std::string& dataType, const std::string& structName, 
	TupleList<std::string, std::string>& varList);
static int findUniformArrayLength(const std::string& src, const std::string& varName);
static Uniform addUniform(const std::string& varType, const std::string& varName);
static void setUniformLocations();

static void getCompileStatus(int shaderID);
static void createProgram();

static Shader shader;
static ArrayList<Shader> shaders = ArrayList<Shader>();
static ArrayList<String> uniformNames;

Shader Scene::Importer::LoadShader(const char* vertexShader, const char* fragmentShader) 
{
	shader = Shader();
	shader.vertexPath = vertexShader;
	shader.fragmentPath = fragmentShader;

	uniformNames = ArrayList<String>();
	createShader(vertexShader);
	createShader(fragmentShader);
	createProgram();

	shaders.Add(shader);
	return shader;
}

static void createProgram() 
{
	shader.shaderID = glCreateProgram();
	if (shader.vertexStageID != -1) glAttachShader(shader.shaderID, shader.vertexStageID);
	if (shader.geometryStageID != -1) glAttachShader(shader.shaderID, shader.geometryStageID);
	if (shader.fragmentStageID != -1) glAttachShader(shader.shaderID, shader.fragmentStageID);
	glLinkProgram(shader.shaderID);
	glValidateProgram(shader.shaderID);
	setUniformLocations();
}

static void getCompileStatus(int shaderID) 
{
	int status;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (!status) 
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		Debug::Log("ERROR: Shader Compilation Failed:\n\n");
		Debug::Log(infoLog);
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
	readUniforms(cSrc);

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

static void readUniforms(const std::string& src) 
{
	int uniformIndex = 0;
	while (std::string::npos != (uniformIndex = src.find("uniform ", uniformIndex + 1)))
	{
		int varTypeBegin = src.find_first_not_of(" ", uniformIndex + 7);
		int varTypeEnd = src.find(" ", varTypeBegin);
		const std::string varType = src.substr(varTypeBegin, varTypeEnd - varTypeBegin);

		int varNameBegin = src.find_first_not_of(" ", varTypeEnd);
		int varNameEnd = src.find(";", varNameBegin);
		const std::string varName = src.substr(varNameBegin, varNameEnd - varNameBegin);

		int uniformArrayLength = findUniformArrayLength(src, varName);
		if (uniformArrayLength > 1)
		{
			std::string s;
			for (int i = 0; i < uniformArrayLength; i++)
			{
				int bracketBegin = varName.find("[");
				const std::string indexedVarName = varName.substr(0, bracketBegin) + "[" + std::to_string(i) + "]";

				TupleList<std::string, std::string> uniforms;
				findUniformStruct(src, varType, indexedVarName, uniforms);

				if (uniforms.GetLength() == 0) uniforms.Add(varType, indexedVarName);
				for (int j = 0; j < uniforms.GetLength(); j++) 
				{
					Uniform uniform = addUniform(uniforms.Get<0>(j), uniforms.Get<1>(j));
					shader.uniforms.Add(uniforms.Get<1>(j).c_str(), uniform);
					uniformNames.Add(uniforms.Get<1>(j).c_str());
				}
			}
		}
		else 
		{
			TupleList<std::string, std::string> uniforms;
			findUniformStruct(src, varType, varName, uniforms);

			if (uniforms.GetLength() == 0) uniforms.Add(varType, varName);
			for (int i = 0; i < uniforms.GetLength(); i++) 
			{
				Uniform uniform = addUniform(uniforms.Get<0>(i), uniforms.Get<1>(i));
				shader.uniforms.Add(uniforms.Get<1>(i).c_str(), uniform);
				uniformNames.Add(uniforms.Get<1>(i).c_str());
			}
		}
	}
}

static int findUniformArrayLength(const std::string& src, const std::string& varName) 
{
	int elements = 0;
	if (std::string::npos != varName.find("["))
	{
		int bracketBegin = varName.find("[");
		int bracketEnd = varName.find("]");
		const std::string elementCount = varName.substr(bracketBegin + 1, bracketEnd - bracketBegin - 1);

		try
		{
			elements = std::stoi(elementCount);
		}
		catch (const std::invalid_argument& invalidArg)
		{
			int defineIndex = 0;
			while (std::string::npos != (defineIndex = src.find("#define ", defineIndex + 1)))
			{
				int macroNameBegin = src.find_first_not_of(" ", defineIndex + 7);
				int macroNameEnd = src.find(" ", macroNameBegin);
				const std::string macroName = src.substr(macroNameBegin, macroNameEnd - macroNameBegin);

				if (elementCount == macroName)
				{
					int integerliteralBegin = src.find_first_not_of(" ", macroNameEnd);
					int integerliteralEnd = src.find("\n", integerliteralBegin);
					const std::string integerLiteral = src.substr(integerliteralBegin, integerliteralEnd - integerliteralBegin);
					try
					{
						elements = std::stoi(integerLiteral);
					}
					catch (const std::invalid_argument& invalidArg) {}
				}
			}
		}
		return elements;
	}
	else return 1;
}

static void findTypeUniformStruct(const std::string& src, const std::string& dataType, const std::string& structName,
	TupleList<std::string, std::string>& varList)
{
	int primitiveTypeIndex = 0;
	while (std::string::npos != (primitiveTypeIndex = src.find(dataType, primitiveTypeIndex + 1)))
	{
		int varNameBegin = src.find_first_not_of(" ", primitiveTypeIndex + dataType.length() - 1);
		int varNameEnd = src.find(";", varNameBegin);
		const std::string varName = src.substr(varNameBegin, varNameEnd - varNameBegin);

		varList.Add(dataType.substr(0, dataType.length() - 1), structName + "." + varName);
	}
}

static void findUniformStruct(const std::string& src, const std::string& varType, const std::string& varName,
	TupleList<std::string, std::string>& varList)
{
	if (varType != "float" && varType != "int" && varType != "sampler2D"
		&& varType != "vec2" && varType != "vec3" && varType != "vec4" && varType != "mat4") 
	{
		int structIndex = 0;
		while (std::string::npos != (structIndex = src.find("struct ", structIndex + 1))) 
		{
			int structNameBegin = src.find_first_not_of(" ", structIndex + 6);
			
			int structSpace = src.find(" ", structNameBegin);
			int structEndLine = src.find("\n", structNameBegin);
			int structOpenBracket = src.find("{", structNameBegin);

			int structNameEnd = (int)Min(Min((float)structSpace, (float)structEndLine), (float)structOpenBracket);

			if (varType == src.substr(structNameBegin, structNameEnd - structNameBegin)) 
			{
				int structCloseBracket = src.find("}", structNameEnd);

				const std::string structCode = src.substr(structOpenBracket, structCloseBracket - structOpenBracket);
				findTypeUniformStruct(structCode, "float ", varName, varList);
				findTypeUniformStruct(structCode, "int ", varName, varList);
				findTypeUniformStruct(structCode, "vec2 ", varName, varList);
				findTypeUniformStruct(structCode, "vec3 ", varName, varList);
				findTypeUniformStruct(structCode, "vec4 ", varName, varList);
				findTypeUniformStruct(structCode, "mat4 ", varName, varList);
				findTypeUniformStruct(structCode, "sampler2D ", varName, varList);
			}
		}
	}
}

static Uniform addUniform(const std::string& varType, const std::string& varName) 
{
	Uniform uniform;
	uniform.name = varName.c_str();
	
	if (varType == "float")
	{
		uniform.type = FLOAT;
		uniform.uniformIndex = shader.uniformBuffer.floatList.GetLength();
		shader.uniformBuffer.floatList.Add(0, 0);
	}
	else if (varType == "int" || varType == "sampler2D")
	{
		uniform.type = INT;
		uniform.uniformIndex = shader.uniformBuffer.intList.GetLength();
		shader.uniformBuffer.intList.Add(0, 0);
	}
	else if (varType == "vec2")
	{
		uniform.type = VECTOR2;
		uniform.uniformIndex = shader.uniformBuffer.vector2List.GetLength();
		shader.uniformBuffer.vector2List.Add(Vector2(), 0);
	}
	else if (varType == "vec3")
	{
		uniform.type = VECTOR3;
		uniform.uniformIndex = shader.uniformBuffer.vector3List.GetLength();
		shader.uniformBuffer.vector3List.Add(Vector3(), 0);
	}
	else if (varType == "vec4")
	{
		uniform.type = VECTOR4;
		uniform.uniformIndex = shader.uniformBuffer.vector4List.GetLength();
		shader.uniformBuffer.vector4List.Add(Vector4(), 0);
	}
	else if (varType == "mat4")
	{
		uniform.type = MATRIX4X4;
		uniform.uniformIndex = shader.uniformBuffer.matrix4x4List.GetLength();
		shader.uniformBuffer.matrix4x4List.Add(Matrix4x4(), 0);
	}

	return uniform;
}

static void setUniformLocations() 
{
	for (int i = 0; i < shader.uniforms.GetLength(); i++)
	{
		const Uniform& uniform = shader.uniforms[i].Get<1>();
		if (uniform.type == FLOAT)
			shader.uniformBuffer.floatList.Set(uniform.uniformIndex, 0, glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
		else if (uniform.type == INT)
			shader.uniformBuffer.intList.Set(uniform.uniformIndex, 0, glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
		else if (uniform.type == VECTOR2)
			shader.uniformBuffer.vector2List.Set(uniform.uniformIndex, Vector2(), glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
		else if (uniform.type == VECTOR3)
			shader.uniformBuffer.vector3List.Set(uniform.uniformIndex, Vector3(), glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
		else if (uniform.type == VECTOR4)
			shader.uniformBuffer.vector4List.Set(uniform.uniformIndex, Vector4(), glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
		else if (uniform.type == MATRIX4X4)
			shader.uniformBuffer.matrix4x4List.Set(uniform.uniformIndex, Matrix4x4(), glGetUniformLocation(shader.shaderID, uniform.name.GetBuffer()));
	}
}

void Scene::Importer::DeleteShaderRegistry() 
{
	for (int i = 0; i < shaders.GetLength(); i++) 
	{
		glDeleteProgram(shaders[i].shaderID);
		if (shaders[i].vertexStageID != -1) glDeleteShader(shaders[i].vertexStageID);
		if (shaders[i].geometryStageID != -1) glDeleteShader(shaders[i].geometryStageID);
		if (shaders[i].fragmentStageID != -1) glDeleteShader(shaders[i].fragmentStageID);
	}
}