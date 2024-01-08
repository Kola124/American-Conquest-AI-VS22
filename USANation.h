#if !defined(AMERICAN_CONQUEST_Usa_NATION)
#define AMERICAN_CONQUEST_Usa_NATION

// Spnoware nations header file

#include "Import.h"

class USAUnits {
public:	
	GAMEOBJ Pik;
	GAMEOBJ S15;
	GAMEOBJ S17;
	GAMEOBJ S18;
	GAMEOBJ Mil;

	GAMEOBJ O17;
	GAMEOBJ O18;
	GAMEOBJ B17;
	GAMEOBJ B18;
	GAMEOBJ F17;
	GAMEOBJ F18;

	GAMEOBJ Rei;
	GAMEOBJ DO17;
	GAMEOBJ D18;
	GAMEOBJ DO18;
	GAMEOBJ DF18;
	
	GAMEOBJ Lodka;
	GAMEOBJ Parom;
	GAMEOBJ Pinta;
	GAMEOBJ Santa;
	GAMEOBJ Fregat;

	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Tap;
	GAMEOBJ Sha;
	GAMEOBJ Can;
};

class USABuildings {
public:
	GAMEOBJ Rud;
	GAMEOBJ Iro;
	GAMEOBJ Coa;
	GAMEOBJ Stn;

	GAMEOBJ Do1;
	GAMEOBJ Do2;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Hra;
	GAMEOBJ Cen;
	GAMEOBJ Kr7;
	GAMEOBJ Kr8;
	GAMEOBJ Kuz;
	GAMEOBJ Blg;
	GAMEOBJ Blg2;
	
	GAMEOBJ Fer;

	GAMEOBJ Ver;
};

class USAUpgrades {
public:

	//Mine
	GAMEOBJ MineEnable1; //CEN21EN(EN)SpnRudINS(EN)ENABLE
	GAMEOBJ Geology; //CEN21EN

	GAMEOBJ Gld0;
	GAMEOBJ Gld1;
	GAMEOBJ Gld2;
	GAMEOBJ Gld3;
	GAMEOBJ Gld4;
	GAMEOBJ Gld5;

	GAMEOBJ Stn0;
	GAMEOBJ Stn1;
	GAMEOBJ Stn2;
	GAMEOBJ Stn3;
	GAMEOBJ Stn4;
	GAMEOBJ Stn5;

	GAMEOBJ Iro0;
	GAMEOBJ Iro1;
	GAMEOBJ Iro2;
	GAMEOBJ Iro3;
	GAMEOBJ Iro4;
	GAMEOBJ Iro5;

	GAMEOBJ Coa0;
	GAMEOBJ Coa1;
	GAMEOBJ Coa2;
	GAMEOBJ Coa3;
	GAMEOBJ Coa4;
	GAMEOBJ Coa5;

	GAMEOBJ Kr7_Stage0;
	GAMEOBJ Kr8_Stage0;

	GAMEOBJ BldBuild1; //CEN53SP

	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 ...Do2
	GAMEOBJ Kre_RAZBROS; //RAZBROS GRP 1 ...Mus -35%

	GAMEOBJ S18Unlock; //18 century upgrade
	GAMEOBJ MuskSpeed; //Musk build speed
	GAMEOBJ	S18RifFire;
	GAMEOBJ	S18FusFire;
	GAMEOBJ S18Firepower;

	// Food
	GAMEOBJ CEN18; //EFFECT_FOOD +2000
	GAMEOBJ CEN52; //EFFECT_FOOD +3000
	GAMEOBJ CEN57; //EFFECT_FOOD +2000
	GAMEOBJ CEN55; //EFFECT_FOOD +3000
	
	GAMEOBJ Mel_GETRES; //EFFECT_FOOD +14
	GAMEOBJ Mel_GETRES2; //EFFECT_FOOD +25
	GAMEOBJ CEN19; //EFFECT_FOOD +16
	GAMEOBJ CEN22; //EFFECT_FOOD +8
	GAMEOBJ CEN23; //EFFECT_FOOD +6

	// Wood
	GAMEOBJ Wood1; //CEN29SP
	GAMEOBJ Wood2; //CEN30SP
	GAMEOBJ Wood3;
	
	// Krepost
	GAMEOBJ KreBuild; //CEN25SP

	// Kri
	GAMEOBJ KriBuild1; //CEN24SP
	GAMEOBJ KriBuild2; //CEN36SP
	GAMEOBJ KriBuild3; //CEN48SP

	// Pik
	GAMEOBJ PikBuild1; //KUZ20(SP)
	GAMEOBJ PikBuild2; //CEN26SP
	GAMEOBJ PikBuild3; //CEN27SP
	GAMEOBJ PikBuild4; //CEN28SP

	GAMEOBJ S15Build1; //CEN33US
	GAMEOBJ S15Build2; //CEN34US
	GAMEOBJ S15Build3; //CEN35US

	GAMEOBJ S17Build1;//CEN60US

	// S18
	GAMEOBJ S18Build1; //CEN61SP
	GAMEOBJ S18Build2; //CEN62SP
	GAMEOBJ S18Build3; //CEN63SP

	GAMEOBJ PikAttack; //SpnAlb(SP)ATTACK
	GAMEOBJ PikAttack3;
	GAMEOBJ PikAttack4;
	GAMEOBJ PikAttack5;
	GAMEOBJ PikAttack6;
	GAMEOBJ PikAttack7;

	GAMEOBJ PikProtect; //SpnAlb(SP)SHIELD
	GAMEOBJ PikProtect3;
	GAMEOBJ PikProtect4;
	GAMEOBJ PikProtect5;
	GAMEOBJ PikProtect6;
	GAMEOBJ PikProtect7;


	// Can
	GAMEOBJ CanCost;
	GAMEOBJ CanCost3;
	GAMEOBJ CanCost4;
	GAMEOBJ CanCost5;
	GAMEOBJ CanCost6;
	GAMEOBJ CanCost7;

	GAMEOBJ CanBuild;
	GAMEOBJ CanBuild3;
	GAMEOBJ CanBuild4;
	GAMEOBJ CanBuild5;
	GAMEOBJ CanBuild6;
	GAMEOBJ CanBuild7;

	// Cen
	GAMEOBJ ArmShield1; //CEN47SP
	GAMEOBJ ArmShield2; //CEN08SP
	GAMEOBJ ArmShield3;	//CEN49US

	GAMEOBJ StrAttPause1; //CEN01SP

	GAMEOBJ StrDamage1; //CEN45SP
	GAMEOBJ StrDamage2; //CEN50SPA

	GAMEOBJ BldShield1; //CEN37SP
	GAMEOBJ BldShield2; //CEN47SP	

	// Rei

	GAMEOBJ ReiAttack; //SpnRei(SP)ATTACK
	GAMEOBJ ReiAttack3;
	GAMEOBJ ReiAttack4;
	GAMEOBJ ReiAttack5;
	GAMEOBJ ReiAttack6;
	GAMEOBJ ReiAttack7;

	GAMEOBJ ReiProtect; //SpnRei(SP)SHIELD
	GAMEOBJ ReiProtect3;
	GAMEOBJ ReiProtect4;
	GAMEOBJ ReiProtect5;
	GAMEOBJ ReiProtect6;
	GAMEOBJ ReiProtect7;

	// S15
	GAMEOBJ S15Attack; //SpnS15(SP)ATTACK
	GAMEOBJ S15Attack3;
	GAMEOBJ S15Attack4;
	GAMEOBJ S15Attack5;
	GAMEOBJ S15Attack6;
	GAMEOBJ S15Attack7;

	GAMEOBJ S15Protect; //SpnS15(SP)SHIELD
	GAMEOBJ S15Protect3;
	GAMEOBJ S15Protect4;
	GAMEOBJ S15Protect5;
	GAMEOBJ S15Protect6;
	GAMEOBJ S15Protect7;

	// S17 (Mus)
	GAMEOBJ MusAttack; //SpnMus(SP)ATTACK
	GAMEOBJ MusAttack3;
	GAMEOBJ MusAttack4;
	GAMEOBJ MusAttack5;
	GAMEOBJ MusAttack6;
	GAMEOBJ MusAttack7;

	GAMEOBJ MusProtect; //SpnMus(SP)SHIELD
	GAMEOBJ MusProtect3;
	GAMEOBJ MusProtect4;
	GAMEOBJ MusProtect5;
	GAMEOBJ MusProtect6;
	GAMEOBJ MusProtect7;
	
	GAMEOBJ S18Attack;	//UsaM18(US)ATTACK
	GAMEOBJ S18Attack3;
	GAMEOBJ S18Attack4;
	GAMEOBJ S18Attack5;
	GAMEOBJ S18Attack6;
	GAMEOBJ S18Attack7;

	GAMEOBJ S18Protect;	//UsaM18(US)SHIELD
	GAMEOBJ S18Protect3;
	GAMEOBJ S18Protect4;
	GAMEOBJ S18Protect5;
	GAMEOBJ S18Protect6;
	GAMEOBJ S18Protect7;

	// Officers
	GAMEOBJ B17Protect;	//EngB17(US)SHIELD7
	GAMEOBJ O17Damage;	//EngOf17(US)ATTACK7
	GAMEOBJ O17Protect;	//EngOf17(US)SHIELD7
	GAMEOBJ F17Protect;	//EngF17(US)SHIELD7

	GAMEOBJ B18Protect;	//UsaB18(US)SHIELD7
	GAMEOBJ O18Damage;	//UsaOf18(US)ATTACK7
	GAMEOBJ O18Protect;	//UsaOf18(US)SHIELD7
	GAMEOBJ F18Protect;	//UsaF18(US)SHIELD7

	GAMEOBJ Horse17Build;
	GAMEOBJ Horse18Build;
	GAMEOBJ HorseAllBuild;

	//NEW STUFF

	//Artilery TC

	GAMEOBJ ARTROF1;
	GAMEOBJ ARTROF2;
	GAMEOBJ ARTRNG1;
	GAMEOBJ ARTRNG2;
	GAMEOBJ ARTACC1;
	GAMEOBJ ARTACC2;

	GAMEOBJ Kr8_Stage1;
	GAMEOBJ	Kr8_Stage2;
	GAMEOBJ	Kr8_Stage3;

	GAMEOBJ LogDef;
	GAMEOBJ FindGeo;
};

class USANation {
public:
	USANation();
	USAUnits Unit;
	USABuildings Build;
	USAUpgrades Upg;
};
extern USANation USA;

#endif
