#include "dataHandler.hpp"


DataHandler::DataHandler() :
m_voxelColor({.5f, .7f, .4f})
{}


glm::vec3 DataHandler::getVoxelColor()
{
    return m_voxelColor;
}

void DataHandler::setVoxelColor( const glm::vec3 &color )
{
    m_voxelColor = color;
}
