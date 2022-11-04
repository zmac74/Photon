#pragma once

#include <utils/collection/Buffer.h>
#include <scene/Scene.h>

namespace Scene
{
	namespace Importer
	{
		extern const int POSTPROCESS_TARGET_REALTIME_FAST;
		extern const int POSTPROCESS_TARGET_REALTIME_QUALITY;
		extern const int POSTPROCESS_TARGET_REALTIME_MAX_QUALITY;
		
		extern const int POSTPROCESS_CALC_TANGENT_SPACE;
		extern const int POSTPROCESS_CONVERT_TO_LEFT_HANDED;
		extern const int POSTPROCESS_DEBONE;
		extern const int POSTPROCESS_DROP_NORMALS;
		extern const int POSTPROCESS_EMBED_TEXTURES;
		extern const int POSTPROCESS_FIND_DEGENERATES;
		extern const int POSTPROCESS_FIND_INSTANCES;
		extern const int POSTPROCESS_FIND_INVALID_DATA;
		extern const int POSTPROCESS_FIX_INFACING_NORMALS;
		extern const int POSTPROCESS_FLIP_UV;
		extern const int POSTPROCESS_FLIP_WINDING_ORDER;
		extern const int POSTPROCESS_FORCE_GEN_NORMALS;
		extern const int POSTPROCESS_GEN_BOUNDS_BOXES;
		extern const int POSTPROCESS_GEN_NORMALS;
		extern const int POSTPROCESS_GEN_SMOOTH_NORMALS;
		extern const int POSTPROCESS_GEN_UV_COORDS;
		extern const int POSTPROCESS_GLOBAL_SCALE;
		extern const int POSTPROCESS_IMPROVE_CACHE_LOCALITY;
		extern const int POSTPROCESS_JOIN_IDENTICAL_VERTICES;
		extern const int POSTPROCESS_LIMIT_BONE_WEIGHTS;
		extern const int POSTPROCESS_MAKE_LEFT_HANDED;
		extern const int POSTPROCESS_OPTIMIZE_GRAPH;
		extern const int POSTPROCESS_OPTIMIZE_MESHES;
		extern const int POSTPROCESS_POPULATE_ARMATURE_DATA;
		extern const int POSTPROCESS_PRE_TRANSFORM_VERTICES;
		extern const int POSTPROCESS_REMOVE_COMPONENT;
		extern const int POSTPROCESS_REMOVE_REDUNDANT_MATERIALS;
		extern const int POSTPROCESS_SORT_BY_P_TYPE;
		extern const int POSTPROCESS_SPLIT_BY_BONE_COUNT;
		extern const int POSTPROCESS_SPLIT_LARGE_MESHES;
		extern const int POSTPROCESS_TRANSFORM_UV_COORDS;
		extern const int POSTPROCESS_TRIANGULATE;
		extern const int POSTPROCESS_VALIDATE_DATA_STRUCTURE;

		Model LoadModel(const char* path);
		Model LoadModel(const char* path, unsigned int flags);

		VertexArray LoadVertexArray(const ArrayList<float>& positions, const ArrayList<float>& textureCoords, const ArrayList<float>& normals, const ArrayList<float>& colors, const ArrayList<float>& tangents, const ArrayList<int>& indices);
		void DeleteVertexArray(VertexArray vertexArray);
		void DeleteVertexArrayRegistry();

		Shader LoadShader(const char* vertexShader, const char* fragmentShader);
		void DeleteShaderRegistry();

		Image LoadImage(unsigned char* pixels, int width, int height, int channels);
		Image LoadImage(const char* path);
		void DeleteImageRegistry();

		Texture LoadTexture(unsigned char* pixels, int width, int height, int channels);
		Texture LoadTexture(Image image);
		Texture LoadTexture(const char* path);
		void DeleteTextureRegistry();
	}
}

using namespace Scene;
using namespace Importer;