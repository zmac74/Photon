#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utils/math/Vector.h>

namespace Utils
{
	namespace Math
	{
		class Matrix4x4 
		{
		public:
			Matrix4x4() 
			{
				matrix = glm::identity<glm::mat4>();
			}

			Matrix4x4(float* ptr)
			{
				matrix = glm::make_mat4(ptr);
			}

			inline void Translate(Vector3 vector) { matrix = glm::translate(matrix, vector.GetGLMVector()); }

			inline void Translate(float x, float y, float z) { matrix = glm::translate(matrix, glm::vec3(x, y, z)); }

			inline void Rotate(Vector3 axis, float angle) { matrix = glm::rotate(matrix, angle, axis.GetGLMVector()); }

			inline void Rotate(float x, float y, float z, float angle) { matrix = glm::rotate(matrix, angle, glm::vec3(x, y, z)); }
			
			inline void Scale(Vector3 vector) { matrix = glm::scale(matrix, vector.GetGLMVector()); }

			inline void Scale(float x, float y, float z) { matrix = glm::scale(matrix, glm::vec3(x, y, z)); }

			inline Matrix4x4 Multiply(Matrix4x4 matrix) const { return Matrix4x4((float*)glm::value_ptr(this->matrix * matrix.GetGLMMatrix())); }

			inline Matrix4x4 operator * (Matrix4x4 matrix) const { return Matrix4x4((float*)glm::value_ptr(this->matrix * matrix.GetGLMMatrix())); }

			inline void Set00(float val) { matrix[0][0] = val; }
			inline void Set01(float val) { matrix[0][1] = val; }
			inline void Set02(float val) { matrix[0][2] = val; }
			inline void Set03(float val) { matrix[0][3] = val; }

			inline void Set10(float val) { matrix[1][0] = val; }
			inline void Set11(float val) { matrix[1][1] = val; }
			inline void Set12(float val) { matrix[1][2] = val; }
			inline void Set13(float val) { matrix[1][3] = val; }

			inline void Set20(float val) { matrix[2][0] = val; }
			inline void Set21(float val) { matrix[2][1] = val; }
			inline void Set22(float val) { matrix[2][2] = val; }
			inline void Set23(float val) { matrix[2][3] = val; }
			
			inline void Set30(float val) { matrix[3][0] = val; }
			inline void Set31(float val) { matrix[3][1] = val; }
			inline void Set32(float val) { matrix[3][2] = val; }
			inline void Set33(float val) { matrix[3][3] = val; }

			Vector4 operator [] (int index) const 
			{ 
				glm::vec4 vector = matrix[index];
				return Vector4(vector.x, vector.y, vector.z, vector.w);
			}
			
			inline float* GetPtr() const { return (float*)glm::value_ptr(matrix); }

			inline glm::mat4 GetGLMMatrix() const { return matrix; }

		private:
			glm::mat4 matrix;
		};

		inline Matrix4x4 LookAt(Vector3 position, Vector3 look, Vector3 up) 
		{
			return Matrix4x4((float*)glm::value_ptr(glm::lookAt(position.GetGLMVector(), look.GetGLMVector(), up.GetGLMVector())));
		}

		inline Matrix4x4 LookAt(float posX, float posY, float posZ, float lookX, float lookY, float lookZ, float upX, float upY, float upZ) 
		{
			return Matrix4x4((float*)glm::value_ptr(glm::lookAt(glm::vec3(posX, posY, posZ), glm::vec3(lookX, lookY, lookZ), glm::vec3(upX, upY, upZ))));
		}

		inline Matrix4x4 Perspective(float fovY, float aspectRatio, float nearPlane, float farPlane) 
		{
			return Matrix4x4((float*)glm::value_ptr(glm::perspective(fovY, aspectRatio, nearPlane, farPlane)));
		}

		inline Matrix4x4 Orthographic(float bottom, float top, float left, float right, float near, float far) 
		{
			return Matrix4x4((float*)glm::value_ptr(glm::ortho(bottom, top, left, right, near, far)));
		}
	}
}

using namespace Utils;
using namespace Math;