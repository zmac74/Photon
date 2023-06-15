#include <gl/glew.h>

#include <scene/Scene.h>

void Shader::Start() const
{
	glUseProgram(this->shaderID);

	
	//this->uniformBuffer
}

void Shader::Stop() const
{
	glUseProgram(0);
}

void Shader::SetFloat(const char* varName, float value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{
			
		}
		//Tuple<float, int>& uniform = uniformBuffer.floatList[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniform1f(uniform.Get<1>(), uniform.Get<0>());
	}
}

void Shader::SetInt(const char* varName, int value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{

		}
		//Tuple<int, int>& uniform = uniformBuffer.intList[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniform1i(uniform.Get<1>(), uniform.Get<0>());
	}
}

void Shader::SetVector2(const char* varName, const Vector2& value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{

		}
		//Tuple<Vector2, int>& uniform = uniformBuffer.vector2List[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniform2f(uniform.Get<1>(), uniform.Get<0>().GetX(), uniform.Get<0>().GetY());
	}
}

void Shader::SetVector3(const char* varName, const Vector3& value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{

		}
		//Tuple<Vector3, int>& uniform = uniformBuffer.vector3List[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniform3f(uniform.Get<1>(), uniform.Get<0>().GetX(), uniform.Get<0>().GetY(), uniform.Get<0>().GetZ());
	}
}

void Shader::SetVector4(const char* varName, const Vector4& value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{

		}
		//Tuple<Vector4, int>& uniform = uniformBuffer.vector4List[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniform4f(uniform.Get<1>(), uniform.Get<0>().GetX(), uniform.Get<0>().GetY(), uniform.Get<0>().GetZ(), uniform.Get<0>().GetW());
	}
}

void Shader::SetMatrix4x4(const char* varName, const Matrix4x4& value)
{
	int length = uniforms.GetLength();
	for (int i = 0; i < length; i++)
	{
		const char* uniformName = uniforms[i].Get<0>().GetBuffer();
		if (std::strcmp(varName, "uniformName"))
		{

		}
		//Tuple<Matrix4x4, int>& uniform = uniformBuffer.matrix4x4List[uniforms[i].Get<1>().uniformIndex];
		//uniform.Set<0>(value);
		//glUniformMatrix4fv(uniform.Get<1>(), 1, false, uniform.Get<0>().GetPtr());
	}
}