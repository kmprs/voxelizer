#include "sceneHandler.hpp"

#include <utility>

SceneHandler::SceneHandler( std::shared_ptr<ShaderHandler> shaderHandler ) :
        m_shaderHandler( std::move( shaderHandler ))
{
}

void SceneHandler::setScene() const
{
    // light settings
    m_shaderHandler->setFloat( "AMBIENT_STRENGTH", AMBIENT_STRENGTH );
    m_shaderHandler->setVec3( "LIGHT_POSITION", LIGHT_POSITION );
    m_shaderHandler->setVec3( "LIGHT_COLOR", LIGHT_COLOR );
    m_shaderHandler->setVec3( "VOXEL_COLOR", VOXEL_COLOR );
}

