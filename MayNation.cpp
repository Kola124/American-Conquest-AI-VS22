#include "MayNation.h"

MayNation::MayNation() {
	
	// Units	
	RegisterUnitType(&Unit.Pik, "MayPik(MA)");
	RegisterUnitType(&Unit.Lut, "MayLut(MA)");
	RegisterUnitType(&Unit.Sha, "MaySha(MA)");
	RegisterUnitType(&Unit.Vog, "MayVog(MA)");
	RegisterUnitType(&Unit.Voi, "MayVoi(MA)");
	RegisterUnitType(&Unit.Kri, "MayKri(MA)");
	
	RegisterUnitType(&Unit.Ka1, "ShpKanoe1(MA)");
	RegisterUnitType(&Unit.Ka3, "ShpKanoe3(MA)");
	RegisterUnitType(&Unit.Par, "ShpParom(MA)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Rud, "SpnRud(MA)");
	RegisterUnitType(&Build.Iro, "SpnIro(MA)");
	RegisterUnitType(&Build.Coa, "SpnCoa(MA)");
	RegisterUnitType(&Build.Stn, "SpnStn(MA)");
	RegisterUnitType(&Build.Do1, "MayDo1(MA)");
	RegisterUnitType(&Build.Do2, "MayDo2(MA)");
	RegisterUnitType(&Build.Do3, "MayDo3(MA)");
	RegisterUnitType(&Build.Mel, "MayMel(MA)");
	RegisterUnitType(&Build.Skl, "MaySkl(MA)");
	RegisterUnitType(&Build.Hra, "MayHra(MA)");
	RegisterUnitType(&Build.Cen, "MayCen2(MA)");
	RegisterUnitType(&Build.Kre, "MayKre(MA)");
	RegisterUnitType(&Build.Blg, "MayBlg(MA)");
	RegisterUnitType(&Build.Bl2, "MayBlg2(MA)");	
	RegisterUnitType(&Build.Ver, "MayVer(MA)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.Mel_GETRES, "MayMel(MA)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "MayMel(MA)GETRES2");
	RegisterUpgrade(&Upg.CEN10MA, "CEN10MA");
	RegisterUpgrade(&Upg.CEN12MA, "CEN12MA");
	RegisterUpgrade(&Upg.MAY52MA, "MAY52MA");
	RegisterUpgrade(&Upg.CEN01MA, "CEN01MA");
	RegisterUpgrade(&Upg.CEN02MA, "CEN02MA");
	RegisterUpgrade(&Upg.CEN03MA, "CEN03MA");

	RegisterUpgrade(&Upg.ShaSpd, "CEN13MA");
	RegisterUpgrade(&Upg.ShaHeal, "CEN14MA");
	RegisterUpgrade(&Upg.ShaLife, "CEN15MA");

	RegisterUpgrade(&Upg.FieldDur3, "CEN12MA");
	RegisterUpgrade(&Upg.BldSpd,"CEN11MA");
	
	RegisterUpgrade(&Upg.EnDo2, "MayDo2(MA)ENABLE");
	RegisterUpgrade(&Upg.EnDo1, "MayDo1(MA)ENABLE");
	
	RegisterUpgrade(&Upg.EnVoi, "UPSTMAYKRE1");
	RegisterUpgrade(&Upg.EnVog, "UPSTMAYKRE2");

	// Mine
	{
		RegisterUpgrade(&Upg.Gld0, "SpnRud(MA)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(MA)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(MA)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(MA)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(MA)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(MA)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(MA)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(MA)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(MA)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(MA)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(MA)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(MA)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(MA)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(MA)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(MA)INSIDE3");
	}

	// Warriors
	RegisterUpgrade(&Upg.Life1, "MayPik(MA)LIFE");
	
	// Pik
	{		
		RegisterUpgrade(&Upg.PikBuild1, "CEN07MA");
		
		RegisterUpgrade(&Upg.PikA2, "MayPik(MA)ATTACK");
		RegisterUpgrade(&Upg.PikA3, "MayPik(MA)ATTACK3");
		RegisterUpgrade(&Upg.PikA4, "MayPik(MA)ATTACK4");
		RegisterUpgrade(&Upg.PikA5, "MayPik(MA)ATTACK5");
		RegisterUpgrade(&Upg.PikA6, "MayPik(MA)ATTACK6");
		RegisterUpgrade(&Upg.PikA7, "MayPik(MA)ATTACK7");
		RegisterUpgrade(&Upg.PikS2, "MayPik(MA)SHIELD");
		RegisterUpgrade(&Upg.PikS3, "MayPik(MA)SHIELD3");
		RegisterUpgrade(&Upg.PikS4, "MayPik(MA)SHIELD4");
		RegisterUpgrade(&Upg.PikS5, "MayPik(MA)SHIELD5");
		RegisterUpgrade(&Upg.PikS6, "MayPik(MA)SHIELD6");
		RegisterUpgrade(&Upg.PikS7, "MayPik(MA)SHIELD7");
	}

	// Lut
	{
		RegisterUpgrade(&Upg.EnLut, "UPSTMAYKRE0");

		RegisterUpgrade(&Upg.LutS2, "MayLut(MA)SHIELD");
		RegisterUpgrade(&Upg.LutS3, "MayLut(MA)SHIELD3");
		RegisterUpgrade(&Upg.LutS4, "MayLut(MA)SHIELD4");
		RegisterUpgrade(&Upg.LutS5, "MayLut(MA)SHIELD5");
		RegisterUpgrade(&Upg.LutS6, "MayLut(MA)SHIELD6");
		RegisterUpgrade(&Upg.LutS7, "MayLut(MA)SHIELD7");

		RegisterUpgrade(&Upg.LutRaz1, "MayKre(MA)RAZBROS");
		RegisterUpgrade(&Upg.LutRaz2, "MayKre(MA)RAZBROS1");
	}

	// Voi - Makamba
	{
		RegisterUpgrade(&Upg.VoiA2, "MayVoi(MA)ATTACK");
		RegisterUpgrade(&Upg.VoiA3, "MayVoi(MA)ATTACK3");
		RegisterUpgrade(&Upg.VoiA4, "MayVoi(MA)ATTACK4");
		RegisterUpgrade(&Upg.VoiA5, "MayVoi(MA)ATTACK5");
		RegisterUpgrade(&Upg.VoiA6, "MayVoi(MA)ATTACK6");
		RegisterUpgrade(&Upg.VoiA7, "MayVoi(MA)ATTACK7");

		RegisterUpgrade(&Upg.VoiS2, "MayVoi(MA)SHIELD");
		RegisterUpgrade(&Upg.VoiS3, "MayVoi(MA)SHIELD3");
		RegisterUpgrade(&Upg.VoiS4, "MayVoi(MA)SHIELD4");
		RegisterUpgrade(&Upg.VoiS5, "MayVoi(MA)SHIELD5");
		RegisterUpgrade(&Upg.VoiS6, "MayVoi(MA)SHIELD6");
		RegisterUpgrade(&Upg.VoiS7, "MayVoi(MA)SHIELD7");

		RegisterUpgrade(&Upg.Strike1, "CEN05MA");
		RegisterUpgrade(&Upg.VoiSh1, "MayVoiS");
		RegisterUpgrade(&Upg.VoiSh2, "CEN06MA");
	}

	// Kri
	{
		RegisterUpgrade(&Upg.KriBu1, "CEN09MA");
		RegisterUpgrade(&Upg.KriBu2, "CEN08MA");
	}
	
	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102MA");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103MA");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104MA");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105MA");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106MA");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107MA");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96MA");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97MA");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98MA");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99MA");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100MA");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101MA");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90MA");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91MA");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92MA");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93MA");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94MA");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95MA");
	}

	//RegisterUpgrade(&Upg., "");
}

MayNation May;