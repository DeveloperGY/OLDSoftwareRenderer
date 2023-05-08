#include <termDisplay.h>
#include <math3d.h>

int main(void)
{
    const int width = 40;
    const int height = 24;

    td_initialize(width, height);
    while(getch(0) != 'q')
    {
        
    }
    td_terminate(0);
    return 0;
}