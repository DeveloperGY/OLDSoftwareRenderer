#pragma once

#include <math3d.h>

#include <vector>
#include <fstream>
#include <sstream>

namespace sr
{
    struct Model
    {
        m3::vec4 pos;
        m3::vec4 rot;
        m3::vec4 scl;

        std::vector<m3::vec4> vertices;
        std::vector<int> indices;

        Model(std::string filename);
    };
}