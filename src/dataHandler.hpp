#pragma once


#include <glm/vec3.hpp>


class DataHandler
{
public:
    DataHandler();

    // getters and setters
    glm::vec3 getVoxelColor();
    void setVoxelColor(const glm::vec3 &color);

private:
    glm::vec3 m_voxelColor = {};
};