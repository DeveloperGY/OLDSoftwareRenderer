#include "draw.h"
#include "model.h"

int main(void)
{
    const int width = 40;
    const int height = 24;

    if (!sr::init(width, height))
    {
        return -1;
    }

    sr::Model m("res/cube.obj");

    while (getch(0) != 'q')
    {
        sr::display();
        sr::draw(m);
    }

    sr::clean();

    return 0;
}