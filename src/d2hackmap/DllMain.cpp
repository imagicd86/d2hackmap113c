// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#define VARIABLE_DEFINE
#include "global.h"
#undef VARIABLE_DEFINE

HMODULE hInstDLL=NULL;
char szDllPath[MAX_PATH]={0};
char szPluginPath[MAX_PATH]={0};

void UnLoadExtInfo();
void ReleaseMem() {
	UnLoadExtInfo();
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
			hInstDLL = hModule;
			DisableThreadLibraryCalls(hInstDLL);
			dllHeap=HeapCreate(0,0,0);
			GetModuleFileName(hInstDLL,szDllPath,MAX_PATH);
			GetModuleFileName(hInstDLL,szPluginPath,MAX_PATH);
			char *end=strrchr(szPluginPath,'\\');
			if (!end) end=strrchr(szPluginPath,'/');
			if (end) {
				end[1]=0;
				if (end-szPluginPath>=7&&_memicmp(end-7,"runtime",7)==0) end[-7]=0;
			}
			return Install();
		}
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH: {
			ReleaseMem();
			if (!lpReserved) {
				Uninstall();
				if (gameHeap) {HeapDestroy(gameHeap);gameHeap=NULL;}
				if (confHeap) {HeapDestroy(confHeap);confHeap=NULL;}
				if (dllHeap) {HeapDestroy(dllHeap);dllHeap=NULL;}
			}
			if (logfp) {fclose(logfp);logfp=NULL;}
			break;
		}
	}
	return TRUE;
}


#define D2LOADER_PLUGIN

#ifdef D2LOADER_PLUGIN

extern "C" PVOID __stdcall QueryInterface() {//NOTE :- needs to be exported
	char filename[MAX_PATH];
	GetModuleFileName(hInstDLL, filename, MAX_PATH);
	LoadLibrary(filename);
	MessageBox(NULL,filename,"d2hackmap QueryInterface",MB_OK);
	return NULL;
}


#endif
