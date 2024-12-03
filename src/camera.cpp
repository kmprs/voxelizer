#include "camera.hpp"
#include "constants.hpp"

extern std::shared_ptr<DataHandler> dataHandler;


Camera::Camera() :
        m_position( glm::vec3( -2.f, 0, -2.f )),
        m_direction( dataHandler->getWorldCenter() - m_position ),
        m_worldCenter( dataHandler->getWorldCenter())
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

    if ( m_worldCenter != dataHandler->getWorldCenter())
    {
        m_worldCenter = dataHandler->getWorldCenter();
        m_direction = glm::normalize( m_worldCenter - m_position );
    }

    // mouse callback
    if ( dataHandler->getCameraMode() == INDIVIDUAL )
    {
        SDL_GetMouseState( &m_xPosMouse, &m_yPosMouse );
        mouseCallback( static_cast<float>(m_xPosMouse), static_cast<float>(m_yPosMouse),
                       deltaTime );
    } else if ( dataHandler->isCameraModeToggled())
    {
        m_direction = glm::normalize( m_worldCenter - m_position );
        dataHandler->resetCameraModeToggled();
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
            if ( direction != FORWARD && direction != BACKWARD )
            {
                m_position -= m_worldCenter;
                float rotationAngle = glm::radians( cameraRotationSpeed );
                if ( direction == UP || direction == LEFT )
                    rotationAngle = -rotationAngle;

                glm::vec3 pitchAxis = glm::normalize(
                        glm::cross( m_direction, YAW_AXIS ));
                pitchAxis.y = 0;
                glm::vec3 axis = ( direction == UP || direction == DOWN ) ? pitchAxis
                                                                          : YAW_AXIS;
                const float epsilon = 0.0001f;
                float dot = glm::dot( YAW_AXIS, glm::normalize( m_direction ));
                // the camera shall not be rotating over the top in order to avoid flipping
                // the direction of vertical rotation
                if ( axis == YAW_AXIS || std::abs( dot ) > 1 + epsilon ||
                     std::abs( dot ) < 1 - epsilon || ( dot >= 0 && direction == UP ) ||
                     ( dot <= 0 && direction == DOWN ))
                {
                    glm::quat rotation = glm::angleAxis( rotationAngle, axis );
                    m_position = rotation * m_position;
                } else if ( std::abs( dot ) == 1 )
                {
                    m_position.x += epsilon;
                }
                m_position += m_worldCenter;
            }
            m_direction = glm::normalize( m_worldCenter - m_position );

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
    xOffset *= static_cast<float>( MOUSE_SENSITIVITY );
    yOffset *= static_cast<float>( MOUSE_SENSITIVITY );
    m_yaw += xOffset;
    m_pitch += yOffset;

    if ( m_pitch > 89.0f ) m_pitch = 89.0f;
    else if ( m_pitch < -89.0f ) m_pitch = -89.0f;

    m_direction.x = cos( glm::radians( m_yaw )) * cos( glm::radians( m_pitch ));
    m_direction.y = sin( glm::radians( m_pitch ));
    m_direction.z = sin( glm::radians( m_yaw )) * cos( glm::radians( m_pitch ));
    m_direction = glm::normalize( m_direction );

}
