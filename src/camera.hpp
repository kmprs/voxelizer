#pragma once

#include <iostream>
#include "glm/glm.hpp"


class Camera
{
public:
    Camera();
    ~Camera() = default;

    void setPosition( const glm::vec3 &pos );
    glm::vec3 getPosition();

private:
    glm::vec3 m_position = {};
};
