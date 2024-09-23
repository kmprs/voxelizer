#pragma once

#include <iostream>
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
    glm::vec3 m_up = {0, 1, 0};

    bool m_moving = false;
    bool m_forwardMovement = false;
    bool m_upMovement = false;
    bool m_leftMovement = false;

    int m_xPosMouse = -1;
    int m_yPosMouse = -1;
    float m_yaw = -1;
    float m_pitch = -1;
    float m_lastX = -1;
    float m_lastY = -1;
    bool m_dragging = false;
};
