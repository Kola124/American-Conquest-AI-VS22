// AIBuilding0.h: interface for the AIBuilding0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIBUILDING0_H__53AAE081_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
#define AFX_AIBUILDING0_H__53AAE081_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AIBuilding0  
{
public:
	word Index;
	byte PlayerID;
	word BaseID;

	word GroupID;
	word GroupSN;

	int cX, cY;
	int R;
	int gX, gY;	// Gateway x,y

	word Dir;	// Direction to base center
	byte Sect;	// Sector in model of the base
	int Norm;	// Norma of vector from build to center of the base

	word NearestEnemy;
	int EnemyNorm;

	word BackUpID;	// Brigade for BackUp

	GAMEOBJ Remont;
	GAMEOBJ Invite;
	GAMEOBJ Leave;

	AIBuilding0();
	virtual ~AIBuilding0();

	bool Register(int index, int player, int groupID, int groupSN);
};

#endif // !defined(AFX_AIBUILDING0_H__53AAE081_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
