#include "camera.hpp"
#include "constants.hpp"

extern std::shared_ptr<DataHandler> dataHandler;


Camera::Camera() :
        m_position( glm::vec3( -2.f, 0, -2.f )),
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

void Camera::update( Direction direction, float deltaTime )
{
    float cameraSpeed = dataHandler->getCameraSpeed() * deltaTime;
    float cameraRotationSpeed = dataHandler->getRotationSpeed() * deltaTime;
    if ( direction != NO_MOVEMENT )
    {
        // camera is always focused on the center
        if ( direction == FORWARD && ( abs( m_position.x ) + abs( m_position.z )) > 0.01 )
            m_position += cameraSpeed * m_direction;
        else if ( direction == BACKWARD )
            m_position -= cameraSpeed * m_direction;
        else if ( direction == UP )
            m_position = glm::rotate( m_position, glm::radians( cameraRotationSpeed ),
                                      PITCH_AXIS );
        else if ( direction == DOWN )
            m_position = glm::rotate( m_position, glm::radians( -cameraRotationSpeed ),
                                      PITCH_AXIS );
        else if ( direction == RIGHT )
            m_position = glm::rotate( m_position, glm::radians( cameraRotationSpeed ),
                                      YAW_AXIS );
        else if ( direction == LEFT )
            m_position = glm::rotate( m_position, glm::radians( -cameraRotationSpeed ),
                                      YAW_AXIS );
        m_direction = glm::normalize( WORLD_CENTER - m_position );
    }
}