#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include "glm/glm.hpp"
#include "types.hpp"
#include "dataHandler.hpp"


class Camera
{
public:
    Camera();
    ~Camera() = default;

    void update( Direction direction, float deltaTime );
    void setPosition( const glm::vec3 &pos );
    glm::vec3 getPosition();
    glm::vec3 getDirection();

private:

    void mouseCallback( float currentX, float currentY, float deltaTime );

    glm::vec3 m_position = {};
    glm::vec3 m_direction = {};
    glm::vec3 m_worldCenter = {};

    float m_yaw = -1;
    float m_pitch = -1;

    bool m_firstMouse = true;
    int m_xPosMouse = -1;
    int m_yPosMouse = -1;
    float m_lastX = -1;
    float m_lastY = -1;
};
