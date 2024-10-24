#include "dataHandler.hpp"


DataHandler::DataHandler() :
m_voxelColor({.5f, .7f, .4f}), m_windowWidth(1280), m_windowHeight(780)
{}


glm::vec3 DataHandler::getVoxelColor() const
{
    return m_voxelColor;
}

void DataHandler::setVoxelColor( const glm::vec3 &color )
{
    m_voxelColor = color;
}

int DataHandler::getWindowWidth() const
{
    return m_windowWidth;
}

void DataHandler::setWindowWidth(int width)
{
    m_windowWidth = width;
}

int DataHandler::getWindowHeight() const
{
    return m_windowHeight;
}

void DataHandler::setWindowHeight( int height )
{
    m_windowHeight = height;
}

