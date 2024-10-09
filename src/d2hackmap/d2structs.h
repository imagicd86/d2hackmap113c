/*
	Coordinate coversion
	tileX=unitX*5	
	tileY=unitY*5
	drawX=(unitX-unitY)*16
	drawY=(unitX+unitY)*8
*/
#ifndef D2_STRUCTS_H
#define D2_STRUCTS_H

struct GfxCell;
struct CellFile;
struct CellContext;
struct PresetUnit;
struct AreaTile;
struct AreaRectData;
struct AreaRectInfo;
struct DrlgLevel;
struct DrlgMisc;
struct DrlgAct;
struct AutomapNode;
struct AutomapLayer;
struct LevelDefTxt;
struct ObjectTxt;
struct LevelTxt ;
struct ItemTxt;
struct MonsterTxt;
struct SuperUniqueTxt;
struct SetItemTxt;
struct ItemProp;
struct UniqueItemTxt;
struct RuneWordTxt;

struct PlayerData;
struct MonsterData;
struct ObjectData;
struct MissileData;
struct ItemData;
struct UnitInventory ;

struct StaticPath;
struct DynamicPath;
struct UnitAny;
struct RosterUnit;
struct PetUnit;
struct MonsterMinion;


struct TreasureClassItem ;
struct TreasureClass;
struct GameStructInfo;
struct D2MSG;
struct D2EditBox ;
struct QuestInfo;
struct Waypoint;
struct StatList;
struct SkillInfo;
struct Skill;

struct D2Seed {
	DWORD	dwLowSeed;
	DWORD	dwHighSeed;
};


struct DrlgAct {
	DWORD  _1[4];			//+00
	AreaRectData *pAreaRectData;		//+10
	DWORD	dwActNo;		//+14
	DWORD  _2[12];			//+18
	DrlgMisc *pDrlgMisc;	//+48
};

struct DrlgMisc {
	DWORD	_1[37];				//+00
	DWORD	dwStaffTombLvl;		//+94
	DWORD	_2[248];			//+98
	DWORD	*pMemPool;			//+478
	DrlgLevel *pLevelFirst;		//+47C
	DWORD	_3;					//+480
	DWORD	dwBossTombLvl;		//+484
};

struct DrlgLevel {
	DWORD	_1[4];			//+00
	AreaRectInfo *pAreaRectInfo; //+10
	DWORD	_2[102];		//+14
	DrlgLevel *pNext;		//+1AC
	DWORD	_3;				//+1B0
	DrlgMisc  *pDrlgMisc;	//+1B4 
	DWORD	_4[2];			//+1B8	
	DWORD	dwLvlType;		//+1C0
	DWORD	_5[3];			//+1C4			
	DWORD	dwLevelNo;		//+1D0
};

struct AreaRectInfo {
	DWORD   _1[2];			 //+00
	AreaRectInfo **pInfoNear; //+08
	DWORD   _2[5];			 //+0C
	struct{
		DWORD dwDef;		
	}	*pLvlPreset;		 //+20
	AreaRectInfo  *pNext;		 //+24
	int dwAreaTiles;	 //+28
	int	nearbyRectCount;	 //+2C
	AreaRectData *pAreaRectData;	     //+30
	int	tileX;			 //+34
	int	tileY;			 //+38
	int	tileW;		 //+3C
	int	tileH;		 //+40
	DWORD   _4;				 //+44
	DWORD	dwPresetType;	 //+48
	AreaTile *pAreaTiles;	 //+4C
	DWORD   _5[2];			 //+50
	DrlgLevel *pDrlgLevel;	 //+58
	PresetUnit *pPresetUnits;//+5C	
};
struct AreaRectTile {
	int xPixel; //+00
	int yPixel; //+04
	int xi; //+08
	int yi; //+0C
	int off10; //+10
	int flags; //+14
	int off18[6]; //+18
};
struct AreaRectTiles {
	int off0,off4; //+00
	AreaRectTile *tiles; //+08
	int count; //+0C
};
struct AreaRectBitmap {
	int unitX,unitY,unitW,unitH; //+00
	int tileX,tileY,tileW,tileH; //+10
	unsigned short *bitmap;
};
struct AreaRectData {
	AreaRectData **paDataNear; //+00
	DWORD off04;			 //+04				
	AreaRectTiles *tiles;			 //+08
	DWORD off0C;			 //+0C
	AreaRectInfo *pAreaRectInfo;		 //+10
	DWORD	off14[3];			 //+14
	AreaRectBitmap *bitmap; //+20
	int	nearbyRectCount;	 //+24
	int off28[2]; //+28
	int off30[4]; //+30
	int off40[3]; //+40
	int unitX,unitY,unitW,unitH; //+4C
	int tileX,tileY,tileW,tileH; //+5C
	int off6C; //+6C
	int off70[3]; //+70
	AreaRectData *pNext;		 //+7C
};

struct AreaTile {
	AreaRectInfo *pAreaRectInfo;	//+00
	AreaTile  *pNext;	//+04
	DWORD	  _1[2];	//+08
	DWORD	  *pNum;	//+10
};

struct PresetUnit {
	DWORD	_1;			 //+00
	DWORD	dwTxtFileNo; //+04
	DWORD	unitDx;		 //+08
	PresetUnit *pNext;   //+0C
	DWORD	_2;			 //+10
	DWORD	dwUnitType;  //+14
	DWORD	unitDy;		 //+18
};

struct AutomapNode {
	DWORD	fSaved;		//+00
	WORD	wCellNo;	//+04
	WORD	drawXDiv10;		//+06
	WORD	drawYDiv10;		//+08
	WORD	wWeight;	//+0A = -1, 0, 1
	AutomapNode *pLess; //+0C
	AutomapNode *pMore; //+10
};

struct AutomapLayer {
	DWORD	dwLayerNo;		//+00
	DWORD	fSaved;			//+04
	AutomapNode	*pFloors;	//+08
	AutomapNode *pWalls;	//+0C
	AutomapNode *pObjects;	//+10
	AutomapNode *pExtras;	//+14
	AutomapLayer *pNext;	//+18
};


struct GfxCell {
	DWORD	dwFlags;	//+00
	DWORD	dwWidth;	//+04
	DWORD	dwHeight;	//+08
	DWORD	dwXoffs;	//+0c
	DWORD	dwYoffs;	//+10
	DWORD	_2;
	DWORD	dwParent;	//+18
	DWORD	dwLength;	//+1c
	BYTE	nCols[1];	//+20
};

struct CellFile {
	DWORD	dwVersion;		//+00
	struct 
	{
		WORD dwFlags;
		BYTE mylastcol;
		BYTE mytabno:1;
	};						//+04
	DWORD	eFormat;		//+08
	DWORD	dwTermination;	//+0C
	DWORD	dwNumdirs;		//+10
	DWORD	dwNumCells;		//+14
	GfxCell	*pCells[1];		//+18
};

struct CellContext {
	DWORD		dwCellNo;		//+00
	DWORD		dwDirNo;		//+04  (0-63, other values asplode even when file has more dirs) 
	DWORD		dwDirection;	//+08
	DWORD		_1[10];			//+0C
	CellFile	*pCellFile ;	//+34
	DWORD		_2[3];			//+3C һ��Ҫ����0x48�ĳ��ȣ���Ȼ��ʼ������
};

struct UnitAny {
	int	dwUnitType;		//+00
	int	dwTxtFileNo;	//+04
	DWORD	*pMemPool ;		//+08	not used, always NULL 
	int	dwUnitId;		//+0C
	int	dwMode;			//+10
			/*mode index from   PlrMode.txt  MonMode.txt  ObjMode.txt  
					Missiles, Items and VisTiles have their own modes (for missiles this holds the collision type) 
					eItemModes 3=on the floor
			*/
	union {
		PlayerData *pPlayerData; 
		MonsterData *pMonsterData; 
		ObjectData *pObjectData; 
		ItemData *pItemData; 
		MissileData  *pMissileData; 
	};	//+14
	int	dwAct;			//+18
	DrlgAct *pDrlgAct;		//+1C
	D2Seed	seed;			//+20	
	DWORD	dwInitSeed ;	//+28
	union {
		StaticPath	*pItemPath;	//	(Objects, VisTiles, Items) 
        DynamicPath	*pMonPath;	//	(Players, Monsters, Missiles) 
	};	//+2C
	DWORD	_1[11];	//+30
	StatList *pStatList;	//+5C	
	UnitInventory *pInventory; //+60
	DWORD	_2[12];		//+64
	int	dwOwnerType;	//+94
	int	dwOwnerId;		//+98
	DWORD	_3[3];		//+9C
	SkillInfo *pSkill;		//+A8
	DWORD	_4[6];			//+AC
	DWORD	dwFlags1;		//+C4
	DWORD	dwFlags2;		//+C8
	DWORD	_5[6];			//+CC
	UnitAny *pHashNext;		//+E4
	UnitAny *pListNext;		//+E8
};

struct PvPInfo {			//size = 0x0C
	int	dwUnitId;		//+00
	DWORD	dwFlag;			//+04	0000 ���� 0001 ���� 0010 ���� 0100  ��Ĭ 1000 �ж�
	PvPInfo *pNext;			//+08
};
struct MonsterMinion {		//�����Ϣ,һ�㶼��
	int	dwUnitId;		//+00
	MonsterMinion *pNext;	//+04
};
struct RosterUnit { 
   char		szName[16];			//0x00 
   int	dwUnitId;			//0x10 
   int	dwPartyLife;		//0x14 
   int	dwKills;			//0x18 ?
   int	dwClassId;			//0x1C 
   WORD		wLevel;				//0x20 
   WORD		wPartyId;			//0x22 
   int	dwLevelNo;			//0x24 
   int	dwPosX;				//0x28 
   int	dwPosY;				//0x2C 
   DWORD	dwPartyFlags;		//0x30 
   PvPInfo	**pPvPInfo;			//0x34 
   MonsterMinion **pMinon;		//0x38 
   DWORD	_6[10];				//0x3C 
   WORD		_7;					//0x64 
   char		szName2[16];		//0x66 
   WORD		_8;					//0x76 
   DWORD	_9[2];				//0x78 
   RosterUnit * pNext;			//0x80 
};
struct PetUnit {
	int	dwTxtFileNo;		//+00 ��Ӧmonstats.tx��hcidx
	int	dwPetType;			//+04 ��Ӧpettype.txt
	int	dwUnitId;			//+08
	int	dwOwnerId;			//+0C ����GUID
	DWORD	dwFlag1;			//+10
	int	dwOffsetX;			//+14 ��ȷ��
	int	dwOffsetY;			//+18 ��ȷ��
	int	dwHpPercent;		//+1C
	int	dwOwerType;			//+20  
	DWORD	dwInitSeed;			//+24  ��Ӷʱ���ɣ����ٱ仯
	WORD	wLocaleTxtNo;		//+28  �������� for pet
	BYTE	_1[6];				//+2A
	PetUnit *pNext;				//+30
};
struct StatEx {			//size 8
	WORD wParam;	
	WORD wStatId;		//statNo from ItemStatCost.txt
	DWORD dwStatValue;
};
struct Stat{
	StatEx	*pStats;
	WORD	wStats;			
	WORD	wSizeInBits;
};
// StatList ��StatListEx��̬�ṹ��ͨ��dwListFlag���� , 0x80000000ΪStatListEx
// sizeof(StatListEx) = 0x64  sizeof(StatList) = 0x40  
struct StatList {				
	DWORD	pMemPool;			//+00	always NULL
	UnitAny	*pUnit;				//+04	the unit to which the list is attached   for StatListEx & item = item owner
	int	dwOwnerType;		//+08
	int	dwOwnerId;			//+0C
	DWORD	dwListFlag;			//+10
	DWORD	dwStateNo;			//+14
	DWORD	dwExpireFrame;		//+18	the frame at which the state expires 
	int	dwSkillNo;			//+1C	Id of the skill that created the stat list
	int	dwSkillLvl;			//+20	level of the skill that created the stat list 
	Stat	sBaseStat ;			//+24
	StatList *pPrevList;		//+2C	previous list on this unit 
	StatList *pNextLis;			//+30	next list on this unit 
	StatList *pPrev;			//+34	previous list;  for StatListEx , if this one is owned by a item, this points to the item owners list
	union {
		void (__fastcall *func)(UnitAny* ,DWORD ,BOOL);//StatList  function to call when the list is removed 
		StatList *pNextListEx;						   //next StatListEx
	};							//+38
	StatList *pNext;			//+3C	next list  for StatListEx = MyLastList
	//only for StatListEx
	StatList *pMyStatList;		//+40
	UnitAny	 *pUnitOwner;		//+44	StatListEx owner
	Stat	sFullStat ;			//+48
	Stat	sModStat ;			//+50
	void	*StatFlags;			//+58
	void	*fCallback;			//+5C function to call by SetStat, AddStat when a fcallback stat changes
	void	*pGame;				//+60 on server
};
struct DynamicPath {
	WORD	wOffsetX;		//+00
	WORD	wUnitX;			//+02
	WORD	wOffsetY;		//+04
	WORD	wUnitY;			//+06
	int	drawX;		//+08
	int	drawY;		//+0C
	WORD	wTargetX;		//+10
	WORD	wTargetY;		//+12
	DWORD	_2[2];			//+14
	AreaRectData *pAreaRectData;		//+1C
	AreaRectData *pAreaRectDataUnk;	//+20
	DWORD	_3[3];			//+24
	UnitAny *pUnit;			//+30
	DWORD	dwFlags;		//+34
	DWORD	_4;				//+38
	DWORD	dwPathType;		//+3C
	DWORD	dwPrevPathType;	//+40
	DWORD	dwUnitSize;		//+44
	DWORD	_5[4];			//+48
	UnitAny *pTargetUnit;	//+58
	DWORD	dwTargetType;	//+5C
	DWORD	dwTargetId;		//+60
	BYTE	nDirection;		//+64
};
struct StaticPath {
	AreaRectData *pAreaRectData;		//+1C
	int	drawX;		//+04
	int	drawY;		//+08
	int	unitX;			//+0C
	int	unitY;			//+10
};

struct SkillTxt {
	WORD	wSkillId; //+00
	char flags1; //+02
	char flags2; //+03
	char flags3; //+04 0x10:passiveSkill 0x20:aura
	char flags4; //+05 1:canUseInTown 0x10:createMinion
};
struct SkillInfo {
	DWORD *pGame1C;			//+00
	Skill *pFirstSkill;		//+04
	Skill *pLeftSkill;		//+08
	Skill *pRightSkill;		//+0C
	Skill *pCurrentSkill;	//+10
};
struct Skill {
	struct SkillTxt *pSkillInfo;			//+00
	Skill	*pNextSkill;	//+04
	DWORD	dwMode;			//+08
	DWORD	dwFlag0;		//+0C
	DWORD	_1[2];			//+10
	DWORD	dwTagets;		//+18
	DWORD	dwTargetType;	//+1C unit type
	DWORD	dwTargetId;		//+20 unit id
	DWORD	_2;				//+24
	DWORD	dwSkillLevel;	//+28
	DWORD	dwLevelBonus;	//+2C
	DWORD	dwQuality;		//+30  ���� ==> �س���֮�������
	DWORD	dwItemId;		//+34 item charge, -1 for player skill 
};
struct QuestInfo {
	DWORD *pBuffer;					//0x00
	DWORD _flag;
};
struct Waypoint {
	DWORD flags;					//0x00
};
struct PlayerData {
	char	szName[16];				//+00   len of charname <= 15 
	QuestInfo *pNormalQuest;		//0x10
	QuestInfo *pNightmareQuest;		//0x14
	QuestInfo *pHellQuest;			//0x18
	Waypoint *pNormalWaypoint;		//0x1c
	Waypoint *pNightmareWaypoint;	//0x20
	Waypoint *pHellWaypoint;		//0x24
};
struct MissileData{
	BYTE	_1[8];			//+00
	WORD	wActivateFrame;	//+08	Activate column from Missiles.txt 
	WORD	wLvl;			//+0A
	WORD	wSkillNo;		//+0C
	int	wTotalFrames;	//+0E	the number of frames before the missile vanishes from Missiles.txt 
	int	dwCurrentFrame;	//+10	the current traveling frame
	DWORD	dwMissileFlags;	//+14	this depends on the missile functions used 
	int	dwOwnerType;	//+18	unit type of the missile owner 
	int	dwOwnerId;		//+1C	global unique identifier of the missile owner 
	int	dwUnitType;		//+20	unit type of a target, for homing missiles 
	int	dwUnitId;		//+24	global unique identifier of a target, for homing missiles 
	DWORD	dwHomeStatus;	//+28	for homing missiles like Guided Arrow 
	struct {
		WORD	xPos;
		WORD	yPos;
	}	sCoordShort;
};

struct MonsterData {
	MonsterTxt	*pMonsterTxt;	//+00
	BYTE	nComponents[16];	//+04	Order: HD, TR, LG, RA, LA, RH, LH, SH, S1, S2, S3, S4, S5, S6, S7, S8
	WORD	wNameSeed;			//+14;
	union{
		BYTE	bTypeFlags;	//+16
		struct {
			BYTE fOther:1;		//set for some champs, uniques
			BYTE fUnique:1;		//super unique
			BYTE fChamp:1;		
			BYTE fBoss:1;		//unique monster ,usually boss
			BYTE fMinion:1;		
			BYTE fPoss:1;		//possessed
			BYTE fGhost:1;		//ghostly
			BYTE fMulti:1;		//multishotfiring
		}; //+16
	};//+16
	BYTE	nLastMode;			//+17
	DWORD	dwDuriel;			//+18
	BYTE	anEnchants[9];		//+1C
	BYTE	_1;					//+25
	WORD	wUniqueNo;			//+26	hcIdx from superuniques.txt for superuniques 
	void	*pAiGeneral;		//+28
	wchar_t	*wszMonName;		//+2C	server side is pAiParams
	BYTE	_2[16];				//+30
	DWORD	dwNecroPet;			//+40
	BYTE	_3[16];				//+44
	DWORD	dwAiState;			//+54	this is used to tell monsters what special state has been set, this tells them they just got attacked etc
	DWORD	dwLevelNo;			//+58	the Id from levels.txt of the level they got spawned in 
	BYTE	nSummonerFlags;		//+5C	byte used only by the summoner
};
struct ObjectData {
	ObjectTxt *pObjectTxt;		//+00
	BYTE nShrineNo,off05,off06,off07; //+04
	int off08,off0C; //+08
	int off10,off14,off18,off1C; //+10
	int off20,off24; //+20
	char owner[16]; //+28
};
struct ItemData { 
	DWORD	dwQuality;			//+00 
	D2Seed	seed;				//+04
	int	dwOwnerId;			//+0C -1 when not owned by player, otherwise equal to player GUID 
	DWORD	dwFingerPrint;		//+10	initial spawning seed
	DWORD	dwCommandFlags;		//+14
	DWORD	dwItemFlags;		//+18 
	DWORD	_1[2];				//+1C 
	DWORD	ActionStamp;		//+24
	DWORD	dwFileIndex;		//+28 index from data files UniqueItems.txt, SetItems.txt, QualityItems.txt, LowQualityItems.txt
	DWORD	dwItemLevel;		//+2C	ILvl
	WORD	wItemFormat;		//+30
	WORD	wRarePrefix;		//+32
	WORD	wRareSuffix;		//+34
	WORD	wAutoPrefix;		//+36
	WORD	wMagicPrefix[3];	//+38 
	WORD	wMagicSuffix[3];	//+3E 
	BYTE	nBodyLocation;		//+44 Id from BodyLocs.txt;this field isn't always cleared , use D2Common.#11003 instead of checking this 
	BYTE	nItemLocation;		//+45 -1 equiped 0 Inventory , 3 cube , 4 stash  
	BYTE	_2[2];				//+46 
	BYTE	nEarLevel;			//+48
	BYTE	nInvGfxIdx;			//+49
	char	szPlayerName[16];	//+4A	//used for Ears and Personalized items 
	BYTE	_3[2];				//+5A
	UnitInventory *pOwnerInventory;		//0x5C for socketed items this points to the inventory of the parent item
	DWORD	_4;					//+60 
	UnitAny *pNextInvItem;		//+64	item filling the next socket, if pNodeOwnerInventory is set 
	BYTE	_11;				//+68 
	BYTE	nLocation;			//+69 Actual location, 0 ground, 1 cube/stash/inv,2 belt,3 body
}; 
struct UnitInventory { 
	DWORD	dwInvStamp;			//+00 0x1020304, used to verify the inventory is valid 
	void	*pMemPool;			//+04 always NULL
	UnitAny *pOwner;			//+08 
	UnitAny *pFirstItem;		//+0C 
	UnitAny *pLastItem;			//+10 
	UnitInventory *pInvInfo;	//+14 list of pointers to equipped gear 
	DWORD	dwInvInfoCount;		//+18 count for above 
	DWORD	dwWeaponId;			//+1C
	UnitAny *pCursorItem;		//+20 points to self on items that aren't placed into sockets ,for player point to cursor item
	int	dwOwnerId;			//+24 
	int	dwFilledSockets;	//+28 
};
struct TreasureClassItem {	//size = 0x1C ����һ��Ҫ���㣬��Ȼʹ��ʱ������
	DWORD _1[2];		//+00
	DWORD dwThingNo;	//+08
	struct {
		DWORD _2:2;
		DWORD fTc:1;
	};					//+0C
	DWORD _3[3];		//+10
};
struct TreasureClass {	//size = 0x2C
	WORD wGroup;		//+00
	WORD wLevel;		//+02
	int dwItemNums;	//+04
	DWORD _1[8];		//+08
	TreasureClassItem *pItems; //+28
};
struct D2MSG {
	HWND	hwnd;				//+00
	DWORD	dwMessage;			//+04
	WPARAM	wParam;				//+08
	union {
		DWORD lParam;
		struct {
			WORD xpos;
			WORD ypos;
		};
	};							//+0C
	DWORD	_1;					//+10
	HWND	hwnd2;				//+14
	DWORD	_2[2];				//+18
};
struct D2EditBox {
	DWORD	dwType;				//+00
	CellFile *pCellFile;		//+04
	DWORD   dwFlag;				//+08
	int	dwPosX;				//+0C   
	int	dwPosY;				//+10
	int	dwSizeX;			//+14
	int	dwSizeY;			//+18
	void (__fastcall *fnCallBack)(D2EditBox*); // +1C
	DWORD _3[7];				//+20
	D2EditBox *pNext;			//+3C
	DWORD   _4;					//+40
	int   dwOffsetY;			//+44
	union {
		DWORD   dwMaxLength;		//+48
		DWORD	dwScrollEntries;	//+48
	};
	DWORD   dwScrollPosition;	//+4C ?
	DWORD	_5;					//+50
	DWORD	dwSelectStart;		//+54
	DWORD	dwSelectEnd;		//+58
	wchar_t wszText[256];		//+5C
	DWORD	dwCursorPos;		//+25C
	DWORD	dwIsCloaked;		//+260
	DWORD _6[6]; //+264
	struct D2EditBox *pNext2; //+27c
};
struct Damage {
	DWORD	dwHitFlags;			//+00
	/*
		0x00000001 - HITFLAG_SRCDAMAGE_MISSILE 
		0x00000002 - HITFLAG_SUCCESSFUL_CRITICAL_HIT 
		0x00000010 - HITFLAG_FRIENDLY_FIRE 
		0x00000020 - HITFLAG_SRCDAMAGE_MELEE 
		0x00000100 - HITFLAG_BYPASS_UNDEAD 
		0x00000200 - HITFLAG_BYPASS_DEMONS 
		0x00000400 - HITFLAG_BYPASS_BEASTS 
	*/

	DWORD	dwResultFlags;			//+04
	/*
		0x00000001 - RESULTFLAG_HIT 
		0x00000002 - RESULTFLAG_DEATH 
		0x00000004 - RESULTFLAG_GETHIT 
		0x00000008 - RESULTFLAG_KNOCKBACK 
		0x00000010 - RESULTFLAG_BLOCK 
		0x00000020 - RESULTFLAG_DISALLOW_EVENTS 
		0x00000100 - RESULTFLAG_DODGE 
		0x00000200 - RESULTFLAG_AVOID 
		0x00002000 - RESULTFLAG_SOFTHIT 
		0x00008000 - RESULTFLAG_WEAPONBLOCK 
	*/
	DWORD	dwPhysicalDamage;		//+08
	DWORD	dwEnhancedDamagePercent;//+0C
	DWORD	dwFireDamage;			//+10
	DWORD	dwBurnDamage;			//+14
	DWORD	dwBurnLength;			//+18
	DWORD	dwLightningDamage;		//+1C
	DWORD	dwMagicDamage;			//+20
	DWORD	dwColdDamage;			//+24
	DWORD	dwPoisonDamage;			//+28
	DWORD	dwPoisonLength;			//+2C
	DWORD	dwColdLength;			//+30
	DWORD	dwFreezeLength;			//+34
	DWORD	dwLifeSteal;			//+38
	DWORD	dwManaSteal;			//+3C
	DWORD	dwStaminaSteal;			//+40
	DWORD	dwStunLength;			//+44
	DWORD	dwAbsorbedLife;			//+48
	DWORD	dwDamageTotal;			//+4C
	DWORD	_1;						//+50	
	DWORD	dwPiercePct;			//+54	chance to pierce target for missiles 
	DWORD	dwDamageRate;			//+58
	DWORD	_2;						//+5C
	DWORD	dwHitClass;				//+60
	BYTE	fHitClassActiveSet;		//+64
	BYTE	nType;					//+65
	WORD	_3;						//+66
	DWORD	dwConvPercent;			//+68
};


struct SuperUniqueTxt {		//size = 0x34
	WORD	wUniqueNo;		//+00
	WORD	wLocaleTxtNo;	//+02
	DWORD	wMonIdx;		//+04	index in monstat.txt
	DWORD	dwUniqueNo;		//+08
	DWORD	dwMod1;			//+0C
	DWORD	dwMod2;			//+10
	DWORD	dwMod3;			//+14
	DWORD	dwMonSound;		//+18
	DWORD	dwMinGrp;		//+1C
	DWORD	dwMaxGrp;		//+20
	DWORD	_1;				//+24
	BYTE	Utrans[4];		//+28
	WORD	Tcs[4];			//+2C

};

struct ObjectTxt {				//size = 0x1C0
	char	szName[64];			//+00
	wchar_t wszName[64];		//+40
	char	szToken[3];			//+C0
	BYTE	nSpwanMax;			//+C3
	BYTE	nSelectable[8];		//+C4
	WORD	wTrapProp;			//+CC
	BYTE	_1[2];				//+CE
	DWORD	dwSizeX;			//+D0
	DWORD	dwSizeY;			//+D4
	DWORD	dwFrameCnt[8];		//+D8	��Ҫ����8λ
	WORD	wFrameDelta[8];		//+F8
	BYTE	nCycleAnim[8];		//+108
	BYTE	nLit[8];			//+110
	BYTE	nBlockLight[8];		//+118
	BYTE	nHasCollision[8];	//+120
	BYTE	fAttackable;		//+128
	BYTE	nStrart[8];			//+129
	BYTE	nOrderFlag[8];		//+131
	BYTE	nEnvEffect;			//+139
	BYTE	nIsDoor;			//+13A
	BYTE	nBlocksVis;			//+13B
	BYTE	nOrientation;		//+13C
	BYTE	nPreOperate;		//+13D
	BYTE	nTrans;				//+13E
	BYTE	nMode[8];			//+13F
	BYTE	_2;					//+147
	DWORD	dwXoffset;			//+148
	DWORD	dwYoffset;			//+14C
	BYTE	nDraw;				//+150
	BYTE	nHd;				//+151
	BYTE	nTR;				//+152
	BYTE	nLG;				//+153
	BYTE	nRA;				//+154
	BYTE	nLA;				//+155
	BYTE	nRH;				//+156
	BYTE	nLH;				//+157
	BYTE	nSH;				//+158
	BYTE	nS[8];				//+159	S1-S8
	BYTE	nTotalPieces;		//+161
	BYTE	nXSpace;			//+162
	BYTE	nYSpace;			//+163
	BYTE	nRed;				//+164
	BYTE	nGreen;				//+165
	BYTE	nBlue;				//+166
	BYTE	nSubClass;			//+167
	DWORD	dwNameOffset;		//+168
	BYTE	_3[2];				//+16C
	BYTE	nOperateRange;		//+16E
	BYTE	nShrineFnc;			//+16F
	BYTE	nAct;				//+170
	BYTE	_4[7];				//+171
	DWORD	dwParm[8];			//+178
	BYTE	_5[4];				//+198
	BYTE	nDamage;			//+19C
	BYTE	_6[3];				//+19D
	DWORD	dwLeft;				//+1A0
	DWORD	dwTop;				//+1A4
	DWORD	dwWidth;			//+1A8
	DWORD	dwHeight;			//+1AC
	BYTE	_7;					//+1B0
	BYTE	nInitFn;			//+1B1
	BYTE	nPopulateFn;		//+1B2
	BYTE	nOperateFn;			//+1B3
	BYTE	nClientFn;			//+1B4
	BYTE	_8[7];				//+1B5
	DWORD	nAutoMap;			//+1BC

};

struct LevelTxt	{				//size = 0x220
	WORD	wLevelNo;			//+00
	BYTE	nPal;				//+02
	BYTE	nAct;				//+03
	BYTE off4,weather,off6,off7; //+04
	DWORD	off08;				//+08
	DWORD	dwWarpDist;			//+0C
	WORD	nMonLv[2][3];		//+10	Area Level
	DWORD	nMonDen[3];			//+1C 
	BYTE	monumin[3];			//+28
	BYTE	monumax[3];			//+2B
	BYTE	MonWndr;			//+2E
	BYTE	MonSpcWalk;			//+2F
	DWORD	_2[49];				//+30
	BYTE	_3;					//+F4
	char	szName[40];			//+F5
	char	szEntranceText[40];	//+11D
	char	szLvlDesc[40];		//+145
	BYTE	_4;					//+16D	
	wchar_t wszName[40];		//+16E
	wchar_t wszEntranceText[40];//+1BE
	BYTE	_5[2];				//+20E
	DWORD	wSoundEnv;			//+210
	DWORD	_6[2];				//+214
	WORD	wThemes;			//+21C
	WORD	_7;					//+21E
};

struct LevelDefTxt {			//size = 0x9C
	DWORD	dwQuestFlag;		//+00
	DWORD	dwQuestFlagEx;		//+04
	DWORD	dwLayerNo;			//+08
	DWORD	dwSizeX[3];			//+0C
	DWORD	dwSizeY[3];			//+18
	DWORD	dwOffsetX;			//+24
	DWORD	dwOffsetY;			//+28
	DWORD	dwDepend;			//+2C
	DWORD	dwDrlgType;			//+30 1=���������  2=�̶���ͼ 3=������ɣ�����ͼ��С�����ı�
	DWORD	dwLevelType;		//+34
	DWORD	dwSubType;			//+38
	DWORD	dwSubTheme;			//+3C
	DWORD	dwSubWaypoint;		//+40
	DWORD	dwSubShrine;		//+44
	DWORD	dwVis[8];			//+48
	DWORD	dwWarp[8];			//+68
	BYTE	nIntensity;			//+88
	BYTE	nRed;				//+89
	BYTE	nGreen;				//+8A
	BYTE	nBlue;				//+8B
	DWORD	dwPortal;			//+8C
	DWORD	dwPosition;			//+90
	DWORD	dwSaveMonsters;		//+94
	DWORD	dwIsInside;			//+98
};

struct ItemTxt {				//size = 0x1A8
	char szFlippyfile[32];		//+00
	char szInvfile[96];			//+20 ==>three names 32*3
	union{
		DWORD dwCode[5];
		char szCode[20];
	};							//+80
	BYTE nPotionflag;			//+94 //potion cube ,book 
	BYTE _1[39];				//+95  have 2byte only misc have ,and heal potion is diff
	char szMisc1[4];			//+BC
	char szWeap1[8];			//+C0
	char szMisc2[4];			//+C8
	int dwMinDef;				//+CC
	int dwMaxDef;				//+D0
	DWORD dwGambleCost;			//+D4
	int  dwSpeed;				//+D8
	int  dwBitfield1;			//+DC
	DWORD dwCost;				//+E0
	DWORD _2[2];				//+E4
	BYTE nContainerType;		//+EC
	BYTE _3[7];					//+ED
	WORD wLocaleTxtNo;			//+F4
	BYTE nVersion;				//+F6
	BYTE _4[5];					//+F7
	BYTE nRarity;				//+FC
	BYTE nQLevel;				//+FD
	BYTE nMindam;				//+FE one hand
	BYTE nMaxdam;				//+FF
	BYTE _5[2];					//+100
	BYTE nMindam2;				//+102 two hand
	BYTE nMaxdam2;				//+103
	BYTE nRangeAdder;			//+104
	BYTE _6;					//+105
	WORD wStrBonus;				//+106
	WORD wDexBonus;				//+108
	WORD wReqstr;				//+10A
	WORD wReqDex;				//+10C
	BYTE nAbsorbs;				//+10E
	BYTE nInvwidth;				//+10F
	BYTE nInvheight;			//+110
	BYTE _8;					//+111
	BYTE nDurability;			//+112
	BYTE _8a[2];				//+113
	BYTE nComponent;			//+115
	BYTE _8b[8];				//+116
	BYTE nType;					//+11E
	BYTE _3a[11];				//+11F
	BYTE fQuest;				//+12A
	BYTE fDiffCheck;			//+12B
	BYTE _9[12];				//+12C
	BYTE nSocket;				//+138
	BYTE _10[6];				//+139
	BYTE nLevelReq;				//+13F
	BYTE nMagicLvl;				//+140
};



struct ItemProp {
	int PropId;
	int Param;
	int MinVal;
	int MaxVal;
};

struct UniqueItemTxt {  //sizeof = 0x14C
	WORD dwIndex ;			//+00
	char  szDesc[32];		//+02
	WORD  wLocaleTxtNo;		//+22
	char  szUnk1[4];		//+24 version
	char  szCode[4];		//+28
	DWORD	_1[2];			//+2C
	WORD  wQlvl;			//+34
	WORD  wReqlvl;			//+36
	DWORD	_2[17];			//+38
	DWORD dwCostMult;		//+7C
	DWORD dwCostAdd;		//+80
	DWORD	_3[2];			//+84	
	ItemProp Prop[12] ;		//+8C

};



struct SetItemTxt{			//sizof = 0x1B8
	WORD dwIndex ;			//+00
	char  szDesc[32];		//+02
	char  szUnk1[2];		//+22 version
	WORD  wLocaleTxtNo;		//+24
	WORD  wUnk;				//+26
	char  szCode[4];		//+28
	DWORD  dwSetIdx;		//+2C
	WORD  wQlvl;			//+30
	WORD  wReqlvl;			//+32
	WORD  wRarity;			//+34
	WORD  _2 ;				//+36
	DWORD dwCostMult;		//+38
	DWORD dwCostAdd;		//+3C
	DWORD	_3[18];			//+40
	ItemProp Prop[9] ;		//+88
};

struct RuneWordTxt {	//sizof=0x120
	char szCode[64];	//+00
	char szName[64];	//+40
	WORD wComplete;		//+80
	WORD wLocaleTxtNo;	//+82
	WORD wServer;		//+84
	WORD wIType[6];		//+86 //�����õ�����
	WORD wEType[3];		//+92
	DWORD dwRuneNo[6];	//+98
	ItemProp Prop[7] ;	//+B0
};


struct ItemTypeTxt{  //sizeof = 0xE4
	char szCode[8];		//+00
	BYTE _1[18];		//+08
	BYTE nMaxSock1;		//+1A
	BYTE nMaxSock25;	//+1B
	BYTE nMaxSock40;	//+1C
	BYTE _2[0xC7];		//+1D
};

struct ItemStatCostTxt {   //sizeof = 0x144
	DWORD dwStatNo;			//+00
	DWORD dwUnk1 ;			//+04
	DWORD dwSendBits;		//+08
	DWORD dwDivide;			//+0C
	DWORD dwMultiply;		//+10
	DWORD dwAdd;			//+14
	BYTE  _1[4];			//+18
	DWORD dwSaveAdd;		//+1C
	DWORD _2[4];			//+20
	BYTE nItemEvent[2];		//+30
	BYTE nItemEventFunc[2];	//+32	
	WORD wDescPriority;		//+34
	BYTE nDescFunc;			//+36
	BYTE nDescVal;			//+37
	WORD wDescStrpos;		//+38
	WORD wDescStrneg;		//+3A
	WORD wDescStr2;			//+3C
	WORD nDgrp;				//+3E
	BYTE nDgrpFunc;			//+40
	BYTE nDgrpVal;			//+41
	WORD wDgrpStrpos;		//+42
	WORD wDgrpStrneg;		//+44
	WORD wDgrpStr2;			//+46
	BYTE _3[252];			//+48
	// +54 ==>OP
};

struct PropertiesTxt {	//sizeof = 0x2E
	WORD   wPropId ;	//+00
	BYTE   nSet[8] ;	//+02
	short  wVal[7];		//+0A
	BYTE   nFunc[8];	//+18
	short  wStatNo[7] ;	//+20
};


struct MonsterTxt {			//size = 0x1A8
	WORD	hcIdx ;			//+00
	WORD	hcIdx2;			//+02
	BYTE	_1[2];			//+04
	WORD	wLocaleTxtNo;	//+06
	WORD	wFlag;			//+08
	WORD	_2;				//+0A
	union{
		BYTE	nflag1;
		struct{
			BYTE _2a:6 ;
			BYTE fBoss:1 ;
			BYTE fPrimeevil:1 ;
		};
	};						//+0C
	union{
		BYTE	nflag2;
		struct{
			BYTE fNpc:1 ;
		};
	};						//+0D

	BYTE	flag3;			//+0E
	union{
		BYTE	nflag4;
		struct{
			BYTE fInventory:1 ;
		};
	};						//+0F
	char   szCode[4];		//+10
	char	_3[30];			//+14
	WORD	velocity;		//+32
	WORD	run;			//+34
	BYTE	_4[24];			//+36
	BYTE	nTreat;			//+4E
	BYTE	Aidel[3];		//+4F
	BYTE	Aidst[3];		//+52
	BYTE	_5;				//+55
	WORD	Aip1[3];		//+56
	WORD	Aip2[3];		//+5C
	WORD	Aip3[3];		//+62
	WORD	Aip4[3];		//+68
	char	_6[24];			//+6E
	WORD	Tcs[3][4];		//+86
	BYTE	nTcQuestId;		//+9E
	BYTE	nTcQuestCp;		//+9F
	BYTE	Drain[3];		//+A0
	BYTE	ToBlock[3];		//+A3
	BYTE	nCrit;			//+A6
	BYTE	_7[3];			//+A7
	WORD	Level[3];		//+AA
	WORD	MinHp[3];		//+B0
	WORD	MaxHp[3];		//+B6
	WORD	Ac[3];			//+BC
	WORD	A1TH[3];		//+C2
	WORD	A2TH[3];		//+C8
	WORD	S1TH[3];		//+CE
	WORD	Exp[3];			//+D4
	WORD	A1MinD[3];		//+DA
	WORD	A1MaxD[3];		//+E0
	WORD	A2MinD[3];		//+E6
	WORD	A2MaxD[3];		//+EC
	WORD	S1MinD[3];		//+F2
	WORD	S1MaxD[3];		//+F8
	WORD	_8[3];			//+FE
	char	szDesc[48];		//+104
	char	_9[116];		//+134

};

struct SkillDescTxt {
	WORD	wSkillNo ;
	BYTE	nSkillPage;
	BYTE	nSkillRow;
	BYTE	nSkillColumn;
	BYTE	nListRow;
	BYTE	nListPool;
	BYTE	nIconCel;
	WORD	wLocaleTxtNo;
};


struct GameStructInfo{
	BYTE	_1[27];				//+00
	char	szGameName[24];		//+1B
	char	szGameServerIp[86];	//+33
	char	szAccountName[48];	//+89
	char	szCharName[24];		//+B9
	char	szRealmName[24];	//+D1
	BYTE	_2[258];			//+E8 
	union{
		BYTE nGameMode;
		struct
		{
			BYTE nCharStat:2;
			BYTE nHardcore:2;
			BYTE _unk1:1;
			BYTE nExpansion:1;
			BYTE nLadder:2;	
		};
	};							//+1EB 
	BYTE	nReadyAct;			//+1EC  quest info 
	BYTE	_3[60];				//+1ED
	char	szServerVersion[24];//+229  battle net gameversion
	char	szGamePassword[24];	//+241
	char	szGameDescription[32];	//+259
};

#pragma pack(1)
struct WaypointMenuItem {
	BYTE areaId;
	BYTE	_1[3];	//+1
	BYTE enable;	//+4
};
#pragma pack(1)
struct KeyboardSetting {
/*
cmd table:
0   Character Screen 1   Inventory Screen 2   Party Screen 3   Message Log 4   Quest Log
5   Chat 6   Help Screen
7   Automap (Show/Hide) 8   Center Automap 9   Fade Automap 10  Party on Automap 11  Names on Automap
12  Skill Tree 13  Skill Speed Bar
14  Skill1 15  Skill2 16  Skill3 17  Skill4 18  Skill5 19  Skill6 20  Skill7 21  Skill8
22  Show Belt 23  Use Belt 1 24  Use Belt 2 25  Use Belt 3 26  Use Belt 4
27  Say Help 28  Say Follow me 29  Say This is for you 30  Say Thanks 31  Say Sorry
32  Say Bye 33  Say Now you die
34  Run (up/down) CONTROL 35  Toggle Run/Walk 36  Stand Still (up/down) SHIFT
37  Show Items (up/down) ALT 38  Clear Screen  39  Select Previous Skill 40  Select Next Skill
41  Clear Nessage 43  Show Portraits 44  Swap Weapons 45  Toggle MiniMap (Left/Right)
46  Skill9 47  Skill10 48  Skill11 49  Skill12 50  Skill13 51  Skill14 52  Skill15 53  Skill16
54  Hiring Screen 55  Say Retreat 56  ESC
*/
	int cmd; //+00
	short key; //+04
	short off6[2]; //+06 total size 10
};


/*
sgptDataTables
  +000 - pPlayerClassTxt 
  +004 - pPlayerClassLink 
  +008 - pBodyLocsTxt 
  +00C - pBodyLocsLink 
  +010 - pStorePageTxt 
  +014 - pStorePageLink 
  +018 - pElemTypesTxt 
  +01C - pElemTypesLink 
  +020 - pHitClassTxt 
  +024 - pHitClassLink 
  +028 - pMonModeTxt 
  +02C - pMonModeLink 
  +030 - pPlrModeTxt 
  +034 - pPlrModeLink 
  +038 - pSkillCalcTxt 
  +03C - pSkillCalcLink 
  +040 - pSkillCalcCache 
  +044 - nSkillCalcCache 
  +048 - nSkillCalcCacheDelta 
  +04C - pSkillDescCalcCache 
  +050 - nSkillDescCalcCache 
  +054 - nSkillDescCalcCacheDelta 
  +058 - pMissCalcTxt 
  +05C - pMissCalcLink 
  +060 - pMissCalcCache 
  +064 - nMissCalcCache 
  +068 - nMissCalcCacheDelta 
  +06C - pSkillCodesBin - created from the first column of skills.txt 
  +070 - pSkillCodesLink 
  +074 - pEventsTxt 
  +078 - pEventsLink 
  +07C - pCompCodesTxt 
  +080 - pCompCodesLink 
  +084 - nCompCodes 
  +088 - pMonAiTxt 
  +08C - pMonAiLink 
  +090 - nMonAi 
  +094 - pItemLink - the actual item text files are linked to gptItemTables 
  +098 - pItemCalcCache 
  +09C - nItemCalcCache 
  +0A0 - nItemCalcCacheDelta 
  +0A4 - pPropertiesTxt 
  +0A8 - pPropertiesLink 
  +0AC - nProperties 
  +0B0 - pRunesLink 
  +0B4 - pHireDescTxt 
  +0B8 - pHireDescLink 
  +0BC - pStatesTxt 
  +0C0 - pStatesLink 
  +0C4 - nStates 
  +0C8 - pStateMaskFirst 
  +0CC - pStateMaskArray[40] 
  +16C - pProgressiveStates[arrSize] - list of states with progressive = true 
  +170 - nProgressiveStates 
  +174 - pCurseStates[arrSize] - list of states with curse = true 
  +178 - nCurseStates 
  +17C - pTransformStates[arrSize] - list of states with transform = true 
  +180 - nTransformStates 
  +184 - pActionStates[arrSize] - states with actions assigned 
  +188 - nActionStates 
  +18C - pColorStates[arrSize] - states that change color 
  +190 - nColorStates 
  +194 - pSoundCodesBin - created from the first column of sounds.txt, the rest is only found in D2Client.dll 
  +198 - pSoundCodesLink 
  +19C - nSoundCodes 
  +1A0 - pHirelingsTxt 
  +1A4 - nHirelings 
  +1A8 - HireNameListStart[256] - first entry of 256 lists of hireling names 
  +5A8 - HireNameListEnd[256] - last entry of 256 lists of hireling names 
  +9A8 - pNpcsTxt 
  +9AC - nNpcs 
  +9B0 - pColorsTxt 
  +9B4 - pColorsLink 
  +9B8 - pTreasureClassExLink 
  +9BC - pTreasureClassExTxt 
  +9C0 - nTreasureClassEx 
  +9C4 - pChestTreasureClassList[45] 
  +A78 - pMonStatsTxt 
  +A7C - pMonStatsLink 
  +A80 - nMonStats 
  +A84 - pMonSoundsTxt 
  +A88 - pMonSoundsLink 
  +A8C - nMonSounds 
  +A90 - pMonStats2Txt 
  +A94 - pMonStats2Link 
  +A98 - nMonStats2 
  +A9C - pMonPlaceTxt 
  +AA0 - pMonPlaceLink 
  +AA4 - nMonPlace 
  +AA8 - pMonPresetTxt 
  +AAC - pMonPresetActList[5] - first record for each act 
  +AC0 - nMonPresetEachAct[5] - count for # of records per act 
  +AD4 - pSuperUniquesTxt 
  +AD8 - pSuperUniquesLink 
  +ADC - nSuperUniques 
  +AE0 - SuperUniqueHcIdxList[66] (66 words) 
  +B64 - pMissilesTxt 
  +B68 - pMissilesLink 
  +B6C - nMissiles 
  +B70 - pMonLvlTxt 
  +B74 - nMonLvl 
  +B78 - pMonSeqTxt 
  +B7C - pMonSeqLink 
  +B80 - nMonSeq 
  +B84 - pMonSequences - created from MonSeq.txt after reading it 
  +B88 - nMonSequences 
  +B8C - pSkillDescTxt 
  +B90 - pSkillDescLink 
  +B94 - nSkillDesc 
  +B98 - pSkillsTxt 
  +B9C - pSkillsLink 
  +BA0 - nSkills 
  +BA4 - pPlayerSkillCount[arrSize] - an array of player skill counts (all words) 
  +BA8 - nPlayerSkillCount 
  +BAC - pPlayerSkillList[arrSize] - the skill Ids (all words) 
  +BB0 - nPassiveSkillCount 
  +BB4 - pPassiveSkillList[arrSize] - the skill Ids (all words) 
  +BB8 - pOverlayTxt 
  +BBC - pOverlayLink 
  +BC0 - nOverlay 
  +BC4 - pCharStatsTxt 
  +BC8 - nCharStats 
  +BCC - pItemStatCostTxt 
  +BD0 - pItemStatCostLink 
  +BD4 - nItemStatCost 
  +BD8 - pOpStatNesting[arrSize] 
  +BDC - nOpStatNesting 
  +BE0 - pMonEquipTxt 
  +BE4 - nMonEquip 
  +BE8 - pPetTypesTxt 
  +BEC - pPetTypesLink 
  +BF0 - nPetTypes 
  +BF4 - pItemTypesLink 
  +BF8 - pItemTypesTxt 
  +BFC - nItemTypes 
  +C00 - nItemTypeNesting 
  +C04 - pItemTypeNesting[arrSize] 
  +C08 - pSetsLink 
  +C0C - pSetsTxt 
  +C10 - nSets 
  +C14 - pSetItemsLink 
  +C18 - pSetItemsTxt 
  +C1C - nSetItems 
  +C20 - pUniqueItemsLink 
  +C24 - pUniqueItemsTxt 
  +C28 - nUniqueItems 
  +C2C - pMonPropLink 
  +C30 - pMonPropTxt 
  +C34 - nMonProp 
  +C38 - pMonTypeLink 
  +C3C - pMonTypeTxt 
  +C40 - nMonType 
  +C44 - pMonTypeNesting[arrSize] 
  +C48 - nMonTypeNesting 
  +C4C - pMonUModLink 
  +C50 - pMonUModTxt 
  +C54 - nMonUMod 
  +C58 - pLevelsTxt 
  +C5C - nLevels 
  +C60 - pLvlDefsBin 
  +C64 - pLvlPrestTxt 
  +C68 - nLvlPrest 
  +C6C - ItemStatCostStuff[2] - related to opstats, stuff column (etc) 
  +C74 - pAnimTables (gptAnimTables) 
  +C78 - pExperienceTxt 
  +C7C - pDifficultyLevelsTxt 
  +C80 - nDifficultyLevels 
  +C84 - pExpFieldD2 - collision detection map 
  +C88 - ExpFieldRuntimeData[10] 
  +CB0 - pLvlSubExtraStuff[arrSize] 
  +CB4 - nLvlSubExtraStuff 
  +CB8 - pCharTemplateTxt 
  +CBC - nCharTemplate 
  +CC0 - pArenaTxt 
  +CC4 - pLvlTypesTxt 
  +CC8 - pWaypoints[arrSize] 
  +CCC - nWaypoints 
  +CD0 - nLvlTypes 
  +CD4 - pLvlWarpTxt 
  +CD8 - nLvlWarp 
  +CDC - pLvlMazeTxt 
  +CE0 - nLvlMaze 
  +CE4 - pLvlSubTxt 
  +CE8 - nLvlSub 
  +CEC - pLvlSubCache[arrSize] 
  +CF0 - three unused dwords here 
  +CFC - pMapCache[arrSize] 
  +D00 - nMapCache 
  +D04 - pCubeMainTxt 
  +D08 - nCubeMain 
  +D0C - bWriteBinFiles (BOOL)
*/


#endif 
