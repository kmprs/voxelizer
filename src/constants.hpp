#pragma once
#include <iostream>

// WINDOW
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 780;
const std::string TITLE = "TestVoxelizer";

// CAMERA
constexpr float CAMERA_SPEED = 0.002f;
constexpr float SENSITIVITY = 0.2f;
constexpr float CLIP_MIN = 0.1;
constexpr float CLIP_MAX = 100;

// WORLD
constexpr glm::vec3 WORLD_CENTER = {.0f, .0f, .0f};