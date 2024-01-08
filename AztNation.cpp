#include "AztNation.h"

AztNation::AztNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "MayKri(AC)");
	RegisterUnitType(&Unit.Met, "AtcMet(AC)");	
	RegisterUnitType(&Unit.Lut, "AtcLut(AC)");	
	RegisterUnitType(&Unit.Sha, "AtcSha(AC)");
	RegisterUnitType(&Unit.Vog, "AtcVog(AC)");	
	{
		RegisterUnitType(&Unit.Ka1, "ShpKanoe1(AC)");
		RegisterUnitType(&Unit.Ka3, "ShpKanoe3(AC)");
		RegisterUnitType(&Unit.Par, "ShpParom(AC)");
	}
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Do1, "AtcDo1(AC)");
	RegisterUnitType(&Build.Do2, "AtcDo2(AC)");
	RegisterUnitType(&Build.Rud, "SpnRud(AC)");
	RegisterUnitType(&Build.Iro, "SpnIro(AC)");
	RegisterUnitType(&Build.Coa, "SpnCoa(AC)");
	RegisterUnitType(&Build.Stn, "SpnStn(AC)");
	RegisterUnitType(&Build.Mel, "MayMel(AC)");
	RegisterUnitType(&Build.Skl, "MaySkl(AC)");
	RegisterUnitType(&Build.Hra, "AtcHra(AC)");
	RegisterUnitType(&Build.Cen, "AtcCen(AC)");
	RegisterUnitType(&Build.Kre, "AtcKre(AC)");	
	RegisterUnitType(&Build.Blg, "AtcBlg(AC)");
	RegisterUnitType(&Build.Blg2, "MayBlg2(AC)");	
	RegisterUnitType(&Build.Ver, "AtcVer(AC)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades

	// Center
	{
		RegisterUpgrade(&Upg.ConstrBuild1, "CEN11AC");
	}

	// Mine
	{
		RegisterUpgrade(&Upg.Gld0, "SpnRud(AC)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(AC)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(AC)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(AC)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(AC)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(AC)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(AC)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(AC)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(AC)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(AC)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(AC)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(AC)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(AC)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(AC)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(AC)INSIDE3");
	}

	RegisterUpgrade(&Upg.CEN07, "CEN07AC"); //BUILD GRP 1 AtcMet_ -50%
	RegisterUpgrade(&Upg.CEN01, "CEN01AC"); //EFFECT_FOOD +4
	RegisterUpgrade(&Upg.CEN02, "CEN02AC"); //EFFECT_FOOD +4
	RegisterUpgrade(&Upg.CEN03, "CEN03AC"); //EFFECT_FOOD +5
	//GAMEOBJ CEN05; //DAMAGE WEAPONKIND PIKA GRP 2 AtcMet_ AtcVog_ +5 
	RegisterUpgrade(&Upg.CEN10, "CEN10AC"); //EFFECT_FOOD +2000
	
	//GAMEOBJ Met_LIFE; //LIFE GRP 2 AtcMet_ AtcLut_ +10%
	RegisterUpgrade(&Upg.Do2_ENABLE, "AtcDo2(AC)ENABLE"); //ENABLE UNITS GRP 1 AtcDo2
	RegisterUpgrade(&Upg.Kre_RAZBROS, "AtcKre(AC)RAZBROS"); //RAZBROS GRP 1 AtcLut -35%
	RegisterUpgrade(&Upg.Kre_RAZBROS1, "AtcKre(AC)RAZBROS1"); //RAZBROS GRP 1 AtcLut -35%
	RegisterUpgrade(&Upg.Mel_GETRES, "MayMel(AC)GETRES"); //EFFECT_FOOD +14
	RegisterUpgrade(&Upg.Mel_GETRES2, "MayMel(AC)GETRES2"); //EFFECT_FOOD +25
	RegisterUpgrade(&Upg.UPSTATCKRE0, "UPSTATCKRE0"); //UPSTAGE0
	RegisterUpgrade(&Upg.UPSTATCKRE1, "UPSTATCKRE1"); //UPSTAGE1
	RegisterUpgrade(&Upg.UPSTATCKRE2, "UPSTATCKRE2"); //UPSTAGE2
	
	RegisterUpgrade(&Upg.BlgPrice, "CEN25AC");

	RegisterUpgrade(&Upg.MetBuild, "CEN07AC");
	RegisterUpgrade(&Upg.MetProtArrow, "CEN06AC");
	RegisterUpgrade(&Upg.LutProtPika, "AtcVoiS");
	RegisterUpgrade(&Upg.WarLife, "AtcMet(AC)LIFE");

	// Kri
	{
		RegisterUpgrade(&Upg.KriBu1, "CEN09AC");
		RegisterUpgrade(&Upg.KriBu2, "CEN08AC");
	}

	RegisterUpgrade(&Upg.Met_ATTACK, "AtcMet(AC)ATTACK"); //DAMAGE WEAPONKIND PIKA AtcMet_ +1
	RegisterUpgrade(&Upg.Met_ATTACK3, "AtcMet(AC)ATTACK3"); //DAMAGE WEAPONKIND PIKA AtcMet_ +2
	RegisterUpgrade(&Upg.Met_ATTACK4, "AtcMet(AC)ATTACK4"); //DAMAGE WEAPONKIND PIKA AtcMet_ +3
	RegisterUpgrade(&Upg.Met_ATTACK5, "AtcMet(AC)ATTACK5"); //DAMAGE WEAPONKIND PIKA AtcMet_ +2
	RegisterUpgrade(&Upg.Met_ATTACK6, "AtcMet(AC)ATTACK6"); //DAMAGE WEAPONKIND PIKA AtcMet_ +1
	RegisterUpgrade(&Upg.Met_ATTACK7, "AtcMet(AC)ATTACK7"); //DAMAGE WEAPONKIND PIKA AtcMet_ +1
	RegisterUpgrade(&Upg.Met_SHIELD, "AtcMet(AC)SHIELD"); //PROTECTION GRP 2 MECH PIKA AtcMet_ +1
	RegisterUpgrade(&Upg.Met_SHIELD3, "AtcMet(AC)SHIELD3"); //PROTECTION GRP 2 MECH PIKA AtcMet_ +1
	RegisterUpgrade(&Upg.Met_SHIELD4, "AtcMet(AC)SHIELD4"); //PROTECTION GRP 2 MECH PIKA AtcMet_ +3
	RegisterUpgrade(&Upg.Met_SHIELD5, "AtcMet(AC)SHIELD5"); //PROTECTION GRP 2 MECH PIKA AtcMet_ +2
	RegisterUpgrade(&Upg.Met_SHIELD6, "AtcMet(AC)SHIELD6"); //PROTECTION GRP 2 MECH PIKA  AtcMet_ +2
	RegisterUpgrade(&Upg.Met_SHIELD7, "AtcMet(AC)SHIELD7"); //PROTECTION GRP 2 MECH PIKA AtcMet_ +2
	
	//GAMEOBJ Lut_ATTACK; //DAMAGE WEAPONKIND MECH AtcLut_ +1
	//GAMEOBJ Lut_ATTACK3; //DAMAGE WEAPONKIND MECH AtcLut_ +1
	//GAMEOBJ Lut_ATTACK4; //DAMAGE WEAPONKIND MECH AtcLut_ +1                                   
	//GAMEOBJ Lut_ATTACK5; //DAMAGE WEAPONKIND MECH AtcLut_ +1
	//GAMEOBJ Lut_ATTACK6; //DAMAGE WEAPONKIND MECH AtcLut_ +1
	//GAMEOBJ Lut_ATTACK7; //DAMAGE WEAPONKIND MECH AtcLut_ +1
	RegisterUpgrade(&Upg.Lut_SHIELD, "AtcLut(AC)SHIELD"); //PROTECTION GRP 2 MECH PIKA AtcLut_ +2
	RegisterUpgrade(&Upg.Lut_SHIELD3, "AtcLut(AC)SHIELD3"); //PROTECTION GRP 2 MECH PIKA AtcLut_ +1
	RegisterUpgrade(&Upg.Lut_SHIELD4, "AtcLut(AC)SHIELD4"); //PROTECTION GRP 2 MECH PIKA AtcLut_ +3
	RegisterUpgrade(&Upg.Lut_SHIELD5, "AtcLut(AC)SHIELD5"); //PROTECTION GRP 2 MECH PIKA AtcLut_ +1
	RegisterUpgrade(&Upg.Lut_SHIELD6, "AtcLut(AC)SHIELD6"); //PROTECTION GRP 2 MECH PIKA  AtcLut_ +2
	RegisterUpgrade(&Upg.Lut_SHIELD7, "AtcLut(AC)SHIELD7"); //PROTECTION GRP 2 MECH PIKA AtcLut_ +1
	
	RegisterUpgrade(&Upg.Vog_ATTACK, "AtcVog(AC)ATTACK");
	RegisterUpgrade(&Upg.Vog_ATTACK3, "AtcVog(AC)ATTACK3");
	RegisterUpgrade(&Upg.Vog_ATTACK4, "AtcVog(AC)ATTACK4");
	RegisterUpgrade(&Upg.Vog_ATTACK5, "AtcVog(AC)ATTACK5");
	RegisterUpgrade(&Upg.Vog_ATTACK6, "AtcVog(AC)ATTACK6");
	RegisterUpgrade(&Upg.Vog_ATTACK7, "AtcVog(AC)ATTACK7");	
	RegisterUpgrade(&Upg.Vog_SHIELD, "AtcVog(AC)SHIELD");
	RegisterUpgrade(&Upg.Vog_SHIELD3, "AtcVog(AC)SHIELD3");
	RegisterUpgrade(&Upg.Vog_SHIELD4, "AtcVog(AC)SHIELD4");
	RegisterUpgrade(&Upg.Vog_SHIELD5, "AtcVog(AC)SHIELD5");
	RegisterUpgrade(&Upg.Vog_SHIELD6, "AtcVog(AC)SHIELD6");
	RegisterUpgrade(&Upg.Vog_SHIELD7, "AtcVog(AC)SHIELD7");
	
	RegisterUpgrade(&Upg.CEN52, "ATC52AC"); //EFFECT_FOOD +3000
	//GAMEOBJ VoiS; //PROTECTION GRP 1 PIKA AtcLut_ +5
	RegisterUpgrade(&Upg.CEN12, "CEN12AC"); //EFFECT_FOOD +3000
	RegisterUpgrade(&Upg.UPSTATCVER0, "UPSTATCVER0"); //UPSTAGE0
	RegisterUpgrade(&Upg.UPSTATCVER1, "UPSTATCVER1"); //UPSTAGE1

	// Met
	RegisterUpgrade(&Upg.MetPika1, "CEN05AC");

	// Sha
	RegisterUpgrade(&Upg.ShaBuild1, "CEN13AC");
	RegisterUpgrade(&Upg.ShaLife1, "CEN15AC");
	RegisterUpgrade(&Upg.ShaMedik1, "CEN14AC");
	
	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102AC");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103AC");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104AC");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105AC");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106AC");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107AC");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96AC");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97AC");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98AC");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99AC");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100AC");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101AC");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90AC");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91AC");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92AC");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93AC");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94AC");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95AC");
	}

	//RegisterUpgrade(&Upg., "");
}

AztNation Azt;