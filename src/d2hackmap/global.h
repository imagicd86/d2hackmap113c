#ifdef FUNCTION_DECLARE
#define VK_WHEELDOWN 0x87
#define VK_WHEELUP 0x86
#define LEVELNO dwCurrentLevel
#define ACTNO dwCurrentAct
#define PLAYER (*d2client_pPlayerUnit)
#define PLAYERLIST (*d2client_pRosterUnitList)
#define GAMEINFO (*d2client_pGameInfo)
#define ACT (*d2client_pDrlgAct)
#define LAYER (*d2client_pAutomapLayer)
#define SCREENSIZE (*d2client_pScreenSize)
#define SCREENWIDTH (*d2client_pScreenWidth)
#define SCREENHEIGHT (*d2client_pScreenHeight)
#define DRAWOFFSET (*d2client_pDrawOffset)
#define DIFFICULTY (*d2client_pDifficulty)
#define EXPANSION (*d2client_pExpansion)
#define PING (*d2client_pPing)
#define FPS (*d2client_pFps)
#define QUESTDATA (*d2client_pQuestData)
#define QUESTPAGE (*d2client_pQuestPage)
#define GAMEQUESTDATA (*d2client_pGameQuestData)
#define FOCUSECONTROL (*d2win_pFocusedControl)
#define MONSTER_TYPE_NEUTRAL 0x80
#define MONSTER_TYPE_NORMAL 1
#define MONSTER_TYPE_DANGROUS 2
#define MONSTER_TYPE_REVIVE 4 
#define MONSTER_TYPE_MF 8 
#define MONSTER_TYPE_ACTBOSS 0x10
enum ToggleVarType {
	TOGGLEVAR_ONOFF=1,
	TOGGLEVAR_DOWN=2,
	TOGGLEVAR_DOWNPARAM=3,
	TOGGLEVAR_DOWNUPPARAM=4,
	TOGGLEVAR_DOWNPTR=5,
};
enum ToggleVarKeyType {
	ToggleVarKeyType_InGame=0,
	ToggleVarKeyType_OutGame=1,
	ToggleVarKeyType_Always=2,
};
struct ToggleVar {
	int type;//1按键切换开关(可触发事件) 2按键触发事件不带参数 3或0按键触发事件带参数 4:带参数且松开时有响应函数
	int isOn;//是否开启
	int key;//触发按键
	int value32;//命令值 set to >=1 if isOn
	char* desc;//事件描述
	union {
		void *func; //调用的函数 return 0 if handled
		int (*funcVoid)();
		int (*funcInt)(int);
		int (*funcPtr)(void *ptr);
	};
	union {
		int param;     //func2函数参数
		void *paramPtr;
	};
	int isLoad;  //是否在配置中加载的
	int keyType; //0在游戏内起作用,1在游戏外起作用,2一直起作用
	union {
		void *funcUp;
		int (*funcUpVoid)();
		int (*funcUpInt)(int);
		int (*funcUpPtr)(void *ptr);
	};
	wchar_t *wdesc;
	struct ToggleVar *next; //Same key value
};
enum ConfigVarType {
	CONFIG_VAR_TYPE_KEY=1,
	CONFIG_VAR_TYPE_INT=2,
	CONFIG_VAR_TYPE_STR=3,
	CONFIG_VAR_TYPE_WSTR=4,
	CONFIG_VAR_TYPE_D2STR=5,
	CONFIG_VAR_TYPE_CHAR_ARRAY0=6,
	CONFIG_VAR_TYPE_CHAR_ARRAY1=7,
	CONFIG_VAR_TYPE_INT_ARRAY0=8,
	CONFIG_VAR_TYPE_INT_ARRAY1=9,
	CONFIG_VAR_TYPE_STR_ARRAY0=10,
	CONFIG_VAR_TYPE_STR_ARRAY1=11,
	CONFIG_VAR_TYPE_KEY_ARRAY0=12,
	CONFIG_VAR_TYPE_KEY_ARRAY1=13,
	CONFIG_VAR_TYPE_LEVEL_TARGET=14,
	CONFIG_VAR_TYPE_SWITCH_SKILL=15,
	CONFIG_VAR_TYPE_SCREEN_SCROLL=16,
	CONFIG_VAR_TYPE_MINIMAP_SCROLL=17,
	CONFIG_VAR_TYPE_ACCOUNT=18,
};
struct ConfigVar {
	int		type;
	char	*szCmdName;
	void	*pVar;
	int	size32;
	short	anArrayMax[4];
	int keyType;//0:inGame,1:outGame,2:Always
	char *keyDesc;
	int (*keyFunc)(int);
	int base; //First array index
	int useCount;
};
void addConfigVar(ConfigVar *var);
int IsKeyDown(int keyCode);
void formatKey(char *buf,int vk);
void setupKey(ToggleVar *p);
ToggleVar *addExtraKey(int key);
int GetItemIndex(int dwTxtFileNo);
void recheckSelfItems();
int DropProtection(UnitAny *pItem);
void checkBossMonster( UnitAny  *pUnit );
void CheckDangerousPlayer( UnitAny  *pUnit );
void CheckDangerousMonster( UnitAny  *pUnit );
BOOL Install();
void Uninstall();
BOOL LoadConfig();
void ShowWarningMessage();
extern ToggleVar tPacketHandler;
#endif
#ifdef VARIABLE_DEFINE
#ifndef GVARDEF
	#define GVARDEF
	#define GVAR(d1,v1,v2) extern d1 v1 ;
	#define GVAR2(d1,v1,...) extern d1 v1 ;
#else
	#define GVAR(d1,v1,v2) d1 v1 = v2 ;
	#define GVAR2(d1,v1,...) d1 v1 = { __VA_ARGS__ } ;
#endif
#endif
#ifdef VARIABLE_DEFINE
	extern char *szVersion;
	GVAR(HANDLE,dllHeap,NULL)
	GVAR(HANDLE,confHeap,NULL)
	GVAR(HANDLE,gameHeap,NULL)
	GVAR (int,			dwCpuUser,					0)
	GVAR (int,			dwCpuKernel,					0)
	GVAR (int,			dwGameWindowId,					1)
	GVAR(char,			szRuntimePath[256]	,		"runtime")
	GVAR (BOOL,		fSinglePlayer,				0)
	GVAR (volatile int,			dwCurMs,					0)
	GVAR (int,			dwEnterGameMs,					0)
	GVAR (int,			dwSinglePlayerContext,					0)
	GVAR (BOOL,			fInGame,				FALSE)
	GVAR (BOOL,			fPlayerInTown,			TRUE)
	GVAR (int,			dwGameLng,					-1)
	GVAR (int,		dwCurrentAct,				0)
	GVAR (int,		dwCurrentLevel,				1)
	GVAR (int,		dwPlayerX,				0)
	GVAR (int,		dwPlayerY,				0)
	GVAR (int,		dwPlayerId,					0)
	GVAR (int,		dwPlayerPartyId,					0)
	GVAR (int,		dwPlayerClass,					0)
	GVAR (Skill *,			pLeftSkill,					NULL)
	GVAR (Skill *,			pRightSkill,					NULL)
	GVAR (int,			dwLeftSkill,					-1)
	GVAR (int,			dwRightSkill,					-1)
	GVAR (int,			dwLeftSkillStatus,					0)
	GVAR (int,			dwRightSkillStatus,					0)
	GVAR (int,			fCanUseLeftSkill,		1)
	GVAR (int,			fCanUseRightSkill,		1)
	GVAR (int,		dwPlayerLevel,					0)
	GVAR (int,		dwPlayerMaxHP,					0)
	GVAR (int,		dwPlayerHP,					0)
	GVAR (int,		dwPlayerMaxMana,				0)
	GVAR (int,		dwPlayerMana,					0)
	GVAR (int,		dwPlayerFcrFrame,					0)
	GVAR (int,		dwPlayerFcrMs,					0)

	GVAR (int,		dwLoopFPS,					0)
	GVAR (int,		dwDrawFPS,					0)

	GVAR (int,		dwRecheckSelfItemMs,					0)
	GVAR (UnitAny *,		leftWeapon,					0)
	GVAR (UnitAny *,		rightWeapon,					0)
	GVAR (int,		dwTownPortalCount,					0)
	GVAR (int,		dwIdentifyPortalCount,					0)
	GVAR (int,		fUsingBow,					0)
	GVAR (int,		fUsingCrossBow,					0)
	GVAR (int,		fUsingThrow,					0)
	GVAR (int,		dwHPotionCount,					0)
	GVAR (int,		dwMPotionCount,					0)
	GVAR (int,		dwRPotionCount,					0)
	GVAR (int,		dwArrowCount,					0)
	GVAR (int,		dwCArrowCount,					0)
	GVAR (int,		dwThrowCount,					0)
	GVAR (int,		dwSkillChangeCount,					0) //increase if skill level maybe changed

	GVAR (BOOL,			fEnterGameSound,				0)
	GVAR (int,			dwEnterGameShowDifficultyMs,				0)
	GVAR2(int,		actlvls[],	1, 40, 75, 103, 109, 137 )
	GVAR (BOOL,			fLanguageCheck,			TRUE)
	GVAR (BOOL,			fLocalizationSupport,		FALSE)
	GVAR (BOOL,			fLoadItemColours,		1)

	GVAR (int,		fWinActive,						1)
	GVAR (int,		fUserOperating,						0)
	GVAR (int,		fLeftBtnDown,						0)
	GVAR (int,		fRightBtnDown,						0)
	GVAR (int,		dwBtnReleaseMs,						0)
	GVAR (int,	forceStandStill,				0)
	
	GVAR2(ToggleVar,tShowTestInfo,TOGGLEVAR_ONOFF,0,-1,	1,"ShowTestInfo")
#endif
#ifdef VARIABLE_DEFINE
	#undef GVAR
	#undef GVAR2
#endif
