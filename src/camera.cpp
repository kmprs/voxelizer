#include "camera.hpp"

Camera::Camera()
{

}

void Camera::setPosition( const glm::vec3 &position )
{
    m_position = position;
}

glm::vec3 Camera::getPosition()
{
    return m_position;
}
