#include "stdafx.h"
#include "d2ptrs.h"
#include "multi.h"

int BackToTown();
int QuickNextGame(int addnum);
void SaveGameName();
int QuickExitGame();
int fCanExitGame=0,fBackToTown=0,nTownportalAlertNums=-1;
int fAutoNextGameName=0,fAutoNextGamePassword=0,fAutoNextGameDescription=0;
static int takeWPtoTownDis=6;
wchar_t	wszGameName[32]={0};
wchar_t wszGamePassword[32]={0};
wchar_t wszGameDescription[32]={0};
ToggleVar tBackToTown={TOGGLEVAR_DOWN,	0,	-1,		1,	"Quick Back Town",		&BackToTown};
ToggleVar tExitGame={TOGGLEVAR_DOWN,	0,	-1,	 1, 	"ExitGame",	&QuickExitGame, 0};
ToggleVar tQuickNextGame={TOGGLEVAR_DOWNPARAM,	0,	-1,	 1, "NextGame",	&QuickNextGame,	1};
ToggleVar tQuickNextGame2={TOGGLEVAR_DOWNPARAM,	0,	-1,	 1, "NextGame2",	&QuickNextGame,	2};
static ConfigVar aConfigVars[] = {
	{CONFIG_VAR_TYPE_KEY, "QuickBackToTownKey",   &tBackToTown		    	},
	{CONFIG_VAR_TYPE_INT, "TakeWaypointToTownDis",  &takeWPtoTownDis, 4    },
	{CONFIG_VAR_TYPE_INT, "TownportalNumsAlert",  &nTownportalAlertNums, 4    },
  {CONFIG_VAR_TYPE_KEY, "QuickExitGameKey",      &tExitGame              },
  {CONFIG_VAR_TYPE_KEY, "QuickNextGameKey",      &tQuickNextGame         },
  {CONFIG_VAR_TYPE_KEY, "QuickNextGameKey2",     &tQuickNextGame2        },
  {CONFIG_VAR_TYPE_INT, "AutoNextGameName",      &fAutoNextGameName  ,     4 },
  {CONFIG_VAR_TYPE_INT, "AutoNextGamePassword",  &fAutoNextGamePassword  , 4 },
  {CONFIG_VAR_TYPE_INT, "AutoNextGameDescription",  &fAutoNextGameDescription  , 4 },
  {CONFIG_VAR_TYPE_WSTR, "DefaultGameName",       &wszGameName,     1,  {32 }},
  {CONFIG_VAR_TYPE_WSTR, "DefaultGamePassword",   &wszGamePassword, 1,  {32 }},
  {CONFIG_VAR_TYPE_WSTR, "DefaultGameDescription",   &wszGameDescription, 1,  {32 }},
};
void quick_addConfigVars() {
	for (int i=0;i<_ARRAYSIZE(aConfigVars);i++) addConfigVar(&aConfigVars[i]);
}
void quick_NewGame() {
	SaveGameName();
	fCanExitGame = TRUE;
}
void quick_EndGame() {
	fCanExitGame = FALSE;
}
static int lastSkill=-1;
int skillCount(int skillid){
	if (PLAYER->pSkill){
		Skill *pSkill = PLAYER->pSkill->pFirstSkill;
		while(pSkill){
			if(pSkill->pSkillInfo->wSkillId == skillid){
				return pSkill->dwQuality;
			}
			pSkill= pSkill->pNextSkill;
		}
	}
	return 0;
}

int takeWaypointToTown(int maxdis);
int BackToTown() {
	if (fPlayerInTown) return 0;
	if (takeWPtoTownDis&&takeWaypointToTown(takeWPtoTownDis)) return 0;
	fBackToTown = TRUE;
	lastSkill=PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId;
	switchRightSkill(skillCount(219)>0?0xDB:0xDC);//use scroll first
	BYTE rightSkill[5] = {0x0C};
	*(short *)&rightSkill[1] = PLAYER->pMonPath->wTargetX;
	*(short *)&rightSkill[3] = PLAYER->pMonPath->wTargetY;
	SendPacket(rightSkill,sizeof(rightSkill));
	return 0;
}

extern int dwTeamMemberCount;
void __fastcall AutoBackToTown(BYTE *aPacket) {
	//LOG("QuickBackTown packet %02x\n",aPacket[0]);
	/*if (aPacket[0]==0x60) {
		LOG("QuickBackTown state=%d area=%d id=%d\n",
			aPacket[1],aPacket[2],*(int *)(aPacket+3));
	}
	*/
	if( aPacket[0]==0x60 && aPacket[1] == 0x00 ) //00�޶�ֻ����ͨ�����Ĵ�����
	{
		if ( fBackToTown ){
			fBackToTown = FALSE;
			int id=*(int*)&aPacket[3];// portal ID
			BYTE castMove[9] = {0x13};
			*(int*)&castMove[1] = 2;
			*(int*)&castMove[5] = id; 
			if (fWinActive&&dwTeamMemberCount) leader_click_object(UNITNO_OBJECT,id);
			SendPacket(castMove,sizeof(castMove));
		}

		if( nTownportalAlertNums!= (DWORD)-1 ){
			int srollcount = skillCount(220);
			if ( srollcount<= nTownportalAlertNums ){
				wchar_t temp[512];
				wsprintfW(temp,  L"<Hackmap>: Warning !! Only %d Townportals Left ", srollcount);
				d2client_ShowGameMessage(temp, 8);
			}
		}

		/*if (lastSkill != -1) {
			BYTE castTP1[9] = {0x3C};
			*(DWORD*)&castTP1[1] = lastSkill;
			*(DWORD*)&castTP1[5] = 0xFFFFFFFF;
			SendPacket(castTP1,sizeof(castTP1));
		}
		*/
	}
}


void __declspec(naked) RecvCommand_60_Patch_ASM() {
	__asm {
		//ecx = cmdbuf
		push ecx
		call AutoBackToTown;
		pop ecx
		pop edx //ret code
//org:
		sub esp, 8
		mov eax, dword ptr [ecx]
		jmp edx
	}
}
void SaveGameName() {
	if(GAMEINFO->szGameName[0]) {
		int n=MultiByteToWideChar(CP_ACP, 0, GAMEINFO->szGameName, -1, wszGameName, 32);
		wchar_t *dst=wszGamePassword;
		char *src=GAMEINFO->szGamePassword;
		do {*dst++=*src++;} while (*src);
		MultiByteToWideChar(CP_ACP, 0, GAMEINFO->szGameDescription, -1, wszGameDescription, 32);
	}
}
int QuickExitGame(){
	if (fCanExitGame==FALSE) return -1;
	fCanExitGame = FALSE;
	ExitGame();
	return 0;
}

int QuickNextGame(int addnum) {	
	if (fCanExitGame==FALSE) return -1;
	fCanExitGame = FALSE;
	SaveGameName();
	wchar_t *s = wszGameName;
	wchar_t *endptr;
	int len=wcslen(wszGameName);
	int end=0;
	for (int i=len-1;i>=0;i--) {
		wchar_t c=wszGameName[i];
		if ('0'<=c&&c<='9') {end=i+1;break;}
	}
	if (end) {
		wchar_t fmt[8],buf[32];
		int start=end-1;
		for (int i=start-1;i>=0;i--) {
			wchar_t c=wszGameName[i];
			if ('0'<=c&&c<='9') start=i;else break;
		}
		fmt[0]='%';fmt[1]='0';
		wsprintfW(fmt+2, L"%dd%%s",end-start);
		wcscpy(buf,wszGameName+end);
		long n = wcstol(wszGameName+start, &endptr, 10);
		wsprintfW(wszGameName+start, fmt, n+addnum,buf);
	} else {
		wszGameName[len]='1';
		wszGameName[len+1]=0;
	}
	ExitGame();
	return 0;
}

void __fastcall NextGameNamePatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,int,char*)) {
	if (fAutoNextGameName) {
		d2win_SetEditBoxText(box, wszGameName);
		d2win_SelectEditBoxText(box);
	}
	// original code
	d2win_SetEditBoxProc(box, FunCallBack);
}
void __fastcall NextGamePasswordPatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,int,char*)) {
	if (fAutoNextGamePassword) {
		d2win_SetEditBoxText(box, wszGamePassword);
		d2win_SelectEditBoxText(box);
	}
	// original code
	d2win_SetEditBoxProc(box, FunCallBack);
}
void __fastcall NextGameDecriptionPatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,int,char*)) {
	if (fAutoNextGameDescription) {
		d2win_SetEditBoxText(box, wszGameDescription);
		d2win_SelectEditBoxText(box);
	}
	// original code
	d2win_SetEditBoxProc(box, FunCallBack);
}
void *__fastcall SelectGamePatch(D2EditBox* box, wchar_t* wcszTxt) {
	if (!fInGame&&box) {
		D2EditBox *next=box->pNext2;
		if (next&&next->pNext2==box&&box->dwPosY==148&&next->dwPosY==148
			&&box->dwPosX==432&&next->dwPosX==606) {
			d2win_SetEditBoxText(next, L"");
		}
	}
	if (wcszTxt[1]==':') wcszTxt+=2;
	// original code
	return d2win_SetEditBoxText(box, wcszTxt);
}

