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
    [[nodiscard]] int getVoxelResolution() const;
    void setVoxelResolution( int resolution);
    [[nodiscard]] float getCameraSpeed() const;
    void setCameraSpeed(float speed);
    [[nodiscard]] float getRotationSpeed() const;
    void setRotationSpeed(float speed);
    [[nodiscard]] Representation getModelRepresentation() const;
    void toggleModelRepresentation();
    [[nodiscard]] CameraMode getCameraMode() const;
    void toggleCameraMode();
    [[nodiscard]] bool isCameraModeToggled() const;
    void resetCameraModeToggled();
    [[nodiscard]] bool isWindowFreezed() const;
    void toggleWindowFreeze();

private:
    glm::vec3 m_voxelColor = {};
    glm::vec3 m_worldCenter = {};
    int m_windowWidth = -1;
    int m_windowHeight = -1;
    int m_currentFPS = -1;
    int m_numberOfVoxels = -1;
    int m_voxelResolution = -1;
    float m_cameraSpeed = -1.f;
    float m_rotationSpeed = -1.f;
    Representation m_modelRepresentation = VOXEL;
    CameraMode m_cameraMode = CENTERED;
    bool m_cameraModeToggled = false;
    bool m_isWindowFreezed = false;
};