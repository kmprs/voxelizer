#include "camera.hpp"
#include "constants.hpp"

extern std::shared_ptr<DataHandler> dataHandler;


Camera::Camera() :
        m_position( glm::vec3( -2.f, 0, -2.f )),
        m_direction( dataHandler->getWorldCenter() - m_position )
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
    // key callback
    float cameraSpeed = dataHandler->getCameraSpeed() * deltaTime;
    glm::vec3 worldCenter = dataHandler->getWorldCenter();

    // mouse callback
    if ( dataHandler->getCameraMode() == INDIVIDUAL )
    {
        SDL_GetMouseState( &m_xPosMouse, &m_yPosMouse );
        mouseCallback( static_cast<float>(m_xPosMouse), static_cast<float>(m_yPosMouse),
                       deltaTime );
    } else if ( dataHandler->isCameraModeToggled() )
    {
        m_direction = worldCenter - m_position;
    }

    float cameraRotationSpeed = dataHandler->getRotationSpeed() * deltaTime;

    if ( direction != NO_MOVEMENT )
    {
        if ( direction == FORWARD && ( abs( m_position.x ) + abs( m_position.z )) > 0.01 )
            m_position += cameraSpeed * m_direction;
        else if ( direction == BACKWARD )
            m_position -= cameraSpeed * m_direction;

        if ( dataHandler->getCameraMode() == CENTERED )
        {
            m_position -= worldCenter;
            if ( direction == UP )
                m_position = glm::rotate( m_position, glm::radians( cameraRotationSpeed ),
                                          PITCH_AXIS );
            else if ( direction == DOWN )
                m_position = glm::rotate( m_position,
                                          glm::radians( -cameraRotationSpeed ),
                                          PITCH_AXIS );
            else if ( direction == RIGHT )
                m_position = glm::rotate( m_position, glm::radians( cameraRotationSpeed ),
                                          YAW_AXIS );
            else if ( direction == LEFT )
                m_position = glm::rotate( m_position,
                                          glm::radians( -cameraRotationSpeed ),
                                          YAW_AXIS );
            m_position += worldCenter;

            // Only update m_direction if not in free mode
            m_direction = glm::normalize( worldCenter - m_position );
        } else if ( dataHandler->getCameraMode() == INDIVIDUAL )
        {
            if ( direction == UP )
                m_position += cameraSpeed * YAW_AXIS;
            else if ( direction == DOWN )
                m_position -= cameraSpeed * YAW_AXIS;
            else if ( direction == RIGHT )
                m_position += glm::normalize( glm::cross( m_direction, YAW_AXIS )) *
                              cameraSpeed;
            else if ( direction == LEFT )
                m_position -= glm::normalize( glm::cross( m_direction, YAW_AXIS )) *
                              cameraSpeed;
        }
    }
}

void Camera::mouseCallback( float currentX, float currentY, float deltaTime )
{
    if ( currentX < GUI_WIDTH ||
         currentX > static_cast<float>(dataHandler->getWindowWidth()) - GUI_WIDTH ||
         currentY <= 1 ||
         currentY >= static_cast<float>(dataHandler->getWindowHeight()) - 1 )
    {
        return;
    }

    if ( m_firstMouse )
    {
        m_lastX = currentX;
        m_lastY = currentY;
        m_firstMouse = false;
        return;
    }

    float xOffset = currentX - m_lastX;
    float yOffset = m_lastY - currentY;

    const float MAX_OFFSET = 50.0f;
    // ignoring large offsets in order to avoid rapid camera movements
    if ( fabs( xOffset ) > MAX_OFFSET || fabs( yOffset ) > MAX_OFFSET )
    {
        m_lastX = currentX;
        m_lastY = currentY;
        return;
    }

    m_lastX = currentX;
    m_lastY = currentY;
    xOffset *= static_cast<float>( MOUSE_SENSITIVITY ) * ( float ) deltaTime;
    yOffset *= static_cast<float>( MOUSE_SENSITIVITY ) * ( float ) deltaTime;
    m_yaw += xOffset;
    m_pitch += yOffset;

    if ( m_pitch > 89.0f ) m_pitch = 89.0f;
    else if ( m_pitch < -89.0f ) m_pitch = -89.0f;

    m_direction.x = cos( glm::radians( m_yaw )) * cos( glm::radians( m_pitch ));
    m_direction.y = sin( glm::radians( m_pitch ));
    m_direction.z = sin( glm::radians( m_yaw )) * cos( glm::radians( m_pitch ));
    m_direction = glm::normalize( m_direction );

}
