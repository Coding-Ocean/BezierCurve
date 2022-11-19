#define _BEZIER
//#define _DERIVATIVE
#ifdef _BEZIER
#include"libOne.h"
#include"moveWithMouse.h"
VECTOR lerp(VECTOR& p0, VECTOR& p1, float t)
{
    return p0 + (p1 - p0) * t;
}
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
    addPointToMoveWithMouse(&p0);
    addPointToMoveWithMouse(&p1);
    addPointToMoveWithMouse(&p2);
    addPointToMoveWithMouse(&p3);
    //For animation
    float t = 0;
    float dt = 0.005f;
    const float DT = dt;
    //Animation Switch
    const int STATIC_CUBIC = 0;
    const int DYNAMIC_CUBIC = 1;
    const int STATIC_QUADRATIC = 2;
    const int DYNAMIC_QUADRATIC = 3;
    int sw = STATIC_CUBIC;
    bool advance = true;
    //Main Loop
    while (notQuit) {
        clear();

        movePointWithMouse();

        //Switch animation
        if (isTrigger(KEY_D)) { 
            ++sw %= 4; 
            t = 0;
        }
        if (isTrigger(KEY_A)) { 
            --sw; 
            if (sw < 0)sw = 3; 
        }
        if( sw == STATIC_CUBIC || 
            sw == STATIC_QUADRATIC) { 
            t = 1; 
        }
        if (sw == DYNAMIC_CUBIC || 
            sw == DYNAMIC_QUADRATIC) {
            if (isTrigger(KEY_S)) {
                advance = !advance;
            }
            if (advance) {
                t += dt;
                if (t < 0 || t > 1) {
                    dt = -dt;
                }
            }
        }
        //Bezier Curve
        VECTOR a = p0, b = p1, c = p2, d = p0, e = p1, p = p0;
        VECTOR sp = p0;//start position
        for (float tm = DT; tm <= t; tm += DT) {
            a = lerp(p0, p1, tm);
            b = lerp(p1, p2, tm);
            c = lerp(p2, p3, tm);
            d = lerp(a, b, tm);
            e = lerp(b, c, tm);
            p = lerp(d, e, tm);
            if (sw == DYNAMIC_QUADRATIC ||
                sw == STATIC_QUADRATIC) {
                rainbow.set(360 * tm, 100, 100, 20);
                line(a, b, rainbow, 1);
                line(b, c, rainbow, 1);
            }
            else if (sw == DYNAMIC_CUBIC||
                sw == STATIC_CUBIC){
                line(sp, p, yellow, 10);
            }
            sp = p;
        }
        //Bezier Points
        if (sw == DYNAMIC_CUBIC) {
            line(a, b, blue, 2);
            line(b, c, blue, 2);
            line(d, e, red, 2);
            circle(a, 14, black, blue, 6);
            circle(b, 14, black, blue, 6);
            circle(c, 14, black, blue, 6);
            circle(d, 14, black, red, 6);
            circle(e, 14, black, red, 6);
            circle(p, 14, black, yellow, 6);
        }
        //Points
        line(p0, p1, white, 1);
        line(p1, p2, white, 1);
        line(p2, p3, white, 1);
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
        circle(p2, 14, black, white, 6);
        circle(p3, 14, black, white, 6);

        fill(white);
        print("Push [d] to change scene.");
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
    COLOR white(0, 0, 100, 30);
    COLOR blue(220, 100, 100);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Points
    VECTOR p0(600, 500);
    VECTOR p1(933, 500);
    VECTOR p2(1266, 500);
    VECTOR p3(1600, 500);
    addPointToMoveWithMouse(&p0);
    addPointToMoveWithMouse(&p1);
    addPointToMoveWithMouse(&p2);
    addPointToMoveWithMouse(&p3);
    //tでキャラを動かす
    float t = 0;
    int img = loadImage("sukebo.png");
    //distでキャラを動かす
    std::vector<float> LUT;
    float dist = 0;
    int imgBlue = loadImage("sukeboBlue.png");
    //Main Loop
    while (notQuit) {
        movePointWithMouse();
        clear();
        //３次ベジェ曲線を描く
        {
            VECTOR sp = p0;
            VECTOR ep;
            float dt = 0.05f;
            float dist = 0;
            LUT.clear();
            LUT.push_back(dist);
            for (float t = dt; t < 1.00001f; t += dt) {
                ep = bezier(p0, p1, p2, p3, t);
                line(sp, ep, yellow, 5);
                point(sp, yellow, 15);
                //距離の累計をテーブルに保存
                dist += (sp - ep).mag();
                LUT.push_back(dist);
                fill(white); printPosX(200); print(dist);
                //終点をつぎの始点にする
                sp = ep;
            }
        }
        //distでキャラを動かす
        {
            float vel = 5;
            dist += vel;
            if (dist > LUT.back())dist = 0;
            float t = distToT(&LUT.front(), LUT.size(), dist);
            VECTOR p = bezier(p0, p1, p2, p3, t);
            VECTOR v = derivative(p0, p1, p2, p3, t);
            float angle = Atan2(v.y, v.x);
            image(imgBlue, p, angle, 1, CENTER);
        }
        //tでキャラを動かす
        {
            float dt = 0.005f;
            t += dt;
            if (dist==0)t = 0;//スタートをそろえる
            VECTOR p = bezier(p0, p1, p2, p3, t);
            VECTOR v = derivative(p0, p1, p2, p3, t);
            float angle = Atan2(v.y, v.x);
            arrow(p, p + v*0.1f, red, 5);
            image(img, p, angle, 1, CENTER);
        }
        //Points
        line(p0, p1, white, 1);
        line(p2, p3, white, 1);
        circle(p0, 14, black, white, 6);
        circle(p1, 14, black, white, 6);
        circle(p2, 14, black, white, 6);
        circle(p3, 14, black, white, 6);
    }
}
#endif