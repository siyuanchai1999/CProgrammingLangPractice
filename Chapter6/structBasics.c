#include <stdio.h>
#include <math.h>
struct point{
	int x;
	int y;
};

struct rect{
	struct point p1;
	struct point p2;
};

void showPoint(struct point p){
	printf("(%d, %d)",p.x, p.y);
}

int computeLen(struct rect r){
	return sqrt((double)((r.p1.x - r.p2.x) * (r.p1.x - r.p2.x) )+ (double)((r.p1.y - r.p2.y) *(r.p1.y - r.p2.y)));
}

