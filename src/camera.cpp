#include "camera.h"

sr::Camera::Camera(): pos{m3::vec4(0, 0, 3, 1)}, world_up{m3::vec4(0, 1, 0, 0)}, front{m3::vec4(0, 0, -1, 0)}
{
    this->rotation = m3::quat(0, m3::vec4(0, 1, 0, 0));
    return;
}

m3::mat4 sr::Camera::viewMatrix()
{
    this-> front = this->rotation * this->front * m3::quat::inverse(this->rotation);

    m3::vec4 target = this->pos + this->front;

    m3::vec4 direction = m3::vec4::normalized(this->pos - target);
    m3::vec4 right = m3::vec4::normalized(direction % this->world_up);
    m3::vec4 up = this->world_up;

    m3::vec4 rows[4] = {
        right,
        up,
        direction,
        m3::vec4(0, 0, 0, 1)
    };

    m3::mat4 matrix(rows);

    return matrix * m3::mat4::gen_translation(-this->pos.x(), -this->pos.y(), -this->pos.z());
}