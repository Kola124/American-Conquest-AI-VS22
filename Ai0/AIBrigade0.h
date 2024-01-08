// AIBrigade0.h: interface for the AIBrigade0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIBRIGADE0_H__53AAE082_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
#define AFX_AIBRIGADE0_H__53AAE082_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AIBrigade0  
{
public:
	AIBrigade0();
	virtual ~AIBrigade0();

	word Index;
	byte PlayerID;
	word ArmyID;

	word BranchID;
	GAMEOBJ Men;
	
	GAMEOBJ Arch;
	GAMEOBJ Cold;
	GAMEOBJ Shoot;
	GAMEOBJ Peasant;

	GAMEOBJ Enemy;

	// Brigade info
	word NMen;
	word NCenter;
	int x,y;
	int Top;

	byte Order;	
	/*	
		0xFF - relax, 
		0 - primary target, 
		1 - secondary,
		2 - connect to 0,
		3 - connect to 1,
		4 - attack enemy army,
		5 - storm, // ustarevshiy
		6 - fire,
		7 - protect building,
		8 - divert peasant,
		9 - razvedka
		10 - connect to nearest
		11 - personal deffence
		12 - zone deffence
	*/
	
	// Order info
	int DstTop;	// Topological zone to control for order 4
	

	int NeedMan;
	bool Storm;

	int EnmX;
	int EnmY;
	int EnmNorm;
	int EnmForce;

	byte StormSect;	// Sector of enemy base
	byte EnemyID;
	word EnemyBaseID;

	word PrimTargetID; // for order 5,6
	word PrimTargetSN;

	int PrevTop;

	int Divert;

	word Build;	// index of building in Build[] array

	// Methods
	void Init(word index, word army, byte player);
	void GetInfo();
	void Clear();
	bool CallFree(int x, int y);

	void DivideByCategory(GAMEOBJ* Src, bool Clear=false);

};

#endif // !defined(AFX_AIBRIGADE0_H__53AAE082_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
