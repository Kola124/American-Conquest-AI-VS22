#ifndef AI_PURPOSE_H
#define AI_PURPOSE_H

//---------------------SYCRO------------------
DLLIMPORT int RandNew(char*,int);
DLLIMPORT void AddRandNew(char*,int,int);
DLLIMPORT void AddUN(char* File,int Line,int Param,int Type);

#define rando() RandNew(__FILE__,__LINE__)
#define addrand(v) AddRandNew(__FILE__,__LINE__,v)
#define addname(v) AddUN(__FILE__,__LINE__,v,0)
//#define rando() RandNew(__FILE__,__LINE__)
//#define addrand(v)
//#define addname(v)

#pragma comment(linker,"/DEFAULTLIB:..\\..\\dmcr.lib")

DLLIMPORT void SGP_RepairBuilding(GAMEOBJ* Grp,byte Type,int Index);

DLLIMPORT void SGP_TakeResources(GAMEOBJ* Grp,byte Type,byte NI,int ResType);
DLLIMPORT bool IsResourceEnabled(byte NI, word ResID);

DLLIMPORT void SGP_ComeIntoBuilding(GAMEOBJ* Grp,byte Type,int Index);
DLLIMPORT void SGP_LeaveBuilding(GAMEOBJ* Grp,byte Type,int Index);

DLLIMPORT void SetBuildingsCollector(byte NI,GAMEOBJ* Grp);
DLLIMPORT void SetEnemyBuildingsCollector(byte NI,GAMEOBJ* Grp);
DLLIMPORT void SetUnitsCollector(byte NI,GAMEOBJ* Grp);

DLLIMPORT void CreateFields(byte NI);

DLLIMPORT int GetMaxUnits(byte NI);
DLLIMPORT int GetCurrentUnits(byte NI);

DLLIMPORT int GetInsideAmount(int Index);
DLLIMPORT int GetMaxInsideAmount(int Index);

//Fields
#define AFL_COOR     1
#define AFL_NUNITS   2
#define AFL_FORCE    4
#define AFL_MINIMAX  8

// BufSize - number of DWORD
DLLIMPORT int EnumEnemyArmies(byte NI,DWORD Fields,DWORD* Data,int BufSize);

DLLIMPORT bool GetGrpCenter(GAMEOBJ* Grp,int* x,int* y);

// Flags for move purpose
#define MSO_ALLOW_ENEMY_SEARCH 1
#define MSO_ALLOW_ANSWER_ATTACK 2
#define MSO_ALLOW_ONLY_ARMATTACK 4
#define MSO_ALLOW_ATTACK_WITHOUT_MOVEMENT 8
#define MSO_CANCEL_WHEN_ATTACKED 16
#define MSO_CANCEL_WHEN_FIRST 32

DLLIMPORT void SGP_MoveToPoint(byte NI,GAMEOBJ* Grp,int x,int y,int Direction,int DF,int DR,DWORD Flags);
DLLIMPORT int SGP_MakeOneStepTo(byte NI,GAMEOBJ* Grp,int x,int y,int Direction,DWORD Flags);
DLLIMPORT int SGP_ExMakeOneStepTo(byte NI,GAMEOBJ* Grp,int x,int y,int DF,int DR,int Direction,DWORD Flags);

DLLIMPORT bool SGP_AttackByArchers(byte NI,GAMEOBJ* GRP,int R,DWORD Flags);


DLLIMPORT void SetUnitsState(GAMEOBJ* GRP,bool SearchEnemy,bool StandGround,bool ArmAttack,bool FriendlyFire);

// Purpose
const DWORD P_REPAIR = 'REPB';
const DWORD P_RESOURCE = 'TRES';
const DWORD P_COMEINTO = 'IBLD';
const DWORD P_MOVE = 'MOVE';
const DWORD P_ARCA = 'ARCA';
const DWORD P_ARCP = 'ARCP';
const DWORD P_LEVEMINE = 'LEBL';

DLLIMPORT DWORD GetCurrentPurpose(GAMEOBJ* GRP);
DLLIMPORT void CancelCurrentPurpose(GAMEOBJ* GRP);
DLLIMPORT void CancelAllPurposes(GAMEOBJ* GRP);

//DLLIMPORT int GetEnemyBuildList(byte NI,word** IDS);

struct EnemyInfo2{
	word Index;
	int NInside;
	int MaxInside;
	int x,y,NI;
	byte Usage;
};
DLLIMPORT bool GetUnitInfo2(word Index, EnemyInfo2* BINF);

// Topology zones
DLLIMPORT int GetTopZone(int x,int y);
DLLIMPORT bool GetTopZoneCoor(int Zone,int* x,int* y);
DLLIMPORT bool GetTopZRealCoor(int Zone,int* x,int* y);
DLLIMPORT int GetListOfNearZones(int Zone,word** ZonesAndDist);
DLLIMPORT int GetNextZone(int Start,int Fin);
DLLIMPORT int GetZonesDist(int Start,int Fin);
DLLIMPORT int GetTopDist(int xa,int ya,int xb,int yb);
DLLIMPORT int GetNZones();
DLLIMPORT bool CheckIfPointsNear(int xa,int ya,int xb,int yb);
DLLIMPORT bool isGroupNearXY(GAMEOBJ* Grp, int x, int y);

DLLIMPORT byte GetUnitCategory(int Index);
DLLIMPORT byte GetUnitTypeCategory(int NIndex);

DLLIMPORT void CreateDangerMap(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void CreateDangerMapForDef(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void CreateDangerMapWithoutPeasants(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void CreateDangerMapForTom(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void CreateDangerMapForStorm(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void CreateDangerMapForFire(byte NI,short* DangMap,int MaxSize,int* FearArray,int ItrAmount);
DLLIMPORT void SetDangerMap(int* Map);

DLLIMPORT int FindNextZoneOnTheSafeWay(int Start,int Fin,short* DangerMap,int* MaxDanger,int DangSteps);
DLLIMPORT int FindNextZoneOnTheSafeWayToObject(int Start,short* DangerMap,word* ObjIds,int* MaxDanger,int DangSteps,word* DestObj);

DLLIMPORT int GetLastFullWay(word** buf);

DLLIMPORT bool CheckMineCaptureAbility(int Index);
DLLIMPORT void DeleteUnit(int Index);
DLLIMPORT bool AttackEnemyInZone2(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI);

DLLIMPORT bool Attack3(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm);
DLLIMPORT bool AttackByTomahawks(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm);
DLLIMPORT bool Attack4(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm);
DLLIMPORT bool Attack5(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm);
DLLIMPORT bool Attack7(GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm, int Force); //same as Att3 but Grp->Force>Force
DLLIMPORT int GetEnemy3(int Zone, int Radius, byte NI);
DLLIMPORT bool GrpAttackObject(byte NI,GAMEOBJ* Grp,int TargetID);
DLLIMPORT bool AttackGrpByGrp(GAMEOBJ* Att, GAMEOBJ* Enm);
DLLIMPORT bool MakeOneShotToBuild(GAMEOBJ* Zone,GAMEOBJ* Grp,byte NI);

DLLIMPORT int GetEnemyForce(GAMEOBJ* Zone,byte NI);
DLLIMPORT int GetAlliesForce(GAMEOBJ* Zone,byte NI);

// AI storm

//0-archer
//1-short range unit
//2-shooter
//3-peasant
//4-hidden
//5-tamagavshik & kopiemet
DLLIMPORT void FilterUnitsByCategory(GAMEOBJ* G_Src,GAMEOBJ* G_Dst,int Ctg);
DLLIMPORT int StormSimulator(GAMEOBJ* StormGroup,GAMEOBJ* AddDefenders,word BldIndex);
DLLIMPORT void CopyUnits(GAMEOBJ* Src,GAMEOBJ* Dest,int start,int n,bool add,bool remove);

/*
DLLEXPORT
bool isGroupNearXY(GAMEOBJ* Grp, int x, int y){
	if(Grp->Type!='UNIT'||Grp->Index>=SCENINF.NUGRP) return false;
	UnitsGroup* UG=SCENINF.UGRP+Grp->Index;
	//int x,y;
	//if(GetGroupCenter(UG,&x,&y)){
	//}
	int Z0 = GetTopZone(x,y);
	if(Z0<NAreas){
		int N=UG->N;
		for(int i=0;i<N;i++){
			word MID=UG->IDS[i];
			if(MID!=0xFFFF){
				OneObject* OB=Group[MID];
				if(OB&&OB->Serial==UG->SNS[i]){
					int x1 = OB->RealX>>4;
					int y1 = OB->RealY>>4;
					int Z1 = GetTopZone(x1, y1);
					if(GetNextZone(Z0,Z1)==Z1) return true;
				};
			};
		};
	}
	return false;
}
*/

struct ArmInfo{
	int x,y;
	word NMen;
	word MenID[3000];
	word MenSN[3000];
	word NIndex[2048];
	word aNIndex;			// amount of units type
	word NUnits[10][32];	// amount of warriors [NIndex][Kills level of unit]
};

DLLIMPORT void GetEArmyInfo(byte NI, ArmInfo* Army, int Radius);

DLLIMPORT bool GetBuildingEntryPoint(int* x,int* y,word Index,int AddDistance);


#include "OneObj.h"

DLLIMPORT OneObject* GetOBJ(int Index);
DLLIMPORT void OBJ_SendTo(word Index,int x,int y,byte Prio,byte OrdType);
DLLIMPORT void OBJ_SmartSendTo(word Index,int x,int y,int dx,int dy,byte Prio,byte OrdType);
DLLIMPORT void OBJ_AttackObj(word Index,word Enemy,byte Prio,int NTimes);
DLLIMPORT bool OBJ_GoToMine(word Index,word DestMine,byte prio,byte OrdType);
DLLIMPORT bool OBJ_LeaveMine(word Index,word NIndex);
DLLIMPORT bool OBJ_GoToTransport(word Index,word TrID,byte Prio);
DLLIMPORT void OBJ_LeaveTransport(word Index,word NIndex);
DLLIMPORT bool OBJ_BuildObj(word Index,word BldIndex,byte Prio,byte OrdType);
DLLIMPORT int OBJ_TakeResource(word Index,int x,int y,byte ResID,byte Prio,byte OrdType);
DLLIMPORT void OBJ_Produce(word Index,word NIndex,word GroupID);

DLLIMPORT int GetOrderType(OneObject* OB);
DLLIMPORT void GetTargetObject(word AttackID, word* Index, word* Serial);
DLLIMPORT int GetSearchRadius(int Index);

DLLIMPORT int GetGroupForce(GAMEOBJ* Grp);

DLLIMPORT int GetRND(int Max);

// DipServer import
CIMPORT void AddStorm(GAMEOBJ* Src, byte Owner, int Diff=0);
CIMPORT void AddFirers(GAMEOBJ* Src,byte Owner);
CIMPORT void AddPsKillers(GAMEOBJ* Src,byte Owner,bool SeakMine=true);
CIMPORT void AddTomahawks(GAMEOBJ* Src,byte Owner,word Base,int DriftRadius, int CriticalMass);
CIMPORT void AddCannon(GAMEOBJ* Src, byte Owner);

// 
CIMPORT bool SetAIForDiplo(byte nat, int x, int y);

// List of targets
DLLIMPORT void CreateMeatList(word* IDS, byte NI, int MaxOB);
DLLIMPORT void CreateFarmList(word* IDS, byte NI);

DLLIMPORT void AddOneUnitToGroup(GAMEOBJ* Units,OneObject* OB);

DLLIMPORT bool CreateFormation(byte NI,GAMEOBJ* Officers,GAMEOBJ* Drummers,GAMEOBJ* FlagBearers,GAMEOBJ* Soldiers,GAMEOBJ* DestGroup,char* FormID);

DLLIMPORT int CreateListOfResourceSprites(byte ResID,int* Xi,int* Yi,int NMax);
DLLIMPORT int EraseFarSpritesFromList(byte NI,byte ResID,int* Xi,int* Yi,int N,int MaxR);

DLLIMPORT void CreateNonFiredEnemyBuildingsTopList(word* IDS,byte NI);
DLLIMPORT void CreateTopListForStorm(word* IDS,byte NI);
DLLIMPORT void CreateTopListEnArmy(word* IDS,byte NI,int MinPS);
DLLIMPORT void CreateFriendBuildingsTopList(word* IDS,byte NI);

DLLIMPORT int SearchCapturedTopToDeffend(byte NI,word* DefTop);

DLLIMPORT bool ArtAttackGroud(byte NI,GAMEOBJ* Grp, int x, int y);
DLLIMPORT bool ArtAttackObject(byte NI,GAMEOBJ* Grp,int TargetID);

DLLIMPORT void MakeEnemyAgrTopGrp(byte NI, GAMEOBJ* EATG, word* BaseTop);

DLLIMPORT bool CheckDef(GAMEOBJ* Def, word DefZone, GAMEOBJ* Branch, word* BaseTop);

DLLIMPORT void AssignDesantStartGroup(byte NI,GAMEOBJ* Grp);
DLLIMPORT void AssignDesantDestGroup(byte NI,GAMEOBJ* Grp);

DLLIMPORT void DieUnit(word MID);

DLLIMPORT int GetExtraction(byte ResID);

DLLIMPORT void SetMaxInTransport(byte NI,int Max);

DLLIMPORT bool TryUpgradeEx(GAMEOBJ* Upgrade,int CostPercent,int Probability,int MaxCenterR,int MaxBuildingR);


#endif