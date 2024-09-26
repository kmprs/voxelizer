#pragma once

#include <iostream>

// WINDOW
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 780;
const std::string TITLE = "TestVoxelizer";

// CAMERA
constexpr float CAMERA_SPEED = 0.003f;
constexpr float CAMERA_ROTATION_SPEED = 0.03f;
constexpr float SENSITIVITY = 0.2f;
constexpr float CLIP_MIN = 0.1;
constexpr float CLIP_MAX = 100;
constexpr glm::vec3 YAW_AXIS = {0, 1, 0};
constexpr glm::vec3 PITCH_AXIS = {1, 0, 0};

// WORLD
constexpr glm::vec3 WORLD_CENTER = {.0f, .0f, .0f};
constexpr float AMBIENT_STRENGTH = .6f;
constexpr glm::vec3 LIGHT_POSITION = {10.f, 10.f, 10.f};
constexpr glm::vec3 LIGHT_COLOR = {1.f, 1.f, 1.f};
constexpr glm::vec3 VOXEL_COLOR = {1.f, .8f, .1f};