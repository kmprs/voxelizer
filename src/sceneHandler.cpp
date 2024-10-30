#include "sceneHandler.hpp"


extern std::shared_ptr<DataHandler> dataHandler;

extern float rgb[3];
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
    m_shaderHandler->setVec3( "VOXEL_COLOR", dataHandler->getVoxelColor() );
    m_shaderHandler->setFloat( "SPECULAR_STRENGTH", SPECULAR_STRENGTH );
    m_shaderHandler->setInt( "SHININESS", SHININESS );
}

