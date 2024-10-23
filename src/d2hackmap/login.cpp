#include "stdafx.h"
#include "d2ptrs.h"
#include "d2ptrs2.h"

struct LoginInfo {int key;char *name,*pass;struct LoginInfo *next;};
static LoginInfo *accountInfos=NULL;
static LoginInfo *lastAccount=NULL;
int inputUserPassword(LoginInfo *pai);
int dwAutoLoginMs=0;
int lastSelectedCharacterIndex=0;

void login_initConfigVars() {
	accountInfos=NULL;
}
void addAccount(int key,char *name,char *pass) {
	for (LoginInfo *p=accountInfos;p;p=p->next) {
		if (p->key==key) {
			p->name=heap_strdup(confHeap,name);
			p->pass=heap_strdup(confHeap,pass);
			return;
		}
	}
	LoginInfo *pai=(LoginInfo *)HeapAlloc(confHeap,0,sizeof(LoginInfo));
	pai->key=key;pai->name=heap_strdup(confHeap,name);pai->pass=heap_strdup(confHeap,pass);
	pai->next=accountInfos;accountInfos=pai;
	ToggleVar *ptv=addExtraKey(key);if (!ptv) {LOG("ERROR: too many keys\n");return;}
	ptv->type=TOGGLEVAR_DOWNPTR;ptv->key=key;
	ptv->paramPtr=pai;ptv->keyType=1;
	ptv->func=inputUserPassword;ptv->funcUp=NULL;
	ptv->desc="Account";
}
int isLoginScreen() {
	if (fInGame) return 0;
	D2EditBox *focus=(*d2win_pFocusedControl);
	if (!focus) return 0;
	D2EditBox *next=focus->pNext2;
	if (!next) return 0;
	if (next->pNext2!=focus) return 0;
	D2EditBox *nameBox,*passBox;
	if (focus->dwPosY<next->dwPosY) {nameBox=focus;passBox=next;}
	else {nameBox=next;passBox=focus;}
	if (nameBox->dwPosY!=342) return 0;
	if (passBox->dwPosY!=396) return 0;
	return 1;
}
static void c2w(char *p,wchar_t *w) {
	while (1) {*w=(*p)&0xFF;if (!*p) break;w++;p++;}
}
int inputUserPassword(LoginInfo *pai) {
	char *name=pai->name;char *password=pai->pass;
	if (!name) return -1;if (!password) password="";
	wchar_t wb[64]={0};
	D2EditBox *focus=(*d2win_pFocusedControl);
	if (!focus) return -1;
	D2EditBox *next=focus->pNext2;
	if (!next) return -1;
	if (next->pNext2!=focus) return -1;
	D2EditBox *nameBox,*passBox;
	if (focus->dwPosY<next->dwPosY) {nameBox=focus;passBox=next;}
	else {nameBox=next;passBox=focus;}
	if (nameBox->dwPosY!=342) return -1;
	if (passBox->dwPosY!=396) return -1;
	c2w(password,wb);d2win_SetEditBoxText(passBox,wb);
	c2w(name,wb);d2win_SetEditBoxText(nameBox,wb);
	lastAccount=pai;
	return 0;
}
void autoLogin() {
	if (!lastAccount) return;
	inputUserPassword(lastAccount);
}
/*
6FA59524 - 68 00040000           - push 00000400 { 1024 }
6FA59529 - 8D 54 24 10           - lea edx,[esp+10]
6FA5952D - 52                    - push edx //buf
6FA5952E - 53                    - push ebx
6FA5952F - 68 B4E0A56F           - push 6FA5E0B4 { ("Last BNet") }
6FA59534 - 68 04E2A56F           - push 6FA5E204 { ("Diablo II") }
6FA59539 - E8 1602FFFF           - call 6FA49754 { ->->6FC2C2B0 storm_regQueryValue } <---------------
6FA5953E - 85 C0                 - test eax,eax
*/
int __stdcall LastBNet_Patch(char *keyName,char *valueName,int arg,char *buf,int len) {
	if (lastAccount) dwAutoLoginMs=dwCurMs+300;
	int ret=storm_regQueryValue(keyName,valueName,arg,buf,len);
	return ret;
}
static void initSelectChar() {
	LOG("Enter char selection %x\n",*d2launch_pD2Characters);
	//for (D2Character *p=*d2launch_pD2Characters;p;p=p->next) LOG("Char: %s\n",p->name);
	*d2launch_pSelectedCharIndex=0;
}
// 6FA4D19B - 89 1D B04DA66F        - mov [6FA64DB0],ebx { (2) } <------------SelectedCharIndex
void __declspec(naked) InitSelectCharPatch_ASM() {
	__asm {
		pushad
		call initSelectChar
		popad
		ret 
	}
}

// 6FA4E1B1 - A3 B04DA66F           - mov [6FA64DB0],eax { (2) }
void __declspec(naked) SelectCharPatch_ASM() {
	__asm {
		push ebx
		mov lastSelectedCharacterIndex,eax
		mov ebx,d2launch_pSelectedCharIndex
		mov dword ptr [ebx],eax
		pop ebx
		ret 
	}
}
