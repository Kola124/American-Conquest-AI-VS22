#if !defined(AMERICAN_CONQUEST_Pue_NATION)
#define AMERICAN_CONQUEST_Pue_NATION

// Pueoware nations header file

#include "Import.h"

class PueUnits {
public:	
	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Lut;
	GAMEOBJ Sha;
	GAMEOBJ S15;
	GAMEOBJ Vog;
	GAMEOBJ Vsd;	// vsadnik
	GAMEOBJ Ka1; // Kanoe 1
	GAMEOBJ Ka3; // Kanoe 2
	GAMEOBJ Par; // Parom
};

class PueBuildings {
public:
	GAMEOBJ Rud;
	GAMEOBJ Iro;
	GAMEOBJ Coa;
	GAMEOBJ Stn;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Pst;
	GAMEOBJ Gor;
	GAMEOBJ Ver;
};

class PueUpgrades {
public:

	// Food & Field
	GAMEOBJ FoodMel1; //EFFECT_FOOD +14
	GAMEOBJ FoodMel2; //EFFECT_FOOD +25

	GAMEOBJ FoodCen01; //EFFECT_FOOD +4
	GAMEOBJ FoodCen02; //EFFECT_FOOD +4
	GAMEOBJ FoodCen03; //EFFECT_FOOD +5
	
	GAMEOBJ FieldCen10; //EFFECT_FOOD +2000
	GAMEOBJ FieldCen52; //EFFECT_FOOD +3000
	GAMEOBJ FieldCen12; //EFFECT_FOOD +3000

	// Wood
	GAMEOBJ Wood1; //CEN29PU
	GAMEOBJ Wood2; //CEN30PU

	// Mine
	GAMEOBJ Stn0;
	GAMEOBJ Stn1;
	GAMEOBJ Stn2;
	GAMEOBJ Stn3;
	GAMEOBJ Stn4;
	GAMEOBJ Stn5;

	// Center
	GAMEOBJ CenStage1; //UPSTPUEGOR0
	GAMEOBJ CenStage2; //UPSTPUEGOR1 Lut,S15
	GAMEOBJ CenStage3; //UPSTPUEGOR2 Sha
	GAMEOBJ CenStage4; //UPSTPUEGOR3 Vsd

	// Warriors
	GAMEOBJ WarDamage1; //CEN05PU Vog,Str,Vsd +5
	GAMEOBJ WarLife1; //PueS15(PU)LIFE Lut,Str,Vsd +10%

	// Lut
	//GAMEOBJ LutEnable;
	GAMEOBJ LutRazbros1; // PueGor(PU)RAZBROS -35%
	GAMEOBJ LutRazbros2; // PueGor(PU)RAZBROS1 -35%
	GAMEOBJ LutLife1; // CEN50PU +300%
	GAMEOBJ LutBuild1; // CEN08PU -20%
	GAMEOBJ LutBuild2; // CEN47PU -20%
	GAMEOBJ LutBuild3; // CEN48PU -20%

	// S15
	GAMEOBJ S15Enable; // PueS15(PU)ENABLE
	GAMEOBJ S15Build1; // CEN07PU -20%
	GAMEOBJ S15Build2; // CEN45PU -20%
	GAMEOBJ S15Build3; // CEN46PU -20%

	GAMEOBJ S15Att; 
	GAMEOBJ S15Att3;
	GAMEOBJ S15Att4;
	GAMEOBJ S15Att5;
	GAMEOBJ S15Att6;
	GAMEOBJ S15Att7;

	GAMEOBJ S15Def; // PueS15(PU)SHIELD
	GAMEOBJ S15Def3;
	GAMEOBJ S15Def4;
	GAMEOBJ S15Def5;
	GAMEOBJ S15Def6;
	GAMEOBJ S15Def7;

	// Vsd
	//GAMEOBJ VsdEnable; // UPSTPUEGOR3
	GAMEOBJ VsdBuild1; // CEN09PU

	// Sha
	//GAMEOBJ ShaEnable;
	GAMEOBJ ShaLife1; // CEN15PU +400%
	GAMEOBJ ShaMedik1; // CEN14PU +15
	GAMEOBJ ShaBuild1; // CEN13PU -50%

	// Vog
	GAMEOBJ VogEnable; //PueVog(PU)ENABLE

	// Parom
	GAMEOBJ ParSpeed1; //CEN102DE
	GAMEOBJ ParSpeed2; //CEN103DE
	GAMEOBJ ParSpeed3; //CEN104DE
	GAMEOBJ ParSpeed4; //CEN105DE
	GAMEOBJ ParSpeed5; //CEN106DE
	GAMEOBJ ParSpeed6; //CEN107DE

	// Kanoe 3 build speed
	GAMEOBJ Ka3Build1; //CEN96DE
	GAMEOBJ Ka3Build2; //CEN97DE
	GAMEOBJ Ka3Build3; //CEN98DE
	GAMEOBJ Ka3Build4; //CEN99DE
	GAMEOBJ Ka3Build5; //CEN100DE
	GAMEOBJ Ka3Build6; //CEN101DE

	// Fishing
	GAMEOBJ Ka1Fishing1; //CEN90DE
	GAMEOBJ Ka1Fishing2; //CEN91DE
	GAMEOBJ Ka1Fishing3; //CEN92DE
	GAMEOBJ Ka1Fishing4; //CEN93DE
	GAMEOBJ Ka1Fishing5; //CEN94DE
	GAMEOBJ Ka1Fishing6; //CEN95DE
};

// FIELD(MA)       FIELD
class PueNation {
public:
	PueNation();
	PueUnits Unit;
	PueBuildings Build;
	PueUpgrades Upg;
};
extern PueNation Pue;

#endif
