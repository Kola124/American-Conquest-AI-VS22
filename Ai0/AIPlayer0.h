// AIPlayer0.h: interface for the AIPlayer0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPLAYER0_H__53AAE080_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
#define AFX_AIPLAYER0_H__53AAE080_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AIBase0.h"

class AIPlayer0
{
public:
	byte Index;	// ID in players array

	word NBase;
	AIBase0 Base[N_AI_BASE_0];
	word NBranch;
	AIBranch0 Branch[N_AI_BRANCH_0];
	word NBuild;
	AIBuilding0 Build[N_AI_BUILD_0];
	word NArmy;
	AIArmy0 Army[N_AI_ARMY_0];
	word NOrder;
	AIOrder0 Order[N_AI_ORDER_0];

	//StartEngine
	bool AIStart;
	int AITurn;
	
	bool Evropean;
	
	//Units
	GAMEOBJ NewUnits;
	
	// EnemyInfo
	GAMEOBJ NewBld;
	GAMEOBJ NewEnmBld;

	int NEA;
	DWORD* EA;	// enemy armies

	short* TD;	// top danger

	word NEnmBase;
	AIBase0 EnmBase[N_AI_BASE_0];

	word NEnmArmy;
	//AIArmy0 EnmArmy[N_AI_ARMY_0];

	int HouseMenType;

	// Razvedka
	bool DetectEnemy[7];
	int DetectDelay;

	bool StartRes;
	void SetStartRes(int Wood, int Food, int Stone, int Gold, int Coal, int Iron);

	// Methods

	AIPlayer0();
	virtual ~AIPlayer0();
	
	void Init(byte Color);
	void StartAI();

	void Process();

	inline byte GetColor(){return Index;}

	// Priority
	// 1. Units (GAMEOBJ)
	// 2. Coordinats (x,y)
	// 3. Units type (Branch) (NIndex)
	// 4. Players (Color)
	// Priority create functions

	void CheckInfo();

	int RegisterBuilding(int groupID);	// Group[groupID], return Build[id]
	int RegisterArmy(int base);

};
extern AIPlayer0 AIPlayer[8];


#endif // !defined(AFX_AIPLAYER0_H__53AAE080_78F0_11D6_8F84_D2CF6D35823E__INCLUDED_)
