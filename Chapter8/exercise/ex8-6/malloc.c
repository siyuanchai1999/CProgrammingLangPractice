#define NALLOC 8
#include <unistd.h>
typedef long Align;

union header{
	struct{
		union header *ptr;
		unsigned size;
	}s;
	Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;

void FREE(void *ap){
	Header *bp,*p;
	bp = (Header *) ap - 1;
	for(p = freep; !(bp > p && bp <p->s.ptr); p = p->s.ptr){
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr)){
			break;		//freed block at the end
		}
	}
	
	if(bp + bp->s.size == p->s.ptr){
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}else{
		bp->s.ptr = p->s.ptr;
	}
	if(p + p->s.size == bp){
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}else{
		p->s.ptr = bp;
	}
	freep = p;
}

static Header *MORECORE(unsigned nu){
	nu = (nu < NALLOC) ? NALLOC : nu;
	Header *up;
	char *cp;
	cp = sbrk(nu * sizeof(Header));
	if(cp == (char *) -1){
		return NULL;
	}
	up = (Header *) cp;
	up->s.size = nu;
	FREE((void *)(up + 1));
	return freep;	
}

void *MALLOC(unsigned nbytes){
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	nunits = (nbytes + sizeof(Header) - 1) /sizeof(Header) + 1;

	if( (prevp = freep) == NULL){
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr){
		if(p->s.size >= nunits){
			if(p->s.size == nunits){
				prevp->s.ptr = p->s.ptr;	//cut the cycle
			}else{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p+1);
		}
		if(p == freep){
			if((p = MORECORE(nunits)) == NULL){
				return NULL;
			}
		}
	
	}
}

#include <stdio.h>
#include <string.h>
#include <stdint.h>

void printx(int cnt){
	while(cnt-- > 0){
		printf("x");
	}
}

void visualize(){
	Header *p = &base;

	do{
		printf("%ld: size = %d bytes" ,(uintptr_t)p,p->s.size);
		printx((p->s.size + 7) /8 );
		printf("\n");
		//p = p->s.ptr;
	}while(p < p->s.ptr && (p = p->s.ptr));

}

int main(){
	char *x = (char *) MALLOC(15);
	strcpy(x,"hello world\n");
	printf("x = %s",x);
	char *z = (char *) MALLOC(512);
	char *y = (char *) MALLOC(128);
	char *p = (char *) MALLOC(2048*sizeof(Header));
	visualize();
}
