#include "model.h"

sr::Triangle::Triangle(m3::vec4 v0, m3::vec4 v1, m3::vec4 v2)
{
    this->vertices[0] = v0;
    this->vertices[1] = v1;
    this->vertices[2] = v2;

    return;
}