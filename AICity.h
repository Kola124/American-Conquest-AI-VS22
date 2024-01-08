// AICity.h: interface for the AICity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AICITY_H__B03D6948_B757_4B45_97F5_1F52603BFB44__INCLUDED_)
#define AFX_AICITY_H__B03D6948_B757_4B45_97F5_1F52603BFB44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// a class that gives intelligence to a group of units
// eyes, legs, teeth???
class GroupAI{
public:

};

// the spirit of the unit
class Spirit{
public:
	Spirit();
	bool Alive();
	bool SetLink(word ID, GAMEOBJ* Grp=NULL);
	void Clear();
	bool Equal(word ID, GAMEOBJ* Grp=NULL);
	word Index;
//private:	
	word Serial;
};

// economy
class AIBuild{
public:
	AIBuild();

	Spirit Unit;
	
	GAMEOBJ Invaters;
	GAMEOBJ Duzers;
	GAMEOBJ InDeffend;
	GAMEOBJ Exiters;

	word NConstructs;	// peasant for construct
	word NDuzers;	// peasant for repaire
	
	bool UnderConst;

	GAMEOBJ Guard;

	byte Usage;

	word BackID;

	bool Pulemet;

	bool UjePodjigali;

	void Init(word Index, byte Builders, byte usage);
	
	int GetNecessaryBuilders(GAMEOBJ* Builders);

	void Set();
	bool Alive();
	void Clear();
	void Process();
};

class AIMine: public AIBuild
{
public:
};

// tactics
struct LocustLimb{
	int NIndex;
	GAMEOBJ Group;

	// target choice priority
	int TCPW;	// width

	int Capture;
	int Fire;
	int Storm;
	int Peasant;

	// weapon kind
	bool ColdWeapon;
	bool Ballistic;
	bool Bullet;

};

struct LocustGroup{
};

class AIEnemy{
public:
	GAMEOBJ Build;
	GAMEOBJ CaptBld; // captured buildings
};

// New
class NewArmy{
public:
	int ArchID;

	int NatID;
	GAMEOBJ g; // Main group	
	GAMEOBJ g0;	
	GAMEOBJ g1;
	int z; // Main topology zone
	int z0; // Top Zone step destination (move)
	int z1;
	int zEnm;
	int zAli;
	void Init(int Nat);
	void Process();

	int GetArmyAmount();
	void GiveToArmy(GAMEOBJ* Src, int N);
	
};

enum AIArmyOrder{
	aiaCaptureBuild,
	aiaDestroyMine
};

class AIArmy{
public:	
	bool Guard;
	EnemyInfo2 Target;
	byte State; // 0 - free, 1 - prepair, 2 - in process, 3 - success
	AIArmyOrder Order;
	int TopZone;
	int NMen;
	byte NI;
	GAMEOBJ Fire;
	GAMEOBJ Ice;
	void Init(byte Color);
	bool Creat(AIArmyOrder order, int men, bool guard=false);
	void Process();
	int DetectTarget(GAMEOBJ* Bld);
};

const int NARMIES = 10;

class AIFront{
public:
	GAMEOBJ Warriors;
	AIArmy Army[NARMIES];
	byte NI;
	void Init();
};

const int NBrRole=3;

const int brForward=0;
const int brCenter=1;
const int brBack=2;

enum BrType{
	btStorm,
	btFire,
	btCannon,
	btTomahawk,
	btKillers,
	btRifleman
};

struct Branch{
	// type
	int NIndex;	
	// distribution
	int Part[NBrRole];
	int RestPart[NBrRole];
	int Prio[NBrRole];
	BrType Type[NBrRole];
	// units
	GAMEOBJ Group;
	int Min;
	int Max;
	int Rise;
	bool Formation;
	// protect base, captured units
	GAMEOBJ* DefTopGrp;

	bool Strelok;
	bool Rush;
	bool BaseGuard;
	bool SeakMine;
	// Domovi Horsemen
	bool Domovoi;
	bool Hunter;
};

struct Crew{

	int NIndex;

	int Role;
	GAMEOBJ Group;

	// back
	int BuildID;

	int LastMoveTime;

};

struct Hunter{
	word Index;
	word Serial;

	word TargetID;
	word TargetSN;
};

const int NHOUSES = 256;

// defenders of their island
struct iGuardGroup{
	GAMEOBJ Group;
	int x,y;
	int LastTop;
	int LastMoveTime;
};

// AICity main class
class AICity{
public:
	AICity();
	virtual ~AICity();
	void AIFree();

	int StartArmy;

	bool DefenceLess;

	bool DefendAlarm;

	int NStrelok;
	int NUnits;

	// defenders of the native island
	iGuardGroup* iGuards;
	int NiGuards;

	GAMEOBJ iGuardGrp;
	GAMEOBJ iGuardLut;
	GAMEOBJ iGuardStr;

	void AddIslandGuard(GAMEOBJ* Src);
	void ProcessIslandGuard();

	//
	int InDefNIndex;
	int CoolHuntNIndex;
	GAMEOBJ CoolHuntGroup;

	// Fields
	DWORD TimeNextField;
	
	// general
	byte NatID;
	void Init(byte NI);
	void Process();
	
	// where the water is on the map
	int LandType;
	// 0 - land ai
	// 1 - island ai

	// economy
	AIBuild House[NHOUSES];

	GAMEOBJ NewHouses;

	GAMEOBJ NewUnits;
	GAMEOBJ Free;	
	GAMEOBJ Militia;
	GAMEOBJ Fire;

	GAMEOBJ Fermers;
	GAMEOBJ Wooders;

	GAMEOBJ MainArmy;
	
	int Flags[255];

	// unit type
	int MineFobe;
	int Peasant;

	int MinFermers;
	int MinWooders;	
	int MaxDuzers;
	int PKrepost;

	// Landing
	GAMEOBJ DesantArchers;
	GAMEOBJ DesantStrelki;
	GAMEOBJ DesantWarriors;

	GAMEOBJ DesantIn;
	GAMEOBJ DesantOut;
	int DesantNOut;

	GAMEOBJ Paroms;
	int ParomNIndex;

	bool ParomIsArrive;
	//word ParomIndex;
	//word ParomSerial;

	// Hunters
	bool MeatEnabled;
	int NextDeadMeatSearch;

	int MinHuters;
	word HuntNIndex;
	int NeedHunt;
	
	word Meat[4096];
	int NextMeatSearch;

	word Farm[4096];
	int NextFarmSearch;

	GAMEOBJ HuntGroup;
	GAMEOBJ AnimKill;

	GAMEOBJ ArmHunt;
	GAMEOBJ ArmFood;
	GAMEOBJ ArmWood;	

	int NHunters;
	Hunter* HUNTERS;
	void AddHunter(GAMEOBJ* Grp);
	void ProcessHunter();	
	// Hunters
	
	int CombatPeasant;

	// tactics
	
	// cannons
	int CannonNIndex;
	GAMEOBJ Cannons;
	
	// --- distribution warriors: forward, center, backward ---
	int NBranch;
	Branch* BRANCH;
	// --- --- //

	void CrewProcess();
	Branch* AddBranch(int NIndex, byte Role, int Min, int Max);
	void AddForward(GAMEOBJ* Grp, int NIndex);
	void AddCenter(GAMEOBJ* Grp, int NIndex);
	void AddBack(GAMEOBJ* Grp, int NIndex, int BuildID);
	// --- ------------------------------------------------ ---

	AIArmy Army[NARMIES];
	int NCapBuild;
	int NCapMine;

	int CapBuild;
	int CapMine;
	int CapBuildMen;
	int CapMineMen;

	GAMEOBJ EnmBuild;
	
	AIFront Guard;
	AIFront Front[7];
	AIEnemy Enemy[7];

	int NDuzBuild;
	
	NewArmy NA[10]; // New army test
	int Man[10];

	int FirersType;
	int NFirers;
	GAMEOBJ Firers;

	int KillFromFirePerc; // create killers from incendiaries

	int PsKillType;
	int NPsKill;
	GAMEOBJ PsKill;

	int NTomahawk;
	GAMEOBJ Tomahawks;

	int NIndexBrb;
	int NIndexOff;
	int NIndexFlg;

	int NIndexMoff;

	GAMEOBJ Baraban;
	GAMEOBJ Officer;
	GAMEOBJ Flag;

	GAMEOBJ MOfficer;

	GAMEOBJ Squad;

	bool BaseDefend;
	int NextDefendTime;

	// Protect base
	//int NDefTop;
	// DefTop - it's a mask
	// 0 - captured object
	// 1 - building
	// 2 - sprawl, adjacent zones level 1
	word* DefTop;
	int NextSearchDefTop;
	
	GAMEOBJ* EnmAgrTopGrp;
	int NextSearchEnmAgrTop;
	
	// Start resource
	bool StartRes;
	void SetStartRes(int Wood, int Food, int Stone, int Gold, int Coal, int Iron);

	// map of danger
	int Fear[256];
	short TopDanger[2048];

	GAMEOBJ Gu[6];
	DWORD EA[2048];

	void Tactica();
	void Economica();

	int CallPeasantToStorm(GAMEOBJ* Dst);
	int CallPeasant(GAMEOBJ* Dst, int n, int x, int y, int r);

	bool Try(GAMEOBJ* UnitType,int Max,byte CostPercent,byte Probability);
	
};
extern AICity Village[8];

bool PrepareUpgrade(byte AiNat, byte SellRes, byte BuyRes, GAMEOBJ* Upgrade);

int Norma(int x,int y);
void SetZone(GAMEOBJ* Zone, int X, int Y, int R);

int GetSellAmount(byte,byte,int);

#define TryUnit city->Try

#endif // !defined(AFX_AICITY_H__B03D6948_B757_4B45_97F5_1F52603BFB44__INCLUDED_)
