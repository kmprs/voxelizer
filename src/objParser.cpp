#include "objParser.hpp"

vecTriangleFace OBJParser::parse( const std::string &path )
{
    // resetting the triangle information
    m_positions.clear();
    m_normals.clear();
    m_faceIndices.clear();
    vecTriangleFace faces = {};

    // reading each line and writing its content in one of three vectors based on their prefix
    std::ifstream file( path );
    if ( !file.is_open())
    {
        std::cerr << "Could not open the file: " << path << std::endl;
        exit( EXIT_FAILURE );
    }

    std::string line;
    while ( std::getline( file, line ))
    {
        std::istringstream iss( line );
        std::string prefix;
        iss >> prefix;
        if ( prefix == "v" )
        {
            glm::vec3 coordinates = {};
            iss >> coordinates.x >> coordinates.y >> coordinates.z;
            m_positions.emplace_back( coordinates );
        } else if ( prefix == "vn" )
        {
            glm::vec3 normal = {};
            iss >> normal.x >> normal.y >> normal.z;
            m_normals.emplace_back( normal );
        } else if ( prefix == "f" )
        {
            std::vector<std::string> vertices = {};
            std::string token;
            while ( iss >> token ) vertices.push_back( token );
            std::vector<OBJFaceIndices> facesInfo = toFaceIndices( vertices );
            for ( OBJFaceIndices faceIndices : facesInfo ) m_faceIndices.push_back(faceIndices);
        }
    }
    file.close();

    // normalize vertex coordinates
    float maximum = util::findMax( m_positions );
    for (glm::vec3 &vec : m_positions)
    {
        vec.x = vec.x / maximum;
        vec.y = vec.y / maximum;
        vec.z = vec.z / maximum;
    }

    // creation of triangle faces based on the obj file
    for ( OBJFaceIndices faceIndices: m_faceIndices )
    {
        glm::vec3 pos1 = m_positions[faceIndices.f1Coords];
        glm::vec3 pos2 = m_positions[faceIndices.f2Coords];
        glm::vec3 pos3 = m_positions[faceIndices.f3Coords];
        glm::vec3 normal1 = m_normals[faceIndices.f1Normal];
        glm::vec3 normal2 = m_normals[faceIndices.f2Normal];
        glm::vec3 normal3 = m_normals[faceIndices.f3Normal];

        Vertex v1 = { pos1.x, pos1.y, pos1.z, normal1.x, normal1.y, normal1.z };
        Vertex v2 = { pos2.x, pos2.y, pos2.z, normal2.x, normal2.y, normal2.z };
        Vertex v3 = { pos3.x, pos3.y, pos3.z, normal3.x, normal3.y, normal3.z };
        Vertex vertices[3] = { v1, v2, v3 };
        std::shared_ptr<TriangleFace> face = std::make_shared<TriangleFace>( vertices,
                                                                             static_cast<unsigned int>(faces.size()) *
                                                                             3 );
        faces.emplace_back( face );
    }
    return faces;
}

/**
 * @brief takes in a f line of an obj file and returns a vector of OBJFaceIndices
 * in the format
 * @param fInput extracted .../.../... of the f-line
 * @return vector of OBJFaceIndices
 */
std::vector<OBJFaceIndices> OBJParser::toFaceIndices( const std::vector<std::string> &fInput )
{
    std::vector<OBJFaceIndices> faceIndices = {};
    std::vector<std::string> baseElement = util::split( fInput[0], '/' );
    for ( int i = 1; i < fInput.size() - 1; i++ )
    {
        std::vector<std::string> element1 = util::split( fInput[i], '/' );
        std::vector<std::string> element2 = util::split( fInput[i + 1], '/' );
        // the index in the f line in obj starts at 1, not 0
        OBJFaceIndices face = { std::stoi( baseElement[0]) - 1, std::stoi( baseElement[2] ) - 1,
                                std::stoi( element1[0] ) - 1, std::stoi( element1[2] ) - 1,
                                std::stoi( element2[0] ) - 1, std::stoi( element2[2] ) - 1};
        faceIndices.push_back(face);
    }

    return faceIndices;
}


