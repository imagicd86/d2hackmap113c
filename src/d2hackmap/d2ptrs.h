
#ifdef INIT_D2PTR_ADDR
  #define D2VARADDR(dll,addr1,name1,t1)     dll##_p##name1=(t1 *)(addr1-##dll##_ADDR+(DWORD)addr_##dll);
  #define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) dll##_##name1=(t1 (t2 *) t3)(addr1-##dll##_ADDR+(DWORD)addr_##dll);
  #define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) dll##_##name1=(t1 (t2 *) t3)GetProcAddress(addr_##dll,(LPCSTR)str1);
  #define D2ASMPTR(dll,addr1,name1)        dll##_v##name1=addr1-##dll##_ADDR+(DWORD)addr_##dll;
#else
	#ifdef DECLARE_D2PTR_VARIBLE
		#define D2VARADDR(dll,addr1,name1,t1)     t1 *dll##_p##name1;
		#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) t1 (t2 * dll##_##name1) t3;
		#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) t1 (t2 * dll##_##name1) t3;
		#define D2ASMPTR(dll,addr1,name1)        DWORD dll##_v##name1;
	#else
		#ifdef EXPORT_D2PTR_NAME_ADDRESS
			#define D2VARADDR(dll,addr1,name1,t1)     {addr1,#dll,#name1},
			#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) {addr1,#dll,#name1},
			#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) {addr1,#dll,#name1},
			#define D2ASMPTR(dll,addr1,name1)        {addr1,#dll,#name1},
		#else
			#define D2VARADDR(dll,addr1,name1,t1)     extern t1 *dll##_p##name1;
			#define D2FUNCADDR(dll,addr1,name1,t1,t2,t3) extern t1 (t2 * dll##_##name1) t3;
			#define D2FUNCNAME(dll,addr1,str1,name1,t1,t2,t3) extern t1 (t2 * dll##_##name1) t3;
			#define D2ASMPTR(dll,addr1,name1)        extern DWORD dll##_v##name1;
			#define DEFINE_D2PTR
		#endif
	#endif
#endif

#define d2client_ADDR 0x6FAB0000
	D2FUNCADDR(d2client,0x6FABBE84, Storm511,           void,__stdcall, (D2MSG *pMsg) )
	D2FUNCADDR(d2client,0x6FABC3DC, getNearbyRectData,void,__stdcall, (AreaRectData *pAreaRectData,AreaRectData ***pDataNear,int *n) )
	D2FUNCADDR(d2client,0x6FAC0DF0, SetResolutionMode,        void,__stdcall, ())
	D2FUNCADDR(d2client,0x6FAC85E0, ShouldClick85E0,           int,__stdcall, () ) //ecx=buf
	D2FUNCADDR(d2client,0x6FACBC40, RightClickBC40,           int,__stdcall, () ) //esi=buf
	D2FUNCADDR(d2client,0x6FACBDE0, LeftClickBDE0,           int,__stdcall, () ) //esi=buf
	D2FUNCADDR(d2client,0x6FAD16A0, GetMonsterOwner,    int,__fastcall, (int dwUnitId))
	D2FUNCADDR(d2client,0x6FAD3200, ItemProtect,		void,__stdcall, (UnitAny *pUnit, DWORD dwType))
	D2FUNCADDR(d2client,0x6FAD3F20, PlaySound,           int,__fastcall, (int unitId,int unitType,int sndId))
	D2FUNCADDR(d2client,0x6FAD8BC0, DrawSkillButton,        void,__stdcall, (Skill *pSkill,int x,int y,int isLeft))
	D2FUNCADDR(d2client,0x6FAD9250, DrawClient,         void,__fastcall, ())
	D2FUNCADDR(d2client,0x6FAD9990, UseBelt,         void,__fastcall, (UnitInventory *pInventory,UnitAny *player,int id)) //edx=PLAYER ecx=PLAYER->pInventory eax=0x8000(shift)or0
	D2FUNCADDR(d2client,0x6FAEB8B0, ShowMap,            void,__fastcall, ())
	D2FUNCADDR(d2client,0x6FAEDA60, SkillUnusable,      void,__fastcall, ()) //eax(pSkill),esi(playerUnit)
	D2FUNCADDR(d2client,0x6FAEE5E0, DrawSkillButtonE5E0,void,__stdcall,(int a,int b,int c,int d,int e,int isLeft))
	D2FUNCADDR(d2client,0x6FAEF6C0, GetScreenDrawX,   long,__stdcall, ())
	D2FUNCADDR(d2client,0x6FAEF6D0, GetScreenDrawY,   long,__stdcall, ())
	D2FUNCADDR(d2client,0x6FAF6150, Unknown6150,           int,__stdcall, ())
	D2FUNCADDR(d2client,0x6FB01A80, GetSelectedUnit,    UnitAny *,__stdcall, ())
	D2FUNCADDR(d2client,0x6FB0F6B0, NewAutomapNode,     AutomapNode *,__fastcall, ())
	D2FUNCADDR(d2client,0x6FB0F8A0, SetAutomapNamesStub ,   void,__fastcall, (DWORD flag) )    //parm = flag  ==> esi 
	D2FUNCADDR(d2client,0x6FB0F8D0, SetAutomapPartyStub	,   void,__fastcall, (DWORD flag) )    //parm = flag  ==> esi 
	D2FUNCADDR(d2client,0x6FB11320, AddAutomapNode,     void,__fastcall, (AutomapNode *cell, AutomapNode **node))
	D2FUNCADDR(d2client,0x6FB12580, AddAreaRectToMinimap,void,__stdcall, (AreaRectData *pData, DWORD clipflag, AutomapLayer *layer))
	D2FUNCADDR(d2client,0x6FB12710, InitAutomapLayerStub,   AutomapLayer*,__fastcall, (DWORD nLayerNo)) //nLayerNo==>eax 设置当前Layer指针,如果对应nLayerNo未生成,则分配一个，存于客户端
	D2FUNCADDR(d2client,0x6FB20C45, ChatInputStub ,         void,__stdcall, (D2MSG *pmsg) )  //与入口偏移了5个长度,使用自定义的eax
	D2FUNCADDR(d2client,0x6FB2D610, ShowPartyMessage,   void,__stdcall, (wchar_t* text, int nColor))
	D2FUNCADDR(d2client,0x6FB2D850, ShowGameMessage,    void,__stdcall, (wchar_t* text, int nColor) )
	D2FUNCADDR(d2client,0x6FB3AFD0, CalcShake,          void,__stdcall, (int *pPosX, int *pPosY))
	D2FUNCADDR(d2client,0x6FB3B110, DrawAllUnits,        int,__stdcall, ())
	D2FUNCADDR(d2client,0x6FB554A0, CanUseSkillNow,           int,__stdcall, (int skillId) ) //eax=pUnit
	D2FUNCADDR(d2client,0x6FB55B40, GetUnitFromId,      UnitAny *,__fastcall, (int dwUnitId, int dwUnitType)) //根据编号和类型获取对象,monster and palyer
	D2FUNCADDR(d2client,0x6FB5C3D0, RecvCommand08,      void,__fastcall, (BYTE *cmdbuf))
	D2FUNCADDR(d2client,0x6FB5C440, RecvCommand07,      void,__fastcall, (BYTE *cmdbuf))
	D2FUNCADDR(d2client,0x6FB5CE20, PacketHandler,      void,__stdcall, (int len)) //eax=buf
	D2FUNCADDR(d2client,0x6FB6E400, CheckUiStatusStub,  int,__fastcall, (int dwUiNo) )//dwUiNo ==> eax
	D2FUNCADDR(d2client,0x6FB72790, SetUiStatus,        int,__fastcall, (int dwUiNo, int howset, DWORD unknown1))
	D2FUNCADDR(d2client,0x6FB739E0, DrawControls,        int,__stdcall, (int unknown1))
	D2VARADDR(d2client,0x6FB8BC48, ScreenSize,         POINT)  //屏幕宽度X 800*600   640*480
	D2VARADDR(d2client,0x6FB8BC48, ScreenWidth,        int ) //屏幕宽度X 800*600   640*480
	D2VARADDR(d2client,0x6FB8BC4C, ScreenHeight,        int ) //屏幕宽度Y 800*600   640*480
	D2VARADDR(d2client,0x6FB8BC54, LastMousePos,		POINT )//最后的鼠标位置
	D2VARADDR(d2client,0x6FB90EB8, CursorInvGridX,     int)//最后的物品栏位置
	D2VARADDR(d2client,0x6FB90EBC, CursorInvGridY,     int)//最后的物品栏位置
	D2VARADDR(d2client,0x6FBA16B0, MinimapZoom,int)
	D2VARADDR(d2client,0x6FBA23E8, MercData16,         int ) 
	D2VARADDR(d2client,0x6FBA4F10, GameControlStart,  int) //游戏控制函数
	D2VARADDR(d2client,0x6FBA4F14, GameControlEnd,  int) //游戏控制函数
	D2VARADDR(d2client,0x6FBA8C9C, ExitAppFlag,        int)
	D2VARADDR(d2client,0x6FBA9E14, InfoPositionX,      int) //游戏信息显示X坐标
	D2VARADDR(d2client,0x6FBAAD60, UiDropGoldWindow,        void *)  //打开丢下金币窗口时此值不为零
	D2VARADDR(d2client,0x6FBAAD84, UiInventoryOn,        int) 
	D2VARADDR(d2client,0x6FBAAD88, UiCharacterOn,        int) 
	D2VARADDR(d2client,0x6FBAAD8C, UiSelectSkillOn,        int) 
	D2VARADDR(d2client,0x6FBAAD90, UiSkillTreeOn,        int) 
	D2VARADDR(d2client,0x6FBAAD94, UiChatOn,        int) 
	D2VARADDR(d2client,0x6FBAAD98, UiNewStatOn,        int) 
	D2VARADDR(d2client,0x6FBAAD9C, UiNewSkillOn,        int) 
	D2VARADDR(d2client,0x6FBAADA0, UiInteractOn,        int) 
	D2VARADDR(d2client,0x6FBAADA4, UiGameMenuOn,        int) 
	D2VARADDR(d2client,0x6FBAADA8, AutomapOn,          int) //小地图是否打开
	D2VARADDR(d2client,0x6FBAADB0, UiNpcTradeOn,   int) 
	D2VARADDR(d2client,0x6FBAADB4, UiShowItemsOn,   int) 
	D2VARADDR(d2client,0x6FBAADB8, UiModItemOn,   int) 
	D2VARADDR(d2client,0x6FBAADBC, UiQuestOn,   int) 
	D2VARADDR(d2client,0x6FBAADC4, UiNewQuestOn,   int) 
	D2VARADDR(d2client,0x6FBAADD0, UiWaypointOn,   int) 
	D2VARADDR(d2client,0x6FBAADD8, UiPartyOn,   int) 
	D2VARADDR(d2client,0x6FBAADDC, UiPPLTradeOn,   int) 
	D2VARADDR(d2client,0x6FBAADE0, UiMessageLogOn,   int) 
	D2VARADDR(d2client,0x6FBAADE4, UiStashOn,   int) 
	D2VARADDR(d2client,0x6FBAADE8, UiCubeOn,   int) 
	D2VARADDR(d2client,0x6FBAADFC, UiBeltOn,   int) 
	D2VARADDR(d2client,0x6FBAAE04, UiHelpOn,   int) 
	D2VARADDR(d2client,0x6FBACD8C, WaypointMenuItems, struct WaypointMenuItem) 
	D2VARADDR(d2client,0x6FBACDD6, WaypointMenuCurTab, int ) //classic(0-3) expansion(0-4)
	D2VARADDR(d2client,0x6FBACDDA, WaypointMenuCount, int ) //act1:9 act4:3
	D2VARADDR(d2client,0x6FBBA608, UnitTable,         UnitAny * ) //type*128+(id&0x7f)
	D2VARADDR(d2client,0x6FBBB9DC, MapShakeY,          long)
	D2VARADDR(d2client,0x6FBC973B, QuestData,          unsigned short **) 
	D2VARADDR(d2client,0x6FBC973F, GameQuestData,      unsigned short **)
	D2VARADDR(d2client,0x6FBC97AC, TradeRelated,      int *) 
	D2VARADDR(d2client,0x6FBC97F8, CurFrame,          int)
	D2VARADDR(d2client,0x6FBC9804, Ping,               int )
	D2VARADDR(d2client,0x6FBC9854, Expansion,          int ) // 1资料片 0 非资料片
	D2VARADDR(d2client,0x6FBC985C, CastingDelayEndFrame,int)
	D2VARADDR(d2client,0x6FBC9D30, SkillHotKeys,             int ) 
	D2VARADDR(d2client,0x6FBC9E20, SkillHotKeyLeft,          int ) 
	D2VARADDR(d2client,0x6FBCA2E0, KeyboardSettingStart, struct KeyboardSetting)
	D2VARADDR(d2client,0x6FBCA754, KeyboardSettingEnd, struct KeyboardSetting)
	D2VARADDR(d2client,0x6FBCA768, XButton2,           BOOL )
	D2VARADDR(d2client,0x6FBCA76C, XButton1,           BOOL )
	D2VARADDR(d2client,0x6FBCB824, MousePos,           POINT )//鼠标位置
	D2VARADDR(d2client,0x6FBCB824, MouseY,           int )//鼠标位置
	D2VARADDR(d2client,0x6FBCB828, MouseX,           int )//鼠标位置
	D2VARADDR(d2client,0x6FBCB980, GameInfo,           GameStructInfo *)
	D2VARADDR(d2client,0x6FBCB99C, Is800x600,          int)
	D2VARADDR(d2client,0x6FBCB9A0, DrawOffset,         POINT )//显示框偏移量
	D2VARADDR(d2client,0x6FBCBBB0, GoldInTranBox,         int)
	D2VARADDR(d2client,0x6FBCBBFC, PlayerUnit,         UnitAny *)
	D2VARADDR(d2client,0x6FBCBC14, RosterUnitList,     RosterUnit *) //玩家列表
	D2VARADDR(d2client,0x6FBCBC38, CurrentViewItem,    UnitAny*) //选择显示的物品
	D2VARADDR(d2client,0x6FBCBC48, NpcTradeCurrentTab,    int) //Npc trade current tab
	D2VARADDR(d2client,0x6FBCBC94, ActiveWeapon,    int) 
	D2VARADDR(d2client,0x6FBCBEFC, IsMapShakeOn,       BOOL)
	D2VARADDR(d2client,0x6FBCBF00, MapShakeX,          long)
	D2VARADDR(d2client,0x6FBCC028, ChatTextLength,         int)
	D2VARADDR(d2client,0x6FBCC1B0, MinimapType,         int) // 1小地图 0 大地图
	D2VARADDR(d2client,0x6FBCC1C0, AutomapLayerList,   AutomapLayer *) //所有AutomapLayer列表
	D2VARADDR(d2client,0x6FBCC1C4, AutomapLayer,       AutomapLayer *) //当前所在的AutomapLayer
	D2VARADDR(d2client,0x6FBCC1C8, MinimapCellFile,       struct CellFile *) 
	D2VARADDR(d2client,0x6FBCC1E8, AutomapPos,         POINT)
	D2VARADDR(d2client,0x6FBCC1F8, ScreenMinimapX,             int)
	D2VARADDR(d2client,0x6FBCC1FC, ScreenMinimapY,            int)
	D2VARADDR(d2client,0x6FBCC21C, InfoPositionY,      int) //游戏信息显示Y坐标
	D2VARADDR(d2client,0x6FBCC228, MinimapOffset,      POINT) //小地图边缘地址 ，大地图为 -16*-16
	D2VARADDR(d2client,0x6FBCC230, AutoMapSize,        POINT) //地图大小
	D2VARADDR(d2client,0x6FBCC2AC, Fps,                int )
	D2VARADDR(d2client,0x6FBCC2F4, HasSelectedObject,             BOOL ) 
	D2VARADDR(d2client,0x6FBCC2F8, FlagUnknownC2F8,             BOOL ) 
	D2VARADDR(d2client,0x6FBCC334, MercData32,         int ) 
	D2VARADDR(d2client,0x6FBCC390, Difficulty,         BYTE) //当前难度 0 1 2
	D2VARADDR(d2client,0x6FBCC3A0, InGame,             BOOL ) //是否在游戏中?
	D2VARADDR(d2client,0x6FBCC3A0, MButton,            BOOL )
	D2VARADDR(d2client,0x6FBCC3A4, notAcceptKeys,         int ) //not accept input?
	D2VARADDR(d2client,0x6FBCC3B8, DrlgAct,            DrlgAct *)
	D2VARADDR(d2client,0x6FBCC3F0, StandStill,         BOOL ) //是否站立不动
	D2VARADDR(d2client,0x6FBCC414, ScreenBlocked,       int) //bit0 right half blocked, bit 1 left half blocked
	D2VARADDR(d2client,0x6FBCC484, BeltNotEmpty,  char) 
	D2VARADDR(d2client,0x6FBCC4B0, ShowLifeStr,         BOOL)
	D2VARADDR(d2client,0x6FBCC4B4, ShowManaStr,         BOOL)
	D2VARADDR(d2client,0x6FBCC4D4, PetUnitList,        PetUnit * ) //玩家召唤物列表
	D2VARADDR(d2client,0x6FBCEC80, LastChatMessage,    wchar_t)  
	D2VARADDR(d2client,0x6FBD3395, QuestPage,          int)
	D2VARADDR(d2client,0x6FBD3424, IsEquipment800x600,          int)
	D2ASMPTR(d2client,0x6FADB420, LoadUiImageFunc)
	D2ASMPTR(d2client,0x6FBC3880, AutomapNodeListBaseAddr)
#undef d2client_ADDR

#define d2common_ADDR 0x6FD50000
	D2FUNCADDR(d2common,0x6FD51330,  GetNearRectDataWithPos,AreaRectData *,__fastcall, ())//eax=pData,ebx=x,edi=y
	D2FUNCADDR(d2common,0x6FD513B0,  GetMonStats2,        void *,__fastcall, ())//eax=dwTxtFileNo
	D2FUNCNAME(d2common,0x6FD6DFB0,11017,   GetCursorItem,        UnitAny *,__stdcall, (UnitInventory * ptInventory))//pUnit->pInventory->pCursorItem
	D2FUNCNAME(d2common,0x6FD6E190,10460,   GetFirstItemInInv,    UnitAny *,__stdcall, (UnitInventory* ptInventory)) // pUnit->pInventory->pFirstItem
	D2FUNCNAME(d2common,0x6FD6E8F0,10464,   GetNextItemInInv,     UnitAny *,__stdcall, (UnitAny *pItem))
	D2FUNCNAME(d2common,0x6FD6F1F0,11148,   CheckInvLocation,     int,__stdcall, (UnitInventory* pInventory, UnitAny *pItem, int dwCursorGridX, int dwCursorGridY, int dwBoxType, int* GridCount, int* ItemCount, BYTE invType))
	D2FUNCNAME(d2common,0x6FD72640,10620,   GetItemFileIndex,     int,__stdcall, (UnitAny *pItem) ) //pItem->pItemData->dwFileIndex
	D2FUNCNAME(d2common,0x6FD73940,10202,   CheckItemFlag,        BOOL,__stdcall, (UnitAny *pItem, DWORD dwFlagMask, int dwLineno, char *filename) )
	D2FUNCNAME(d2common,0x6FD79D00,10987,   EncodeItem, int,__stdcall, (UnitAny *pUnit,char *buf,int size,int a,int b,int c) ) 
	D2FUNCNAME(d2common,0x6FD79D60,10107,   GetItemValue,         int,__stdcall, (UnitAny * pPlayer, UnitAny * pItem, int dwDifficulty, void* questinfo, int value, DWORD dwFlag))
	D2FUNCNAME(d2common,0x6FD7CCC0,10458,   GetMercInfo, int,__stdcall, (int seed,int arg,int diff,void *buf)) //ecx=EXPANISION edx=PLAYER 
	D2FUNCNAME(d2common,0x6FD7D0F0,10174,   CheckQuestFlag,       BOOL,__stdcall, ( void *pQuestData, int dwQuestNo, int dwCheckFlag ))
	D2FUNCNAME(d2common,0x6FD7D9B0,10207,   GetDrlgLevel,         DrlgLevel *,__fastcall, (DrlgMisc *drlgmisc, int levelno))//分配一个新的DrlgLevel结构,存于服务端
	D2FUNCNAME(d2common,0x6FD7E360,10322,   InitDrlgLevel,        void,__stdcall, (DrlgLevel *drlglevel))
	D2FUNCNAME(d2common,0x6FD7FB60,10584,   GetBoxType,           int,__stdcall, (UnitAny * pUnit, BYTE invType, int dwExpansion))//箱子类型
	D2FUNCNAME(d2common,0x6FD7FE10,10331,   getRectData,        AreaRectData *,__stdcall, (UnitAny *pUnit))
	D2FUNCNAME(d2common,0x6FD80460,10828,   getLeftSkill,   Skill *,__stdcall, (UnitAny *pUnit)) //pUnit->pSkill->pLeftSkill
	D2FUNCNAME(d2common,0x6FD814A0,10839,   IsUnitBlocked, int,__stdcall, (UnitAny *playerUnit,UnitAny *pUnit,int bitmask)) 
	D2FUNCNAME(d2common,0x6FD82330,11027,   GetMonsterHpPercent,  int,__stdcall, (UnitAny *pUnit) )//对玩家无效
	D2FUNCNAME(d2common,0x6FD83CD0,10494,   CheckUnitState,       BOOL,__stdcall, (UnitAny *pUnit, int dwStateNo))
	D2FUNCNAME(d2common,0x6FD84B80,10750,   GetUnitPosY,          int,__stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 
	D2FUNCNAME(d2common,0x6FD84BB0,10867,   GetUnitPosX,          int,__stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 
	D2FUNCNAME(d2common,0x6FD87EC0,10930,   GetStatListWithFlag,  StatList * ,__stdcall, (UnitAny *pUnit, int dwStatNo, DWORD dwListFlag) )//
	D2FUNCNAME(d2common,0x6FD88710,11110,   GetStatFromStatList,  BOOL,__stdcall, (StatList *pStatList, DWORD dwStatNo, StatEx *pStatVal ,DWORD dwMask ) ) //是否存在属性,有则得到属性值
	D2FUNCNAME(d2common,0x6FD88B70,10973,   GetUnitStat,          int,__stdcall, (UnitAny *pUnit, int dwStatNo, WORD dwLayerNo))
	D2FUNCNAME(d2common,0x6FD88C20,10587,   GetUnitBaseStat,      int,__stdcall, (UnitAny *pUnit, int dwStatNo, WORD dwLayerNo))//只会查询第一条statlist,对玩家大部分属性能查到
	D2FUNCNAME(d2common,0x6FD8C000,10826,   GetLevelIdFromRectData,   int,__stdcall, (AreaRectData *pData))
	D2FUNCNAME(d2common,0x6FD8C390,10057,   isInTown,    int,__stdcall, (AreaRectData *pAreaRectData))
	D2FUNCNAME(d2common,0x6FD8E980,10688,   GetObjectTxt,         ObjectTxt *,__stdcall, (int objno))
	D2FUNCNAME(d2common,0x6FD9AD20,11076,   IsLineBlocked, int,__stdcall, (AreaRectData *pData,POINT *p1,POINT *p2,int bitmask))
	D2FUNCNAME(d2common,0x6FDA0150,10444,   CheckCorpseCanUse,    BOOL,__stdcall, (UnitAny *pMon,DWORD flag))
	D2FUNCNAME(d2common,0x6FDA2340,10787,   getSkillStatus, int,__stdcall,(UnitAny *pUnit,Skill *pSkill))
	D2FUNCNAME(d2common,0x6FDA3370,10038,   GetSuperUniqueTxt,    SuperUniqueTxt *,__stdcall, (int dwUniqueNo))
	D2FUNCNAME(d2common,0x6FDA3420,10634,   GetTreasureClasses,   TreasureClass *,__stdcall, (WORD tcno, int lvlno))
	D2FUNCNAME(d2common,0x6FDAE810,10399,   GetMinExpToLevel,     int,__stdcall, (int dwCharClass, int dwLevel))
	D2FUNCNAME(d2common,0x6FDBCB20,10749,   GetLevelDefTxt,       LevelDefTxt*,__fastcall, (int levelno))
	D2FUNCNAME(d2common,0x6FDBCC30,10499,   GetLevelTxt06,      char ,__stdcall, (int levelno))
	D2FUNCNAME(d2common,0x6FDBCC60,10884,   GetLevelTxt07,      char ,__stdcall, (int levelno))
	D2FUNCNAME(d2common,0x6FDBCC90,10215,   GetLevelWeather,      char ,__stdcall, (int levelno)) //txt05
	D2FUNCNAME(d2common,0x6FDBCCC0,10014,   GetLevelTxt,          LevelTxt *,__stdcall, (int levelno))
	D2FUNCNAME(d2common,0x6FDC19A0,10695,   GetItemTxt,           ItemTxt *,__stdcall, (int itemno)) //6fdc19a0
	D2FUNCADDR(d2common,0x6FD9FCB0, getSkillBonus, int,__fastcall, () )//esi:PLAYER eax:pSkill
	D2VARADDR(d2common,0x6FDE9E1C, DataTables,        DWORD)
	D2VARADDR(d2common,0x6FDEFB94, ItemTxtCount,         int)
	D2VARADDR(d2common,0x6FDEFB98, ItemTxts,         ItemTxt *) //size 0x1A8
	D2VARADDR(d2common,0x6FDEFBA0, WeaponsTxts,         int)
	D2VARADDR(d2common,0x6FDEFBA8, ArmorTxts,           int)
	D2VARADDR(d2common,0x6FDEFBD4, RuneWords,         int)
	D2VARADDR(d2common,0x6FDEFBD8, RuneWordTxt,	   DWORD)
#undef d2common_ADDR

#define d2gfx_ADDR 0x6FA80000
	D2FUNCNAME(d2gfx,0x6FA8B9C0,10010,DrawLine,void,__stdcall, (int x1, int y1, int x2, int y2, int dwColor, int dwTransLvl)) 
	D2FUNCNAME(d2gfx,0x6FA8AFD0,10011,drawShadow,void,__stdcall, (void *ptr,int x,int y))
	D2FUNCNAME(d2gfx,0x6FA8BA30,10014,DrawRectangle,void,__stdcall, (long dwXstart, long dwYstart, long dwXend, long dwYend, int dwPal, int dwTransLvl)) //filled
	D2FUNCNAME(d2gfx,0x6FA8B050,10019,drawSomething,void,__stdcall, (void *ptr,int x,int y,int d,int e,int f)) //6fa8b050 d=-1 e=(4:char,5:skill button) f=(0:normal 1:inactive)
	D2FUNCNAME(d2gfx,0x6FA8B080,10041,DrawCellFile,void,__stdcall, (CellContext *context, int xPos, int yPos, DWORD dw1, int dwTransLvl, BYTE *coltab)) 
	D2FUNCNAME(d2gfx,0x6FA87FB0,10048,GetHwnd,HWND,__stdcall, ()) 
	D2FUNCNAME(d2gfx,0x6FA87FC0,10059,MinimizeWindows,void,__stdcall, (DWORD dwFlag))
	D2FUNCNAME(d2gfx,0x6FA888B0,10043,Ordinal10043,void,__stdcall,())
	D2FUNCNAME(d2gfx,0x6FA8B020,10074,FillOrb, void,__stdcall, (int arg0,int x,int y,int arg3,int arg4,int arg5)) 
	D2FUNCNAME(d2gfx,0x6FA8B320,10031,getResolutionMode, int,__stdcall, ()) 
	D2FUNCNAME(d2gfx,0x6FA87C80,10076,drawGroundPiece, void,__stdcall, (void *buf0,void *buf1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7,int arg8)) 
	D2FUNCNAME(d2gfx,0x6FA8AFF0,10079,DrawAutomapNode,void,__stdcall, (CellContext *context, int xpos, int ypos, RECT *cliprect, DWORD dwTransLvl)) 
	D2FUNCNAME(d2gfx,0x6FA8ADF0,10085,clearFramebuf,void,__stdcall, (int a,int b,int c,int d))
	D2FUNCNAME(d2gfx,0x6FA8ADD0,10040,flushFramebuf,void,__stdcall, ())
	D2VARADDR(d2gfx,0x6FA9D66C, WinState,int)
	D2VARADDR(d2gfx,0x6FA91260, ResolutionMode,int)
	D2VARADDR(d2gfx,0x6FA9D468, DrawGoundH1,int)
	D2VARADDR(d2gfx,0x6FA948CC, DrawGoundH2,int)
#undef d2gfx_ADDR

#define d2win_ADDR 0x6F8E0000
	D2ASMPTR(d2win,0x6F8E7720, ToggleSound)
	D2FUNCNAME(d2win,0x6F8F3720,10021,   SelectEditBoxText,      void,__fastcall,  (D2EditBox* box))
	D2FUNCNAME(d2win,0x6F8F2B20,10028,   GetTextPixelLen,        int,__fastcall, (wchar_t *wStr) )//这个函数不能分辨颜色代码，只能用于无色字符串
	D2FUNCNAME(d2win,0x6F8F59E0,10048,   DestroyEditBox,         int,__fastcall, (D2EditBox* box))
	D2FUNCNAME(d2win,0x6F8F8490,10050,   DestroyListBox,         void,__stdcall,   (D2EditBox* box))
	D2FUNCNAME(d2win,0x6F8F61B0,10057,   CreateEditBox,          D2EditBox*,__fastcall, (int dwPosX, int dwPosY, int dwSizeX, int dwSizeY, int dwOffsetX, int dwOffsetY, CellFile *pCellFile, DWORD dwReturnHandler, DWORD arg9, DWORD dwIsCloaked, void* buf))
	D2FUNCNAME(d2win,0x6F8F5450,10064,   AddEditBoxChar,         DWORD,__fastcall, (D2EditBox* box, BYTE keycode))
	D2FUNCNAME(d2win,0x6F8F36A0,10166,   GetEditBoxText,         wchar_t*,__fastcall, (D2EditBox* box))
	D2FUNCNAME(d2win,0x6F8F2700,10177,   GetTextAreaSize,        int,__fastcall, (wchar_t *wStr, int* pWidth, int* pHeight)) 
	D2FUNCNAME(d2win,0x6F8F2FE0,10184,   SetTextFont,            int,__fastcall, (int dwFont))
	D2FUNCNAME(d2win,0x6F8E9740,10022,   PrintLineOnTextBox,  void,__fastcall, (void *textbox, char *buf, int color))
	D2FUNCNAME(d2win,0x6F8F87E0,10024,   DrawMainMenu,         void*,__fastcall, ())
	D2FUNCNAME(d2win,0x6F8F4DF0,10042,   SetEditBoxText,         void*,__fastcall, (D2EditBox* box, wchar_t* wcszTxt))
	D2FUNCNAME(d2win,0x6F8F2730,10070,   DrawUnitLifeBar,        int,__fastcall, (wchar_t *wStr ,long xPos, long yPos, int dwColor, DWORD dwUnk1 ,DWORD dwUnk2) )
	D2FUNCNAME(d2win,0x6F8F18F0,10085,   DrawHoverText,          void,__fastcall, (wchar_t *wStr, long xPos, long yPos, int dwTran, int dwColor))
	D2FUNCNAME(d2win,0x6F8F8560,10098,   CreateTextBox,  void *,__stdcall, (DWORD* param))
	D2FUNCNAME(d2win,0x6F8F33A0,10110,   DrawHover,              void, __fastcall, ()) //真正显示字符框的地方，上面3个只是设置了变量,显示优先级非常高 6f8f33a0
	D2FUNCNAME(d2win,0x6F8F2FA0,10150,   DrawText,            void, __fastcall, (wchar_t *wStr, long xPos, long yPos, int dwColor, int dwAlign))
	D2FUNCNAME(d2win,0x6F8F3970,10170,   SetEditBoxProc,         void, __fastcall, (D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,int,char*)))
	D2VARADDR(d2win,0x6F9014B0, FocusedControl,        D2EditBox*)
	D2VARADDR(d2win,0x6F9014C0, RunningFlag,        int)
	D2VARADDR(d2win,0x6F9A9CF8, music_volumn,  int) //0-100
#undef d2win_ADDR

#define d2lang_ADDR 0x6FC00000
	D2FUNCNAME(d2lang,0x9A9450,10003,   GetLocaleText,          wchar_t*,__fastcall, (int dwLocaleTxtNo))
#undef d2lang_ADDR

#define d2cmp_ADDR 0x6FE10000
	D2FUNCNAME(d2cmp,0x6FE21AC0,10006,   InitCellFile,           void,__stdcall, (void *cellfile, CellFile **outptr, char *srcfile, int lineno, int filever, char *filename))
	D2FUNCNAME(d2cmp,0x6FE21520,10065,   DeleteCellFile,         void,__stdcall, (CellFile *cellfile))
	D2FUNCADDR(d2cmp,0x6FE23010, mpq_path_3010,  int,__fastcall, (char *path))
#undef d2cmp_ADDR

#define bnclient_ADDR 0x6FF20000
	D2VARADDR(bnclient,0x6FF3F64C, BnChatMessage,     LPDWORD )
#undef bnclient_ADDR

#define d2net_ADDR 0x6FBF0000
	D2FUNCNAME(d2net,0xAF7650,10024,   SendPacket,   void,__stdcall, (size_t len, DWORD arg1, BYTE* buf))
	D2VARADDR(d2net,0x6FBFB244, UnkNetFlag,	 DWORD)
#undef d2net_ADDR

#define d2game_ADDR 0x6FC20000
	D2FUNCADDR(d2game,0x6FC2A364, GetSinglePlayerContext1,  int,__stdcall, (int))
	D2FUNCADDR(d2game,0x6FC4AAE0, GetSinglePlayerContext2,  int,__stdcall, (int))
	D2FUNCADDR(d2game,0x6FD003A0, GetSinglePlayerUnit,  int,__fastcall, (int,int))
	D2FUNCADDR(d2game,0x6FD0C7F0, MakeD2S,  int,__fastcall, (UnitAny *pUnit,int context,char *buf,int *size,int cap,int zero,int one))
	D2VARADDR(d2game,0x6FD1B014, SPUnitOffsets,		int)
#undef d2game_ADDR

#define d2launch_ADDR 0x6FA40000
	D2VARADDR(d2launch,0x6FA611F0, createTextBoxParam11F0,  DWORD *)
	D2VARADDR(d2launch,0x6FA652B8, launchChildren,  void *)
	D2VARADDR(d2launch,0x6FA65E30, launchNumChildren,  int)
#undef d2launch_ADDR

#define d2gdi_ADDR 0x6F870000
	D2VARADDR(d2gdi,0x6F87C150, ColorMap,  int)
	D2VARADDR(d2gdi,0x6F87CA80, FrameBufWidth,  int)
	D2VARADDR(d2gdi,0x6F87CA90, FrameBufHeight,  int)
	D2VARADDR(d2gdi,0x6F87CA9C, DisplayRight,  int)
	D2VARADDR(d2gdi,0x6F87CAA8, FrameBuf,  void *)
#undef d2gdi_ADDR

#ifdef DEFINE_D2PTR
typedef struct {
	int off0,off4;
	char path[256]; //+08
	int off108,off10c; //+108
} mpq_block;
	
#endif
#define storm_ADDR 0x6FBF0000
	D2FUNCNAME(storm,0x6FC12700,552,mpq_uncompress,int,__stdcall,(void *dst, int *psize, void *src,int src_size))
	D2FUNCNAME(storm,0x6FC18960,268,mpq_open_block_from,int,__stdcall,(void *mpq, char *path, int flags,mpq_block *b)) 
	D2FUNCNAME(storm,0x6FC18DA0,267,mpq_open_block,int,__stdcall,(char *path, mpq_block *b))
	D2FUNCADDR(storm,0x6FC15ED0, mpq_hashstring, int,__stdcall,(int group)) //eax=path
	D2FUNCADDR(storm,0x6FC18450, mpq_read_block, int,__stdcall,(mpq_block *b,int offset,char *outbuf,int size))//return size
	D2VARADDR(storm,0x6FC43120, mpq_crypt_table,  int) //size 0x500*4
	D2VARADDR(storm,0x6FC43130, mpq_load_flag,  int) //bit0,1:loadExternal?
#undef storm_ADDR

#define fog_ADDR 0x6FF50000
	D2FUNCNAME(fog,0x6FF61100,10024,reportError,void,__cdecl,(int arg0,int arg1,int arg2))
	D2FUNCNAME(fog,0x6FF67E40,10102,mpq_open_block,int,__fastcall,(char *path,mpq_block *ptr))
#undef fog_ADDR

#define d2sound_ADDR 0x6F9B0000
	D2FUNCNAME(d2sound,0x6F9B9AA0,10004,set_music_volumn,int,__fastcall,(int volumn))
	D2FUNCNAME(d2sound,0x6F9B9AC0,10011,get_music_volumn,int,,())
	D2VARADDR(d2sound,0x6F9C64A8, music_volumn,  int) //0-100
#undef d2sound_ADDR

#undef D2FUNCADDR
#undef D2FUNCNAME
#undef D2VARADDR
#undef D2ASMPTR
#ifdef DEFINE_D2PTR
	#undef DEFINE_D2PTR
#endif
