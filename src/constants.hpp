#pragma once

#include <string>
#include <glm/glm.hpp>

// WINDOW
constexpr glm::vec3 BACKGROUND_COLOR = { .12f, .12f, .12f };
const std::string TITLE = "Voxelizer";
constexpr int TARGET_FPS = 1000;
constexpr int FRAME_DELAY = 1000/TARGET_FPS;
constexpr int GUI_WIDTH = 250;

// CAMERA
constexpr float CAMERA_SPEED_LIMIT = 1000.f;
constexpr float ROTATION_SPEED_LIMIT = 2000.f;
constexpr float INIT_CAMERA_SPEED = 2.f;
constexpr float INIT_ROTATION_SPEED = 120.f;
constexpr float MOUSE_SENSITIVITY = .2f;
constexpr float CLIP_MIN = 0.01;
constexpr float CLIP_MAX = 200;
constexpr glm::vec3 YAW_AXIS = {0, 1, 0};
constexpr glm::vec3 PITCH_AXIS = {1, 0, 0};


// WORLD
constexpr float AMBIENT_STRENGTH = .5f;
constexpr float SPECULAR_STRENGTH = .5f;
constexpr int SHININESS = 32;
constexpr glm::vec3 LIGHT_POSITION = {-1.5f, 1.5f, -1.5f};
constexpr glm::vec3 LIGHT_COLOR = {1.f, 1.f, 1.f};
constexpr float ATTENUATION_CONSTANT = 0.5f;
constexpr float ATTENUATION_LINEAR = 0.2f;
constexpr float ATTENUATION_QUADRATIC = 0.1f;

constexpr int VOXEL_MEMORY_SIZE = 24;

// VOXELIZER
constexpr int INIT_RESOLUTION = 6;
constexpr int MAX_RESOLUTION_VIEWER = 10;
constexpr int MAX_RESOLUTION_BENCHMARK = 5;
constexpr int BVH_DEPTH = 12;

// MODEL
const std::string BINARY_PATH = "../binaries";