#include "draw.h"
#include "model.h"

#include <chrono>

int main(void)
{
    const int width = 80;
    const int height = 48;

    if (!sr::init(width, height, 40.0f))
    {
        return -1;
    }

    sr::Model m("res/cube.obj");
    // m.rotate(15, 0, 0);
    m.translate(0, 0, 0);

    sr::Camera c;

    auto past = std::chrono::steady_clock::now();

    char ch = ' ';

    while ((ch = getch(0)) != 'q')
    {
        auto now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - past).count() / 1000.0f;
        past = now;
        m.rotate(90 * dt, 90 * dt, 90 * dt);
        sr::draw(m, c);
        sr::display();

        if (ch == 'w')
        {
            c.pos.data[2] += 5 * dt;
        }

    }

    sr::clean();

    return 0;
}