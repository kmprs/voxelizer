#pragma once

#include "shaderHandler.hpp"
#include "constants.hpp"
#include "dataHandler.hpp"


class SceneHandler
{
public:
    SceneHandler( std::shared_ptr<ShaderHandler> shaderHandler );
    ~SceneHandler() = default;

    void setScene( const glm::vec3 &cameraPosition ) const;

private:
    std::shared_ptr<ShaderHandler> m_shaderHandler = nullptr;
};