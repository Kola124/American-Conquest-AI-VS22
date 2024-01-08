// AIArmy0.h: interface for the AIArmy0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIARMY0_H__DFACA322_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
#define AFX_AIARMY0_H__DFACA322_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AIBase0.h"
#include "AIBuilding0.h"

class AIArmy0
{
public:
	AIArmy0();
	virtual ~AIArmy0();

	word Index;
	byte PlayerID;	
	word BaseID;

	byte EnemyID;
	word EnemyBaseID;	

	word NEArmy;
	ArmInfo EArmy[20];

	int cX, cY;
	//int zTop;
	
	word NBranch;
	word BranchID[N_AI_BRANCH_0];
	
	GAMEOBJ Men[N_AI_BRANCH_0];

	word NBrigade;
	AIBrigade0 Brigade[N_AI_BRIGADE_0];

	word Acceptor;	// acceptor of new units

	//bool Defend[8];
	int TopDest[8];		
	bool Storm[8];	

	byte aSec[2];	// sectors of enemy base to attack
	
	word Prim;	// primary brigade
	word Secd;	// secondary brigade
	
	word Brg[8];	// brigade working on building
	word Bld[8];	// target building
	
	word NMen[8];	// men on orders
	word NeedMen[8]; // nessesary amount of wariors
	

	void GetInfo();
	void Attack();
	void Defend();
	void Process();

	// Orders
	void MoveToEBase(AIBrigade0* BR);
	void SafeMoveToZone(AIBrigade0* BR, int DstTop);
	void StormTheBase(AIBrigade0* Br);
	void Razvedka(AIBrigade0* Br);
	void ConnectToNearestArmy(AIBrigade0* Br);
	
	void BackUpForBuild(AIBrigade0* Br);

	void DestroyNearest(AIBrigade0* Br);
	void CallNearest(AIBrigade0* Br);

	bool GiveBackUpForBuild(AIBuilding0* Bl); // backup for buildings
	
	// Methods
	void Init(word index, byte player, word base);

	word RegisterBrigade();

	int MakeFromZone(int x, int y, int r, bool add);	

	void ClearEArmies();
	bool AddEArmy(int x, int y);


};

#endif // !defined(AFX_AIARMY0_H__DFACA322_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
