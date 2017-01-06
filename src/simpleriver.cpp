#include "simpleriver.h"

SimpleRiver::SimpleRiver() : count(0)
{}

void SimpleRiver::generateRiver(glm::vec2 start, int width, float slope)
{
    count++;
    if (width <= 16 || count > 20)
    {
        return;
    }

    glm::vec2 end = getEndpt(start, 64, slope, 1);

    glm::vec2 delta = end - start;
    float dx = std::abs(delta.x);
    float dy = std::abs(delta.y);
    float px = 2 * dy - dx;
    float py = 2 * dx - dy;
    float x, y, xe, ye = 0;

    // Bresenhaam Algorithm
    if(dy <= dx)
    {
        if (delta.x >= 0)
        {
            x = start.x;
            y = start.y;
            xe = end.x;
        }
        else
        {
            x = end.x;
            y = end.y;
            xe = start.x;
        }

        coordinates.push_back(glm::vec2(x, y));

        for (int i = 0; x < xe; i++)
        {
            x++;
            if (px < 0)
            {
                px = px + 2 * dy;
            }
            else
            {
                if ((delta.x < 0 && delta.y < 0) || (delta.x > 0 && delta.y > 0))
                {
                    y++;
                }
                else
                {
                    y--;
                }
                px = px + 2 * (dy - dx);
            }

            coordinates.push_back(glm::vec2(x, y));
        }
    }
    else
    {
        if (delta.y >= 0)
        {
            x = start.x;
            y = start.y;
            ye = end.y;
        }
        else
        {
            x = end.x;
            y = end.y;
            ye = start.y;
        }

        coordinates.push_back(glm::vec2(x, y));

        for (int i = 0; y < ye; i++)
        {
            y++;
            if (py <= 0)
            {
                py = py + 2 * dx;
            }
            else
            {
                if ((delta.x < 0 && delta.y < 0) || (delta.x > 0 && delta.y > 0))
                {
                    x++;
                }
                else
                {
                    x--;
                }
                py = py + 2 * (dx - dy);
            }
        }
    }

    int random = rand() % (100 + 1) + 1;

    if (random <= 40)
    {
        branch(end, width / 4);
    }

    generateRiver(end, width, slope);
}

void SimpleRiver::branch(glm::vec2 start, int width)
{
    float slope = (rand() / RAND_MAX) - 0.5f;
    generateRiver(start, width, slope);
}

glm::vec2 SimpleRiver::getEndpt(glm::vec2 start, int distance, float slope, int dir)
{
    float k = dir * distance / sqrt(1 + slope * slope);
    return start + k * glm::vec2(1, slope);
}
