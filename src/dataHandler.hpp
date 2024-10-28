#pragma once


#include <glm/vec3.hpp>
#include "constants.hpp"
#include "types.hpp"


class DataHandler
{
public:
    DataHandler();

    // getters and setters
    [[nodiscard]] glm::vec3 getVoxelColor() const;
    void setVoxelColor(const glm::vec3 &color);
    [[nodiscard]] glm::vec3 getWorldCenter() const;
    void setWorldCenter(const glm::vec3 &center);
    [[nodiscard]] int getWindowWidth() const;
    void setWindowWidth(int width);
    [[nodiscard]] int getWindowHeight() const;
    void setWindowHeight(int height);
    [[nodiscard]] int getCurrentFPS() const;
    void setCurrentFPS(int fps);
    [[nodiscard]] int getNumberOfVoxels() const;
    void setNumberOfVoxels(int numberOfVoxels);
    [[nodiscard]] float getCameraSpeed() const;
    void setCameraSpeed(float speed);
    [[nodiscard]] float getRotationSpeed() const;
    void setRotationSpeed(float speed);
    [[nodiscard]] Representation getModelRepresentation() const;
    void setModelRepresentation( Representation representation );
    void toggleModelRepresentation();

private:
    glm::vec3 m_voxelColor = {};
    glm::vec3 m_worldCenter = {};
    int m_windowWidth = -1;
    int m_windowHeight = -1;
    int m_currentFPS = -1;
    int m_numberOfVoxels = -1;
    float m_cameraSpeed = -1.f;
    float m_rotationSpeed = -1.f;
    Representation m_modelRepresentation = VOXEL;
};