#include<vector>
#include"graph.h"
#include"libOne.h"
VECTOR lerp(VECTOR& p0, VECTOR& p1, float t) {
	return p0 + (p1 - p0) * t;
}
int Sw = 0;
VECTOR quadratic(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t) {
	VECTOR v1 = lerp(p0, p1, t);
	VECTOR v2 = lerp(p1, p2, t);
	if (Sw==2) {
		strokeWeight(3);
		stroke(360 * t, 100, 100);
		line(v1.x, v1.y, v2.x, v2.y);
	}
	return lerp(v1, v2, t);
}
VECTOR cube(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t) {
	VECTOR v1 = quadratic(p0, p1, p2, t);
	VECTOR v2 = quadratic(p1, p2, p3, t);
	if (Sw == 3) {
		strokeWeight(3);
		stroke(360 * t, 100, 100);
		line(v1.x, v1.y, v2.x, v2.y);
	}
	return lerp(v1, v2, t);

}
VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t) {
	VECTOR v = 
		pow((1 - t), 3)* p0 + 
		3 * t * pow((1 - t), 2) * p1 + 
		3 * t * t * (1 - t) * p2 + 
		t * t * t * p3;
	return v;
}

COLOR black(0, 0, 0);
COLOR white(0, 0, 80);
COLOR blue(205, 100, 100);
COLOR red(328, 100, 100);
COLOR yellow(65, 100, 80);

void quadraticLine(VECTOR& p0, VECTOR& p1, VECTOR&p2, float t) {
	VECTOR a, b, start = p0, end;
	float dt = 0.01f;
	for (float tm = dt; tm < t - dt; tm += dt) {
		a = lerp(p0, p1, tm);
		b = lerp(p1, p2, tm);
		end = lerp(a, b, tm);
		line(start, end, red, 5);
		start = end;
	}
}
void quadraticPoint(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t) {
	VECTOR a, b, p;
	a = lerp(p0, p1, t);
	b = lerp(p1, p2, t);
	p = lerp(a, b, t);

	line(a, b, blue, 3);
	circle(a, 15, black, blue, 6);
	circle(b, 15, black, blue, 6);

	circle(p, 15, black, red, 6);
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

	//マウスで点をつかむためのデータ
	VECTOR mouse;
	VECTOR* points[] = { &p0, &p1, &p2, &p3 };
	int numPoints = sizeof(points) / sizeof(points[0]);
	VECTOR* grabPoint = nullptr;
	float grabRadiusSq = Pow(7, 2);

	float t = 0;

	bool active = true;
	while (notQuit)
	{
		clear();

		//マウスで点をつかんで移動する
		{
			mouse.set(mouseX, mouseY);
			if (isPress(MOUSE_LBUTTON)) {
				if (grabPoint == nullptr) {
					//つかむ
					for (int i = 0; i < numPoints; i++) {
						if ((*points[i] - mouse).magSq() <= grabRadiusSq) {
							grabPoint = points[i];
						}
					}
				}
				else {
					//移動
					*grabPoint = mouse;
				}
			}
			else {
				grabPoint = nullptr;
			}
		}

		if (isTrigger(KEY_Z)) {
			active = !active;
		}
		if (active) {
			t += 0.005f;
			if (t > 1) {
				t = 0;
			}
		}
		if (isTrigger(KEY_X)) {
			t = 1;
		}

		{
			float dt = 0.01f;
			for (float tm = 0; tm <= 1.000001; tm += dt) {
				VECTOR a = lerp(p0, p1, tm);
				VECTOR b = lerp(p1, p2, tm);
				VECTOR c = lerp(p2, p3, tm);
				COLOR color(360 * tm, 100, 100, 20);
				line(a, b, color, 1);
				line(b, c, color, 1);
			}
		}

		{
			VECTOR start = p0;
			float dt = 0.001f;
			for (float tm = dt; tm < t - dt; tm += dt) {
				VECTOR end = bezier(p0, p1, p2, p3, tm);
				line(start, end, yellow, 5);
				start = end;
			}
		}

		{
			line(p0, p1, white, 3);
			line(p1, p2, white, 3);
			line(p2, p3, white, 3);
			circle(p0, 15, black, white, 6);
			circle(p1, 15, black, white, 6);
			circle(p2, 15, black, white, 6);
			circle(p3, 15, black, white, 6);
		}
		/*
		{
			if (t != 1) {
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
		}
		*/

		{
			//２次元ベジエ
			quadraticLine(p0, p1, p2, t);
			//VECTOR a, b, start=p0, end;
			//float dt = 0.01f;
			//for (float tm = dt; tm < t - dt; tm += dt) {
			//	a = lerp(p0, p1, tm);
			//	b = lerp(p1, p2, tm);
			//	end = lerp(a, b, tm);
			//	line(start, end, red, 5);
			//	start = end;
			//}

			if (t != 1) {
				
				quadraticPoint(p0, p1, p2, t);
				//VECTOR a, b, p;
				//a = lerp(p0, p1, t);
				//b = lerp(p1, p2, t);
				//p = lerp(a, b, t);

				//line(a, b, blue, 3);
				//circle(a, 15, black, blue, 6);
				//circle(b, 15, black, blue, 6);

				//circle(p, 15, black, red, 6);
			}
		}

	}
}
