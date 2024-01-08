#include "IncNation.h"

IncNation::IncNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "MayKri(IN)");
	RegisterUnitType(&Unit.Pik, "IncPik(IN)");
	RegisterUnitType(&Unit.Pra, "IncPra(IN)");
	RegisterUnitType(&Unit.Trb, "IncTrb(IN)");
	RegisterUnitType(&Unit.Lut, "IncLut(IN)");	
	RegisterUnitType(&Unit.Sha, "IncSha(IN)");
	RegisterUnitType(&Unit.Vog, "IncVog(IN)");	
	{
		RegisterUnitType(&Unit.Ka1, "ShpKanoe1(IN)");
		RegisterUnitType(&Unit.Ka3, "ShpKanoe3(IN)");
		RegisterUnitType(&Unit.Par, "ShpParom(IN)");
	}
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Rud, "SpnRud(IN)");
	RegisterUnitType(&Build.Iro, "SpnIro(IN)");
	RegisterUnitType(&Build.Coa, "SpnCoa(IN)");
	RegisterUnitType(&Build.Stn, "SpnStn(IN)");


	RegisterUnitType(&Build.Do1, "IncDo1(IN)");
	RegisterUnitType(&Build.Do2, "IncDo2(IN)");
	RegisterUnitType(&Build.Do3, "IncDo3(IN)");
	RegisterUnitType(&Build.Mel, "MayMel(IN)");
	RegisterUnitType(&Build.Skl, "MaySkl(IN)");
	RegisterUnitType(&Build.Kre, "IncKre(IN)");
	RegisterUnitType(&Build.Blg, "IncBlg(IN)");
	RegisterUnitType(&Build.Ver, "IncVer(IN)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	
	// Mine
	{
		RegisterUpgrade(&Upg.Gld0, "SpnRud(IN)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(IN)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(IN)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(IN)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(IN)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(IN)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(IN)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(IN)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(IN)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(IN)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(IN)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(IN)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(IN)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(IN)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(IN)INSIDE3");
	}

	RegisterUpgrade(&Upg.CEN01, "CEN01IN");
	RegisterUpgrade(&Upg.CEN02, "CEN02IN");
	RegisterUpgrade(&Upg.CEN03, "CEN03IN");
	RegisterUpgrade(&Upg.CEN10, "CEN10IN");
	
	RegisterUpgrade(&Upg.Do2_ENABLE, "IncDo2(IN)ENABLE");
	RegisterUpgrade(&Upg.Do3_ENABLE, "IncDo3(IN)ENABLE");

	RegisterUpgrade(&Upg.Mel_GETRES, "MayMel(IN)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "MayMel(IN)GETRES2");

	RegisterUpgrade(&Upg.CEN52, "INC52IN");
	RegisterUpgrade(&Upg.CEN12, "CEN12IN");

	// Kre
	{
		// stages
		RegisterUpgrade(&Upg.KreStage0, "UPSTINCKRE0");
		RegisterUpgrade(&Upg.KreStage1, "UPSTINCKRE1");
		RegisterUpgrade(&Upg.KreStage2, "UPSTINCKRE2");
	}

	// More Farms
	{
		RegisterUpgrade(&Upg.Do3Farms1, "UPSTINCDO30");
		RegisterUpgrade(&Upg.Do3Farms2, "UPSTINCDO31");
	}

	// Kri
	{
		RegisterUpgrade(&Upg.KriBu1, "CEN09IN");
		RegisterUpgrade(&Upg.KriBu2, "CEN08IN");
	}

	// Warriors
	RegisterUpgrade(&Upg.WarLife,"IncPik(IN)LIFE");
	RegisterUpgrade(&Upg.Strike1, "CEN05IN");

	// Pik
	{
		// build speed
		RegisterUpgrade(&Upg.PikBuild,"CEN07IN");
		// attack
		RegisterUpgrade(&Upg.PikAtt,"IncPik(IN)ATTACK");
		RegisterUpgrade(&Upg.PikAtt3,"IncPik(IN)ATTACK3");
		RegisterUpgrade(&Upg.PikAtt4,"IncPik(IN)ATTACK4");
		RegisterUpgrade(&Upg.PikAtt5,"IncPik(IN)ATTACK5");
		RegisterUpgrade(&Upg.PikAtt6,"IncPik(IN)ATTACK6");
		RegisterUpgrade(&Upg.PikAtt7,"IncPik(IN)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.PikShi,"IncPik(IN)SHIELD");
		RegisterUpgrade(&Upg.PikShi3,"IncPik(IN)SHIELD3");
		RegisterUpgrade(&Upg.PikShi4,"IncPik(IN)SHIELD4");
		RegisterUpgrade(&Upg.PikShi5,"IncPik(IN)SHIELD5");
		RegisterUpgrade(&Upg.PikShi6,"IncPik(IN)SHIELD6");
		RegisterUpgrade(&Upg.PikShi7,"IncPik(IN)SHIELD7");
	}

	// Lut
	{
		RegisterUpgrade(&Upg.LutRaz1, "IncKre(IN)RAZBROS");
		RegisterUpgrade(&Upg.LutRaz2, "IncKre(IN)RAZBROS1");
		// attack
		RegisterUpgrade(&Upg.LutAtt, "IncLut(IN)ATTACK");
		RegisterUpgrade(&Upg.LutAtt3, "IncLut(IN)ATTACK3");
		RegisterUpgrade(&Upg.LutAtt4, "IncLut(IN)ATTACK4");
		RegisterUpgrade(&Upg.LutAtt5, "IncLut(IN)ATTACK5");
		RegisterUpgrade(&Upg.LutAtt6, "IncLut(IN)ATTACK6");
		RegisterUpgrade(&Upg.LutAtt7, "IncLut(IN)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.LutDef, "IncLut(IN)SHIELD");
		RegisterUpgrade(&Upg.LutDef3, "IncLut(IN)SHIELD3");
		RegisterUpgrade(&Upg.LutDef4, "IncLut(IN)SHIELD4");
		RegisterUpgrade(&Upg.LutDef5, "IncLut(IN)SHIELD5");
		RegisterUpgrade(&Upg.LutDef6, "IncLut(IN)SHIELD6");
		RegisterUpgrade(&Upg.LutDef7, "IncLut(IN)SHIELD7");
	}

	// Trb
	{
		
	}

	// Pra
	{
		// build speed
		RegisterUpgrade(&Upg.PraBuild, "CEN17IN");
		// attack
		RegisterUpgrade(&Upg.PraAtt, "IncPra(IN)ATTACK");
		RegisterUpgrade(&Upg.PraAtt3, "IncPra(IN)ATTACK3");
		RegisterUpgrade(&Upg.PraAtt4, "IncPra(IN)ATTACK4");
		RegisterUpgrade(&Upg.PraAtt5, "IncPra(IN)ATTACK5");
		RegisterUpgrade(&Upg.PraAtt6, "IncPra(IN)ATTACK6");
		RegisterUpgrade(&Upg.PraAtt7, "IncPra(IN)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.PraShi,"IncPra(IN)SHIELD");
		RegisterUpgrade(&Upg.PraShi3,"IncPra(IN)SHIELD3");
		RegisterUpgrade(&Upg.PraShi4,"IncPra(IN)SHIELD4");
		RegisterUpgrade(&Upg.PraShi5,"IncPra(IN)SHIELD5");
		RegisterUpgrade(&Upg.PraShi6,"IncPra(IN)SHIELD6");
		RegisterUpgrade(&Upg.PraShi7,"IncPra(IN)SHIELD7");
	}


	// Vog
	{
		// defence
		RegisterUpgrade(&Upg.VogDef, "IncVog(IN)SHIELD");
		RegisterUpgrade(&Upg.VogDef3, "IncVog(IN)SHIELD3");
		RegisterUpgrade(&Upg.VogDef4, "IncVog(IN)SHIELD4");
	}

		// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102IN");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103IN");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104IN");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105IN");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106IN");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107IN");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96IN");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97IN");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98IN");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99IN");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100IN");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101IN");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90IN");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91IN");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92IN");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93IN");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94IN");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95IN");
	}
	
	//RegisterUpgrade(&Upg., "");
}

IncNation Inc;