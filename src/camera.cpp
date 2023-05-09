#include "camera.h"

sr::Camera::Camera(): pos{m3::vec4(0, 0, -5, 1)}, world_up{m3::vec4(0, 1, 0, 0)}, target{m3::vec4(0, 0, 0, 1)}
{
    return;
}

m3::mat4 sr::Camera::viewMatrix()
{
    m3::vec4 direction = m3::vec4::normalized(this->pos - this->target);
    m3::vec4 right = m3::vec4::normalized(direction % this->world_up);
    m3::vec4 up = right % direction;

    m3::vec4 rows[4] = {
        right,
        up,
        direction,
        m3::vec4(0, 0, 0, 1)
    };

    m3::mat4 matrix(rows);

    return matrix * m3::mat4::gen_translation(-this->pos.x(), -this->pos.y(), -this->pos.z());
}