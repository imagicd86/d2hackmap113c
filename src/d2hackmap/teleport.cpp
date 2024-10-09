#include "stdafx.h"
#include "multi.h"
#include "auto.h"
#include "map.h"
#include "d2ptrs.h"

int isWaypointTxt(int txt);
void takeWaypointToLevel(UnitAny *waypoint,int level);
void markNextPathInvalid(int ms);
int RerouteRectPath();

POINT TPtarget;int dwTpMs,dwTpDoneMs;
static char aMonYard[32][2];
static int defMonYard,maxTpYard,tpDelayMs,tpMinStep,stepInvalidMs,avoidEdge=0;
static ToggleVar tLogTP={TOGGLEVAR_ONOFF,0,-1,1,"Log TP Toggle"};
int maxTpDisRaw;
static ConfigVar aConfigVars[] = {
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
struct Mon {
	POINT p;
	int dis;
};
static POINT src,dst;
Mon *mons=NULL;
static int monCap=0,nMons=0,maxTpDis2;
static int moveOn,minDstDis2,maxMonDis;
static POINT minDstP,maxMonP;
static AreaRectData *minDstRect,*maxMonRect;

static int dis(POINT *p1,POINT *p2) {return getDistanceM256(p1->x-p2->x,p1->y-p2->y)>>8;}
static int dis2(POINT *p1,POINT *p2) {int dx=p1->x-p2->x,dy=p1->y-p2->y;return dx*dx+dy*dy;}
static void findMonsters() {
	if (!mons) {monCap=4096;mons=(Mon *)HeapAlloc(dllHeap,0,sizeof(Mon)*monCap);}
	nMons=0;
	for (int i=0;i<128;i++) {
		for (UnitAny *pMon=d2client_pUnitTable[UNITNO_MONSTER*128+i];pMon;pMon=pMon->pHashNext) {
			if (pMon->dwUnitType!=UNITNO_MONSTER) break;
			if (pMon->dwMode==MonsterMode_Death) return; //dying?
			if (pMon->dwMode==MonsterMode_Dead) return; //already dead
			int owner=d2client_GetMonsterOwner(pMon->dwUnitId);if (owner!=-1) return; 
			int mtype=aAutoSkillMonsterType[pMon->dwTxtFileNo];
			if (mtype&MONSTER_TYPE_NEUTRAL) continue;
			if (nMons>=monCap) {monCap*=2;mons=(Mon *)HeapReAlloc(dllHeap,0,mons,sizeof(Mon)*monCap);}
			Mon *pmon=&mons[nMons++];
			pmon->p.x=pMon->pMonPath->wUnitX;pmon->p.y=pMon->pMonPath->wUnitY;
			pmon->dis=aMonYard[dwPlayerFcrFrame][(mtype&MONSTER_TYPE_DANGROUS)?1:0];
			if (!pmon->dis) pmon->dis=defMonYard;
			pmon->dis=(pmon->dis*3)>>1;
		}
	}
}
static int getMonDis(POINT *src) {
	int minDis=0x7FFFFFFF;
	Mon *end=mons+nMons;
	for (Mon *p=mons;p<end;p++) {
		int d=dis(src,&p->p)-p->dis;
		if (d<minDis) minDis=d;
	}
	return minDis;
}
static void checkRect(AreaRectData *pCenter,AreaRectData *pData,POINT *p,int step) {
	if (!pData||!pData->bitmap) return;
	unsigned short *bitmap=pData->bitmap->bitmap;
	int w=pData->bitmap->unitW,h=pData->bitmap->unitH;
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
			POINT p;
			for (int y=0;y<step;y++) {
				for (int x=0;x<step;x++) {
					 if (((*ptr++)&0x1527)==0) {p.x=pData->unitX+tx+x;p.y=pData->unitY+ty+y;goto check;}
				}
				ptr+=w-step;
			}
			continue;
check:
			if (dis2(&src,&p)>maxTpDis2) continue;
			int dst2=dis2(&dst,&p);
			int monDis=getMonDis(&p);
			if (monDis>=0) {if (dst2<minDstDis2) {minDstDis2=dst2;minDstRect=pData;minDstP=p;moveOn=1;}}
			if (monDis>maxMonDis) {maxMonDis=monDis;maxMonRect=pData;maxMonP=p;}
		}
	}
}
static void enter(POINT *src,int type,int txt) {
	POINT p;
	if (type!=2&&type!=5) return;
	for (int i=0;i<128;i++) {
		for (UnitAny *pUnit=d2client_pUnitTable[type*128+i];pUnit;pUnit=pUnit->pHashNext) {
			if (pUnit->dwUnitType!=type) break;
			if (pUnit->dwTxtFileNo!=txt) continue;
			p.x=pUnit->pItemPath->unitX;p.y=pUnit->pItemPath->unitY;
			if (dis2(src,&p)<50) {
				if (type==2&&isWaypointTxt(pUnit->dwTxtFileNo)) {
					takeWaypointToLevel(pUnit,actlvls[ACTNO]);
				}
				LeftClickUnit(pUnit);
				break;
			}
		}
	}
}
extern int dwTotalMonsterCount;
int unexpectedMonCount=0,unexpectedMonTotalMs=0;
int AutoTeleportEnd() {
	if (unexpectedMonCount) {
		gameMessage("%d monster appear after TP, avgMs=%d",unexpectedMonCount,unexpectedMonTotalMs/unexpectedMonCount);
		unexpectedMonCount=0;unexpectedMonTotalMs=0;
	}
	return 0;
}
int AutoTeleport() {
	int targetType=0,targetTxt=0,hasTarget=0,dstType=0;
	static int ms=0,tpMonCount;
	if (src.x==dwPlayerX&&src.y==dwPlayerY) {
		if (dwCurMs-dwTpMs<300&&dwTotalMonsterCount>tpMonCount) {
			int n=dwTotalMonsterCount-tpMonCount;
			unexpectedMonCount+=n;unexpectedMonTotalMs+=n*(dwCurMs-dwTpMs);
			tpMonCount=dwTotalMonsterCount;
		}
	} else if (!dwTpDoneMs) {
		dwTpDoneMs=dwCurMs;
		if (tLogTP.isOn) {
			if (logfp) {
				fprintf(logfp," done %dms",dwTpDoneMs-dwTpMs);
				if (dwPlayerX!=TPtarget.x||dwPlayerY!=TPtarget.y) 
					fprintf(logfp," expect (%d,%d) actual (%d,%d)\n",TPtarget.x,TPtarget.y,dwPlayerX,dwPlayerY);
				fputc('\n',logfp);fflush(logfp);
			}
		}
		ms=dwCurMs+tpDelayMs;
	}
	if (dwCurMs<ms) return 0;
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
	maxTpDis2=maxTpYard;maxTpDis2=(maxTpDis2*maxTpDis2*9)>>2;
	AreaRectData *pData = PLAYER->pMonPath->pAreaRectData;
	src.x=dwPlayerX;src.y=dwPlayerY;
	moveOn=0;minDstDis2=0x7FFFFFFF;maxMonDis=0;
	if (hasTarget) {
		int curdis2=dis2(&src,&dst);
		if (curdis2<5*5) return 1;
		if (curdis2<maxTpDis2) {dwTpMs=dwCurMs;dwTpDoneMs=0;TPtarget=dst;RightSkillPos(dst.x,dst.y);return 1;}
		nMons=0;
		for (int i=0;i<pData->nearbyRectCount;i++) checkRect(pData,pData->paDataNear[i],NULL,5);
		checkRect(pData,minDstRect,&minDstP,5);
		dwTpMs=dwCurMs;dwTpDoneMs=0;TPtarget=minDstP;
		RightSkillPos(minDstP.x,minDstP.y);return 1;
	}
	int retries=0;
search_start:
	dstType=AutoTeleportGetTarget(&dst,&targetType,&targetTxt);
	//LOG("AutoTeleport dst(%d,%d) type %d\n",dst.x,dst.y,dstType);
	if (!dstType) {ms=dwCurMs+200;return 1;}
	nMons=0;
	if (dstType!=4) findMonsters();
	int reachDis=6;
	int curdis=getDistanceM256(dst.x-src.x,dst.y-src.y)>>8;
	if (curdis<reachDis&&dstType==3) {
		enter(&src,targetType,targetTxt);ms=dwCurMs+300;return 0;
	}
	if (dstType>=5&&curdis<dstType) { //find safe place
		checkRect(pData,pData,NULL,5);
		for (int i=0;i<pData->nearbyRectCount;i++) {
			AreaRectData *pNData=pData->paDataNear[i];if (pNData==pData) continue;
			checkRect(pData,pNData,NULL,5);
		}
		POINT p=maxMonP;AreaRectData *pData=maxMonRect;
		checkRect(pData,pData,&p,5);
		p=maxMonP;
		if (abs(src.x-p.x)<=1&&abs(src.y-p.y)<=1) {ms=dwCurMs+300;return 1;}
		if (tLogTP.isOn) 
			LOG("TP find safe (%d,%d) curdis=%d monDis=%d\n",p.x,p.y,curdis,maxMonDis);
		tpMonCount=dwTotalMonsterCount;dwTpDoneMs=0;
		dwTpMs=dwCurMs;dwTpDoneMs=0;TPtarget=p;
		RightSkillPos(p.x,p.y);
		return 0;
	}
	if (curdis<reachDis) { //reached
		int monDis=getMonDis(&src);
		if (monDis>=30) {
			if (tLogTP.isOn) 
				LOG("reached dst=%d monDis=%d\n",curdis,monDis);
			ms=dwCurMs+300;return 1;
		}
	}
	LARGE_INTEGER perfFreq,perfStart,perfEnd;QueryPerformanceCounter(&perfStart);
	int dx=dst.x-src.x,dy=dst.y-src.y;
	checkRect(pData,pData,NULL,5);
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
		checkRect(pData,pNData,NULL,5);
	}
	POINT p=moveOn?minDstP:maxMonP;
	AreaRectData *pDstData=moveOn?minDstRect:maxMonRect;
	checkRect(pData,pDstData,&p,5);
	p=moveOn?minDstP:maxMonP;
	int newDis=getDistanceM256(p.x-dst.x,p.y-dst.y)>>8;
	if (dstType==1&&newDis>reachDis&&curdis-newDis<tpMinStep&&retries<=3) {
		if (tLogTP.isOn) 
			LOG("TP can't move on curdis=%d newdis=%d tpMinStep=%d\n",curdis,newDis,tpMinStep);
		markNextPathInvalid(stepInvalidMs);
		RerouteRectPath();
		retries++;
		goto search_start;
	}
	if (abs(src.x-p.x)<=1&&abs(src.y-p.y)<=1) {ms=dwCurMs+300;return 1;}
	if (tLogTP.isOn) {
		QueryPerformanceCounter(&perfEnd);QueryPerformanceFrequency(&perfFreq);
		double timeMs=(perfEnd.QuadPart-perfStart.QuadPart)*1000.0/perfFreq.QuadPart;
		LOG(" TP(%d,%d)->(%d,%d) dis=%d moveOn=%d new_distance=%d maxMonDis=%d %.3lf ms\n",src.x,src.y,p.x,p.y,
			getDistanceM256(p.x-src.x,p.y-src.y)>>8,moveOn,newDis,maxMonDis,timeMs);
	}
	tpMonCount=dwTotalMonsterCount;dwTpMs=dwCurMs;TPtarget=p;dwTpDoneMs=0;
	RightSkillPos(p.x,p.y);
	return 0;
}
