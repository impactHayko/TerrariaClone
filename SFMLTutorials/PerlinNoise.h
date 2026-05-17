#pragma once
#include <vector>

class PerlinNoise
{
public:
	PerlinNoise(unsigned int seed = 0);
	double noise2D(double x, double y);

private:
	std::vector<int> p; //place to store

	double fade(double t); //to smooth the angles
	double lerp(double t, double a, double b); //mixing two numbers to one (liear interpolation)
	double grad(int hash, double x, double y, double z); //dot product for every uzel
};