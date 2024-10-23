#include <stdio.h>
#include <assert.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define EXPORT_D2PTR_NAME_ADDRESS
struct NV {int addr;char *dll,*name;};
struct NV nvs[]={
#include "/d2hackmap/src/d2hackmap/d2ptrs.h"
#include "/d2hackmap/src/d2hackmap/d2ptrs2.h"
{0,0},
};
void exportCheatEngineTable() {
	FILE *fp=fopen("C:/Documents and Settings/abc/My Documents/My Cheat Tables/Game.CT","w+");assert(fp);
	fprintf(fp,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(fp,"<CheatTable CheatEngineTableVersion=\"31\">\n");
	fprintf(fp,"  <CheatEntries/>\n");
	fprintf(fp,"  <UserdefinedSymbols>\n");
	for (int i=0;nvs[i].addr;i++) {
		int addr=nvs[i].addr;
		char *name=nvs[i].name;
		fprintf(fp,"    <SymbolEntry>\n");
		fprintf(fp,"      <Name>%X %s_%s</Name>\n",addr,nvs[i].dll,name);
		fprintf(fp,"      <Address>0x%X</Address>\n",addr);
		fprintf(fp,"    </SymbolEntry>\n");
	}
	fprintf(fp,"  </UserdefinedSymbols>\n");
	fprintf(fp,"</CheatTable>\n");
	fclose(fp);
}

int main(int argc, char *argv[]) {
	exportCheatEngineTable();
	return 0;
}

