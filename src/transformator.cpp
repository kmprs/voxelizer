#include "transformator.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


Transformator::Transformator( std::shared_ptr<ShaderHandler> shaderHandler ) :
        m_shaderHandler( std::move( shaderHandler ))
{

}


void Transformator::transform( const glm::vec3 &cameraPosition,
                               const glm::vec3 &cameraDirection )
{

    m_view = glm::mat4( 1.0f );
    m_projection = glm::mat4( 1.0f );

    m_view = glm::lookAt( cameraPosition, WORLD_CENTER, glm::vec3( 0, 1, 0 ));
    m_shaderHandler->setMat4( "view", m_view );
    m_shaderHandler->setMat4( "model", m_model );
    m_projection = glm::perspective( glm::radians( 45.0f ),
                                     static_cast<float>(dataHandler->getWindowWidth() -
                                                        GUI_WIDTH) /
                                     static_cast<float>(dataHandler->getWindowHeight()),
                                     static_cast<float>(CLIP_MIN),
                                     static_cast<float>(CLIP_MAX));

    m_shaderHandler->setMat4( "projection", m_projection );

}
