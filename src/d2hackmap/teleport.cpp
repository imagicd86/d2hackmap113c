#include "stdafx.h"
#include "multi.h"
#include "auto.h"
#include "map.h"
#include "d2ptrs.h"

int isWaypointTxt(int txt);
void takeWaypointToLevel(UnitAny *waypoint,int level);
void markNextPathInvalid(int ms);
int RerouteRectPath();

POINT TPtarget;
AreaRectData *TPtargetRect,*TPfailedRect;
int dwTpMs,dwTpDoneMs;
static int dwTpAvoiding,dwLastTpMs;
static char aMonYard[32][2];
static int defMonYard,maxTpYard,tpDelayMs,tpMinStep,stepInvalidMs,avoidEdge=0,dwAutoTeleportSafeDistance;
static int reachDis=6;
static ToggleVar tLogTP={TOGGLEVAR_ONOFF,0,-1,1,"Log TP Toggle"};
int maxTpDisRaw;
static ConfigVar aConfigVars[] = {
	{CONFIG_VAR_TYPE_INT,"AutoTeleportSafeDistance",&dwAutoTeleportSafeDistance,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportMonsterDefaultDistance",&defMonYard,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportMaxDistance",&maxTpYard,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportDelayMs",&tpDelayMs,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportAvoidEdge",&avoidEdge,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportMinStep",&tpMinStep,4 },
	{CONFIG_VAR_TYPE_INT,"AutoTeleportStepInvalidMs",&stepInvalidMs,4 },
	{CONFIG_VAR_TYPE_CHAR_ARRAY0,"AutoTeleportMonsterDistance",&aMonYard,2,{32}},
	{CONFIG_VAR_TYPE_KEY, "LogTPToggle",  &tLogTP		},
};
void autoteleport_addConfigVars() {
	for (int i=0;i<_ARRAYSIZE(aConfigVars);i++) addConfigVar(&aConfigVars[i]);
}
void autoteleport_initConfigVars() {
	memset(aMonYard,0,sizeof(aMonYard));
}
void autoteleport_fixValues() {
	maxTpDisRaw=(maxTpYard*3)>>1;
}
struct TPPos {POINT p;int disM256;AreaRectData *pData;};
struct Mon {POINT p;int dis;};
static POINT src,dst;
static TPPos *tposs=NULL;
static int nPos=0,posCap=0;
static Mon *mons=NULL,*mons_end;
static int monCap=0,nMons=0,maxTpDisM256;
static char monMap[32][32];
static int monMapX,monMapY;
static int maxDisM256;
static POINT bestP;
static AreaRectData *bestRect;
static int rectCountFromTarget=0;

static int comparePos(const void *a,const void *b) {return ((TPPos *)a)->disM256-((TPPos *)b)->disM256;}
static int dis(POINT *p1,POINT *p2) {return getDistanceM256(p1->x-p2->x,p1->y-p2->y)>>8;}
static int disM256(POINT *p1,POINT *p2) {return getDistanceM256(p1->x-p2->x,p1->y-p2->y);}
//static int dis2(POINT *p1,POINT *p2) {int dx=p1->x-p2->x,dy=p1->y-p2->y;return dx*dx+dy*dy;}
static void addMonMap(int x,int y) {
	x-=monMapX;y-=monMapY;if (x<0||x>=128||y<0||y>=128) return;
	monMap[y>>2][x>>2]=1;
}
static int hasMon(int x,int y) {
	x-=monMapX;y-=monMapY;if (x<0||x>=128||y<0||y>=128) return 0;
	return monMap[y>>2][x>>2];
}
static void resetMonsters() {
	if (!mons) {monCap=4096;mons=(Mon *)HeapAlloc(dllHeap,0,sizeof(Mon)*monCap);}
	memset(monMap,0,32*32);
	monMapX=dwPlayerX-64;monMapY=dwPlayerY-64;
	nMons=0;mons_end=mons;
}
int getMonsterOwnerId(int id);
static void findMonsters() {
	resetMonsters();
	for (int i=0;i<128;i++) {
		for (UnitAny *pMon=d2client_pUnitTable[UNITNO_MONSTER*128+i];pMon;pMon=pMon->pHashNext) {
			if (pMon->dwUnitType!=UNITNO_MONSTER) break;
			if (pMon->dwMode==MonsterMode_Death) continue; //dying?
			if (pMon->dwMode==MonsterMode_Dead) continue; //already dead
			int owner=getMonsterOwnerId(pMon->dwUnitId);if (owner!=-1) continue; 
			int mtype=aAutoSkillMonsterType[pMon->dwTxtFileNo];
			if (mtype&MONSTER_TYPE_NEUTRAL) continue;
			if (nMons>=monCap) {monCap*=2;mons=(Mon *)HeapReAlloc(dllHeap,0,mons,sizeof(Mon)*monCap);}
			Mon *pmon=&mons[nMons++];
			int x=pMon->pMonPath->wUnitX;int y=pMon->pMonPath->wUnitY;pmon->p.x=x;pmon->p.y=y;
			pmon->dis=aMonYard[dwPlayerFcrFrame][(mtype&MONSTER_TYPE_DANGROUS)?1:0];
			if (!pmon->dis) pmon->dis=defMonYard;
			pmon->dis=(pmon->dis*3)>>1;
			addMonMap(x-2,y-2);addMonMap(x-2,y+2);addMonMap(x+2,y-2);addMonMap(x+2,y+2);
		}
	}
	mons_end=mons+nMons;
}
static int getMonDis(POINT *src) {
	int minDis=0x7FFFFFFF;
	for (Mon *p=mons;p<mons_end;p++) {
		int d=dis(src,&p->p)-p->dis;
		if (d<minDis) minDis=d;
	}
	return minDis;
}
static void addPossiblePostions(AreaRectData *pCenter,AreaRectData *pData,POINT *p,int step) {
	if (!pData||!pData->bitmap) return;
	if (pData==TPfailedRect) return;
	unsigned short *bitmap=pData->bitmap->bitmap;
	int w=pData->bitmap->unitW,h=pData->bitmap->unitH;
	unsigned short *end=bitmap+w*h;
	int x0=0,x1=w,y0=0,y1=h;
	if (p) {
		x0=p->x-pData->unitX-step;if (y0<0) y0=0;
		x1=p->x-pData->unitX+step;if (x1>w) x1=w;
		y0=p->y-pData->unitY-step;if (y0<0) y0=0;
		y1=p->y-pData->unitY+step;if (y1>h) y0=h;
		step=1;
	}
	if (pCenter!=pData) {
		if (pData->tileX<pCenter->tileX) {if (x0<avoidEdge) x0=avoidEdge;}
		else if (pData->tileX>pCenter->tileX) {if (x1>w-avoidEdge) x1=w-avoidEdge;}
		if (pData->tileY<pCenter->tileY) {if (y0<avoidEdge) y0=avoidEdge;}
		else if (pData->tileY>pCenter->tileY) {if (y1>h-avoidEdge) y1=h-avoidEdge;}
	}
	for (int ty=y0;ty<y1;ty+=step) {
		for (int tx=x0;tx<x1;tx+=step) {
			unsigned short *ptr=bitmap+ty*w+tx;
			int x2=tx+step;if (x2>w) x2=w;
			int y2=ty+step;if (y2>h) y2=h;
			int rowskip=w-(x2-tx);
			POINT p;
			for (int y=ty;y<y2;y++) {
				for (int x=tx;x<x2;x++) {
					if (ptr>=end) goto nextTile;
					if (((*ptr++)&0x1527)==0) {
						p.x=pData->unitX+x;
						p.y=pData->unitY+y;
						if (hasMon(p.x,p.y)) goto nextTile;
						if (disM256(&src,&p)>maxTpDisM256) goto nextTile;
						int dstM256=disM256(&dst,&p);
						if (dstM256>maxDisM256) goto nextTile;
						if (nPos>=posCap) {posCap*=2;tposs=(TPPos *)HeapReAlloc(dllHeap,0,tposs,sizeof(TPPos)*posCap);}
						TPPos *pp=&tposs[nPos++];pp->p=p;pp->disM256=dstM256;pp->pData=pData;
						goto nextTile;
					}
				}
				ptr+=rowskip;
			}
nextTile:
			continue;
		}
	}
}
static int findValidPosition() {
	qsort(tposs,nPos,sizeof(TPPos),comparePos);
	TPPos *end=tposs+nPos;
	for (TPPos *p=tposs;p<end;p++) {
		int minMonDis=0x7FFFFFFF;
		for (Mon *mon=mons;mon<mons_end;mon++) {
			int d=dis(&p->p,&mon->p)-mon->dis;
			if (d<0) goto nextPosition;
			if (d<minMonDis) minMonDis=d;
		}
		bestRect=p->pData;bestP=p->p;return minMonDis;
nextPosition:
		continue;
	}
	return -1;
}
int BackToTown();
static void interactObj(UnitAny *pUnit) {
	if (isWaypointTxt(pUnit->dwTxtFileNo)) {
		takeWaypointToLevel(pUnit,actlvls[ACTNO]);
		return;
	}
	LOG("interactObj txt=%d mode=%d\n",pUnit->dwTxtFileNo,pUnit->dwMode);
	switch (pUnit->dwTxtFileNo) {
		case 268: //wirt's body
			if (pUnit->dwMode==1) {//opened
				UnitAny *leg=NULL;
				for (int i=0;i<128;i++) {
					for (UnitAny *pUnit=d2client_pUnitTable[UNITNO_ITEM*128+i];pUnit;pUnit=pUnit->pHashNext) {
						if (pUnit->dwUnitType!=UNITNO_ITEM) break;
						if (pUnit->dwTxtFileNo!=88) continue;
						if (!pUnit->pItemData) continue;
						if (pUnit->pItemData->dwOwnerId==dwPlayerId) {BackToTown();return;}
						if (pUnit->pItemData->dwOwnerId==-1) {leg=pUnit;goto found_leg;}
					}
				}
found_leg:
				if (leg&&getPlayerDistanceRaw(leg)<7) {
					LeftClickUnit(leg);
				}
			} else {
				LeftClickUnit(pUnit);
			}
			break;
		default:
			LeftClickUnit(pUnit);
	}
}
static void interact(POINT *src,int type,int txt) {
	POINT p;
	if (type!=2&&type!=5) return;
	for (int i=0;i<128;i++) {
		for (UnitAny *pUnit=d2client_pUnitTable[type*128+i];pUnit;pUnit=pUnit->pHashNext) {
			if (pUnit->dwUnitType!=type) break;
			if (pUnit->dwTxtFileNo!=txt) continue;
			p.x=pUnit->pItemPath->unitX;p.y=pUnit->pItemPath->unitY;
			if (dis(src,&p)<7) {
				if (type==2) interactObj(pUnit); 
				else LeftClickUnit(pUnit);
				return;
			}
		}
	}
}
extern int dwTotalMonsterCount;
static int autoTeleportStartMs;
int unexpectedMonCount=0,unexpectedMonTotalMs=0;
int AutoTeleportStart() {
	autoTeleportStartMs=dwCurMs;dwTpAvoiding=0;
	return 0;
}
int AutoTeleportEnd() {
	if (unexpectedMonCount) {
		switch (dwCurrentLevel) {
			case Level_TheWorldstoneChamber:break;
			default:
			gameMessage("%d monster appear after TP, avgMs=%d",unexpectedMonCount,unexpectedMonTotalMs/unexpectedMonCount);
		}
		unexpectedMonCount=0;unexpectedMonTotalMs=0;
	}
	return 0;
}
static int targetType=0,targetTxt=0,hasTarget=0,dstType=0,curdis;
static int startProcessMs=0,tpMonCount;
//0:failed 1:ok
static int teleportForward() {
	wchar_t buf[128];
	LARGE_INTEGER perfFreq,perfStart,perfEnd;
	if (tLogTP.isOn) QueryPerformanceCounter(&perfStart);
	AreaRectData *pData = PLAYER->pMonPath->pAreaRectData;
	maxDisM256=(curdis-tpMinStep)*256;
	nPos=0;
	addPossiblePostions(pData,pData,NULL,5);
	int dx=dst.x-src.x,dy=dst.y-src.y;
	for (int i=0;i<pData->nearbyRectCount;i++) {
		AreaRectData *pNData=pData->paDataNear[i];if (pNData==pData) continue;
		int dtx=pNData->tileX-pData->tileX;
		int dty=pNData->tileY-pData->tileY;
		if (dx>=0) {
			if (dy>=0) {
				if (dtx<0||dty<0) continue;
			} else {
				if (dtx<0||dty>0) continue;
			}
		} else {
			if (dy>=0) {
				if (dtx>0||dty<0) continue;
			} else {
				if (dtx>0||dty>0) continue;
			}
		}
		addPossiblePostions(pData,pNData,NULL,5);
	}
	int monDis=findValidPosition();if (monDis<0) return 0;
	nPos=0;addPossiblePostions(pData,bestRect,&bestP,5);
	monDis=findValidPosition();
	int newDis=getDistanceM256(bestP.x-dst.x,bestP.y-dst.y)>>8;
	if (abs(src.x-bestP.x)<=3&&abs(src.y-bestP.y)<=3) {startProcessMs=dwCurMs+300;return 2;}
	if (tLogTP.isOn) {
		QueryPerformanceCounter(&perfEnd);QueryPerformanceFrequency(&perfFreq);
		int timeUs=(int)((perfEnd.QuadPart-perfStart.QuadPart)*1000000.0/perfFreq.QuadPart);
		LOG(" TP (%d,%d)->(%d,%d) dis=%d new_distance=%d mon=%d monDis=%d search=%dus last=%dms\n",
			src.x,src.y,bestP.x,bestP.y,
			getDistanceM256(bestP.x-src.x,bestP.y-src.y)>>8,newDis,nMons,monDis,timeUs,dwLastTpMs);
	}
	tpMonCount=dwTotalMonsterCount;
	dwTpMs=dwCurMs;TPtarget=bestP;TPtargetRect=bestRect;dwTpDoneMs=0;TPfailedRect=NULL;
	RightSkillPos(bestP.x,bestP.y);
	wsprintfW(buf,dwGameLng?L"����%d ʱ��%d��":L"distance %d time %d",rectCountFromTarget,
		(dwCurMs-autoTeleportStartMs)/1000);
	SetBottomAlertMsg3(buf,dwPlayerFcrMs+50, 2,0);
	return 1;
}
static int findSafestPosition() {
	TPPos *end=tposs+nPos;int maxDis=0;
	for (TPPos *p=tposs;p<end;p++) {
		int monDis=getMonDis(&p->p);
		if (monDis>maxDis) {maxDis=monDis;bestRect=p->pData;bestP=p->p;}
	}
	return maxDis;
}
static int teleportToSafety() {
	wchar_t buf[128];
	int monDis=getMonDis(&src);
	if (monDis>=dwAutoTeleportSafeDistance) {
		startProcessMs=dwCurMs+300;return 0;
	}
	AreaRectData *pData = PLAYER->pMonPath->pAreaRectData;
	maxDisM256=0x7FFFFFFF;nPos=0;
	addPossiblePostions(pData,pData,NULL,5);
	for (int i=0;i<pData->nearbyRectCount;i++) {
		AreaRectData *pNData=pData->paDataNear[i];if (pNData==pData) continue;
		addPossiblePostions(pData,pNData,NULL,5);
	}
	findSafestPosition();
	nPos=0;addPossiblePostions(pData,bestRect,&bestP,5);
	monDis=findSafestPosition();
	if (abs(src.x-bestP.x)<=3&&abs(src.y-bestP.y)<=3) {startProcessMs=dwCurMs+300;return 0;}
	if (tLogTP.isOn) 
		LOG("TP find safe (%d,%d) curdis=%d monDis=%d\n",bestP.x,bestP.y,curdis,monDis);
	tpMonCount=dwTotalMonsterCount;
	dwTpMs=dwCurMs;TPtarget=bestP;TPtargetRect=bestRect;dwTpDoneMs=0;TPfailedRect=NULL;
	RightSkillPos(bestP.x,bestP.y);
	wsprintfW(buf,dwGameLng?L"���%d ʱ��%d��":L"evade %d time %d",rectCountFromTarget,
		(dwCurMs-autoTeleportStartMs)/1000);
	SetBottomAlertMsg3(buf,dwPlayerFcrMs+50, 2,1);
	return 1;
}
//return 1 if auto skill can be used
int AutoTeleport() {
	if (!tposs) {posCap=4096;tposs=(TPPos *)HeapAlloc(dllHeap,0,sizeof(TPPos)*posCap);}
	targetType=0;targetTxt=0;hasTarget=0;dstType=0;
	if (src.x==dwPlayerX&&src.y==dwPlayerY) {
		if (dwCurMs-dwTpMs<300&&dwTotalMonsterCount>tpMonCount) {
			int n=dwTotalMonsterCount-tpMonCount;
			unexpectedMonCount+=n;unexpectedMonTotalMs+=n*(dwCurMs-dwTpMs);
			tpMonCount=dwTotalMonsterCount;
		}
	} else if (!dwTpDoneMs) {
		dwTpDoneMs=dwCurMs;dwLastTpMs=dwTpDoneMs-dwTpMs;
		if (dwTpMs&&abs(dwPlayerX-TPtarget.x)>3&&abs(dwPlayerY-TPtarget.y)>3
			&&abs(dwPlayerX-src.x)<3&&abs(dwPlayerY-src.y)<3) {
			TPfailedRect=TPtargetRect;
			LOG("Tp failed\n");
		}
		startProcessMs=dwCurMs+tpDelayMs;
	}
	if (dwCurMs<startProcessMs) return 0;
	if (!fCanUseRightSkill||dwRightSkill!=Skill_Teleport||fPlayerInTown||fAutoFollowMoving) return 0;
	if (PLAYER->pInventory->pCursorItem) return 0;
	if (PLAYER->dwMode==PlayerMode_Attacking1||PLAYER->dwMode==PlayerMode_Attacking2||PLAYER->dwMode==PlayerMode_Cast)
		return 0;
	switch (dwCurrentLevel) {
		case Level_TowerCellarLevel5:
		case Level_ArcaneSanctuary:
		case Level_HallsofVaught:
		case Level_TheWorldstoneChamber:
			for (int i=0;i<128;i++) {
				for (UnitAny *pUnit=d2client_pUnitTable[UNITNO_MONSTER*128+i];pUnit;pUnit=pUnit->pHashNext) {
					if (pUnit->dwUnitType!=UNITNO_MONSTER) break;
					switch (pUnit->dwTxtFileNo) {
						case Mon_BaalCrab:case Mon_Nihlathak:case Mon_TheSummoner:
							dst.x=pUnit->pMonPath->wUnitX;dst.y=pUnit->pMonPath->wUnitY;hasTarget=1;
							break;
					}
				}
			}
			break;
	}
	maxTpDisM256=maxTpYard*256*3/2;
	src.x=dwPlayerX;src.y=dwPlayerY;
	if (hasTarget) {
		AreaRectData *pData = PLAYER->pMonPath->pAreaRectData;
		int curdisM256=disM256(&src,&dst);
		if (curdisM256<5*256) return 1;
		if (curdisM256<maxTpDisM256) {
			dwTpMs=dwCurMs;TPtarget=dst;TPtargetRect=NULL;dwTpDoneMs=0;TPfailedRect=NULL;
			RightSkillPos(dst.x,dst.y);
			return 1;
		}
		resetMonsters();
		maxDisM256=0x7FFFFFFF;nPos=0;
		for (int i=0;i<pData->nearbyRectCount;i++) addPossiblePostions(pData,pData->paDataNear[i],NULL,5);
		findValidPosition();
		nPos=0;addPossiblePostions(pData,bestRect,&bestP,5);
		findValidPosition();
		dwTpMs=dwCurMs;TPtarget=bestP;TPtargetRect=bestRect;dwTpDoneMs=0;TPfailedRect=NULL;
		RightSkillPos(bestP.x,bestP.y);return 1;
	}
	for (int retries=0;retries<6;retries++) {
		dstType=AutoTeleportGetTarget(&dst,&targetType,&targetTxt,&rectCountFromTarget);
		//0:noTarget 1:continue 2:end 3:interact 4:forceEnter >=5:keep safe distance
		if (!dstType) {startProcessMs=dwCurMs+200;return 1;}
		if (dstType!=4) findMonsters();
		else resetMonsters();
		curdis=getDistanceM256(dst.x-src.x,dst.y-src.y)>>8;
		if (curdis<reachDis&&dstType==3) {
			interact(&src,targetType,targetTxt);startProcessMs=dwCurMs+300;return 0;
		}
		if (dwTpAvoiding||dstType>=5&&curdis<dstType) { //find safe place
			dwTpAvoiding=1;
			return teleportToSafety()?0:1;
		}
		if (dstType>=2&&curdis<reachDis) { //reached
			int monDis=getMonDis(&src);
			if (monDis>=dwAutoTeleportSafeDistance) {
				//if (tLogTP.isOn) LOG("reached dst=%d monDis=%d\n",curdis,monDis);
				startProcessMs=dwCurMs+300;return 2;
			} else {
				return teleportToSafety()?0:1;
			}
		}
		if (teleportForward()) return 0;
		if (dstType<2) {
			markNextPathInvalid(stepInvalidMs);
			RerouteRectPath();
			continue;
		}
		return teleportToSafety()?0:1;
	}
	return 0;
}
