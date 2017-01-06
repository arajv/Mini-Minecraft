#pragma once
#include <QList>
#include <camera.h>
#include <tuple>
#include <unordered_map>
#include <map>
#include <hashtuple.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <scene/chunk.h>
#include <unordered_set>
#include <glwidget277.h>

using namespace std;
using namespace glm;
//const float PI = 3.141592;

class Scene
{
public:
    const float PI = 3.141592;
    enum box {empty = -1, green = 1, grass = 2, dirt = 3, wood = 4, leaf = 5, stone = 6, bedrock = 7, coal = 8, iron_ore = 9, lava = 10, water = 11, snow = 12, sand = 13};
    Scene();
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> > chunks;
    unordered_map< tuple<int,int,int>, int>  allchunks;
    unordered_map<tuple<int,int,int>,int> newchunks;
    unordered_map<tuple<int,int,int>,int> color;
    unordered_map<tuple<int,int>,int> height;
    //QList<QList<QList<bool>>> objects;//A 3D list of the geometry in the world. Currently, it just lists whether or not a given cell contains a block.
    void CreateTestScene();
    glm::ivec3 dimensions;
    unordered_map<tuple<int,int>,float> noise2D;
    void modify_scene(tuple<int,int,int>);
    void create_biome(tuple<int,int,int>);
    unordered_map< tuple<int,int,int>, unordered_map< tuple<int,int,int>, int> >& getChunks();
    void make_caves(tuple<int,int,int>);
    //void createNewChunks();
};

float Noise(int x, int z);
float smoothedNoise(int x, int z);
float PerlinNoise_2D(int x, int z);
float Interpolate(int x, int z, int f);
float PerlinNoise_biomes(int x, int z);

float Noise3D(int x,int y, int z);
float smoothedNoise3D(int x,int y, int z);
float PerlinNoise_3D(int x, int y, int z);
float Interpolate3D(int x, int y, int z, int f);

float Noise1D(int x);
float smoothedNoise1D(int x);
float PerlinNoise_1D(int x);
float Interpolate1D(int x, int f);
float PerlinNoise_biomes2(int x);
float PerlinNoise_1Dnew(int x);
int max(int a, int b);
