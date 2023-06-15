#pragma once

#include <utils/collection/Buffer.h>

#include <utils/generic/String.h>

#include <utils/math/Vector.h>
#include <utils/math/Matrix.h>

namespace Scene 
{
	enum UniformType 
	{
		FLOAT,
		INT,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		MATRIX4X4
	};

	struct UniformBuffer
	{
	public:
		TupleList<float, int> floatList;
		TupleList<int, int> intList;
		TupleList<Vector2, int> vector2List;
		TupleList<Vector3, int> vector3List;
		TupleList<Vector4, int> vector4List;
		TupleList<Matrix4x4, int> matrix4x4List;
	};

	struct Uniform 
	{
	public:
		String name;
		UniformType type;
		int uniformIndex;
	};

	struct Shader
	{
	public:
		unsigned int shaderID;

		const char* vertexPath = "";
		const char* geometryPath = "";
		const char* fragmentPath = "";

		int vertexStageID = -1;
		int geometryStageID = -1;
		int fragmentStageID = -1;

		void Start() const;
		void Stop() const;

		void SetFloat(const char* varName, float value);
		void SetInt(const char* varName, int value);

		void SetVector2(const char* varName, const Vector2& value);
		void SetVector3(const char* varName, const Vector3& value);
		void SetVector4(const char* varName, const Vector4& value);

		void SetMatrix4x4(const char* varName, const Matrix4x4& value);

		UniformBuffer uniformBuffer;
		//Map<String, Uniform> uniforms;
		TupleList<String, Uniform> uniforms;
	};
}

using namespace Scene;