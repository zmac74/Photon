#include <FastNoiseLite.h>

#include <utils/math/Procedual.h>

static FastNoiseLite noise;

void initProcedualDataSet() 
{ 
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin); 
}

float Utils::Math::Noise2D(float x, float y) { return noise.GetNoise(x, y); }