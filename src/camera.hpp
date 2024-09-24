#pragma once

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "glm/glm.hpp"

enum Direction {
    NO_MOVEMENT,
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera();
    ~Camera() = default;

    void update( Direction direction );
    void setPosition( const glm::vec3 &pos );
    glm::vec3 getPosition();
    glm::vec3 getDirection();


private:
    glm::vec3 m_position = {};
    glm::vec3 m_direction = {};

    float m_yaw = -1;
    float m_pitch = -1;
    float m_roll = -1;

    bool m_moving = false;
    bool m_forwardMovement = false;
    bool m_upMovement = false;
    bool m_leftMovement = false;

    int m_xPosMouse = -1;
    int m_yPosMouse = -1;
    float m_lastX = -1;
    float m_lastY = -1;
    bool m_dragging = false;
};
