#include "dataHandler.hpp"


DataHandler::DataHandler() :
        m_voxelColor( { 1.f, 1.f, 1.f } ), m_worldCenter( { 0, 0, 0 } ),
        m_windowWidth( 1280 ), m_windowHeight( 780 ), m_benchmarkWindowWidth ( 1000 ),
        m_benchmarkWindowHeight( 700 ),
        m_cameraSpeed( INIT_CAMERA_SPEED ), m_rotationSpeed( INIT_ROTATION_SPEED ),
        m_modelRepresentation{ VOXEL }, m_voxelResolution( INIT_RESOLUTION ),
        m_voxelizationAlgorithm( OPTIMIZED ), m_currentModelPath("../binaries/bunny.obj"),
        m_benchmarkAlgorithms( { OPTIMIZED, BVH } )
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

void DataHandler::setWindowWidth( int width )
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

int DataHandler::getBenchmarkWindowWidth() const
{
    return m_benchmarkWindowWidth;
}

void DataHandler::setBenchmarkWindowWidth( int width )
{
    if ( width > 0 ) m_benchmarkWindowWidth = width;
}

int DataHandler::getBenchmarkWindowHeight() const
{
    return m_benchmarkWindowHeight;
}

void DataHandler::setBenchmarkWindowHeight( int height )
{
    if ( height > 0 ) m_benchmarkWindowHeight = height;
}

float DataHandler::getCameraSpeed() const
{
    return m_cameraSpeed;
}

void DataHandler::setCameraSpeed( float speed )
{
    if ( speed > 0 && speed <= CAMERA_SPEED_LIMIT ) m_cameraSpeed = speed;
}

float DataHandler::getRotationSpeed() const
{
    return m_rotationSpeed;
}

void DataHandler::setRotationSpeed( float speed )
{
    if ( speed > 0 && speed <= ROTATION_SPEED_LIMIT ) m_rotationSpeed = speed;
}

glm::vec3 DataHandler::getWorldCenter() const
{
    return m_worldCenter;
}

void DataHandler::setWorldCenter( const glm::vec3 &center )
{
    m_worldCenter = center;
}

int DataHandler::getCurrentFPS() const
{
    return m_currentFPS;
}

void DataHandler::setCurrentFPS( int fps )
{
    if ( fps >= 0 ) m_currentFPS = fps;
}

int DataHandler::getNumberOfVoxels() const
{
    return m_numberOfVoxels;
}

void DataHandler::setNumberOfVoxels( int numberOfVoxels )
{
    if ( numberOfVoxels >= 0 ) m_numberOfVoxels = numberOfVoxels;
}

Representation DataHandler::getModelRepresentation() const
{
    return m_modelRepresentation;
}

void DataHandler::toggleModelRepresentation()
{
    if ( m_modelRepresentation == VOXEL ) m_modelRepresentation = TRIANGLE;
    else m_modelRepresentation = VOXEL;
}

int DataHandler::getVoxelResolution() const
{
    return m_voxelResolution;
}

void DataHandler::setVoxelResolution( int resolution )
{
    if ( resolution >= 1 && resolution <= MAX_RESOLUTION_VIEWER ) m_voxelResolution = resolution;
}

CameraMode DataHandler::getCameraMode() const
{
    return m_cameraMode;
}

void DataHandler::toggleCameraMode()
{
    if ( m_cameraMode == CENTERED ) m_cameraMode = INDIVIDUAL;
    else m_cameraMode = CENTERED;
    m_cameraModeToggled = true;
}

bool DataHandler::isCameraModeToggled() const
{
    return m_cameraModeToggled;
}

void DataHandler::resetCameraModeToggled()
{
    m_cameraModeToggled = false;
}

bool DataHandler::isWindowFreezed() const
{
    return m_isWindowFreezed;
}

void DataHandler::toggleWindowFreeze()
{
    m_isWindowFreezed = !m_isWindowFreezed;
}

void DataHandler::setWindowFreeze( bool isFreezed )
{
    m_isWindowFreezed = isFreezed;
}

bool DataHandler::isBenchmarkShown() const
{
    return m_showBenchmarks;
}

void DataHandler::showBenchmarks( bool showBenchmarks )
{
    m_showBenchmarks = showBenchmarks;
}

VoxelizationAlgorithm DataHandler::getVoxelizationAlgorithm() const
{
    return m_voxelizationAlgorithm;
}

void DataHandler::setAlgorithm( VoxelizationAlgorithm algorithm )
{
    m_voxelizationAlgorithm = algorithm;
}

std::string DataHandler::getCurrentModelPath() const
{
    return m_currentModelPath;
}

void DataHandler::setModelPath( const std::string &path )
{
    m_currentModelPath = path;
}

std::set<VoxelizationAlgorithm> DataHandler::getBenchmarkAlgorithms()
{
    return m_benchmarkAlgorithms;
}

void DataHandler::addToBenchmark( VoxelizationAlgorithm algorithm )
{
    m_benchmarkAlgorithms.insert( algorithm );
}

void DataHandler::eraseFromBenchmark( VoxelizationAlgorithm algorithm )
{
    m_benchmarkAlgorithms.erase( algorithm );
}

bool DataHandler::benchmarkChanged() const
{
    return m_benchmarkUpdate && m_benchmarkChanged;
}

void DataHandler::setBenchmarkChanged( bool changed )
{
    m_benchmarkChanged = changed;
}

void DataHandler::setBenchmarkUpdate( bool updated )
{
    m_benchmarkUpdate = updated;
}