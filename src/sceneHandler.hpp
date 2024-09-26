#pragma once

#include <iostream>
#include <memory>
#include "shaderHandler.hpp"
#include "constants.hpp"


class SceneHandler
{
public:
    SceneHandler( std::shared_ptr<ShaderHandler> shaderHandler );
    ~SceneHandler() = default;

    void setScene() const;

private:
    std::shared_ptr<ShaderHandler> m_shaderHandler = nullptr;
};