// AIPlayer0.cpp: implementation of the AIPlayer0 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIHeader0.h"
#include <malloc.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIPlayer0 AIPlayer[8];

AIPlayer0::AIPlayer0()
{
	Index=0xFF;	
	EA = (DWORD*)malloc(256<<1);
	TD = (short*)malloc(GetNZones()*sizeof(short));
}

AIPlayer0::~AIPlayer0()
{
	free(EA);
	free(TD);
}

void AIPlayer0::Init(byte Color){
	Index=Color;
	AIStart=false;

	RegisterDynGroup(&NewUnits);
	//SetUnitsCollector(Color, &NewUnits);
	
	RegisterDynGroup(&NewBld);
	//SetBuildingsCollector(Color,&NewBld);
	
	//SetEnemyBuildingsCollector(Color,&NewEnmBld);

	AIStart=false;
	AITurn=0;
	
	memset(DetectEnemy,0,sizeof(DetectEnemy));
	DetectDelay=0;
	
	StartRes=1;

	HouseMenType=0xFFFF;
}

void AIPlayer0::SetStartRes(int Wood, int Food, int Stone, int Gold, int Coal, int Iron){
	if(StartRes){
		StartRes=0;
		AddResource(GetColor(),FOOD,Food);
		AddResource(GetColor(),WOOD,Wood);
		AddResource(GetColor(),STONE,Stone);
		AddResource(GetColor(),GOLD,Gold);
		AddResource(GetColor(),IRON,Coal);
		AddResource(GetColor(),COAL,Iron);
	}
};

void AIPlayer0::StartAI(){
	AIStart=true;
}

int AIPlayer0::RegisterBuilding(int groupID){
	OneUnit OU;
	GetUnitGlobalInfo(groupID, &OU);
	if(OU.Index!=0xFFFF){
		word id=0xFFFF;
		for(int i=0;i<N_AI_BUILD_0;i++){			
			if(Build[i].Index==0xFFFF) 
				if(id==0xFFFF) id=i;
			else
				if(Build[i].GroupID==OU.Index&&Build[i].GroupSN==OU.Serial) return i;
		}
		if(id!=0xFFFF){
			if(Build[id].Register(id,Index,OU.Index,OU.Serial)) return id;
		}
	}
	return 0xFFFF;
};

int AIPlayer0::RegisterArmy(int base){
	for(int i=0;i<N_AI_ARMY_0;i++){
		if(Army[i].Index==0xFFFF){
			Army[i].Init(i,Index,base);
			return i;
		}
	}
	return 0xFFFF;
};

void AIPlayer0::CheckInfo(){
	int NBL=CleanGroup(&NewBld);
	if(NBL){
		for(int j=0;j<NBL;j++){
			OneUnit ob;
			GetUnitInfo(&NewBld,0,&ob);
			int BID=RegisterBuilding(ob.Index);
			if(BID!=0xFFFF){
				word id=0xFFFF;
				for(int i=0;i<N_AI_BASE_0;i++){			
					AIBase0* BS=Base+i;
					if(BS->Index!=0xFFFF){
						int norma=Norma(BS->cX-ob.x,BS->cY-ob.y);
						if(norma<BS->R+4000){
							id=i;
							break;
						}
					}else{
						if(id==0xFFFF){
							id=i;
						}
					}
				}
				if(id!=0xFFFF){
					AIBase0* BS=Base+id;
					if(BS->Index==0xFFFF) BS->Init(id,Index);
					BS->AddBuild(BID);
					DeleteUnitFromGroup(&NewBld,j);
				}				
			}
		}
	}
	for(int i=0;i<N_AI_BASE_0;i++) if(Base[i].Index!=0xFFFF){
		Base[i].CheckBuild();
		Base[i].MakeSectors();
		Base[i].PredictStorm();
	}

	
	if(!AIStart) return;
	if(AITurn>0){
		AITurn--;
		return;
	}else{
		AITurn=2;
	}


	// Information about enemy armies	
	NEA = EnumEnemyArmies(GetColor(), AFL_COOR|AFL_NUNITS, EA, 256);
	
	for(int i=0;i<N_AI_BASE_0;i++) Base[i].ClearEnemyArmies();
	for(int i=0; i<NEA; i++){
		DWORD X = EA[3*i];
		DWORD Y = EA[3*i+1];
		DWORD N = EA[3*i+2];
		// pripisivaem to base
		word bid=0xFFFF;
		int bmn=100000;
		int dir;
		for(int j=0;j<N_AI_BASE_0;j++){
			AIBase0* B=Base+j;
			if(B->Index!=0xFFFF){
				int dx = X-B->cX;
				int dy = Y-B->cY;
				int nrm = Norma(dx, dy)-B->R;
				if(nrm<bmn){
					bid=j;
					bmn=nrm;
					dir= GetDir(dx,dy);
				}
			}
		}
		if(bid!=0xFFFF){
			Base[bid].AddEnemyArmy(X,Y,bmn,dir);
		}
	}
	
	// Top danger
	int Fear[255];
	memset(Fear,0,sizeof(Fear));
	Fear[0]=10;

	CreateDangerMap(GetColor(), TD, GetNZones(), Fear, 1);

	// Process
	if(GetPeaceTimeLeft()==0){
		for(int i=0;i<N_AI_BASE_0;i++) if(Base[i].Index!=0xFFFF){
			Base[i].Process();
		}
	}

};