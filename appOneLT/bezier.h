#pragma once
#include"VECTOR.h"
VECTOR lenear(VECTOR& p0, VECTOR& p1, float t);
VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t);
VECTOR derivative(VECTOR& p0, VECTOR& p1, VECTOR& p2, float t);
VECTOR bezier(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t);
VECTOR derivative(VECTOR& p0, VECTOR& p1, VECTOR& p2, VECTOR& p3, float t);
float distToT(
	float* LUT, //LUT Look Up Table
	int LUTlength,
	float dist);