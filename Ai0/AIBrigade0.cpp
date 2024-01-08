// AIBrigade0.cpp: implementation of the AIBrigade0 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIHeader0.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIBrigade0::AIBrigade0()
{
	Index=0xFFFF;

}

AIBrigade0::~AIBrigade0()
{

}

void AIBrigade0::Init(word index, word army, byte player){
	Index=index;
	ArmyID=army;
	PlayerID=player;

	if(Men.Type!='UNIT') RegisterDynGroup(&Men);

	if(Arch.Type!='UNIT') RegisterDynGroup(&Arch);
	if(Cold.Type!='UNIT') RegisterDynGroup(&Cold);
	if(Shoot.Type!='UNIT') RegisterDynGroup(&Shoot);
	if(Peasant.Type!='UNIT') RegisterDynGroup(&Peasant);

	if(Enemy.Type!='UNIT') RegisterDynGroup(&Enemy);	
	
	Order=0xFF;	// relax

	PrevTop=0xFFFF;
	
	NeedMan=0;
	Storm=false;

};

void AIBrigade0::GetInfo(){
	if(Index==0xFFFF) return;

	GetGrpCenter(&Men, &x, &y);
	Top = GetTopZone(x,y);

};

void AIBrigade0::DivideByCategory(GAMEOBJ* Src, bool Clear){
	if(Index==0xFFFF) return;
	
	if(Clear){
		ClearGroup(&Cold);
		ClearGroup(&Arch);
		ClearGroup(&Peasant);
		ClearGroup(&Shoot);
	}

	CopyUnits(Src,&Cold,0,2000,1,0);	

	FilterUnitsByCategory(&Cold, &Arch, 0);
	FilterUnitsByCategory(&Cold, &Peasant, 3);
	FilterUnitsByCategory(&Cold, &Shoot, 2);
		
};

void AIBrigade0::Clear(){
	if(Index==0xFFFF) return;
	Index=0xFFFF;

	CancelAllPurposes(&Men);

	CancelAllPurposes(&Cold);
	CancelAllPurposes(&Arch);
	CancelAllPurposes(&Peasant);
	CancelAllPurposes(&Shoot);

	ClearGroup(&Cold);
	ClearGroup(&Arch);
	ClearGroup(&Peasant);
	ClearGroup(&Shoot);

	AIPlayer0* P=AIPlayer+PlayerID;
	RemoveGroup(&Men, &P->NewUnits);
};

bool AIBrigade0::CallFree(int x, int y){
	if(Index==0xFFFF) return false;
	
	AIPlayer0* P=AIPlayer+PlayerID;
	
	RemoveNearestUnit(&P->NewUnits,&Men,x,y,7000);
	
	Village[P->GetColor()].CallPeasantToStorm(&Men);
	GetInfo();
	
	//DivideByCategory(&Men);
	//SetUnitsState(&Arch,1,0,0,1);
	return true;
};


/*
void AIBrigade0::Parade(){

}
*/