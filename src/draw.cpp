#include "draw.h"

int sr::init(int width, int height)
{
    if (!td_initialize(width, height))
    {
        return 0;
    }

    return 1;
}

void sr::clean()
{
    td_terminate(1);

    return;
}

void sr::display()
{
    td_display();

    return;
}

void sr::draw(sr::Model m)
{
    for (auto &v: m.vertices)
    {
        m3::mat4 translate = m3::mat4::gen_translation(10, 10, 10);
        // m3::mat4 rotY = m3::mat4::gen_rotationY(30);
        // m3::mat4 rotZ = m3::mat4::gen_rotationZ(30);
        m3::quat rot(45, m3::vec4(0, 1, 1, 1));
        m3::mat4 scale = m3::mat4::gen_scale(2, 2, 2);
        m3::vec4 v0 = translate * ((rot * scale * v) * m3::quat::inverse(rot));
        td_drawPoint(v0.x(), v0.y(), '*', (v0.y() < 10) ? TD_COLOR_RED: TD_COLOR_DEFAULT, TD_COLOR_DEFAULT);
    }

    return;
}