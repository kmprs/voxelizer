#include "camera.hpp"
#include "constants.hpp"

Camera::Camera() :
        m_position( glm::vec3( 0, 0, 2.f )),
        m_direction( glm::vec3( 0, 0, -1 ))
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

glm::vec3 Camera::getDirection()
{
    return m_direction;
}

void Camera::update( Direction direction )
{
    if ( direction != NO_MOVEMENT )
    {
        // camera is always focused on the center
        m_direction = -glm::normalize( m_position );
        if ( direction == FORWARD ) m_position += CAMERA_SPEED * m_direction;
        else if ( direction == BACKWARD ) m_position -= CAMERA_SPEED * m_direction;
        else if ( direction == UP ) m_position += CAMERA_SPEED * m_up;
        else if ( direction == DOWN ) m_position -= CAMERA_SPEED * m_up;
        else if ( direction == RIGHT ) m_position += CAMERA_SPEED * glm::normalize( glm::cross( m_up, m_direction ));
        else if ( direction == LEFT ) m_position -= CAMERA_SPEED * glm::normalize( glm::cross( m_up, m_direction ));
    }
}
