#include<vector>
#include"input.h"
#include"VECTOR.h"
#include"mathUtil.h"
#include"mouseGrab.h"

//マウスで点をつかむためのデータ
VECTOR mouse;
std::vector<VECTOR*> points;
VECTOR* grabPoint = nullptr;
float grabRadiusSq = Pow(7, 2);

void addPoint(VECTOR* p)
{
	points.push_back(p);
}

//マウスで点をつかんで移動する
void mouseGrab()
{
	mouse.set(mouseX, mouseY);
	if (isPress(MOUSE_LBUTTON)) {
		if (grabPoint == nullptr) {
			//つかむ
			for (int i = 0; i < points.size(); i++) {
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
