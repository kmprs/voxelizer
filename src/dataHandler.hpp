#pragma once


#include <glm/vec3.hpp>


class DataHandler
{
public:
    DataHandler();

    // getters and setters
    [[nodiscard]] glm::vec3 getVoxelColor() const;
    void setVoxelColor(const glm::vec3 &color);
    [[nodiscard]] int getWindowWidth() const;
    void setWindowWidth(int width);
    [[nodiscard]] int getWindowHeight() const;
    void setWindowHeight(int height);

private:
    glm::vec3 m_voxelColor = {};
    int m_windowWidth = -1;
    int m_windowHeight = -1;
};