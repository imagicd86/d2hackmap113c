#include "stdafx.h"
#include "d2ptrs.h"

ToggleVar 	tDropProtectionToggle={				TOGGLEVAR_ONOFF,	0,	-1,	1,  "Drop Protection" };
ToggleVar 	tResetProtectionToggle={				TOGGLEVAR_ONOFF,	0,	-1,	1,  "Reset Protection" };
char 			aDropProtectRune[34]	={0};
char 			aDropProtectRuneword[256]	={0};
char 			aDropProtectUnique[512]	={0};
char 			aDropProtectSet[256]	={0};
static ConfigVar aConfigVars[] = {
	{CONFIG_VAR_TYPE_KEY, "DropProtectionToggle",          &tDropProtectionToggle         },
	{CONFIG_VAR_TYPE_KEY, "ResetProtectionToggle",          &tResetProtectionToggle         },
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "DropProtectionRune",       &aDropProtectRune,       1, {34}},
  {CONFIG_VAR_TYPE_CHAR_ARRAY0, "DropProtectionRuneword",       &aDropProtectRuneword,       1, {256}},
  {CONFIG_VAR_TYPE_CHAR_ARRAY0, "DropProtectionUnique",       &aDropProtectUnique,       1, {512}},
  {CONFIG_VAR_TYPE_CHAR_ARRAY0, "DropProtectionSet",       &aDropProtectSet,       1, {256}},
};
void DropProtection_addConfigVars() {
	for (int i=0;i<_ARRAYSIZE(aConfigVars);i++) addConfigVar(&aConfigVars[i]);
}
void DropProtection_initConfigVars() {
  memset(aDropProtectRune ,    0 ,      sizeof(aDropProtectRune) );
  memset(aDropProtectRuneword ,    0 ,      sizeof(aDropProtectRuneword) );
  memset(aDropProtectUnique ,    0 ,      sizeof(aDropProtectUnique) );
  memset(aDropProtectSet ,    0 ,      sizeof(aDropProtectSet) );
}

static int hasProp(UnitAny *pUnit,int prop,int ge) {
	if (!pUnit) return 0;
	StatList *plist=pUnit->pStatList;
	if (!plist) return 0;
	Stat *stat;
	if (plist->dwListFlag&0x80000000) stat=&plist->sFullStat;
	else stat=&plist->sBaseStat;
	if (!stat||!stat->pStats) return 0;
	int n=stat->wStats;if (n>511) return 0;
	StatEx *se=stat->pStats;
	if (!se||IsBadReadPtr(se,n*8)) return 0;
	int last=-1;
	for (int i=0;i<n;i++) {
		int id=se[i].wStatId;
		if (id<last) return 0; //invalid list
		last=id;
		int value=se[i].dwStatValue;
		int value2=se[i].wParam;
		if (id==prop) {
			if (value>=ge) return 1;
		}
	}
	return 0;
}
int DropProtection(UnitAny *pUnit) {
	if (pUnit->dwUnitType!=UNITNO_ITEM) return 0;
	DWORD dwQuality = pUnit->pItemData->dwQuality;
	int id,value;
	switch (dwQuality) {
		case ITEM_QUALITY_UNIQUE:
			id = d2common_GetItemFileIndex(pUnit);
			//LOG("drop unique %d\n",id);
			value=aDropProtectUnique[id];
			if (value) return 1;
			break;
		case ITEM_QUALITY_SET:
			id = d2common_GetItemFileIndex(pUnit);
			//LOG("drop set %d\n",id);
			value=aDropProtectSet[id];
			if (value) return 1;
			break;
		default:
			if (d2common_CheckItemFlag(pUnit, ITEMFLAG_RUNEWORD, 0, "?")){
				id = d2common_GetRuneWordTxtIndex( pUnit->pItemData->wMagicPrefix[0] );
				value=aDropProtectRuneword[id];
				if (id==49) {
					int fcr = d2common_GetUnitStat(pUnit, STAT_FCR, 0);
					if (value&&fcr>=value) return 1;
				} else {
					if (value) return 1;
				}
			} else {
				int index = GetItemIndex(pUnit->dwTxtFileNo)+1;
				//LOG("drop %d\n",index);
				if (2103<=index&&index<=2135) { //rune
					if (aDropProtectRune[index-2103]) return 1;
				} else if (index==2098) { //grand charm
					if (hasProp(pUnit,188,1)) return 1; //+1 skill
				}
			}
	}
	if (pUnit->pInventory&&pUnit->pInventory->dwFilledSockets) {
		for (UnitAny *pItem=pUnit->pInventory->pFirstItem;pItem;pItem=d2common_GetNextItemInInv(pItem)) {
			if (DropProtection(pItem)) return 1;
		}
	}
	return 0;
}
int DropProtectionPacketSendCheck(int id) {
	UnitAny *pItem=PLAYER->pInventory->pCursorItem;
	if (!pItem||pItem->dwUnitId!=id) return 0;
	if (!tDropProtectionToggle.isOn) return 0;
	int protect=DropProtection(pItem);
	if (protect) {
		d2client_ShowGameMessage(L"ERROR: Drop Protection intercept drop command", 1);
	}
	return protect;
}
int canHireMerc() {
	wchar_t wszbuf[256];char keyname[256];wszbuf[0]=0;
	if (!(EXPANSION)) return 1;
	if (*d2client_pMercData16 != 0xFFFF) {
		formatKey(keyname,tDropProtectionToggle.key);
		wsprintfW(wszbuf, L"Drop Protection, can't hire if merc is dead, (use %hs to unlock)",keyname);
	} else {
		UnitAny *m=GetUnitPet(PLAYER);if (!m) return 1;
		int n=0;
		for (UnitAny *pUnit = d2common_GetFirstItemInInv(m->pInventory);pUnit;pUnit = d2common_GetNextItemInInv(pUnit)) n++;
		if (n==0) return 1;
		formatKey(keyname,tDropProtectionToggle.key);
		wsprintfW(wszbuf, L"Drop Protection, merc has %d equipment, (use %hs to unlock)",n,keyname);
	}
	d2client_ShowGameMessage(wszbuf, 0);
	return 0;
}
int DropProtectionPacketBlock(BYTE *buf,int len) {
	if (!tDropProtectionToggle.isOn) return 0;
	int cmd=buf[0]&0xFF;
	int block=1;
	wchar_t wszbuf[256];wszbuf[0]=0;
	if (cmd==0x36) { //hire merc
		if (canHireMerc()) return 0;
		else return 1;
	} else {
		UnitAny *pItem=NULL;
		int id;char *cmdname;
		if (cmd==0x17) {
			//17   5   Drop item (ground)      17 [DWORD id] 
			id=*(int *)(buf+1);
			cmdname="drop";
			pItem=d2client_GetUnitFromId(id, UNITNO_ITEM) ;
		} else if (cmd==0x33) {
			//33   17   Sell item to NPC buffer      33 [DWORD entity id] [DWORD item id] [DWORD tab] [DWORD cost] 
			id=*(int *)(buf+5);
			cmdname="sell";
			pItem=d2client_GetUnitFromId(id, UNITNO_ITEM) ;
		} else return 0;
		if (!pItem) return 0;
		if (DropProtection(pItem)) {
			wsprintfW(wszbuf, L"Drop Protection intercept command 0x%02X %hs %d",cmd,cmdname,id);
			d2client_ShowGameMessage(wszbuf, 0);
			return 1;
		}
	}
	return 0;
}
int __fastcall DropProtectionPacketCheck17(int id) {
	UnitAny *pItem=PLAYER->pInventory->pCursorItem;
	if (!pItem||pItem->dwUnitId!=id) return 0;
	if (!tDropProtectionToggle.isOn) return 0;
	int protect=DropProtection(pItem);
	if (protect) {
		d2client_ShowGameMessage(L"ERROR: Drop Protection intercept drop command", 1);
	}
	return protect;
}
/*
6FAF9440 - 64 A1 00000000        - mov eax,fs:[00000000] { 0 }
6FAF9446 - 6A FF                 - push -01 { 255 }
6FAF9448 - 68 A4D6B76F           - push 6FB7D6A4 { (0.00) }
6FAF944D - 50                    - push eax
6FAF944E - A1 6397BC6F           - mov eax,[6FBC9763] { (0) }
*/
void __declspec(naked) ClickHireMercMenuItemPatch_ASM() {
	__asm {
		pushad
		call canHireMerc
		cmp eax,0
		je protect
		popad
		mov eax,fs:[0]
		ret
protect:
		popad
		mov eax,1
		add esp,4
		ret
	}
}
/*
int canDeleteCharacter() {
	LOG("click menu item\n");
	return 1;
}
6F8F0190 - 83 EC 08              - sub esp,08 { 8 }
6F8F0193 - 8B 44 24 0C           - mov eax,[esp+0C]
6F8F0197 - 8B 00                 - mov eax,[eax]
6F8F0199 - 83 38 02              - cmp dword ptr [eax],02 { 2 }
6F8F019C - 89 44 24 04           - mov [esp+04],eax

6F8EF4E0 - 53                    - push ebx
6F8EF4E1 - 8B 5C 24 08           - mov ebx,[esp+08]
6F8EF4E5 - 56                    - push esi
6F8EF4E6 - 8B 33                 - mov esi,[ebx]
6F8EF4E8 - 83 3E 06              - cmp dword ptr [esi],06 { 6 }
void __declspec(naked) ClickDeleteCharacterPatch_ASM() {
	__asm {
		pushad
		call canDeleteCharacter
		cmp eax,0
		je protect
		popad
		//mov eax, dword ptr [esp+0x10]
		//mov eax, dword ptr [eax]
		mov esi, dword ptr [ebx]
		cmp dword ptr [esi], 6
		ret
protect:
		popad
		xor eax,eax
		add esp,12
		ret 4
	}
}
*/
