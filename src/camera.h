#pragma once

#include <math3d.h>

namespace sr
{
    class Camera
    {
        public:
        
            m3::vec4 pos;
            m3::vec4 world_up;
            m3::vec4 target;

            Camera();

            m3::mat4 viewMatrix();
    };
}