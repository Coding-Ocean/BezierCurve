#include"graph.h"
void point(const VECTOR& p,const COLOR& c, float strkWeight)
{
	stroke(c);
	strokeWeight(strkWeight);
	point(p.x, p.y);
}

void circle(const VECTOR& p, float diameter, const COLOR& fc, const COLOR& sc, float strkWeight)
{
	fill(fc);
	stroke(sc);
	strokeWeight(strkWeight);
	circle(p.x, p.y, diameter);
}


void line(const VECTOR& p1, const VECTOR& p2, const COLOR& c, float strkWeight)
{
	stroke(c);
	strokeWeight(strkWeight);
	line(p1.x, p1.y, p2.x, p2.y);
}