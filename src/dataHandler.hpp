#pragma once


#include <glm/vec3.hpp>
#include <set>
#include "constants.hpp"
#include "types.hpp"


class DataHandler
{
public:
    DataHandler();

    // getters and setters
    [[nodiscard]] glm::vec3 getVoxelColor() const;
    void setVoxelColor( const glm::vec3 &color );
    [[nodiscard]] glm::vec3 getWorldCenter() const;
    void setWorldCenter( const glm::vec3 &center );
    [[nodiscard]] int getWindowWidth() const;
    void setWindowWidth( int width );
    [[nodiscard]] int getWindowHeight() const;
    void setWindowHeight( int height );
    [[nodiscard]] int getBenchmarkWindowWidth() const;
    void setBenchmarkWindowWidth( int width );
    [[nodiscard]] int getBenchmarkWindowHeight() const;
    void setBenchmarkWindowHeight( int height );
    [[nodiscard]] int getCurrentFPS() const;
    void setCurrentFPS( int fps );
    [[nodiscard]] int getNumberOfVoxels() const;
    void setNumberOfVoxels( int numberOfVoxels );
    [[nodiscard]] int getVoxelResolution() const;
    void setVoxelResolution( int resolution );
    [[nodiscard]] int getNumberOfBenchmarkSamples() const;
    void setNumberOfBenchmarkSamples( int samples );
    [[nodiscard]] float getCameraSpeed() const;
    void setCameraSpeed( float speed );
    [[nodiscard]] float getRotationSpeed() const;
    void setRotationSpeed( float speed );
    [[nodiscard]] Representation getModelRepresentation() const;
    void toggleModelRepresentation();
    [[nodiscard]] CameraMode getCameraMode() const;
    void toggleCameraMode();
    [[nodiscard]] VoxelizationAlgorithm getVoxelizationAlgorithm() const;
    void setAlgorithm( VoxelizationAlgorithm algorithm );
    [[nodiscard]] bool isCameraModeToggled() const;
    void resetCameraModeToggled();
    [[nodiscard]] bool isWindowFreezed() const;
    void toggleWindowFreeze();
    void setWindowFreeze( bool isFreezed );
    [[nodiscard]] bool isBenchmarkShown() const;
    void showBenchmarks( bool isShown );
    [[nodiscard]] std::string getCurrentModelPath() const;
    void setModelPath( const std::string &path );
    [[nodiscard]] std::set<VoxelizationAlgorithm> getBenchmarkAlgorithms();
    void addToBenchmark( VoxelizationAlgorithm algorithm );
    void eraseFromBenchmark( VoxelizationAlgorithm algorithm );
    [[nodiscard]] bool benchmarkChanged() const;
    void setBenchmarkChanged( bool changed );
    void setBenchmarkUpdate( bool updated );
    [[nodiscard]] vecBenchmarkMetricSharedPtr getBenchmarkMetrics() const;
    void setBenchmarkMetrics( const vecBenchmarkMetricSharedPtr &metrics );
    [[nodiscard]] std::set<std::string> getBenchmarkModelPaths();
    void addToBenchmarkModelPaths( const std::string &path );
    void eraseFromBenchmarkModelPath( const std::string &path );

private:
    glm::vec3 m_voxelColor = {};
    glm::vec3 m_worldCenter = {};
    int m_windowWidth = -1;
    int m_windowHeight = -1;
    int m_benchmarkWindowWidth = -1;
    int m_benchmarkWindowHeight = -1;
    int m_currentFPS = -1;
    int m_numberOfVoxels = -1;
    int m_voxelResolution = -1;
    int m_numberOfBenchmarkSamples = -1;
    float m_cameraSpeed = -1.f;
    float m_rotationSpeed = -1.f;
    Representation m_modelRepresentation = VOXEL;
    CameraMode m_cameraMode = CENTERED;
    VoxelizationAlgorithm m_voxelizationAlgorithm = OPTIMIZED;
    bool m_cameraModeToggled = false;
    bool m_isWindowFreezed = false;
    bool m_showBenchmarks = false;
    std::string m_currentModelPath;
    std::set<VoxelizationAlgorithm> m_benchmarkAlgorithms = {};
    bool m_benchmarkChanged = true;
    bool m_benchmarkUpdate = false;
    vecBenchmarkMetricSharedPtr m_benchmarkMetrics = {};
    std::set<std::string> m_benchmarkModelPaths = {};
};