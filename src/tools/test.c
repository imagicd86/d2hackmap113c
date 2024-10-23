//#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

char *load(char *path,int *psize) {
	FILE *fp=fopen(path,"rb");assert(fp);
	fseek(fp,0,2);int size=ftell(fp);*psize=size;
	char *p=malloc(size+1);p[size]=0;fseek(fp,0,0);
	int n=fread(p,1,size,fp);assert(n==size);fclose(fp);
	return p;
}
void save(char *path,char *buf,int size) {
	FILE *fp=fopen(path,"wb+");assert(fp);
	int n=fwrite(buf,1,size,fp);assert(n==size);fclose(fp);
}
int main(int argc, char* argv[]) {
	
	return;
}
