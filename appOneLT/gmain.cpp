#include"graph.h"
#include"mouseGrab.h"
#include"libOne.h"

VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t) 
{
	VECTOR p = 
		Pow((1 - t), 3)* p0 + 
		3 * t * Pow((1 - t), 2) * p1 + 
		3 * t * t * (1 - t) * p2 + 
		t * t * t * p3;
	return p;
}

VECTOR lerp(VECTOR& p0, VECTOR& p1, float t) 
{
	return p0 + (p1 - p0) * t;
}

COLOR black(0, 0, 0);
COLOR white(0, 0, 80);
COLOR blue(205, 100, 100);
COLOR red(328, 100, 100);
COLOR yellow(65, 100, 80);

void threePoints(VECTOR& p0, VECTOR& p1, VECTOR& p2) 
{
	line(p0, p1, white, 3);
	line(p1, p2, white, 3);
	circle(p0, 15, black, white, 6);
	circle(p1, 15, black, white, 6);
	circle(p2, 15, black, white, 6);
}
void quadraticLine(VECTOR& p0, VECTOR& p1, VECTOR&p2, float t) 
{
	VECTOR a, b, start = p0, end;
	float dt = 0.01f;
	for (float tm = dt; tm < t; tm += dt) {
		a = lerp(p0, p1, tm);
		b = lerp(p1, p2, tm);
		end = lerp(a, b, tm);
		line(start, end, red, 5);
		start = end;
	}
}
void quadraticPoint(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t) 
{
	VECTOR a, b, p;
	a = lerp(p0, p1, t);
	b = lerp(p1, p2, t);
	p = lerp(a, b, t);

	line(a, b, blue, 3);
	circle(a, 15, black, blue, 6);
	circle(b, 15, black, blue, 6);

	circle(p, 15, black, red, 6);
}
void oneRainbow(VECTOR& p0, VECTOR& p1, VECTOR& p2) 
{
	float dt = 0.05f;
	for (float tm = 0; tm <= 1.000001; tm += dt) {
		VECTOR a = lerp(p0, p1, tm);
		VECTOR b = lerp(p1, p2, tm);
		COLOR color(360 * tm, 100, 100, 90);
		line(a, b, color, 1);
	}
}

void fourPoints(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3)
{
	line(p0, p1, white, 3);
	line(p1, p2, white, 3);
	line(p2, p3, white, 3);
	circle(p0, 15, black, white, 6);
	circle(p1, 15, black, white, 6);
	circle(p2, 15, black, white, 6);
	circle(p3, 15, black, white, 6);
}
void cubicLine(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t) 
{
	VECTOR a, b, c, d, e, start=p0, end;
	float dt = 0.01f;
	for (float tm = dt; tm < t; tm += dt) {
		a = lerp(p0, p1, tm);
		b = lerp(p1, p2, tm);
		c = lerp(p2, p3, tm);

		d = lerp(a, b, tm);
		e = lerp(b, c, tm);

		end = lerp(d, e, tm);

		line(start, end, yellow, 5);
		start = end;
	}
}
void cubicPoint(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t) 
{
	VECTOR a, b, c, d, e, p;
	a = lerp(p0, p1, t);
	b = lerp(p1, p2, t);
	c = lerp(p2, p3, t);

	d = lerp(a, b, t);
	e = lerp(b, c, t);
	
	p = lerp(d, e, t);

	line(a, b, blue, 3);
	line(b, c, blue, 3);
	circle(a, 15, black, blue, 6);
	circle(b, 15, black, blue, 6);
	circle(c, 15, black, blue, 6);

	line(d, e, red, 3);
	circle(d, 15, black, red, 6);
	circle(e, 15, black, red, 6);

	circle(p, 15, black, yellow, 6);
}
void twoRainbow(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3 )
{
	float dt = 0.01f;
	for (float tm = 0; tm <= 1.000001; tm += dt) {
		VECTOR a = lerp(p0, p1, tm);
		VECTOR b = lerp(p1, p2, tm);
		VECTOR c = lerp(p2, p3, tm);
		COLOR color(360 * tm, 100, 100, 30);
		line(a, b, color, 1);
		line(b, c, color, 1);
	}
}

void gmain()
{
	window(1920, 1080, full);
	colorMode(HSV,100);
	angleMode(DEGREES);

	VECTOR p0, p1, p2, p3;
	p0.set(width / 5 * 1, height / 8 * 7);
	p1.set(width / 5 * 2, height / 8);
	p2.set(width / 5 * 3, height / 8 * 7);
	p3.set(width / 5 * 4, height / 8);

	VECTOR p4, p5, p6;
	p4.set(100, 600);
	p5.set(200, 200);
	p6.set(300, 600);

	addPoint(&p0);
	addPoint(&p1);
	addPoint(&p2);
	addPoint(&p3);
	addPoint(&p4);
	addPoint(&p5);
	addPoint(&p6);

	float t = 0;
	bool active = true;
	
	while (notQuit)
	{
		clear();

		if (isTrigger(KEY_Z)) {
			active = !active;
		}
		if (active) {
			t += 0.005f;
			if (t > 1) {
				t = 0;
			}
		}
		else if(isTrigger(KEY_X)) {
			t = 1;
		}

		mouseGrab();

		//3次ベジエ CubicBezier
		twoRainbow(p0, p1, p2, p3);
		cubicLine(p0, p1, p2, p3, t);
		fourPoints(p0, p1, p2, p3);
		if (t != 1) {
			cubicPoint(p0, p1, p2, p3, t);
		}

		//２次ベジエ QuadraticBezier
		oneRainbow(p4, p5, p6);
		quadraticLine(p4, p5, p6, t);
		threePoints(p4, p5, p6);
		if (t != 1) {
			quadraticPoint(p4, p5, p6, t);
		}
	}
}
