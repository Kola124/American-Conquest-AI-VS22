#if !defined(AMERICAN_CONQUEST_Siu_NATION)
#define AMERICAN_CONQUEST_Siu_NATION

// Siuoware nations header file

#include "Import.h"

class SiuUnits {
public:	
	GAMEOBJ KPik;
	GAMEOBJ KLut;
	GAMEOBJ KVog;
	GAMEOBJ KStr;
	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Lut;
	GAMEOBJ Sha;
	GAMEOBJ Ka1; // Kanoe 1
	GAMEOBJ Ka3; // Kanoe 2
	GAMEOBJ Par; // Parom
};

class SiuBuildings {
public:
	GAMEOBJ Do1;
	GAMEOBJ Do2;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Hra;
	GAMEOBJ Cen;
	GAMEOBJ Kre;
	GAMEOBJ Pst;
	GAMEOBJ Ver;
};

class SiuUpgrades {
public:
	GAMEOBJ CEN01; //EFFECT_FOOD +4
	GAMEOBJ CEN02; //EFFECT_FOOD +4
	GAMEOBJ CEN03; //EFFECT_FOOD +5

	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 AtcDo2

	GAMEOBJ Mel_GETRES; //EFFECT_FOOD +14
	GAMEOBJ Mel_GETRES2; //EFFECT_FOOD +25

	// Food
	GAMEOBJ CEN52; //EFFECT_FOOD +3000
	GAMEOBJ CEN12; //EFFECT_FOOD +3000

	// Wood
	GAMEOBJ Wood1; //CEN30SI

	// Pika
	GAMEOBJ KPikCenDamage1; //CEN05SI

	// KPik
	GAMEOBJ KPikBuild1; //CEN07SI	
	GAMEOBJ KPikCenProtect1; //SiuKPikS

	GAMEOBJ KPikDamage; //SiuKPik(SI)ATTACK
	GAMEOBJ KPikDamage3;
	GAMEOBJ KPikDamage4;
	GAMEOBJ KPikDamage5;
	GAMEOBJ KPikDamage6;
	GAMEOBJ KPikDamage7;

	GAMEOBJ KPikProtect; //SiuKPik(SI)SHIELD
	GAMEOBJ KPikProtect3;
	GAMEOBJ KPikProtect4;
	GAMEOBJ KPikProtect5;
	GAMEOBJ KPikProtect6;
	GAMEOBJ KPikProtect7;

	// KLut
	GAMEOBJ KLutEnable; //VSEDEBILI(SI)0

	GAMEOBJ KLutRazbros1; //SiuKre(SI)RAZBROS
	GAMEOBJ KLutRazbros2; //SiuKre(SI)RAZBROS1

	GAMEOBJ KLutBuild1; //CEN70SI
	GAMEOBJ KLutBuild2; //CEN50SI

	// KStr
	GAMEOBJ KStrEnable; //VSEDEBILI(SI)1

	// KVog
	GAMEOBJ KVogEnable; //VSEDEBILI(SI)2

	GAMEOBJ KVogDamage; //SiuKVog(SI)ATTACK
	GAMEOBJ KVogDamage3;
	GAMEOBJ KVogDamage4;
	GAMEOBJ KVogDamage5;
	GAMEOBJ KVogDamage6;
	GAMEOBJ KVogDamage7;

	GAMEOBJ KVogProtect; //SiuKVog(SI)SHIELD
	GAMEOBJ KVogProtect3;
	GAMEOBJ KVogProtect4;
	GAMEOBJ KVogProtect5;
	GAMEOBJ KVogProtect6;
	GAMEOBJ KVogProtect7;

	// Sha
	GAMEOBJ ShaBuild1; //CEN13SI

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
class SiuNation {
public:
	SiuNation();
	SiuUnits Unit;
	SiuBuildings Build;
	SiuUpgrades Upg;
};
extern SiuNation Siu;

#endif
