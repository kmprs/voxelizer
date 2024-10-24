#pragma once


#include <glm/glm.hpp>
#include <utility>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "constants.hpp"
#include "shaderHandler.hpp"
#include "dataHandler.hpp"


class Transformator
{
public:
    Transformator( std::shared_ptr<ShaderHandler> shaderHandler );
    ~Transformator() = default;

    void transform( const glm::vec3 &cameraPosition, const glm::vec3 &cameraDirection );

private:
    std::shared_ptr<ShaderHandler> m_shaderHandler = nullptr;
    glm::mat4 m_model = glm::mat4( 1.0f );
    glm::mat4 m_view = glm::mat4( 1.0f );
    glm::mat4 m_projection = glm::mat4( 1.0f );
    int m_modelLocation = 0;
    int m_viewLocation = 0;
};