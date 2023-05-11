#pragma once

#include <termDisplay.h>
#include "model.h"
#include "camera.h"
#include <iostream>
#include <cmath>

namespace sr
{
    extern int width;
    extern int height;
    extern float vfov_degrees;

    int init(int width, int height, float vfov);
    void clean();

    void display();
    void draw(sr::Model m, sr::Camera c, bool wireframe);
}