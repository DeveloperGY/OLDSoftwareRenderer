#include "draw.h"
#include "model.h"

#include <termDisplay.h>

#include <chrono>

void handleInput(char ch, sr::Camera &c, double dt);

int main(void)
{
    const int width = 80 * 2;
    const int height = 48 * 2;

    if (!sr::init(width, height, 60.0f))
    {
        return -1;
    }

    sr::Model m("res/monkey.obj");

    sr::Camera c;

    auto past = std::chrono::steady_clock::now();

    char ch = ' ';

    while ((ch = getch(0)) != 'p')
    {
        auto now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - past).count() / 1000.0f;
        past = now;
        m.rotate(0, 90 * dt, 0);
        td_drawFillRect(0, 0, width, height, ' ', TD_COLOR_CYAN, TD_COLOR_CYAN);
        sr::draw(m, c, true);
        td_drawPoint(width/2, height/2, '+', TD_COLOR_MAGENTA, TD_COLOR_DEFAULT);
        sr::display();

        handleInput(ch, c, dt);
    }

    sr::clean();

    return 0;
}

void handleInput(char ch, sr::Camera &c, double dt)
{
    double speed = 7;

    if (ch == 'w')
    {
        m3::vec4 mod = m3::vec4::normalized(c.rotation * c.front * m3::quat::inverse(c.rotation));
        mod.data[0] *= speed * dt;
        mod.data[1] *= speed * dt;
        mod.data[2] *= speed * dt;

        c.pos = c.pos + mod;
    }
    if (ch == 's')
    {
        m3::vec4 mod = m3::vec4::normalized(c.rotation * c.front * m3::quat::inverse(c.rotation));
        mod.data[0] *= speed * dt;
        mod.data[1] *= speed * dt;
        mod.data[2] *= speed * dt;

        c.pos = c.pos - mod;
    }
    if(ch == 'd')
    {
        m3::vec4 mod = m3::vec4::normalized(c.rotation * m3::vec4::normalized(c.front % c.world_up)  * m3::quat::inverse(c.rotation));
        mod.data[0] *= speed * dt;
        mod.data[1] *= speed * dt;
        mod.data[2] *= speed * dt;

        c.pos = c.pos - mod;
    }
    if(ch == 'a')
    {
        m3::vec4 mod = m3::vec4::normalized(c.rotation * m3::vec4::normalized(c.front % c.world_up)  * m3::quat::inverse(c.rotation));
        mod.data[0] *= speed * dt;
        mod.data[1] *= speed * dt;
        mod.data[2] *= speed * dt;

        c.pos = c.pos + mod;
    }
    if(ch == ' ')
    {
        c.pos.data[1] += speed * dt;
    }
    if(ch == 'v')
    {
        c.pos.data[1] -= speed * dt;
    }
    if(ch == 'q')
    {
        m3::quat rot(-180 * dt, m3::vec4(0, 1, 0, 0));

        c.rotation = c.rotation * rot;
    }
    if(ch == 'e')
    {
        m3::quat rot(180 * dt, m3::vec4(0, 1, 0, 0));

        c.rotation = c.rotation * rot;
    }

    return;
}