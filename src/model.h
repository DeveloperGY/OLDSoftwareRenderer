#pragma once

#include <math3d.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

namespace sr
{
    struct Model
    {
        m3::vec4 pos;
        m3::quat rot;
        m3::vec4 scl;

        std::vector<m3::vec4> vertices;
        std::vector<int> indices;

        Model(std::string filename);

        m3::mat4 modelMatrix();

        void rotate(double x, double y, double z);
        void translate(double x, double y, double z);
        void scale(double x, double y, double z);
    };
}