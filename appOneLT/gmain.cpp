#define _BEZIER
//#define _DERIVATIVE

#ifdef _BEZIER
#include"libOne.h"
#include"moveWithMouse.h"
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
        movePointWithMouse();
        clear();
        //Points
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
        circle(p2, 14, black, white, 6);
        circle(p3, 14, black, white, 6);
    }
}
#endif

#ifdef _DERIVATIVE
#include<vector>
#include"libOne.h"
#include"moveWithMouse.h"
#include"bezier.h"
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
    VECTOR p0(600, 500);
    VECTOR p1(900, 500);
    VECTOR p2(1200, 500);
    VECTOR p3(1500, 500);
    //Prepare for Mouse dragging
    addPointToMoveWithMouse(&p0);
    addPointToMoveWithMouse(&p1);
    addPointToMoveWithMouse(&p2);
    addPointToMoveWithMouse(&p3);
    //Main Loop
    while (notQuit) {
        clear();
        movePointWithMouse();
        //Bezier curve
        VECTOR sp = p0;
        VECTOR ep;
        float dtm = 0.05f;
        for (float tm = dtm; tm <= 1.00001f; tm += dtm) {
            ep = bezier(p0, p1, p2, p3, tm);
            line(sp, ep, yellow, 5);
            sp = ep;
        }
        //Points
        line(p0, p1, white, 2);
        line(p3, p2, white, 2);
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
        circle(p2, 14, black, white, 6);
        circle(p3, 14, black, white, 6);
    }
}
#endif