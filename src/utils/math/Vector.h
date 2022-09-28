#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Utils
{
	namespace Math 
	{
		class Vector2
		{
		public:
			Vector2()
			{
				vector = glm::vec2(0, 0);
			}

			Vector2(float x, float y)
			{
				vector = glm::vec2(x, y);
			}

			void Translate(float x, float y)
			{
				vector.x += x;
				vector.y += y;
			}

			void Translate(Vector2 vector)
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
			}

			Vector2 operator + (Vector2 vector) const
			{
				return Vector2(this->vector.x + vector.GetGLMVector().x,
					this->vector.y + vector.GetGLMVector().y);
			}

			Vector2 operator - (Vector2 vector) const
			{
				return Vector2(this->vector.x - vector.GetGLMVector().x,
					this->vector.y - vector.GetGLMVector().y);
			}

			void operator += (Vector2 vector)
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
			}

			void operator -= (Vector2 vector)
			{
				this->vector.x -= vector.GetGLMVector().x;
				this->vector.y -= vector.GetGLMVector().y;
			}

			inline void RotateX(float x) { vector = glm::rotate(vector, x); }

			void Scale(float scaler)
			{
				vector.x *= scaler;
				vector.y *= scaler;
			}

			void Scale(float x, float y)
			{
				vector.x *= x;
				vector.y *= y;
			}

			void Scale(Vector2 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
			}

			Vector2 operator * (float scaler) const
			{
				return Vector2(this->vector.x * scaler,
					this->vector.y * scaler);
			}

			Vector2 operator / (float scaler) const
			{
				return Vector2(this->vector.x / scaler,
					this->vector.y / scaler);
			}

			void operator *= (float scaler)
			{
				this->vector.x *= scaler;
				this->vector.y *= scaler;
			}

			void operator /= (float scaler)
			{
				this->vector.x /= scaler;
				this->vector.y /= scaler;
			}

			Vector2 operator * (Vector2 vector) const
			{
				return Vector2(this->vector.x * vector.GetGLMVector().x,
					this->vector.y * vector.GetGLMVector().y);
			}

			Vector2 operator / (Vector2 vector) const
			{
				return Vector2(this->vector.x / vector.GetGLMVector().x,
					this->vector.y / vector.GetGLMVector().y);
			}

			void operator *= (Vector2 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
			}

			void operator /= (Vector2 vector)
			{
				this->vector.x /= vector.GetGLMVector().x;
				this->vector.y /= vector.GetGLMVector().y;
			}

			inline void Reflect(Vector2 vector) { this->vector = glm::reflect(this->vector, vector.GetGLMVector()); }

			inline void ReflectX() { vector.x * -1; }
			inline void ReflectY() { vector.y * -1; }

			inline float operator [] (int index) const { return vector[index]; }

			inline float GetX() const { return vector.x; }
			inline float GetY() const { return vector.y; }

			inline void SetX(float x) { vector.x = x; }
			inline void SetY(float y) { vector.y = y; }

			inline float GetLength() const { return vector.length(); }

			inline glm::vec2 GetGLMVector() const { return vector; }

		private:
			glm::vec2 vector;
		};

		class Vector3
		{
		public:
			Vector3() 
			{
				vector = glm::vec3(0, 0, 0);
			}

			Vector3(float x, float y, float z) 
			{
				vector = glm::vec3(x, y, z);
			}

			void Translate(float x, float y, float z) 
			{
				vector.x += x;
				vector.y += y;
				vector.z += z;
			}

			void Translate(Vector3 vector)
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
				this->vector.z += vector.GetGLMVector().z;
			}

			Vector3 operator + (Vector3 vector) const
			{
				return Vector3(this->vector.x + vector.GetGLMVector().x,
					this->vector.y + vector.GetGLMVector().y,
					this->vector.z + vector.GetGLMVector().z);
			}

			Vector3 operator - (Vector3 vector) const
			{
				return Vector3(this->vector.x - vector.GetGLMVector().x,
					this->vector.y - vector.GetGLMVector().y,
					this->vector.z - vector.GetGLMVector().z);
			}

			void operator += (Vector3 vector) 
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
				this->vector.z += vector.GetGLMVector().z;
			}

			void operator -= (Vector3 vector)
			{
				this->vector.x -= vector.GetGLMVector().x;
				this->vector.y -= vector.GetGLMVector().y;
				this->vector.z -= vector.GetGLMVector().z;
			}

			inline void RotateX(float x) { vector = glm::rotateX(vector, x); }

			inline void RotateY(float y) { vector = glm::rotateY(vector, y); }

			inline void RotateZ(float z) { vector = glm::rotateZ(vector, z); }

			void Scale(float scaler)
			{
				vector.x *= scaler;
				vector.y *= scaler;
				vector.z *= scaler;
			}
			
			void Scale(float x, float y, float z)
			{
				vector.x *= x;
				vector.y *= y;
				vector.z *= z;
			}

			void Scale(Vector3 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
				this->vector.z *= vector.GetGLMVector().z;
			}

			Vector3 operator * (float scaler) const
			{
				return Vector3(this->vector.x * scaler,
					this->vector.y * scaler,
					this->vector.z * scaler);
			}

			Vector3 operator / (float scaler) const
			{
				return Vector3(this->vector.x / scaler,
					this->vector.y / scaler,
					this->vector.z / scaler);
			}

			void operator *= (float scaler)
			{
				this->vector.x *= scaler;
				this->vector.y *= scaler;
				this->vector.z *= scaler;
			}

			void operator /= (float scaler)
			{
				this->vector.x /= scaler;
				this->vector.y /= scaler;
				this->vector.z /= scaler;
			}

			Vector3 operator * (Vector3 vector) const
			{
				return Vector3(this->vector.x * vector.GetGLMVector().x,
					this->vector.y * vector.GetGLMVector().y,
					this->vector.z * vector.GetGLMVector().z);
			}

			Vector3 operator / (Vector3 vector) const
			{
				return Vector3(this->vector.x / vector.GetGLMVector().x,
					this->vector.y / vector.GetGLMVector().y,
					this->vector.z / vector.GetGLMVector().z);
			}

			void operator *= (Vector3 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
				this->vector.z *= vector.GetGLMVector().z;
			}

			void operator /= (Vector3 vector)
			{
				this->vector.x /= vector.GetGLMVector().x;
				this->vector.y /= vector.GetGLMVector().y;
				this->vector.z /= vector.GetGLMVector().z;
			}

			inline void Reflect(Vector3 vector) { this->vector = glm::reflect(this->vector, vector.GetGLMVector()); }

			inline void ReflectX() { vector.x * -1; }
			inline void ReflectY() { vector.y * -1; }
			inline void ReflectZ() { vector.z * -1; }

			inline void Cross(Vector3 vector) { this->vector = glm::cross(this->vector, vector.GetGLMVector()); }//
			inline float Dot(Vector3 vector) { return glm::dot(this->vector, vector.GetGLMVector()); }

			inline float operator [] (int index) const { return vector[index]; }

			inline float GetX() const { return vector.x; }
			inline float GetY() const { return vector.y; }
			inline float GetZ() const { return vector.z; }

			inline void SetX(float x) { vector.x = x; }
			inline void SetY(float y) { vector.y = y; }
			inline void SetZ(float z) { vector.z = z; }

			inline float GetLength() const { return vector.length(); }

			inline glm::vec3 GetGLMVector() const { return vector; }

		private:
			glm::vec3 vector;
		};

		class Vector4
		{
		public:
			Vector4()
			{
				vector = glm::vec4(0, 0, 0, 0);
			}

			Vector4(float x, float y, float z, float w)
			{
				vector = glm::vec4(x, y, z, w);
			}

			void Translate(float x, float y, float z, float w)
			{
				vector.x += x;
				vector.y += y;
				vector.z += z;
				vector.w += w;
			}

			void Translate(Vector4 vector)
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
				this->vector.z += vector.GetGLMVector().z;
				this->vector.w += vector.GetGLMVector().w;
			}

			Vector4 operator + (Vector4 vector) const
			{
				return Vector4(this->vector.x + vector.GetGLMVector().x,
					this->vector.y + vector.GetGLMVector().y,
					this->vector.z + vector.GetGLMVector().z,
					this->vector.w + vector.GetGLMVector().w);
			}

			Vector4 operator - (Vector4 vector) const
			{
				return Vector4(this->vector.x - vector.GetGLMVector().x,
					this->vector.y - vector.GetGLMVector().y,
					this->vector.z - vector.GetGLMVector().z,
					this->vector.w - vector.GetGLMVector().w);
			}

			void operator += (Vector4 vector)
			{
				this->vector.x += vector.GetGLMVector().x;
				this->vector.y += vector.GetGLMVector().y;
				this->vector.z += vector.GetGLMVector().z;
				this->vector.w += vector.GetGLMVector().w;
			}

			void operator -= (Vector4 vector)
			{
				this->vector.x -= vector.GetGLMVector().x;
				this->vector.y -= vector.GetGLMVector().y;
				this->vector.z -= vector.GetGLMVector().z;
				this->vector.w -= vector.GetGLMVector().w;
			}

			void Scale(float scaler)
			{
				vector.x *= scaler;
				vector.y *= scaler;
				vector.z *= scaler;
				vector.w *= scaler;
			}

			void Scale(float x, float y, float z, float w)
			{
				vector.x *= x;
				vector.y *= y;
				vector.z *= z;
				vector.w *= w;
			}

			void Scale(Vector4 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
				this->vector.z *= vector.GetGLMVector().z;
				this->vector.w *= vector.GetGLMVector().w;
			}

			Vector4 operator * (float scaler) const
			{
				return Vector4(this->vector.x * scaler,
					this->vector.y * scaler,
					this->vector.z * scaler,
					this->vector.w * scaler);
			}

			Vector4 operator / (float scaler) const
			{
				return Vector4(this->vector.x / scaler,
					this->vector.y / scaler,
					this->vector.z / scaler,
					this->vector.w / scaler);
			}

			void operator *= (float scaler)
			{
				this->vector.x *= scaler;
				this->vector.y *= scaler;
				this->vector.z *= scaler;
				this->vector.w *= scaler;
			}

			void operator /= (float scaler)
			{
				this->vector.x /= scaler;
				this->vector.y /= scaler;
				this->vector.z /= scaler;
				this->vector.w /= scaler;
			}

			Vector4 operator * (Vector4 vector) const
			{
				return Vector4(this->vector.x * vector.GetGLMVector().x,
					this->vector.y * vector.GetGLMVector().y,
					this->vector.z * vector.GetGLMVector().z,
					this->vector.w * vector.GetGLMVector().w);
			}

			Vector4 operator / (Vector4 vector) const
			{
				return Vector4(this->vector.x / vector.GetGLMVector().x,
					this->vector.y / vector.GetGLMVector().y,
					this->vector.z / vector.GetGLMVector().z,
					this->vector.w / vector.GetGLMVector().w);
			}

			void operator *= (Vector4 vector)
			{
				this->vector.x *= vector.GetGLMVector().x;
				this->vector.y *= vector.GetGLMVector().y;
				this->vector.z *= vector.GetGLMVector().z;
				this->vector.w *= vector.GetGLMVector().w;
			}

			void operator /= (Vector4 vector)
			{
				this->vector.x /= vector.GetGLMVector().x;
				this->vector.y /= vector.GetGLMVector().y;
				this->vector.z /= vector.GetGLMVector().z;
				this->vector.w /= vector.GetGLMVector().w;
			}

			inline void Reflect(Vector4 vector) { this->vector = glm::reflect(this->vector, vector.GetGLMVector()); }

			inline void ReflectX() { vector.x * -1; }
			inline void ReflectY() { vector.y * -1; }
			inline void ReflectZ() { vector.z * -1; }
			inline void ReflectW() { vector.w * -1; }

			inline float operator [] (int index) const { return vector[index]; }

			inline float GetX() const { return vector.x; }
			inline float GetY() const { return vector.y; }
			inline float GetZ() const { return vector.z; }
			inline float GetW() const { return vector.w; }

			inline void SetX(float x) { vector.x = x; }
			inline void SetY(float y) { vector.y = y; }
			inline void SetZ(float z) { vector.z = z; }
			inline void SetW(float w) { vector.w = w; }

			inline float GetLength() const { return vector.length(); }

			inline glm::vec4 GetGLMVector() const { return vector; }

		private:
			glm::vec4 vector;
		};
	}
}

using namespace Utils;
using namespace Math;