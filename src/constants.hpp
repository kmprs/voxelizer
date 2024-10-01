#pragma once

#include <string>

// MODEL
const std::string MODEL_PATH = "../data/indoor plant_02.obj";

// WINDOW
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 780;
const std::string TITLE = "Voxelizer";
constexpr int TARGET_FPS = 300;
constexpr int FRAME_DELAY = 1000/TARGET_FPS;


// CAMERA
constexpr float CAMERA_SPEED = 5.f;
constexpr float CAMERA_ROTATION_SPEED = 120.f;
constexpr float CLIP_MIN = 0.1;
constexpr float CLIP_MAX = 100;
constexpr glm::vec3 YAW_AXIS = {0, 1, 0};
constexpr glm::vec3 PITCH_AXIS = {1, 0, 0};

// WORLD
constexpr glm::vec3 WORLD_CENTER = {.0f, .0f, .0f};
constexpr float AMBIENT_STRENGTH = .6f;
constexpr glm::vec3 LIGHT_POSITION = {1.f, 3.f, 2.f};
constexpr glm::vec3 LIGHT_COLOR = {1.f, 1.f, 1.f};
constexpr glm::vec3 VOXEL_COLOR = {1.f, .5f, .1f};