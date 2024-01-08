#pragma pack(1)

struct OneObject{
public:
	void* Nat;
	void* GO;
	void* newMons;
	//-----------new path algoritm variables----------------
	short* PathX;
	short* PathY;
	word Index;//номер этого монстра
//--------------------------------------------//
//-----------begin of saving cluster----------//
//--------------------------------------------//
	bool NeedPath;
	word CPdestX;
	word CPdestY;
	word NIPoints;
	word CurIPoint;
	word NIndex;//индекс в национальном списке
	byte Selected;
	byte ImSelected;
	bool SelectedTemp:1;
	bool Borg:1;
	bool Invert:1;
	bool Attack:1;
	bool NoMotion:1;
	bool NoFire:1;
	bool NoInitiate:1;
	bool WasInMobilZone:1;
	bool TempFlag:1;
	bool Mobilised:1;
	bool MoveInRect:1;
	bool DrawUp:1;//СТРРPPОИТЬСЯ!!!
	bool PathBroken:1;//Если хоть раз была преграда на пути
	bool capBuilding:1;
	bool capBuild:1;
	bool capBase:1;
	bool Ready:1;
	bool NoSearchVictim:1;
	bool AskMade:1;
	bool SafeWall:1;
	bool StandGround:1;
	bool Invisible:1;
	bool Zombi:1;
	
	bool Transport:1;
	bool Absent:1;
	bool InFire:1;
	bool RefreshLife:1;
	bool DoWalls:1;
	bool Use_AI:1;
	bool AntiNuc:1;
	
	bool NewMonst:1;
	bool Collision:1;
	bool LeftLeg:1;
	//--------------New
	bool InMotion:1;//Выполняется перемещениe(New)
	bool BackMotion:1;//шаг назад
	bool HasStatePA:1;
	bool NewBuilding:1;
	bool Hidden;
	bool Wall:1;
	bool UnlimitedMotion:1;
	bool LLock:1;
	bool GLock:1;
	bool AlwaysLock:1;
	bool InternalLock:1;
	bool TurnOff:1;
	bool InArmy:1;
	bool InPatrol:1;
	bool FriendlyFire:1;
	bool ArmAttack:1;
	
	//------------------for AI----------------
	bool NoBuilder:1;
	bool DoNotCall:1;
	bool AutoKill:1;
	//-----------For best motion--------------
	short bm_DestX;
	short bm_DestY;
	short bm_NextX;
	short bm_NextY;
	short bm_dx;
	short bm_dy;
	short bm_PrevTopDst;
	word Guard;
	word bm_NextTop;
	void CreateSmartPath(int x,int y,int dx,int dy);
	void FindNextSmartPoint();
	//----------------------------------------
	byte NZalp;
	byte RotCntr;
	byte FiringStage;
	int NextForceX;
	int NextForceY;
	int BestNX;
	int BestNY;
	//char Speed;
	char OverEarth;
	word Kills;
	char VeraVPobedu;
	byte LockType;//0-Land,1-Water
	byte NothingTime;
	word BlockInfo;
	word Sdoxlo;
	byte BackSteps;
	byte BackReserv;
	byte NewState;//0-Normal
				  //1-prepare to attack
	byte LocalNewState;
	byte LeftVeslo;
	byte RightVeslo;
	byte Usage;
	char AddDamage;
	char AddShield;
	//------------Extended animation-----------//
	byte CurAIndex;
	byte MaxAIndex;
	byte MoveStage;
	//-----------------End New-----------------//
	byte BackDelay;
	word AbRes;

	short WallX;
	short WallY;
	
	word NUstages;
	word Ustage;
	word Serial;
	byte Kind;
	short Lx;
	short Ly;
	
	word Life;
	word MaxLife;
	int x;
	int y;
	int DstX;
	int DstY;
	
	word delay;
	byte PathDelay;
	word MaxDelay;
	
	byte StandTime;
	byte NStages;
	word Stage;
	byte NNUM;
	
	word EnemyID;
	word EnemySN;
	byte NMask;
	byte RStage;
	byte RType;
	byte RAmount;
	word NearBase;
	
	word BrigadeID;
	word BrIndex;
	byte Media;//=0-terrain,=1-on water,=2-on air
	word AddInside;
	byte PersonalDelay;
	short RZ;
	word StageState;//if have stages 32768+3 bits/stage, if no then 0
	byte* TempDelay;
	//Flying objects only:
	int  RealX;//1 pixel=16 length units
	int  RealY;
	int  DestX;
	int  DestY;
	int  RealVx;
	int  RealVy;
	int  BestDist;
	int  BestHeight;
	int	 Height;
	int  ForceX;
	int  ForceY;
	int  Radius1;
	int  Radius2;
	int  Speed;
	byte GroundState;
	byte SingleUpgLevel;
	byte RealDir;
	byte GraphDir;
	word NewCurSprite;
	byte MotionDir;
	byte PrioryLevel;
	word NInside;
};