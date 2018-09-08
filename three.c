#include<stdio.h>

volatile int count=1;

int main(int argc, char** argv) {
	for(int i=0;i<1000000000;i++) {
		count++;
	}
}
