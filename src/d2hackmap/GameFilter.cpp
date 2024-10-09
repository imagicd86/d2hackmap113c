#include "stdafx.h"
#include "d2ptrs.h"
#include "d2ptrs2.h"

// 4*eax+6FA2A900
static D2EditBox *pD2FilterBox = NULL ;

static DWORD pdwGamelist[1000] = {0, };
static char szFilter[30]={0};
static int mGames = 0;
static int mGameShows = 0 ;
BOOL fQuickRefresh = 0;
BOOL fAddlistProc = 0;
void ResetGameList(){
	memset(pdwGamelist , 0 , sizeof(pdwGamelist) ) ;
	mGames = 0;
	mGameShows = 0;
}

void hex(FILE *fp,int addr,void *buf1,int n);
BOOL  __fastcall D2MCPPacketHandler_05_Patch(BYTE* aPacket){
	//刷新列表时会将游戏列表重新发一次
	if(pD2FilterBox){
		char szTemp[30] ;
		DWORD dwIndex = *(DWORD*)&aPacket[3];
		BYTE  nPlayers = aPacket[7];
		BYTE  difficulty = aPacket[9]; //0 16 32
		/*if (logfp) {
			LOG("--- %d %d %d diff=%d ---\n",mGames,dwIndex,nPlayers,difficulty);
			hex(logfp,(int)aPacket,aPacket,64);
		}*/
		fAddlistProc  = TRUE ;
		if ( !dwIndex || nPlayers==0 ){
			fAddlistProc = FALSE;
			return TRUE;
		}
		for(int i =0 ; i<mGames ; i ++ ){
			if ( pdwGamelist[i] == dwIndex ) return  TRUE;
		}
		strncpy(szTemp , (char*)&aPacket[12] ,  29);
		/*switch (difficulty) {
			case 0:aPacket[12]=' ';break;
			case 16:aPacket[12]='E';break;
			case 32:aPacket[12]='D';break;
			default:aPacket[12]='?';break;
		}
		aPacket[13]=':';
		strncpy((char*)&aPacket[14], szTemp,  27);
		*/
		_strupr(szTemp);
		if( szFilter[0] && !strstr(szTemp ,szFilter) ){
			mGames++;
			return FALSE;
		}else{
			pdwGamelist[mGames++] = dwIndex;
			mGameShows++;
			return  TRUE;
		}
	}
	return  TRUE;
}
void __declspec(naked) D2MCPPacketHandler_05_Patch_ASM()
{
	__asm{
		pop eax  //ret addr

		push ecx
		push esi

		push eax //push ret addr
		
		push ecx
		push edx

		call D2MCPPacketHandler_05_Patch
		test eax , eax
		
		pop edx
		pop ecx
		mov eax, dword ptr [ecx+0x8]
		jz noadd
		ret
noadd:	
		add dword ptr [esp] , 0x45
		ret
	}
}


BOOL __stdcall Filterbox_ReturnHandler(wchar_t* wText)
{
	wchar_t *p = wText;
	int i = 0 ;
	while(*p){
		szFilter[i++] = (char)*(p++);
	}
	szFilter[i] = '\0';
	_strupr(szFilter);
	fQuickRefresh = 1;
	return TRUE;

}

BOOL __stdcall Filterbox_InputHandler(D2EditBox* pBox, int dwLength, char *pChar)
{
	return TRUE;
}

void CreateFilterBox(){

	if ( !pD2FilterBox ){
		ResetGameList();
		pD2FilterBox  = d2win_CreateEditBox(599, 185, 145, 41, 7, 18, 
				d2client_LoadUiImage("DATA\\GLOBAL\\UI\\FrontEnd\\textbox2"), 
				(DWORD)Filterbox_ReturnHandler, 0, 0, 
				d2multi_pEditboxPreferences);

		if (pD2FilterBox) {
			d2win_SetEditBoxProc( pD2FilterBox , Filterbox_InputHandler);
			pD2FilterBox->dwMaxLength = 6;
			//(pD2FilterBox->fnCallBack)( pD2FilterBox );
		}
	}

}

void __declspec(naked) CreateGameBoxPatch_ASM()
{
	__asm{

		push esi
		push eax

		call CreateFilterBox

		pop eax
		pop esi

		mov edx, 0x10
		ret
	}
}
void __stdcall DestroyGamelistPatch( D2EditBox* pListBox ){

	if( pListBox && pD2FilterBox ){
		ResetGameList();
		d2win_DestroyEditBox(pD2FilterBox);
		pD2FilterBox = NULL;
	}
	d2win_DestroyListBox( pListBox );

}

void __declspec(naked) GameListRefreshTimePatch_ASM()
{
	
	__asm{
		cmp eax, 0x3A98			//原始判断，15秒
		jb mytest
		jmp refresh
mytest:
		cmp eax , 0x5DC
		jb norefresh
		cmp [fAddlistProc] , 1	//还在加载
		je norefresh
		
		cmp [fQuickRefresh] , 0
		je norefresh
		
refresh:
		mov [fQuickRefresh] , 0
		pushad
		call ResetGameList
		popad
		ret

norefresh:
		add dword ptr [esp] , 0x16
		ret		
	}

}

void DrawGameListPatch(){

	if ( (*d2multi_pGameListControl) && pD2FilterBox ){

		wchar_t wszTemp[200];
		DWORD dwOldFone = d2win_SetTextFont(1);
		if( szFilter[0] ){
			wsprintfW(wszTemp ,  L" %d / %d (*%hs*)" , mGameShows , mGames ,szFilter );
		}else{
			wsprintfW(wszTemp ,  L" %d / %d " , mGameShows , mGames );
		}
		d2win_DrawText(L"Filter", 545, 170, 4, -1);
		d2win_DrawText(wszTemp,	  424, 190, 4, -1);
		if ( fAddlistProc ){
			static int loading = 50;
			int max = loading/50 ;
			for( int i = 0 ; i< max ;i++ ){
				wszTemp[i] = L'.';
			}
			wszTemp[max] = L'\0';

			d2win_DrawText(wszTemp,	  424, 170, 4, -1);
			loading++;
			if( loading>600 ) loading = 50;

		}
		d2win_SetTextFont(dwOldFone);

	}

}
void __declspec(naked) DrawGameListPatch_ASM()
{
	
	__asm{

		push esi

		call DrawGameListPatch

		pop esi

		mov esi, dword ptr [esi+0x3C]
		test esi, esi
		ret

	}

}

