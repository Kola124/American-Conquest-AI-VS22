// AIBase0.h: interface for the AIBase0 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIBASE0_H__DFACA320_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
#define AFX_AIBASE0_H__DFACA320_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Sectors base model
extern void InitSectorsModel();
extern byte DirToSec[256];

// Enemy info
const int NAIENEMY0_INDEX = 1000;
const int NAIENEMY0_BRANCH = 20;

struct AIEnemy0{
	int N;
	int X;
	int Y;
	int Index[NAIENEMY0_INDEX];
	AIBranch0 Branch[NAIENEMY0_BRANCH];
};

// Model of the base
const int NAIBASE0_BUILDINGS = 100;
const int NAIBASE0_ENEMY = 20;

const int N_BASE_AGR_0 = 20;

class AIBase0
{
public:
	AIBase0();
	virtual ~AIBase0();

	word Index;
	// Player
	byte PlayerID;	// Owner

	byte EnemyID;	// Enemy base
	word EnemyBaseID;
	
	// Army
	word DefID;	// Deffenders army
	word AgrID[N_BASE_AGR_0];	// Agressors army

	// Buildings	
	word NBldTotal;
	word Bld[9*32];	// index in Bilding array
	word Remote;	// samoe udalennoe zdanie ot centra
	// Geometry model
	int cX, cY;		// Center of the base
	int R;			// Radius of the base
	// Sectors model
	bool ValidState;
	word NBSect[9];	
	word BSect[9][32];		// buildings in sectors
	//word BNorm[9][32];		// norma of vector from building to base center
	//word BldMI[9][32];	// OneObject* Group[] index of buildings: 0..8 - sectors, 9 - center
	
	// Storm strategy
	int LastPredictTime;
	int zStorm[8];	// Top zones for storm sector
	ArmInfo eAgr[8];	// Enemy agressors near the base
	int eAgrL[8];	// Norma (not Top distance) to enemy army

	// Referenced method
	void Init(word Index, byte Player);
	
	bool AddBuild(word buildID);	// Insert new building from build array
	void CheckBuild();

	void CalcBaseZone(); // cX,cY,R
	void MakeSectors();	// Geometry model of the base
	void PredictStorm();	// Storm strategy of the base

	void Process();

	// Not referenced
	void GiveToDefenders(GAMEOBJ* Src, int Free);
	void TakeFromDefenders(GAMEOBJ* Dst, int Need);

	void ClearEnemyArmies();
	int AddEnemyArmy(int x, int y, int norm, int dir);
};

#endif // !defined(AFX_AIBASE0_H__DFACA320_74A4_11D6_9BB0_0004ACE60ADC__INCLUDED_)
