#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRomb(
    const std::string& name,
    glm::vec3 leftCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftCorner;

    std::vector<VertexFormat> vertices_romb =
    {
        VertexFormat(corner + glm::vec3(0, 0, 2), color),
        VertexFormat(corner + glm::vec3(2*length, 0, 2), color),
        VertexFormat(corner + glm::vec3(length, 2*length, 2), color),
        VertexFormat(corner + glm::vec3(length, -2*length, 2), color),

        VertexFormat(corner + glm::vec3(length, length/2, 2), color),
        VertexFormat(corner + glm::vec3(length, -length/2, 2), color),
        VertexFormat(corner + glm::vec3(3*length, length / 2, 2), color),
        VertexFormat(corner + glm::vec3(3*length, -length / 2, 2), color)
    };

    Mesh* romb = new Mesh(name);
    std::vector<unsigned int> indices_romb =
    {
        0, 1, 2,
        0, 2, 3,
        1, 2, 3,
        0, 1, 3,

        4, 5, 6,
        5, 6, 7,
        6, 7, 4,
        7, 4, 5
    };

    if (!fill) {
        romb->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices_romb.push_back(6);
        indices_romb.push_back(7);
    }

    romb->InitFromData(vertices_romb, indices_romb);
    return romb;
}

Mesh* object2D::CreateStea(
    const std::string& name,
    glm::vec3 topCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = topCorner;

    std::vector<VertexFormat> vertices_stea =
    {
        VertexFormat(corner + glm::vec3(0, 0, 3), color),
        VertexFormat(corner + glm::vec3(0, length/2, 3), color),
        VertexFormat(corner + glm::vec3(-length/4, 0, 3), color),
        VertexFormat(corner + glm::vec3(length/4, 0, 3), color),
        VertexFormat(corner + glm::vec3(-length/3, -length/2, 3), color),
        VertexFormat(corner + glm::vec3(length/3, -length/2, 3), color),
        VertexFormat(corner + glm::vec3(-length/2, length/4, 3), color),
        VertexFormat(corner + glm::vec3(length / 2, length / 4, 3), color),
    };

    Mesh* stea = new Mesh(name);
    std::vector<unsigned int> indices_stea =
    {
        2, 0, 1,
        1, 0, 3,
        3, 2, 4,
        3, 2, 5,
        6, 2, 3,
        7, 2, 3
    };

    if (!fill) {
        stea->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices_stea.push_back(1);
        indices_stea.push_back(2);
        indices_stea.push_back(3);
    }

    stea->InitFromData(vertices_stea, indices_stea);
    return stea;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 middle,
    float length,
    glm::vec3 colorMare,
    glm::vec3 colorMic,
    bool fill)
{
    Mesh* hexagon = new Mesh(name);

    std::vector<VertexFormat> vertices_hexa =
    {
        VertexFormat(middle + glm::vec3(0, 0, 3) , colorMare),

        VertexFormat(middle + glm::vec3(-length, 0, 3) , colorMare),
        VertexFormat(middle + glm::vec3(-length/2, length, 3) , colorMare),
        VertexFormat(middle + glm::vec3(length/2, length, 3) , colorMare),
        VertexFormat(middle + glm::vec3(length, 0, 3) , colorMare),
        VertexFormat(middle + glm::vec3(length/2, -length, 3) , colorMare),
        VertexFormat(middle + glm::vec3(-length/2, -length, 3) , colorMare),

        VertexFormat(middle + glm::vec3(0, 0, 4) , colorMic),

        VertexFormat(middle + glm::vec3(-length/2, 0, 4) , colorMic),
        VertexFormat(middle + glm::vec3(-length / 4, length/2, 4) , colorMic),
        VertexFormat(middle + glm::vec3(length / 4, length/2, 4) , colorMic),
        VertexFormat(middle + glm::vec3(length/2, 0, 4) , colorMic),
        VertexFormat(middle + glm::vec3(length / 4, -length/2, 4) , colorMic),
        VertexFormat(middle + glm::vec3(-length / 4, -length/2, 4) , colorMic)
    };

    std::vector<unsigned int> indices_hexa = {
        0, 2, 1,
        0, 3, 2,
        0, 4, 3,
        0, 5, 4,
        0, 6, 5,
        0, 1, 6,

        13, 8, 7,
        13, 9, 8,
        13, 10, 9,
        13, 11, 10,
        13, 12, 11,
        13, 7, 12
    };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {

        indices_hexa.push_back(0);
        indices_hexa.push_back(6);
        indices_hexa.push_back(7);
        indices_hexa.push_back(13);
    }

    hexagon->InitFromData(vertices_hexa, indices_hexa);

    return hexagon;
}