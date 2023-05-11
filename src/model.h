#pragma once

#include <math3d.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

namespace sr
{
    struct Triangle
    {
        m3::vec4 vertices[3];
        Triangle(m3::vec4 v0, m3::vec4 v1, m3::vec4 v2);
    };

    struct Model
    {
        m3::vec4 pos;
        m3::quat rot;
        m3::vec4 scl;

        std::vector<m3::vec4> vertices;
        std::vector<int> indices;
        std::vector<sr::Triangle> triangles;

        Model(std::string filename);

        m3::mat4 modelMatrix();
        int loadModel(std::string filename);
        void genTriangles();

        void rotate(double x, double y, double z);
        void translate(double x, double y, double z);
        void scale(double x, double y, double z);
    };
}