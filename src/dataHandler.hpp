#pragma once


#include <glm/vec3.hpp>
#include "constants.hpp"


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
    [[nodiscard]] float getCameraSpeed() const;
    void setCameraSpeed(float speed);

private:
    glm::vec3 m_voxelColor = {};
    int m_windowWidth = -1;
    int m_windowHeight = -1;
    float m_cameraSpeed = -1.f;
};