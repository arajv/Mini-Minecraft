#ifndef SIMPLERIVER_H
#define SIMPLERIVER_H

#include <la.h>
#include <iostream>

class SimpleRiver
{
public:
    SimpleRiver();
    int count;
    std::vector<glm::vec2> coordinates;
    void branch(glm::vec2 start, int width);
    void generateRiver(glm::vec2 start, int width, float slope);
    glm::vec2 getEndpt(glm::vec2 start, int distance, float slope, int dir);
};

#endif // SIMPLERIVER_H
