#include <stdio.h>
#include "structBasics.c"

#define min(a,b) ( (a)<(b) ? (a): (b))
#define max(a,b) ( (a)>(b) ? (a): (b))
struct point makepoint(int x, int y){
	struct point temp = {x,y};
	return temp;
}

int ptinrect(struct point p, struct rect r){
	return (p.x >= r.p1.x && p.x <= r.p2.x) && (p.y >= r.p1.y && p.y <= r.p2.y);
}

struct rect conicalize(struct rect r){
	/* not doable because r.p1.x and r.p2.y have already been changed !!!
	r.p1.x = min(r.p1.x, r.p2.x);
	r.p1.y = min(r.p1.y, r.p2.y);
	
	r.p2.x = max(r.p1.x, r.p2.x); 
	r.p2.y = max(r.p1.y, r.p2.y);
	int m;
	*/
	
	///correct version on book 
	struct rect temp;
	temp.p1.x = min(r.p1.x, r.p2.x);
	temp.p2.x = max(r.p1.x, r.p2.x);
	temp.p1.y = min(r.p1.y, r.p2.y);
	temp.p2.y = max(r.p1.y, r.p2.y);
	return temp;
}

void showRect(struct rect r){
	printf("[ ");
	showPoint(r.p1);
	printf(", ");
	showPoint(r.p2);
	printf(" ]\n");
}

int main(){
	struct point p1 = makepoint(3,4);
	struct point p2 = makepoint(0,0);
	struct rect  r  = {p1, p2};
	showRect(r);
	r =	conicalize(r);
	showRect(r);
	struct rect *x = &r;
	showPoint(x -> p2);
}
