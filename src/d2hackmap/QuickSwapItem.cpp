#include "stdafx.h"
#include "d2ptrs.h"

extern int dwQuickSwapItemDelayMs;
ToggleVar 	tRightClickSwap={    TOGGLEVAR_ONOFF,	1,	-1,	1 ,	"Right Click Swap"};
ToggleVar 	tQuickDropToggle={	TOGGLEVAR_ONOFF,	0,	-1,	1 , "Quick Drop"};

static ConfigVar aConfigVars[] = {
  {CONFIG_VAR_TYPE_KEY, "RightClickSwapToggle",  &tRightClickSwap   },
  {CONFIG_VAR_TYPE_KEY, "QuickDropToggle",       &tQuickDropToggle  },
};
void quickswap_addConfigVars() {
	for (int i=0;i<_ARRAYSIZE(aConfigVars);i++) addConfigVar(&aConfigVars[i]);
}
struct InventoryType {
	BYTE invType;
	short left;
	short bottom;
	BYTE nGridXs;
	BYTE nGridYs;
	BYTE nGridWidth;
	BYTE nGridHeight;
};


extern int dwQuickSwapItemMs;
static InventoryType invTypes[] = {   //left��bottom�Ѿ�ƫ���˸���һ���С
	{0, 430, 325, 10, 4, 29, 29}, // Inventory
	{4, 165, 152, 6, 8, 29, 29}, // Stash
	{3, 220, 220, 3, 4, 29, 29}, // Cube
	{4, 165, 345, 6, 4, 29, 29}, // Stash_Classic
	{2, 110, 325, 10, 4, 29, 29}, // Trade 1 for others trade
};
static UnitAny *getCube() {
	UnitAny *pUnit = d2common_GetFirstItemInInv(PLAYER->pInventory);
	while (pUnit) {
		if (pUnit->dwUnitType==UNITNO_ITEM) {
			int index = GetItemIndex(pUnit->dwTxtFileNo)+1;
			if (index==2042) return pUnit;
		}
		pUnit = d2common_GetNextItemInInv(pUnit);
	}
	return pUnit;
}
int PutItemIntoCube(D2MSG *pMsg,int dx,int dy) {
	UnitAny *cube=getCube();
	int location= cube->pItemData->nItemLocation;
	InventoryType *pInvType=NULL;
	if (location==0) { //bag
		if (!d2client_CheckUiStatus(UIVAR_INVENTORY)&&!d2client_CheckUiStatus(UIVAR_STASH)) return 0;
		pInvType=&invTypes[0];
	} else if (location==4) { //stash
		if (!d2client_CheckUiStatus(UIVAR_STASH)) return 0;
		if (EXPANSION) pInvType=&invTypes[1];
		else pInvType=&invTypes[3];
	}
	int left=pInvType->left;
	SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(pInvType->left + dx, pInvType->bottom + dy));
	if (*d2client_pCursorInvGridX == 2) //10*10 big box
		left-=2*pInvType->nGridWidth;
	int x=cube->pItemPath->unitX;
	int y=cube->pItemPath->unitY;
	int xpos = left + x*pInvType->nGridWidth+dx;
	int ypos = pInvType->bottom + y*pInvType->nGridHeight+dy;
	SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
	SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
	SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
	SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
	return 1;
}
void  MoveItem(D2MSG *pMsg ){
	int dx=(SCREENSIZE.x-800)/2;
	int dy=(SCREENSIZE.y-600)/2;
	UnitAny *pItem = PLAYER->pInventory->pCursorItem;
	if (!pItem) return ;  //����û����
	if (GetKeyState(VK_MENU)&0x8000) {
		int index = GetItemIndex(pItem->dwTxtFileNo)+1;//all config arrays are based 1
		if (2006<=index&&index<=2010) ; //potions
		else if (2080<=index&&index<=2089) ; //healing and mana potion
		else if (PutItemIntoCube(pMsg,dx,dy)) return;
	}
	int invtype = 0;
	if ( d2client_CheckUiStatus(UIVAR_STASH) ) {
		if ( EXPANSION ) invtype = 1; 
		else invtype = 3; //��������
	} else if ( d2client_CheckUiStatus(UIVAR_CUBE) ){
		invtype = 2;
	} else if ( d2client_CheckUiStatus(UIVAR_PPLTRADE) ) {
		invtype = 4; //���״���
	}
	if ( invtype>0 ) {//��߿�
		InventoryType *pInvType = (pMsg->xpos < SCREENSIZE.x/2) ? &invTypes[0] : &invTypes[invtype];
		if (pInvType) {
			int left=pInvType->left;
			int nx=pInvType->nGridXs;
			int ny=pInvType->nGridYs;
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(pInvType->left + dx, pInvType->bottom + dy));
			if (*d2client_pCursorInvGridX == 2) {//10*10 big box
				nx=10;ny=10;left-=2*pInvType->nGridWidth;
			}
			//LOG("%d*%d\n",nx,ny);
			DWORD dwBoxType = d2common_GetBoxType(PLAYER, pInvType->invType, EXPANSION);
			for (int x = 0; x < nx; ++x) {
				for (int y = 0; y < ny; ++y) {
					int xpos = left + x*pInvType->nGridWidth+dx;
					int ypos = pInvType->bottom + y*pInvType->nGridHeight+dy;
					int gridcount = 0;
					int itemcount = 0;
					SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
					d2common_CheckInvLocation(PLAYER->pInventory, pItem, *d2client_pCursorInvGridX, *d2client_pCursorInvGridY, dwBoxType, &gridcount, &itemcount, pInvType->invType);
					if ( itemcount==0 ) {
						//LOG("MoveItem %x %x %d %d\n",pMsg->hwnd,pMsg->wParam,xpos,ypos);
						SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
						SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
						x = y = 1000; // break;
					}
				}
			}
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
		}
	}else if (tQuickDropToggle.isOn){
		if ( d2client_CheckUiStatus(UIVAR_INVENTORY) && 
			!d2client_CheckUiStatus(UIVAR_STATS) && 
			!d2client_CheckUiStatus(UIVAR_QUEST) && 
			!d2client_CheckUiStatus(UIVAR_PARTY) &&
			!d2client_CheckUiStatus(UIVAR_PET) &&
			!d2client_CheckUiStatus(UIVAR_QUESTSCROLL) ){
			int xpos = 230;
			int ypos = 200;
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos+dx, ypos+dy));
			SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos+dx, ypos+dy));
			SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos+dx, ypos+dy));
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
		}
	}
}

void __stdcall RButtonUpHandlerPatch(D2MSG *pMsg) {
	if( fInGame==FALSE )return;
	if (tRightClickSwap.isOn && pMsg->dwMessage == WM_RBUTTONUP) {
		MoveItem( pMsg );
	}
}


void __declspec(naked) RButtonUpHandlerPatch_ASM() {
	__asm {
		push [esp+8];
		call RButtonUpHandlerPatch;
//oldcode:
		mov eax, d2client_pInGame;
		mov eax, [eax];
		ret;
	}
}

void __declspec(naked) RButtonInTradePatch_ASM() {
	__asm {
		push [esp+4];
		call RButtonUpHandlerPatch
		jmp d2client_Storm511
	}
}
void __declspec(naked) CtrlClickHandlerPatch_ASM() {
	__asm {
		je noNpc 
		ret//���NPC����������
noNpc:
		//cmp [tCtrlClickSwap.isOn] , 0
		//jmp orgjz
		push ebx
		mov eax, dword ptr [dwCurMs]
		mov ebx, dword ptr [dwQuickSwapItemDelayMs]
		add eax, ebx
		mov dword ptr [dwQuickSwapItemMs], eax
		pop ebx
		add dword ptr [esp] ,0x12D //ǿ��������Ʒ
		xor eax ,eax
		ret
//orgjz:	
		//add dword ptr [esp] ,0x141
		//ret
	}
}

//Ctrl+�������
//������ģʽ��������Ҫ�ȴ����ݰ����ز���������Ʒ��������ButtonUp�в�һ���ܴ����
//��������LButtonUp�¼��д���������ܴ���������Ϸѭ���ж���ֱ���������

static int nClickStatus = 0;    //�Ƿ�Ctrl+����¼�
static BOOL fSwapProc = FALSE;  //�Ƿ��ѿ�ʼ����
static BOOL fSwapProcLoop = FALSE; //�Ƿ񽻸���Ϸѭ������
static D2MSG unDealMsg; //LButtonUp��Ϣ�ṹ����
static DWORD dwSwapTimer;//��ʱ��

/*
void __stdcall LButtonUpHandlerPatch(D2MSG *pMsg) {
	if ( fSwapProc ) return ;
	if ( nClickStatus==0 ) return ;
	fSwapProc = TRUE;
	fSwapProcLoop = FALSE;
	dwSwapTimer = dwCurMs;
	fSwapProcLoop = TRUE;
	unDealMsg = *pMsg;
	UnitAny *pItem = PLAYER->pInventory->pCursorItem;
	if ( pItem){
		Sleep(150);
		MoveItem( pMsg );
	}else{
		fSwapProcLoop = TRUE;
		unDealMsg = *pMsg;
		return;
	}
	fSwapProc = FALSE;
	nClickStatus = 0;
}
void __declspec(naked) LButtonUpHandlerPatch_ASM()
{
	//esp+4  = pMsg
	__asm {
		push ebp
		push ebx

		push [esp+0xC]
		call D2Storm511    //ԭʼ���ã��ȵ��ý�LButtonUp��Ϣ�����

		push [esp+0xC]
		call LButtonUpHandlerPatch

		pop ebx
		pop ebp
		ret 4
	}
}
*/
