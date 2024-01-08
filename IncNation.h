#if !defined(AMERICAN_CONQUEST_Inc_NATION)
#define AMERICAN_CONQUEST_Inc_NATION

// Incoware nations header file

#include "Import.h"

class IncUnits {
public:	
	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Pik;	
	GAMEOBJ Pra;
	GAMEOBJ Trb;
	GAMEOBJ Lut;
	GAMEOBJ Sha;	
	GAMEOBJ Vog;
	GAMEOBJ Ka1; // Kanoe 1
	GAMEOBJ Ka3; // Kanoe 2
	GAMEOBJ Par; // Parom
};

class IncBuildings {
public:
	GAMEOBJ Rud;
	GAMEOBJ Iro;
	GAMEOBJ Coa;
	GAMEOBJ Stn;
	GAMEOBJ Do1;
	GAMEOBJ Do2;
	GAMEOBJ Do3;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Kre;
	GAMEOBJ Blg;
	GAMEOBJ Ver;
};

class IncUpgrades {
public:
	
	// Mine
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

	// Food & field
	GAMEOBJ CEN01; //EFFECT_FOOD +4
	GAMEOBJ CEN02; //EFFECT_FOOD +4
	GAMEOBJ CEN03; //EFFECT_FOOD +5
	GAMEOBJ CEN10; //EFFECT_FOOD +2000

	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 AtcDo2
	GAMEOBJ Do3_ENABLE; //ENABLE UNITS GRP 1 AtcDo3

	GAMEOBJ Mel_GETRES; //EFFECT_FOOD +14
	GAMEOBJ Mel_GETRES2; //EFFECT_FOOD +25

	GAMEOBJ CEN52; //EFFECT_FOOD +3000
	GAMEOBJ CEN12; //EFFECT_FOOD +3000

	// Stage
	GAMEOBJ KreStage0;
	GAMEOBJ KreStage1;
	GAMEOBJ KreStage2;

	// More Farms
	GAMEOBJ Do3Farms1; //MFARMINCDO0
	GAMEOBJ Do3Farms2; //MFARMINCDO1
	
	// Kri
	GAMEOBJ KriBu1;	// -15% build speed
	GAMEOBJ KriBu2;	// -25% build speed

	// Warriors
	GAMEOBJ WarLife;
	GAMEOBJ Strike1;

	// Pik
	// build speed
	GAMEOBJ PikBuild;
	// attack
	GAMEOBJ PikAtt;
	GAMEOBJ PikAtt3;
	GAMEOBJ PikAtt4;
	GAMEOBJ PikAtt5;
	GAMEOBJ PikAtt6;
	GAMEOBJ PikAtt7;
	// defence
	GAMEOBJ PikShi;
	GAMEOBJ PikShi3;
	GAMEOBJ PikShi4;
	GAMEOBJ PikShi5;
	GAMEOBJ PikShi6;
	GAMEOBJ PikShi7;
	
	// Lut
	GAMEOBJ LutRaz1; //IncKre(IN)RAZBROS
	GAMEOBJ LutRaz2; //IncKre(IN)RAZBROS1
	// attack
	GAMEOBJ LutAtt;
	GAMEOBJ LutAtt3;
	GAMEOBJ LutAtt4;
	GAMEOBJ LutAtt5;
	GAMEOBJ LutAtt6;
	GAMEOBJ LutAtt7;
	// defence
	GAMEOBJ LutDef;
	GAMEOBJ LutDef3;
	GAMEOBJ LutDef4;
	GAMEOBJ LutDef5;
	GAMEOBJ LutDef6;
	GAMEOBJ LutDef7;


	// Trb
	
	// Pra
	// build speed
	GAMEOBJ PraBuild;
	// attack
	GAMEOBJ PraAtt;
	GAMEOBJ PraAtt3;
	GAMEOBJ PraAtt4;
	GAMEOBJ PraAtt5;
	GAMEOBJ PraAtt6;
	GAMEOBJ PraAtt7;
	// defence
	GAMEOBJ PraShi;
	GAMEOBJ PraShi3;
	GAMEOBJ PraShi4;
	GAMEOBJ PraShi5;
	GAMEOBJ PraShi6;
	GAMEOBJ PraShi7;

	
	// Vog
	// defence
	GAMEOBJ VogDef; //IncVog(IN)SHIELD
	GAMEOBJ VogDef3;
	GAMEOBJ VogDef4;
	GAMEOBJ VogDef5;
	GAMEOBJ VogDef6;
	GAMEOBJ VogDef7;
	
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
class IncNation {
public:
	IncNation();
	IncUnits Unit;
	IncBuildings Build;
	IncUpgrades Upg;
};
extern IncNation Inc;

#endif
