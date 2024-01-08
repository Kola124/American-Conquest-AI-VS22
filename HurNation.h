#if !defined(AMERICAN_CONQUEST_Hur_NATION)
#define AMERICAN_CONQUEST_Hur_NATION

// Huroware nations header file

#include "Import.h"

class HurUnits {
public:	
	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Tam;
	GAMEOBJ Lut;
	GAMEOBJ Sha;
	GAMEOBJ S15;
	GAMEOBJ Vog;
	GAMEOBJ Vsd;	// vsadnik
	GAMEOBJ Ka1; // Kanoe 1
	GAMEOBJ Ka3; // Kanoe 2
	GAMEOBJ Par; // Parom
};

class HurBuildings {
public:
	GAMEOBJ Do1;
	GAMEOBJ Do2;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Hra;
	GAMEOBJ Cen;
	GAMEOBJ Kre;
	GAMEOBJ Pst;
	GAMEOBJ Kaz;
	GAMEOBJ Ver;
};

class HurUpgrades {
public:
	//Food
	GAMEOBJ CEN01; //EFFECT_FOOD +4
	GAMEOBJ CEN02; //EFFECT_FOOD +4
	GAMEOBJ CEN03; //EFFECT_FOOD +5
	GAMEOBJ CEN10; //EFFECT_FOOD +2000	
	GAMEOBJ Mel_GETRES; //EFFECT_FOOD +14
	GAMEOBJ Mel_GETRES2; //EFFECT_FOOD +25
	GAMEOBJ CEN52; //EFFECT_FOOD +3000
	GAMEOBJ CEN12; //EFFECT_FOOD +3000

	// Wood
	GAMEOBJ Wood1; //CEN29HU
	GAMEOBJ Wood2; //CEN30HU

	//
	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 AtcDo2

	// Vsd
	GAMEOBJ EnVsd; //SIUKRE(HU)ENABLE
	// attack
	GAMEOBJ VsdAtt; //PueVsd(HU)ATTACK
	GAMEOBJ VsdAtt3; //PueVsd(HU)ATTACK3
	GAMEOBJ VsdAtt4; //PueVsd(HU)ATTACK4
	GAMEOBJ VsdAtt5; //PueVsd(HU)ATTACK5
	GAMEOBJ VsdAtt6; //PueVsd(HU)ATTACK6
	GAMEOBJ VsdAtt7; //PueVsd(HU)ATTACK7
	// deffence
	GAMEOBJ VsdDef; //PueVsd(HU)SHIELD
	GAMEOBJ VsdDef3; //PueVsd(HU)SHIELD3
	GAMEOBJ VsdDef4; //PueVsd(HU)SHIELD4
	GAMEOBJ VsdDef5; //PueVsd(HU)SHIELD5
	GAMEOBJ VsdDef6; //PueVsd(HU)SHIELD6
	GAMEOBJ VsdDef7; //PueVsd(HU)SHIELD7

	// Peasant
	// speed
	GAMEOBJ KriBuildSpeed1; //BUILD GRP 1 DelKri(HU) -15%
	GAMEOBJ KriBuildSpeed2; //BUILD GRP 1 DelKri(HU) -25%
	// life
	GAMEOBJ KriIR; //MORELIFE GRP 1 DelKri(HU) +20%
	GAMEOBJ KriIR3; //MORELIFE GRP 1 DelKri(HU) +30%
	GAMEOBJ KriIR4; //MORELIFE GRP 1 DelKri(HU) +40%
	GAMEOBJ KriIR5; //MORELIFE GRP 1 DelKri(HU) +50%
	GAMEOBJ KriIR6; //MORELIFE GRP 1 DelKri(HU) +60%
	GAMEOBJ KriIR7; //MORELIFE GRP 1 DelKri(HU) +70%
	// attack
	GAMEOBJ KriAtt; //DelKri(HU)ATTACK
	GAMEOBJ KriAtt3; //DelKri(HU)ATTACK3
	GAMEOBJ KriAtt4; //DelKri(HU)ATTACK4
	GAMEOBJ KriAtt5; //DelKri(HU)ATTACK5
	GAMEOBJ KriAtt6; //DelKri(HU)ATTACK6
	GAMEOBJ KriAtt7; //DelKri(HU)ATTACK7
	// defence
	GAMEOBJ KriDef; //DelKri(HU)SHIELD
	GAMEOBJ KriDef3; //DelKri(HU)SHIELD3
	GAMEOBJ KriDef4; //DelKri(HU)SHIELD4
	GAMEOBJ KriDef5; //DelKri(HU)SHIELD5
	GAMEOBJ KriDef6; //DelKri(HU)SHIELD6
	GAMEOBJ KriDef7; //DelKri(HU)SHIELD7

	// Tam
	GAMEOBJ EnTam; //HurTam(HU)ENABLE

	GAMEOBJ TamStrike1; //CEN58HU
	
	// attack
	GAMEOBJ TamAtt; //HurTam(HU)ATTACK
	GAMEOBJ TamAtt3; //HurTam(HU)ATTACK3
	GAMEOBJ TamAtt4; //HurTam(HU)ATTACK4
	GAMEOBJ TamAtt5; //HurTam(HU)ATTACK5
	GAMEOBJ TamAtt6; //HurTam(HU)ATTACK6
	GAMEOBJ TamAtt7; //HurTam(HU)ATTACK7

	// defence
	GAMEOBJ TamDef; //HurTam(HU)SHIELD
	GAMEOBJ TamDef3; //HurTam(HU)SHIELD3
	GAMEOBJ TamDef4; //HurTam(HU)SHIELD4
	GAMEOBJ TamDef5; //HurTam(HU)SHIELD5
	GAMEOBJ TamDef6; //HurTam(HU)SHIELD6
	GAMEOBJ TamDef7; //HurTam(HU)SHIELD7

	// Lut
	GAMEOBJ EnLut; //HurLut(HU)ENABLE

	GAMEOBJ LutPerc1; //HurKre(HU)RAZBROS
	GAMEOBJ LutPerc2; //HurKre(HU)RAZBROS1

	GAMEOBJ LutLife1; //CEN61HU

	// attack
	GAMEOBJ LutAtt; //HurLut(HU)ATTACK
	GAMEOBJ LutAtt3; //HurLut(HU)ATTACK3
	GAMEOBJ LutAtt4; //HurLut(HU)ATTACK4
	GAMEOBJ LutAtt5; //HurLut(HU)ATTACK5
	GAMEOBJ LutAtt6; //HurLut(HU)ATTACK6
	GAMEOBJ LutAtt7; //HurLut(HU)ATTACK7

	// defence
	GAMEOBJ LutDef; //HurLut(HU)SHIELD
	GAMEOBJ LutDef3; //HurLut(HU)SHIELD3
	GAMEOBJ LutDef4; //HurLut(HU)SHIELD4
	GAMEOBJ LutDef5; //HurLut(HU)SHIELD5
	GAMEOBJ LutDef6; //HurLut(HU)SHIELD6
	GAMEOBJ LutDef7; //HurLut(HU)SHIELD7

	// Str
	GAMEOBJ EnStr; //HurStr(HU)ENABLE

	// attack
	GAMEOBJ StrAtt; //HurS15(HU)ATTACK
	GAMEOBJ StrAtt3;
	GAMEOBJ StrAtt4;
	GAMEOBJ StrAtt5;
	GAMEOBJ StrAtt6;
	GAMEOBJ StrAtt7;
	// defence
	GAMEOBJ StrDef;
	GAMEOBJ StrDef3;
	GAMEOBJ StrDef4;
	GAMEOBJ StrDef5;
	GAMEOBJ StrDef6;
	GAMEOBJ StrDef7;

	// Sha
	GAMEOBJ ShaBuild1; //CEN13HU
	GAMEOBJ ShaMedic1; //CEN14HU
	GAMEOBJ ShaLife1; //CEN15HU

	// Vog
	GAMEOBJ EnVog; //HurVog(HU)ENABLE

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
class HurNation {
public:
	HurNation();
	HurUnits Unit;
	HurBuildings Build;
	HurUpgrades Upg;
};
extern HurNation Hur;

#endif
