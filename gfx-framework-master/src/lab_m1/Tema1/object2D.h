#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRomb(const std::string &name, glm::vec3 leftCorner, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateStea(const std::string& name, glm::vec3 topCorner, float length, glm::vec3 color, bool fill = true);
    Mesh* CreateHexagon(const std::string& name, glm::vec3 corner, float length, glm::vec3 colorMare, glm::vec3 colorMic, bool fill = true);
}
