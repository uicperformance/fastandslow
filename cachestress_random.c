#include<stdint.h>
#include<stddef.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>

char *buf;

const uint64_t SAMPLES = 100000000;
volatile uint64_t global_offset = 0;

int main(int argc, char** argv) {
	if(argc<2) {
		fprintf(stderr, "Usage: cachestress [-s size] [-i interval]>\n");
		exit(1);
	}

	uint64_t size=(1l<<30);
	uint64_t interval=1;

	char ch;
	while((ch=getopt(argc,argv,"s:i:")) != -1) {
		int signedsize, signedinterval;
		switch(ch) {
		case 's':
			signedsize=atoi(optarg);
			if(size<64) {
				fprintf(stderr,"Size must be >=64\n");
				exit(1);
			}
			size=signedsize;
			if((size & (size-1)) > 0 ) {
				fprintf(stderr,"Size must a power of 2\n");
				exit(1);
			}
			break;
		case 'i': 
      signedinterval=atoi(optarg);
			if(interval < 1) {
				fprintf(stderr,"Interval must be >0\n");
				exit(1);
			}
			interval = signedinterval;
			break;		
		}
	}
	
	buf = calloc(1,size);
	memset(buf,0,size);
	if(!buf) perror("malloc failed");

	struct timeval before;
	gettimeofday(&before,0);	
	uint64_t offset=0;	
	for(uint64_t i=0;i<SAMPLES;i++) {
		offset=(offset+buf[offset]*43298737+interval) & (size-1);
	}

	struct timeval after;
	gettimeofday(&after,0);

	printf("%ld %ld %.1f ns/op\n",size,interval,1000.0*((after.tv_sec-before.tv_sec)*1000000+(after.tv_usec-before.tv_usec))/(1.0*SAMPLES));

	global_offset=offset; // this is to force the compiler to actually compute offset

}
