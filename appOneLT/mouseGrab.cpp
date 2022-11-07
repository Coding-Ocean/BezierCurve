#include<vector>
#include"input.h"
#include"VECTOR.h"
#include"mathUtil.h"
#include"mouseGrab.h"

//�}�E�X�œ_�����ނ��߂̃f�[�^
VECTOR mouse;
std::vector<VECTOR*> points;
VECTOR* grabPoint = nullptr;
float grabRadiusSq = Pow(7, 2);

void addPoint(VECTOR* p)
{
	points.push_back(p);
}

//�}�E�X�œ_������ňړ�����
void mouseGrab()
{
	mouse.set(mouseX, mouseY);
	if (isPress(MOUSE_LBUTTON)) {
		if (grabPoint == nullptr) {
			//����
			for (int i = 0; i < points.size(); i++) {
				if ((*points[i] - mouse).magSq() <= grabRadiusSq) {
					grabPoint = points[i];
				}
			}
		}
		else {
			//�ړ�
			*grabPoint = mouse;
		}
	}
	else {
		grabPoint = nullptr;
	}
}
