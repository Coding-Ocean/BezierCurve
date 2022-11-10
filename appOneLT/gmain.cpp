#define _BEZIER
//#define _DERIVATIVE

#ifdef _BEZIER
#include"moveWithMouse.h"
#include"libOne.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100, 50);
    COLOR blue(220, 100, 100);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Points
    VECTOR p0(600, 800);
    VECTOR p1(950, 200);
    VECTOR p2(1300, 800);
    VECTOR p3(1650, 200);
    //Prepare for Mouse dragging
    addPointToMoveWithMouse(&p0);
    addPointToMoveWithMouse(&p1);
    addPointToMoveWithMouse(&p2);
    addPointToMoveWithMouse(&p3);
    //Main Loop
    while (notQuit) {
        clear();
        movePointWithMouse();
        //Points
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
    }
}
#endif

#ifdef _DERIVARTIVE
#include"moveWithMouse.h"
#include"libOne.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100, 50);
    COLOR blue(220, 100, 100);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Points
    VECTOR p0(600, 800);
    VECTOR p1(950, 200);
    VECTOR p2(1300, 800);
    VECTOR p3(1650, 200);
    //Prepare for Mouse dragging
    addPointToMoveWithMouse(&p0);
    addPointToMoveWithMouse(&p1);
    addPointToMoveWithMouse(&p2);
    addPointToMoveWithMouse(&p3);
    //Main Loop
    while (notQuit) {
        clear();
        movePointWithMouse();
        //Points
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
        circle(p2, 14, black, white, 6);
        circle(p3, 14, black, white, 6);
    }
}
#endif