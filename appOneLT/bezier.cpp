#include"mathUtil.h"
#include"bezier.h"
VECTOR lenear(VECTOR& p0, VECTOR& p1, float t)
{
	return (1 - t) * p0 + t * p1;
}
VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t)
{
	float omt = 1 - t;//one minus t
	return
		omt * omt * p0 +
		2 * omt * t * p1 +
		t * t * p2;
}
VECTOR derivative(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t)
{
	return	2 * (1-t) * (p1 - p0) + 2 * t * (p2 - p1);
}
VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t)
{
	float omt = 1 - t;//one minus t
	return
		omt * omt * omt * p0 +
		3 * omt * omt * t * p1 +
		3 * omt * t * t * p2 +
		t * t * t * p3;
}
VECTOR derivative(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t)
{
	float omt = 1 - t;
	return
		3 * omt * omt * (p1 - p0) +
		6 * omt * t * (p2 - p1) +
		3 * t * t * (p3 - p2);
}
//ãóó£Ç©ÇÁãﬂéóÇÃÇîÇãÅÇﬂÇÈ
float distToT(
	float* LUT, //LUT Look Up Table
	int LUTlength,
	float dist)
{
	float arcLength = LUT[LUTlength - 1];
	int n = LUTlength;
	if (0 <= dist && dist <= arcLength) {
		for (int i = 0; i < n; i++) {
			if (LUT[i] <= dist && dist <= LUT[i + 1]) {
				return Map(dist,
					LUT[i], LUT[i + 1],
					i / (n - 1.0f), (i + 1) / (n - 1.0f));
			}
		}
	}
}