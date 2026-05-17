#include "PerlinNoise.h"
#include <numeric>    // std::iota
#include <algorithm>  // std::shuffle
#include <random>     // std::default_random_engine

PerlinNoise::PerlinNoise(unsigned int seed)
{
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);  //fills 

    std::default_random_engine engine(seed);
    std::shuffle(p.begin(), p.end(), engine);

    p.insert(p.end(), p.begin(), p.end()); //double to avoid boundaries exit
}

double PerlinNoise::fade(double t)
{
    return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
}

double PerlinNoise::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = (h < 8) ? x : y;
    double v = (h < 4) ? y : (h == 12 || h == 14) ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double PerlinNoise::noise2D(double x, double y)
{
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;


    x -= floor(x);
    y -= floor(y);

    double u = fade(x);// local coordinates smooth version
    double v = fade(y);// local coordinates smooth version

    int A = p[X] + Y;
    int AA = p[A] + 0;
    int AB = p[A + 1] + 0;
    int B = p[X + 1] + Y;
    int BA = p[B] + 0;
    int BB = p[B + 1] + 0;

    return lerp(v,
        lerp(u, grad(p[AA], x, y, 0),
            grad(p[BA], x - 1, y, 0)),
        lerp(u, grad(p[AB], x, y - 1, 0),
            grad(p[BB], x - 1, y - 1, 0)));
}