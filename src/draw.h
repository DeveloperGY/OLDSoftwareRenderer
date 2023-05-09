#pragma once

#include <termDisplay.h>
#include "model.h"
#include <iostream>

namespace sr
{
    int init(int width, int height);\
    void clean();

    void display();
    void draw(sr::Model m);
}