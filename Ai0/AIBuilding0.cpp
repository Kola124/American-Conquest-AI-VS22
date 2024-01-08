// AIBuilding0.cpp: implementation of the AIBuilding0 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIHeader0.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIBuilding0::AIBuilding0()
{
	Index=0xFFFF;
}

AIBuilding0::~AIBuilding0()
{

}

bool AIBuilding0::Register(int index, int player, int groupID, int groupSN){	
	OneUnit OU;
	GetUnitGlobalInfo(groupID, &OU);
	if(OU.Index!=0xFFFF && OU.Serial==groupSN){
		Index=index;
		PlayerID=player;
		BaseID=0xFFFF;
		GroupID=groupID;
		GroupSN=groupSN;
		cX=OU.x;
		cY=OU.y;
		GetBuildingEntryPoint(&gX,&gY,groupID,150);
		NearestEnemy=0xFFFF;		
		if(Remont.Type!='UNIT') RegisterDynGroup(&Remont);
		SGP_RepairBuilding(&Remont,0,GroupID);
		if(Invite.Type!='UNIT') RegisterDynGroup(&Invite);
		SGP_ComeIntoBuilding(&Invite,0,GroupID);
		if(Leave.Type!='UNIT') RegisterDynGroup(&Leave);
		SGP_LeaveBuilding(&Leave,0,GroupID);
		BackUpID=0xFFFF;
		//R,
		return true;
	}
	return false;
};