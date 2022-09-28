#include <gl/glew.h>

#include <scene/Scene.h>

void Shader::Start()
{
	glUseProgram(this->shaderID);
}

void Shader::Stop()
{
	glUseProgram(0);
}

void Shader::SetFloat(const char* varName, float value) 
{
	int location = glGetUniformLocation(this->shaderID, varName);
	glUniform1f(location, value);
}

void Shader::SetVector2(const char* varName, Vector2 value)
{
	int location = glGetUniformLocation(this->shaderID, varName);
	glUniform2f(location, value.GetX(), value.GetY());
}

void Shader::SetVector3(const char* varName, Vector3 value)
{
	int location = glGetUniformLocation(this->shaderID, varName);
	glUniform3f(location, value.GetX(), value.GetY(), value.GetZ());
}

void Shader::SetVector4(const char* varName, Vector4 value)
{
	int location = glGetUniformLocation(this->shaderID, varName);
	glUniform4f(location, value.GetX(), value.GetY(), value.GetZ(), value.GetW());
}

void Shader::SetMatrix4x4(const char* varName, Matrix4x4 value)
{
	int location = glGetUniformLocation(this->shaderID, varName);
	glUniformMatrix4fv(location, 1, false, value.GetPtr());
}