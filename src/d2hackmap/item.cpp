#include "stdafx.h"
#include "d2ptrs.h"

#define VIEWITEMUNIT (*d2client_pCurrentViewItem)
extern int fMonitorQuantity;
int LoadExtInfo();
int SwitchItemMode();
void SetExtInfoPos(int xPos , int yPos , int txtWidth , int txtHeight);
BYTE GetItemColour(UnitAny *pItem,int arridx);
int CheckItemVisible(UnitAny *pItem);
int 		dwGoldGoodNum=					   0;
char 			anGoldGoodCol[4]=		  {(BYTE)-1};
char 			anGoldPoorCol[4]=		  {(BYTE)-1};
char 			anRuneColours[100][4]	={		 {0}};
char 			anItemColours[3000][8][2][7][4]	={{0}};
char 			anItemHideLevel[3000][8]		={{0}};
char 			anItemShowCLevel[3000]		={{0}};
ToggleVar 	tSwitchItemMode={		TOGGLEVAR_DOWN,	0,	-1,		1,	"SwitchItemMode",	&SwitchItemMode};
int 	    dwItemShowMode=1;
int 			fSimplifiedPotionName=			0;
BYTE 			nQuestItemColour=			(BYTE)-1;
wchar_t 		wszEtherealItemPrefix[30]=  {L'\0'};
wchar_t 		wszEtherealItemPostfix[30]= {L'\0'};
ToggleVar 	tRuneNumbers={		TOGGLEVAR_ONOFF,	1,	-1,	1,"Rune numbers"};
ToggleVar 	tSocketNumbers={		TOGGLEVAR_ONOFF,	1,	-1,	1,"Socket numbers"};
ToggleVar 	tItemLevel={			TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemLevel"};
ToggleVar 	tItemValue={			TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemValue"};
ToggleVar 	tItemIndex={			TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemIndex"};
ToggleVar 	tItemFileIndex={		TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemFileIndex"};
ToggleVar 	tUnitNumber={		TOGGLEVAR_ONOFF,	0,	-1,	1, "UnitNumber"};
ToggleVar 	tItemQLevel={		TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemQLevel"};
ToggleVar 	tItemMLevel={		TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemMLevel"};
ToggleVar 	tItemALevel={		TOGGLEVAR_ONOFF,	0,	-1,	1, "ItemALevel"};
ToggleVar 	tAfterCube={			TOGGLEVAR_ONOFF,	0,	-1,	1, "AfterCube"};
ToggleVar 	tLifePerLevel={		TOGGLEVAR_ONOFF,	0,	-1,	1, "LifePerLevel"};
int 		dwItemValueNpc[5]={	154,178,255,405,513 };
ToggleVar 	tShowBaseED={				TOGGLEVAR_ONOFF,	0,	-1,	1 , "Show Base ED"};
int  dwShowValuableItem= 0;
ToggleVar 	tShowIdentifiedItem={  TOGGLEVAR_ONOFF,	0,	-1,		1,	"Show Identified items"};
ToggleVar     tHiddenItems={         TOGGLEVAR_ONOFF,	1,	VK_ADD,	1,	"Show hidden items"};
ToggleVar 	tPermShowItems={				TOGGLEVAR_ONOFF,	0,	-1,	1,	"Perm show items"};
ToggleVar 	tLockAltToggle={				TOGGLEVAR_ONOFF,	0,	-1,	1,	"Lock Alt"};
ToggleVar 	tItemBasicStat={				TOGGLEVAR_ONOFF,	0,	-1,	1 , "Item basic stat"};
ToggleVar 	tViewSocketable={			TOGGLEVAR_ONOFF,	0,	-1,	1 , "View socketables"};
ToggleVar 	tViewSocketBase={			TOGGLEVAR_ONOFF,	0,	-1,	1 , "View socketed base"};
ToggleVar 	tShowItemVariableProp={	  TOGGLEVAR_ONOFF,	0,	-1,	1 , "Item Variable Prop"};
ToggleVar 	tSocketProtect={				TOGGLEVAR_ONOFF,	0,	-1,	1 , "Socket protect"};
char 			szItemExtInfoCfgName[2][256]	={			{'\0'}};
ToggleVar 	tItemExtInfo={			TOGGLEVAR_ONOFF,	0,	-1,	1 , "ItemExtInfo" , &LoadExtInfo};
BYTE 			nDefaultExtInfoColour=				8;
static ConfigVar aConfigVars[] = {
//--- m_ItemDefine.h ---
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "ItemColours",       &anItemColours,       4, {3000 , 8 , 2 , 7}},
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "WeaponColours",     &anItemColours,       4, {1000 , 8 , 2 , 7}},
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "ArmorColours",      &anItemColours[1000], 4, {1000 , 8 , 2 , 7}},
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "MiscItemColours",   &anItemColours[2000], 4, {1000 , 8 , 2 , 7}},
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "RuneColours",       &anRuneColours,       4, {100} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "CharmColours",      &anItemColours[2095], 4, {3, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "RejuvPotColours",   &anItemColours[2007], 4, {2, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "HealingPotColours", &anItemColours[2079], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "ManaPotColours",    &anItemColours[2084], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "AmethystColours",   &anItemColours[2049], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "TopazColours",      &anItemColours[2054], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "SapphireColours",   &anItemColours[2059], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "EmeraldColours",    &anItemColours[2064], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "RubyColours",       &anItemColours[2069], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "DiamondColours",    &anItemColours[2074], 4, {5, 8, 2, 7} },
  //{CONFIG_VAR_TYPE_CHAR_ARRAY1, "SkullColours",      &anItemColours[2089], 4, {5, 8, 2, 7} },
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "ItemHideLvl",       &anItemHideLevel,     1, {3000 , 8} },
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "ItemShowCLvl",       &anItemShowCLevel,     1, {3000} },
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "GoodGoldColour",      &anGoldGoodCol,     4,{1}},
  {CONFIG_VAR_TYPE_CHAR_ARRAY1, "PoorGoldColour",      &anGoldPoorCol,     4,{1}},
  {CONFIG_VAR_TYPE_INT, "GoodGoldNumber",      &dwGoldGoodNum,     4 },
  {CONFIG_VAR_TYPE_KEY, "SwitchItemShowMode",  &tSwitchItemMode    },
  {CONFIG_VAR_TYPE_INT, "ShowValuableItem", &dwShowValuableItem,     4 },
//--- m_ItemName.h ---
  {CONFIG_VAR_TYPE_INT, "SimplifiedPotionName",        &fSimplifiedPotionName, 1 },
  {CONFIG_VAR_TYPE_INT, "QuestItemColour",        &nQuestItemColour, 1 },
  {CONFIG_VAR_TYPE_KEY, "RuneNumbersToggle",      &tRuneNumbers        },
  {CONFIG_VAR_TYPE_KEY, "SocketNumbersToggle",    &tSocketNumbers      },
  {CONFIG_VAR_TYPE_KEY, "ItemLevelsToggle",       &tItemLevel       },
  {CONFIG_VAR_TYPE_KEY, "ItemValueToggle",        &tItemValue       },
  {CONFIG_VAR_TYPE_KEY, "ItemIndexsToggle",       &tItemIndex       },
  {CONFIG_VAR_TYPE_KEY, "ItemFileIndexsToggle",   &tItemFileIndex   },
  {CONFIG_VAR_TYPE_KEY, "UnitNumbersToggle",      &tUnitNumber      },
  {CONFIG_VAR_TYPE_D2STR, "EtherealItemPrefix",     &wszEtherealItemPrefix, 1,  {30 }},
  {CONFIG_VAR_TYPE_D2STR, "EtherealItemPostfix",    &wszEtherealItemPostfix,1,  {30 }},
  
  {CONFIG_VAR_TYPE_KEY, "ItemQLevelToggle",       &tItemQLevel      },
  {CONFIG_VAR_TYPE_KEY, "ItemMLevelToggle",       &tItemMLevel      },
  {CONFIG_VAR_TYPE_KEY, "ItemALevelToggle",       &tItemALevel      },
  {CONFIG_VAR_TYPE_KEY, "ItemAfterCubeToggle",    &tAfterCube       },

  {CONFIG_VAR_TYPE_KEY, "ItemLifePerLevelToggle", &tLifePerLevel    },
  {CONFIG_VAR_TYPE_KEY, "ShowBaseEDToggle",           &tShowBaseED      },
//--- m_ItemInGround.h ---
  {CONFIG_VAR_TYPE_KEY, "ShowIdentifiedItem",    &tShowIdentifiedItem	 },
  {CONFIG_VAR_TYPE_KEY, "HiddenItemsToggle",     &tHiddenItems         },
//--- m_PermShowItem.h ---
	{CONFIG_VAR_TYPE_KEY, "PermShowItemsToggle",		&tPermShowItems     },
	{CONFIG_VAR_TYPE_KEY, "LockAltToggle",			&tLockAltToggle     },
//--- m_ItemDesc.h ---
  {CONFIG_VAR_TYPE_KEY, "ViewSocketablesToggle",		&tViewSocketable    },
  {CONFIG_VAR_TYPE_KEY, "ItemBasicStatsToggle",		&tItemBasicStat     },
  {CONFIG_VAR_TYPE_KEY, "ViewSocketBaseItemsToggle",  &tViewSocketBase    },
//--- m_ItemVariableProp.h ---
	{CONFIG_VAR_TYPE_KEY, "ShowItemVariablePropToggle",					&tShowItemVariableProp         },
//--- m_ItemExtInfo.h ---
	{CONFIG_VAR_TYPE_STR, "ItemExtInfoFileEng",		&szItemExtInfoCfgName[0], 1,  {255 }},
	{CONFIG_VAR_TYPE_STR, "ItemExtInfoFileChi",		&szItemExtInfoCfgName[1], 1,  {255 }},
	{CONFIG_VAR_TYPE_KEY, "ItemExtInfoToggle",		&tItemExtInfo         },
	{CONFIG_VAR_TYPE_INT, "DefaultExtInfoColour",     &nDefaultExtInfoColour,   1 },
	{CONFIG_VAR_TYPE_KEY, "SocketProtectToggle",   &tSocketProtect   },
};
void item_addConfigVars() {
	for (int i=0;i<_ARRAYSIZE(aConfigVars);i++) addConfigVar(&aConfigVars[i]);
}
void item_initConfigVars() {
  memset(anGoldGoodCol,     -1,       sizeof(anGoldGoodCol));
  memset(anGoldPoorCol,     -1,       sizeof(anGoldPoorCol));
  memset(anItemColours,     -1,       sizeof(anItemColours));
  memset(anRuneColours,     -1,       sizeof(anRuneColours));
  memset(anItemHideLevel,   -1,       sizeof(anItemHideLevel));
  memset(anItemShowCLevel,   -1,       sizeof(anItemShowCLevel));
  memset(wszEtherealItemPrefix ,    0 ,      sizeof(wszEtherealItemPrefix) );
  memset(wszEtherealItemPostfix ,   0 ,      sizeof(wszEtherealItemPostfix) );
}
void item_NewGame() {dwItemShowMode=EXPANSION?1:2;}

extern int dwTownPortalCount,dwIdentifyPortalCount;

wchar_t *wcs_insert(wchar_t *dest, wchar_t *src) {
	memmove(dest+wcslen(src), dest, (wcslen(dest)+1)*sizeof(wchar_t));
	memcpy(dest, src, wcslen(src)*sizeof(wchar_t));
	return dest;
}
static wchar_t * wscolorcpy(wchar_t *dest, wchar_t *src , BYTE color) {
	wcscpy(dest,src) ; 
  wchar_t *p = dest;	
	while(*p) p++;
	if (p[-1]!=255) return dest;
	if (color==(BYTE)-1) {p[-1]=0;return dest;}
	*p++='c';*p++='0'+color;*p=0;
	return dest;
}


int GetItemIndex(int dwTxtFileNo) {
	if (dwTxtFileNo < *d2common_pWeaponsTxts) return dwTxtFileNo;
	dwTxtFileNo-=*d2common_pWeaponsTxts;
	if (dwTxtFileNo<*d2common_pArmorTxts) return dwTxtFileNo+1000;
	return dwTxtFileNo-*d2common_pArmorTxts+2000;
}
int CheckItemVisible(UnitAny *pItem){
	// false ����ʾ true ��ʾ
	if( tHiddenItems.isOn ) return TRUE;
	//�ѱ�ʶ��Ʒ�����ж�
	if( tShowIdentifiedItem.isOn && fPlayerInTown && pItem->pItemData->dwQuality>=3){
		if( d2common_CheckItemFlag(pItem, ITEMFLAG_IDENTIFIED, 0, "?") ) return TRUE;
	}
	//���֮�ﲻ����
	if ( d2common_CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ) return TRUE;
	if (dwShowValuableItem) {
		int value=d2common_GetItemValue( PLAYER, pItem, DIFFICULTY, QUESTDATA, dwItemValueNpc[ACTNO], 1);
		if (value>=dwShowValuableItem) return 1;
	}
	BYTE nColour = GetItemColour(pItem, 1);
	if ( nColour == 0xFE ) return FALSE;
	return TRUE;
}

BYTE GetItemColour(UnitAny *pItem,int isMinimap) {
	ItemTxt *pItemTxt = d2common_GetItemTxt( pItem->dwTxtFileNo );
	int arridx=isMinimap?dwItemShowMode:0;
	if ( pItemTxt->nType==4 ) {//gold
		return (d2common_GetUnitStat(pItem, STAT_GOLD, 0) >= (int)dwGoldGoodNum) ? anGoldGoodCol[arridx] : anGoldPoorCol[arridx];
	}

	if ( pItemTxt->nType == 74) {//rune
		DWORD dwRuneNo = (pItemTxt->szCode[1]-'0')*10+(pItemTxt->szCode[2]-'0')-1;
		if ( dwRuneNo < 100 ) return anRuneColours[dwRuneNo][arridx];
	}

	int index = GetItemIndex(pItem->dwTxtFileNo);
	if ( index >2999 ) index= 2999;

	BYTE nShowClevel = anItemShowCLevel[index];
	if (nShowClevel!=(BYTE)-1 ) {
		DWORD lvl = d2common_GetUnitStat(PLAYER, STAT_LEVEL, 0);
		if (lvl<=nShowClevel) return (BYTE)-1;
	}
	DWORD dwQuality = (pItem->pItemData->dwQuality-1)&7;
	if ( arridx>0 ){
		BYTE nHiddenLevel = anItemHideLevel[index][dwQuality];//С�����صȼ�������
		if (nHiddenLevel!=(BYTE)-1 && ( pItem->pItemData->dwItemLevel < (DWORD)(nHiddenLevel>99?0:nHiddenLevel) )  ) return (BYTE)-2;
	}
	int socknum = d2common_GetUnitStat(pItem, STAT_NUMSOCKETS, 0);
	if( socknum > 6) socknum = 6;
	char color = anItemColours[index][dwQuality][!!d2common_CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?")][socknum][arridx];
	if (color==-2) {
		if (fMonitorQuantity) {
			if (index==2021&&dwTownPortalCount<20) return (BYTE)-1;
			if (index==2022&&dwIdentifyPortalCount<20) return (BYTE)-1;
		}
		if (fUsingBow&&index==2018) {
			return (BYTE)-1;
		} else if (fUsingCrossBow&&index==2020) {
			return (BYTE)-1;
		} else if (fUsingThrow) {
			if (pItemTxt->nType==43||pItemTxt->nType==44) return (BYTE)-1;
		}
	}
	return (BYTE)color;
}

int SwitchItemMode(){
	dwItemShowMode++;if (dwItemShowMode>=4) dwItemShowMode=1;
	if (dwGameLng) {
		wchar_t *mode=L"��������";
		if (dwItemShowMode==1) mode=L"����Ƭ����";
		else if (dwItemShowMode==2) mode=L"��������";
		partyMessageW(L"<Hackmap>: �л���Ʒ��ʾ���õ�%s",mode);
	} else {
		char *mode="Extra Mode";
		if (dwItemShowMode==1) mode="Expansion Mode";
		else if (dwItemShowMode==2) mode="Classic Mode";
		partyMessage("<Hackmap>: Switch to Item Show Mode to %s",mode);
	}
	return 0;
}

void trimspaces(char *str) {
	char *p1 = str, *p2 = str+strlen(str);
	while (isspace(*p1)) p1++;
	do p2--; while ((p2 >= p1) && isspace(*p2));
	*++p2 = 0;
	memmove(str, p1, (p2+1-p1)*sizeof(char));
}
void trimspaces(wchar_t *str) {
	wchar_t *p1 = str, *p2 = str+wcslen(str);
	while (iswspace(*p1)) p1++;
	do p2--; while ((p2 >= p1) && iswspace(*p2));
	*++p2 = 0;
	memmove(str, p1, (p2+1-p1)*sizeof(wchar_t));
}
wchar_t * __fastcall ColourD2String(wchar_t *str, DWORD col) {
	memmove(str+3, str, (wcslen(str)+1)*sizeof(wchar_t));
	str[0] = 0xff;
	str[1] = 'c';
	str[2] = '0'+(int)col;
	return str;
}
BOOL ItemHaveLevel(BYTE nType) {	
	if (nType==74)return FALSE;
	if (nType==4)return FALSE;
	if (nType==22)return FALSE;
	if (nType>=76 && nType<=81)return FALSE;
	if (nType>=91 && nType<=102)return FALSE;
	return TRUE;
}
void __fastcall ItemNamePatch(wchar_t *wscNameOld, UnitAny *pItem ,ItemTxt *pItemTxt ){
	wchar_t wscTemp[0x40];
	memset(wscTemp,0,sizeof(wscTemp));

	wchar_t wscName[0x100];
	memset(wscName,0,sizeof(wscName));
	wcscpy(wscName,wscNameOld);


	int showValue=tItemValue.isOn;
	BYTE nColour = GetItemColour(pItem,0);
	int itemIndex = GetItemIndex(pItem->dwTxtFileNo);
	if (fSimplifiedPotionName) {
		static wchar_t *potions[2][10]={
			{L"H1",L"H2",L"H3",L"H4",L"H",
			L"M1",L"M2",L"M3",L"M4",L"M",},
			{L"��1",L"��2",L"��3",L"��4",L"��",
			L"��1",L"��2",L"��3",L"��4",L"��",}
			};
		wchar_t *name=NULL;
		if (itemIndex==2007) name=L"��";
		else if (itemIndex==2008) name=L"ȫ��";
		else if (2079<=itemIndex&&itemIndex<=2088) name=potions[dwGameLng][itemIndex-2079];
		else if (2049<=itemIndex&&itemIndex<=2078) showValue=0;//gem
		if (name) {wcscpy(wscName,name);showValue=0;}
	}
	trimspaces(wscName);
	if (pItemTxt->nType==4) {// gold
		wsprintfW(wscTemp, L"%d ", d2common_GetUnitStat(pItem, STAT_GOLD, 0) );
		wcs_insert(wscName,wscTemp);
	}else{
		DWORD dwQuality =(pItem->pItemData->dwQuality-1)&7;
		if ( (nColour == (BYTE)-1 ) && pItemTxt->fQuest) {
			nColour = nQuestItemColour; //������Ʒ
		}

		if ( pItemTxt->fQuest && pItemTxt->fDiffCheck  && d2common_GetUnitStat(pItem, STAT_ITEMDIFFICULTY, 0)< DIFFICULTY ){
			nColour = (BYTE)-1 ;  //��Ч�������,ԭ�����У�飬����ɫ
		}
		if ( d2common_CheckItemFlag(pItem, ITEMFLAG_BROKEN, 0, "?") ){
			nColour = 1 ; //�𻵵ĵ���
		};

		// ethereal
		if ( d2common_CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?") ) {
			if (wszEtherealItemPrefix[0]){
				wcs_insert(wscName, wscolorcpy(wscTemp,wszEtherealItemPrefix,nColour));
			}
			if (wszEtherealItemPostfix[0]){
				wscolorcpy(wscName+wcslen(wscName),wszEtherealItemPostfix,nColour);
			}
		}
		// rune numbers
		if (tRuneNumbers.isOn && (pItemTxt->nType == 74)) {
			int bktnum = (pItemTxt->szCode[1]-'0')*10+(pItemTxt->szCode[2]-'0');
			wsprintfW(wscName+wcslen(wscName), L" (%d)", bktnum);
		}
	
		// socket number
		if (tSocketNumbers.isOn && d2common_CheckItemFlag(pItem, ITEMFLAG_SOCKETED, 0, "?") ) {
			wsprintfW(wscName+wcslen(wscName), L" (%d)", d2common_GetUnitStat(pItem, STAT_NUMSOCKETS, 0) );
		}

		// item level
		if (tItemLevel.isOn && ItemHaveLevel(pItemTxt->nType)) {
			wsprintfW(wscName+wcslen(wscName), L" (%ld)", pItem->pItemData->dwItemLevel);
		}
		// item value
		if (showValue && (pItemTxt->fQuest == 0) && d2client_CheckUiStatus(UIVAR_NPCTRADE)==0 ) {
			int value=d2common_GetItemValue( PLAYER, pItem, DIFFICULTY, QUESTDATA, dwItemValueNpc[ACTNO], 1);
			if (value>=tItemValue.value32)
				wsprintfW(wscName+wcslen(wscName), L" ($%d)", value);
		}
		// unit number
		if (tUnitNumber.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" [0x%X]", pItem->dwUnitId);
		}

		// item index
		if (tItemIndex.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" [i%d]", itemIndex + 1 );
		}
		
		// item Qlevel
		if (tItemQLevel.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" (Q:%ld)", pItemTxt->nQLevel);
		}
		// item Magiclevel
		if (tItemMLevel.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" (M:%ld)", pItemTxt->nMagicLvl);
		}
		
		// item Alevel
		if (tItemALevel.isOn) {
			if (dwQuality==3 || dwQuality==5 || dwQuality==7){
				wsprintfW(wscName+wcslen(wscName), L" (A:%ld)", GetItemAlvl( pItem->pItemData->dwItemLevel,pItemTxt->nQLevel,pItemTxt->nMagicLvl) );
			}
		}
		
		if (tAfterCube.isOn)
		{
			if (dwQuality==3)
			{
				int iLvl = GetItemILvlAfterCube( 1 , pItem->pItemData->dwItemLevel ,d2common_GetUnitStat(PLAYER, STAT_LEVEL, 0) );
				wsprintfW(wscTemp, L"[After Craft Ilvl: %d Alvl: %d]\n",iLvl,GetItemAlvl(iLvl,pItemTxt->nQLevel,pItemTxt->nMagicLvl));
				wcs_insert(wscName,  wscTemp);
			}
			else if (dwQuality==5)
			{
				int iLvl = GetItemILvlAfterCube( 2 , pItem->pItemData->dwItemLevel ,d2common_GetUnitStat(PLAYER, STAT_LEVEL, 0));
				wsprintfW(wscTemp, L"[After Cube Ilvl: %d Alvl: %d]\n",iLvl,GetItemAlvl(iLvl,pItemTxt->nQLevel,pItemTxt->nMagicLvl));
				wcs_insert(wscName,wscTemp );
			}
		}

		if ( d2common_CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ){
			if ( tLifePerLevel.isOn ){
				int iPerlvValue=d2common_GetUnitStat(pItem, 216, 0);
				if (iPerlvValue) {
					int d1000=iPerlvValue*1000/2048;
					wsprintfW(wscTemp, L"[%d.%03d life/level]\n",d1000/1000,d1000%1000);
					wcs_insert(wscName,wscTemp);
				}
			}
			if (tShowBaseED.isOn){
				int ed = 0 ;
				if( itemIndex<1000 ){//����
					ed = GetUnitMagicStat(pItem, 0x11);
				}else{//����
					ed = GetUnitMagicStat(pItem, 0x10);
				}
				wsprintfW(wscTemp, L"[Base Ed: %d%%]\n",ed);
				wcs_insert(wscName,wscTemp);

			}
		}
	
		// item file index
		if (tItemFileIndex.isOn) {
			wsprintfW(wscTemp, L" [TXT:%d F:%d Type:%d]\n",pItem->dwTxtFileNo, d2common_GetItemFileIndex(pItem) ,pItemTxt->nType );
			wcs_insert(wscName,wscTemp);
		}

	}
	if (nColour != (BYTE)-1) ColourD2String(wscName, nColour);
	
	wscName[124] = 0 ;
	wcscpy(wscNameOld,wscName);

}
void __declspec(naked) ItemNamePatch_ASM()
{
	__asm {
//ebx = ptr unit item
//edi = ptr item name string
//ebp = pItemTxt
		push ebx
		push ebp
		push edi

		mov ecx, edi
		mov edx, ebx
		push ebp
		call ItemNamePatch
		
		pop edi
		pop ebp
		pop ebx

		mov al, [ebp+0x12A]
		ret
	}
}


wchar_t * __fastcall OpenCubeStringPatch(wchar_t *wcstr, DWORD dwColour)
{
	BYTE nColour = (BYTE)anItemColours[2041][0][0][0][0];
	if ( nColour != (BYTE)-1){
		return ColourD2String(wcstr, nColour);
	}
	if ( nQuestItemColour != (BYTE)-1 ){
		return ColourD2String(wcstr, nQuestItemColour);
	}else{
		return  wcstr;
	}
}

void __declspec(naked) OpenCubeStringPatch_ASM()
{
	__asm {
	//edi = str
	//esi = col
	mov ecx, edi
	mov edx, esi
	call OpenCubeStringPatch
	ret 4
	}
}
BOOL PermShowItemsPatch1() {
	//ALT �����Ƿ���Ч
	if ( tLockAltToggle.isOn || tPermShowItems.isOn || d2client_CheckUiStatus(UIVAR_SHOWITEMS)) return true ;
	return false;
}
BOOL PermShowItemsPatch2() {
	//�Ƿ���ʾ������false����ʾ true ��ʾ
	if( tLockAltToggle.isOn ) return false;
	if ( d2client_CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn && tPermShowItems.value32==3)return true;
		return false;
	}else{
		return tPermShowItems.isOn?true:false;
	}
}
BOOL PermShowItemsPatch3() {
	//�Ƿ���ʾ��Ʒ�� true ��ʾ  false ����ʾ
	if( tLockAltToggle.isOn ) return true;
	if ( d2client_CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn==FALSE) return true ;
		return tPermShowItems.isOn && tPermShowItems.value32==1 ;
	}else{
		return tPermShowItems.isOn?true:false;
	}
}
void __declspec(naked) PermShowItemsPatch1_ASM() {
	__asm {
		call PermShowItemsPatch1
		test eax,eax
		ret
	}
}
void __declspec(naked) PermShowItemsPatch2_ASM() {
	__asm {
		call PermShowItemsPatch2
		test eax,eax
		je orgcode
		ret
orgcode:
		mov eax, dword ptr [esp+0x20]
		test eax,eax
		ret
	}
}
void __declspec(naked) PermShowItemsPatch3_ASM() {
	__asm {
		push ebp
		push esi
		call PermShowItemsPatch3
		test eax,eax
		pop esi
		pop ebp
		jz 	outcode
		cmp ebp, 0x20
		jge outcode
		ret
outcode:
		add dword ptr [esp], 0x38A  //to 6FB0DD89
		ret
	}
}
void __declspec(naked) PermShowItemsPatch4_ASM() {
	__asm {
		push eax
		call PermShowItemsPatch1
		mov ecx, eax
		pop eax
		ret
	}
}

BOOL fViewSockFlag = FALSE;
BOOL fViewSocketableOn = FALSE;
wchar_t wszDescText[0x400] = {L'\0'};
void __fastcall ItemDescPath( wchar_t *wszDesc , int xPos , int yPos , int unk1, int unk2 ) {
	fViewSockFlag = TRUE;
	static int yPosition = 0 ;
	int dwWidth, dwHeight;
	if (fViewSocketableOn) {
		wcs_insert(wszDescText, L"\n\n");
		wcs_insert(wszDescText, wszDesc);
		d2win_GetTextAreaSize(wszDescText, &dwWidth, &dwHeight);
		yPos = yPosition + dwHeight;
	} else {
		wcscpy(wszDescText, wszDesc);
		d2win_GetTextAreaSize(wszDescText, &dwWidth, &dwHeight);
		yPosition = yPos - dwHeight;
	}
	wszDescText[0x3FF] = 0;
	d2win_DrawHoverText(wszDescText , xPos , yPos ,unk1 ,unk2);
	SetExtInfoPos(xPos,yPos,dwWidth,dwHeight);
}
void __declspec(naked) __fastcall SocketViewCallRoutine(UnitAny *pUnitView, DWORD arg, void (__stdcall *func)(UnitAny*, DWORD)) {
	__asm {
		mov eax,0x6650
		push edx
		push ecx
		call [esp+0x0c]
		ret 4
	}
}
void __stdcall ItemSocketViewPatch(void (__stdcall *func)(UnitAny*, DWORD), UnitAny *pUnitView, DWORD arg) {
	fViewSockFlag = FALSE;
	SocketViewCallRoutine(pUnitView, arg, func);
	if ( fViewSockFlag && (tViewSocketable.isOn || tViewSocketBase.isOn) )	{
		fViewSocketableOn = TRUE;
		UnitAny *pUnit = VIEWITEMUNIT;
		if ( pUnit && pUnit->pInventory ) {
			UnitAny *pItem = d2common_GetFirstItemInInv(pUnit->pInventory);
			while (pItem) {
				VIEWITEMUNIT = pItem;
				SocketViewCallRoutine(pUnit, 1, func);
				pItem = d2common_GetNextItemInInv(pItem);
			}
		}
		fViewSocketableOn = FALSE;
		VIEWITEMUNIT = pUnit;
	}
}
void __declspec(naked) ItemSocketViewPatch_ASM() {
	__asm {
		pop eax // exchange return address
		pop ecx
		push eax
		push ecx
		jmp ItemSocketViewPatch
	}
}
/*��������鿴��Ƕ�ֻ�鿴��ʵ����Ч������ */
void __declspec(naked) SocketItemStatViewPatch_ASM() {
	__asm {
		cmp fViewSocketableOn, 0
		jz outcode
		pop esi // discard my return adress
		pop esi // restore esi
		pop ebx // restore ebx
		ret
outcode:
		mov ecx, 0xF9E
		ret
	}
}
/*�����Ƿ�鿴��ϸ����*/
StatList *  __stdcall GetItemExtStatListPatch(UnitAny *pUnit, DWORD dwStatNo, DWORD dwListFlag) {
	if ( tViewSocketBase.isOn ) return 0;
	return d2common_GetStatListWithFlag(pUnit,dwStatNo,dwListFlag);
}
/*�����Ƿ�鿴��Ƕ�︽��������*/
void __declspec(naked) ItemBasicStatPatch_ASM() {
	__asm {
		cmp [tItemBasicStat.isOn], 1
		je quitcode
		cmp [tViewSocketBase.isOn],1
		je quitcode
	//org
		push dword ptr [esp+4]
		call d2common_GetFirstItemInInv
		ret 4
quitcode:
		xor eax, eax
		ret 4
	}
}
//������Χ��ʾ
/*
��һ������ʱ���ȳ�ʼ��������ɫ���������֮������Ա�
����ĳЩ��������Ҫ�������Ͳ������
short aItemPropInfo[3][500][30][4];
��һλ 0 ���� 1 ��ɫ 2 ���֮��
�ڶ�λ �����Ͷ�Ӧ��� set 128�� unique 397��  runeword 169��
����λ װ������  ��359������ , ֻ����ɱ��
����λ 0 ��¼statnoֵ 1 ��¼paramֵ 2 ��¼��Сֵ 3 ��¼���ֵ
(3*500*20*4*4)/1024 = 469K ;
���ڱ����д������ܣ�����ʱ�������ܣ�gethit��������3�����ԣ�����ȼ��ɱ䣬�㷨�Ƚ��鷳��ֱ��if elseά����
*/
/*
TEST
wchar_t wszTemp[512];
wsprintfW(wszTemp, L"[%d] [%d] [%d] [%d]" , mPropId ,  pItemProp[i].Param , pItemProp[i].MinVal,pItemProp[i].MaxVal);
D2ShowGameMessage(wszTemp,0);
*/

static int aItemPropInfo[3][500][20][4];
static int nStatCount = 0 ;
void SetPropInfo( int itemType , int index ,int propMax , ItemProp *pItemProp){
	if (!pItemProp)return;
	int nCount = 0 ;
	int (*pStat)[4] = &aItemPropInfo[itemType][index][0];
	for ( int i=0 ; i<propMax ; i++){//1
		int mPropId = pItemProp[i].PropId ;
		if ( mPropId>=0 && pItemProp[i].MinVal!= pItemProp[i].MaxVal ){//2
			PropertiesTxt *pPropertiesTxt = d2common_GetPropertiesTxt( mPropId );
			if ( !pPropertiesTxt ) continue;
			short *pStatNo = pPropertiesTxt->wStatNo;
			if ( mPropId==267 && pPropertiesTxt->nFunc[0]==36) continue;
			//�������Բ��
			if ( pPropertiesTxt->nFunc[0]==21 ){
				//�ӽ�ɫ����
				pStat[nCount][0] = 83;
				pStat[nCount][1] = pPropertiesTxt->wVal[0];
				pStat[nCount][2] = pItemProp[i].MinVal ;
				pStat[nCount][3] = pItemProp[i].MaxVal ;
				nCount++;
				continue;
			}
			if ( mPropId == 29 ){
				//��ǿ�˺�
				pStat[nCount][0] = 17;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				pStat[nCount][0] = 18;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				continue;
			}
			//�������ԣ�ɾ��
			if ( mPropId>=134 && mPropId<=140)continue;  //���������˺�������
			if ( mPropId==248 )continue;  //������������˺�
			if ( mPropId <= 128 &&  mPropId >=126){
				//�����ʱ��������ʱ������ʱ��������
				if (pItemProp[i].MaxVal==0){
					int statno = -1 ;
					int min = -1 ;
					int max = -1;
					if ( mPropId == 126 ){
						if ( index==254 ) {
							statno = 195;
							min = 16;
							max = 20;
						}else if ( index==259 ) {
							statno = 195;
							min = 14;
							max = 20;
						}
					}
					if ( mPropId == 127 ){
						if ( index==136 ) {
							statno = 198;
							min = 13;
							max = 20;
						}
					}
					if ( mPropId == 128 ){
						if ( index==264 ) {
							statno = -1; //��Ϊ����Ҫ��̫�ߣ����ʵ�ʱ���˲��ɱ�
							min = 20;
							max = 20;
						}else if ( index==270 ) {
							statno = 201;
							min = 13;
							max = 19;
						}else if ( index==245 ) {
							statno = 201;
							min = 7;
							max = 19;
						}else if ( index==137 ) {
							statno = 201;
							min = 12;
							max = 20;
						}
					}
					if ( statno>=0 ){
						pStat[nCount][0] = statno;
						pStat[nCount][1] = pItemProp[i].Param ;
						pStat[nCount][2] = min ;
						pStat[nCount][3] = max ;
						nCount++;
					}
				}
				continue;
			}
			for( int j=0 ; j< 7; j++ ){//3  �����Բ��
				if ( pStatNo[j]>=0 ){//4
					pStat[nCount][0] = pStatNo[j];
					pStat[nCount][1] = pItemProp[i].Param;
					pStat[nCount][2] = pItemProp[i].MinVal ;
					pStat[nCount][3] = pItemProp[i].MaxVal ;
					nCount++;
				}//4
			}//3
		}//2
	}//1
	if ( nCount> nStatCount) nStatCount = nCount;
}
wchar_t *GetStatRange( wchar_t *wszStr , DWORD dwStatId , DWORD wParam = 0) {
	static BOOL fItemStatInit = FALSE;
	if ( fItemStatInit == FALSE ){
		memset(aItemPropInfo,	-1	,	sizeof(aItemPropInfo));
		nStatCount = 0 ;
		//����
		for ( int i =0  ; i < 500 ; i++ ){
			UniqueItemTxt *pUniqueTxt = d2common_GetUniqueItemTxt(i);
			if (!pUniqueTxt)break;
			SetPropInfo( 0 , i , 12 , pUniqueTxt->Prop );
		}
		//��ɫ
		for ( int i =0  ; i < 200 ; i++ ){
			SetItemTxt *pSetTxt = d2common_GetSetItemTxt(i);
			if (!pSetTxt)break;
			SetPropInfo( 1 , i , 9 , pSetTxt->Prop );
		}
		//���֮��
		for ( int i =0  ; i < 169 ; i++ ){
			RuneWordTxt *pRuneWordTxt = d2common_GetRuneWordTxt(i);
			if (!pRuneWordTxt)break;
			SetPropInfo( 2 , i , 7 ,pRuneWordTxt->Prop );
		}
		fItemStatInit = TRUE;
	}
	UnitAny *pUnit = VIEWITEMUNIT ;
	if (pUnit){
		DWORD dwQuality = pUnit->pItemData->dwQuality;
		int idx = -1;
		int fileindex = -1 ;
		if ( dwQuality==ITEM_QUALITY_UNIQUE ) {
			idx = 0 ;
			fileindex = d2common_GetItemFileIndex(pUnit);
		}else if (  dwQuality==ITEM_QUALITY_SET ){
			idx = 1 ;
			fileindex = d2common_GetItemFileIndex(pUnit);
		}else if ( d2common_CheckItemFlag(pUnit, ITEMFLAG_RUNEWORD, 0, "?") ){
			idx = 2 ;
			fileindex = d2common_GetRuneWordTxtIndex( pUnit->pItemData->wMagicPrefix[0] );
		}
		if ( idx>=0 && fileindex>=0 ){
			int (*pStat)[4] = &aItemPropInfo[idx][fileindex][0];
			for ( int i=0 ; i<nStatCount ; i++){
				if ( pStat[i][0]<0 ) break;
				if ( pStat[i][0]==dwStatId &&  pStat[i][1]==wParam ){
					if (dwStatId==194){
						ItemTxt *pItemTxt = d2common_GetItemTxt(pUnit->dwTxtFileNo);
						if ( pStat[i][3] > (pItemTxt->nSocket)){
							pStat[i][3] = (pItemTxt->nSocket);
						}
					}
					if ( dwStatId==216 ){
						int lvl = d2common_GetUnitStat(PLAYER, STAT_LEVEL, 0);
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]*lvl/8 , pStat[i][3]*lvl/8 );
					}else{
						int extvalue = 0 ;
						if(idx==2){
							/*�������֮������ĵ�����Ҳ�ӵ�������Χ��*/
							UnitAny *pItem = d2common_GetFirstItemInInv(pUnit->pInventory);
							while (pItem) {
								extvalue = extvalue + d2common_GetUnitStat(pItem,dwStatId,0);
								pItem = d2common_GetNextItemInInv(pItem);
							}
						}
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]+extvalue , pStat[i][3]+extvalue);
					}
					break;
				}
			}
		}
	}
	return wszStr;
}
DWORD __fastcall GetItemPropStringPatch( wchar_t *wszStr , StatEx * pStatEx ,DWORD flag){
	if ( tShowItemVariableProp.isOn && !flag ){
		//ShowGameMessage(pStatEx->wParam);
		DWORD dwStatId = pStatEx->wStatId;
		DWORD dwParam = pStatEx->wParam ;
		switch( dwStatId ){
			case 195:
			case 198:
			case 201:
				dwParam = dwParam>>6;
				break;
			case 188:
				{
					int chartype = dwParam/8;
					int skilltab = dwParam%8;
					dwParam = chartype*3+skilltab;
				}
				break;
			default:
				break;
		}
		GetStatRange( wszStr , dwStatId , dwParam );
	}
	return pStatEx->wStatId;
}
void __declspec(naked) GetItemPropStringPatch_ASM() {
	// esp +4 +8*ebp+2D4 = pStatEx
	// ebx = dwStatNo
	// esi = wszPropStr
	__asm {
		lea edx , [esp+4+8*ebp+0x2D4]
		mov ecx , esi
		push [esp+0x10]
		call GetItemPropStringPatch
//org , eax from ebx
		sub eax, 0x17
		ret
	}
}
void __fastcall StrcatItemPropStringPatch( wchar_t *wszMainStr  , wchar_t *wszPropStr ,DWORD dwStatNo ){
	int len = wcslen(wszPropStr);
	if ( len == 0 ) return;
	wszPropStr [ len-1] = L'\0';//ȥ���س�
	if (tShowItemVariableProp.isOn&&tViewSocketBase.isOn==0) {
		GetStatRange( wszPropStr , dwStatNo );
	}
	wcscat( wszMainStr , wszPropStr );
	wcscat( wszMainStr , L"\n");
}
void __declspec(naked) StrcatItemPropStringPatch_ASM() {
	__asm {
		push [esp+0xC]
		call StrcatItemPropStringPatch
		ret
	}
}
wchar_t * __fastcall StrcatSocketStringPatch( wchar_t *wszStr ) {
	//ƴ�����ַ����ĵط�,��һ������ƴ�ӻس�
	if ( tShowItemVariableProp.isOn ){
		GetStatRange( wszStr , 194 );
	}
	return wszStr;
}
void __declspec(naked) StrcatSocketStringPatch_ASM() {
	__asm {
		push edi
		mov ecx , eax
		call StrcatSocketStringPatch
		pop edi
		mov edx, dword ptr [esp+0x14]
		mov ecx, eax
		ret
	}
}
wchar_t * __fastcall StrcatDefenseStringPatch( wchar_t *wszStr ) {
	//ƴ�����ַ����ĵط�,��һ������ƴ�ӻس�
	//����ETH��Ʒ Bug��ף����bug�����������ķ�bug���ֵ��С������Ϊ�Ƿ�bug
	if ( tShowItemVariableProp.isOn ){
		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit){
			ItemTxt *pItemTxt = d2common_GetItemTxt( pUnit->dwTxtFileNo );
			if( pItemTxt && pItemTxt->dwMinDef>0 ){
				int mDef = d2common_GetUnitBaseStat(pUnit, 31,0);
				int mMinDef = pItemTxt->dwMinDef;
				int mMaxDef = pItemTxt->dwMaxDef ;
				wchar_t wszPrep[256] = {L"\0"};
				wchar_t wszTemp[512] = {L"\0"};
				if ( d2common_CheckItemFlag(pUnit, ITEMFLAG_ETHEREAL, 0, "?") ){
					mMinDef = (int)(mMinDef * 1.5) ;
					mMaxDef = (int)(mMaxDef * 1.5) ;
					if ( mDef>mMaxDef && pUnit->pItemData->dwQuality==2 && d2common_CheckItemFlag(pUnit, ITEMFLAG_SOCKETED, 0, "?")  ){
						//��ͨ��Ʒ ,���ף�������������������ΪETH BUG
						mMinDef = (int)(mMinDef * 1.5) ;
						mMaxDef = (int)(mMaxDef * 1.5) ;
						wcscpy(wszPrep , L"(Bug)");
					}
				}
				if ( mDef > mMaxDef ){//������������˵��������ED�������Զ�max+1
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d+%d)\n" ,wszPrep, mMinDef , mMaxDef , mMaxDef ,mDef - mMaxDef );
				}else{
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d)\n" ,wszPrep, mMinDef , mMaxDef , mDef);
				}
				wcs_insert(wszStr,  wszTemp);
			}
		}
	}
	return wszStr;
}
void __declspec(naked) StrcatDefenseStringPatch_ASM() {
	__asm {
		push ebx
		mov ecx , edi
		call StrcatDefenseStringPatch
		pop ebx
		mov edx, dword ptr [esp+0x1C]
		mov ecx, eax
		ret
	}
}
wchar_t * __fastcall StrcatDamageStringPatch(wchar_t *wszStr) {
	//ƴ�����ַ�����ֱ��ƴ��(����Ҳ�����)
	if (tShowItemVariableProp.isOn ){
		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit) {
			ItemTxt *pItemTxt=d2common_GetItemTxt(pUnit->dwTxtFileNo);
			if(pItemTxt&&pUnit->dwTxtFileNo<*d2common_pWeaponsTxts+*d2common_pArmorTxts){
				wchar_t wszTemp[512] = {L"\0"};
				int Sockets = pItemTxt->nSocket;
				if (pUnit->pItemData->dwQuality<=3) {
					int maxSockets = 0;
					int iLevel = pUnit->pItemData->dwItemLevel;
					ItemTypeTxt *pItemTypeTxt = d2common_GetItemTypeTxt(pItemTxt->nType);
					if (iLevel<=25) {
						maxSockets = pItemTypeTxt->nMaxSock1;
					} else if (iLevel<=40) {
						maxSockets = pItemTypeTxt->nMaxSock25;
					} else {
						maxSockets = pItemTypeTxt->nMaxSock40;
					}
					if (Sockets>maxSockets)Sockets = maxSockets;
					wszTemp[0]=0xff;wszTemp[1]='c';wszTemp[2]='0';
					wsprintfW(wszTemp+3,L"(Range: %d, Speed: %d, Sockets: 1-%d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed , Sockets);
				} else {
					wszTemp[0]=0xff;wszTemp[1]='c';wszTemp[2]='0';
					wsprintfW(wszTemp+3,L"(Range: %d, Speed: %d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed);
				}
				wcs_insert(wszStr,  wszTemp);
			}
		}
	}
	return wszStr;
}
//һ����Ʒ����
void __declspec(naked) StrcatDamageStringPatch_ASM1() {
	__asm {
		push ebx
		mov ecx , edi
		call StrcatDamageStringPatch
		pop ebx
		mov edx, eax
		lea ecx, dword ptr [esp+0x64]
		ret
	}
}
//��ɫ��������
void __declspec(naked) StrcatDamageStringPatch_ASM2() {
	__asm {
		push ebp
		mov ecx , edi
		call StrcatDamageStringPatch
		pop ebp
		mov edx, eax
		lea ecx, dword ptr [esp+0x194C]
		ret
	}
}
void ShowSocketProtectInfo(){
	char buf[256];formatKey(buf,tSocketProtect.key);
	wchar_t wszbuf[256];
	wsprintfW(wszbuf, L"<Hackmap>: Socket Protect On, press %hs to disable",buf);
	d2client_ShowPartyMessage(wszbuf, 8);
}
void __declspec(naked) SocketProtectPatch_ASM() {
	__asm {
		mov eax, d2client_pPlayerUnit
		mov eax, [eax]
		push 0x13
		push eax
		call d2client_ItemProtect
		call ShowSocketProtectInfo
		ret
	}
}
void __declspec(naked) SocketProtectPatch1_ASM() {
	__asm {
		cmp [tSocketProtect.isOn], 0
		jz outcode
		call SocketProtectPatch_ASM
		add dword ptr [esp], 0x47 
		ret
outcode:
// original code
		mov eax, [esp+4+0x18] 
		test eax, eax
		ret
	}
}
void __declspec(naked) SocketProtectPatch2_ASM() {
	__asm {
		cmp [tSocketProtect.isOn], 0
		jz outcode
		call SocketProtectPatch_ASM
		add dword ptr [esp], 0x36
		ret
outcode:
		mov eax, [esp+4+0x44] // 4 bytes for return address
		test eax, eax
		ret
	}
}

