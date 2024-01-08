#include "PueNation.h"

PueNation::PueNation() {
	
	// Units	
	{
		RegisterUnitType(&Unit.Kri, "PueKri(PU)");
		RegisterUnitType(&Unit.Lut, "PueLut(PU)");	
		RegisterUnitType(&Unit.Sha, "PueSha(PU)");
		RegisterUnitType(&Unit.S15, "PueS15(PU)");
		RegisterUnitType(&Unit.Vog, "PueVog(PU)");	
		RegisterUnitType(&Unit.Vsd, "PueVsda(PU)"); // vsadnik	
		{
			RegisterUnitType(&Unit.Ka1, "ShpKanoe1(PU)");
			RegisterUnitType(&Unit.Ka3, "ShpKanoe3(PU)");
			RegisterUnitType(&Unit.Par, "ShpParom(PU)");
		}
		//RegisterUnitType(&Unit., "");
	}
	
	// Buildings
	{
		RegisterUnitType(&Build.Rud, "SpnRud(PU)");
		RegisterUnitType(&Build.Iro, "SpnIro(PU)");
		RegisterUnitType(&Build.Coa, "SpnCoa(PU)");
		RegisterUnitType(&Build.Stn, "SpnStn(PU)");
		RegisterUnitType(&Build.Mel, "PueMel(PU)");
		RegisterUnitType(&Build.Skl, "PueSkl(PU)");
		RegisterUnitType(&Build.Pst, "SiuPst(PU)");
		RegisterUnitType(&Build.Gor, "PueGor(PU)");
		RegisterUnitType(&Build.Ver, "PueVer(PU)");
		//RegisterUnitType(&Build., "");
	}	
	
	
	// Upgrades
	
	// Food & Field
	{
		RegisterUpgrade(&Upg.FoodMel1, "PueMel(PU)GETRES");
		RegisterUpgrade(&Upg.FoodMel2, "PueMel(PU)GETRES2");
		RegisterUpgrade(&Upg.FoodCen01, "CEN01PU");
		RegisterUpgrade(&Upg.FoodCen02, "CEN02PU");
		RegisterUpgrade(&Upg.FoodCen03, "CEN03PU");

		RegisterUpgrade(&Upg.FieldCen10, "CEN10PU");
		RegisterUpgrade(&Upg.FieldCen52, "MAY52PU");
		RegisterUpgrade(&Upg.FieldCen12, "CEN12PU");
	}
	
	// Wood
	{
		RegisterUpgrade(&Upg.Wood1, "CEN29PU");
		RegisterUpgrade(&Upg.Wood2, "CEN30PU");
	}

	// Mine
	{
		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(PU)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(PU)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(PU)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(PU)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(PU)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(PU)INSIDE6");
	}

	// Center
	{
		RegisterUpgrade(&Upg.CenStage1, "UPSTPUEGOR0");
		RegisterUpgrade(&Upg.CenStage2, "UPSTPUEGOR1");
		RegisterUpgrade(&Upg.CenStage3, "UPSTPUEGOR2");
		RegisterUpgrade(&Upg.CenStage4, "UPSTPUEGOR3");
	}

	// Warriors
	{
		RegisterUpgrade(&Upg.WarDamage1, "CEN05PU");
		RegisterUpgrade(&Upg.WarLife1, "PueS15(PU)LIFE");
	}

	// Lut
	{
		RegisterUpgrade(&Upg.LutRazbros1, "PueGor(PU)RAZBROS");
		RegisterUpgrade(&Upg.LutRazbros2, "PueGor(PU)RAZBROS1");
		RegisterUpgrade(&Upg.LutLife1, "CEN05PU");
		RegisterUpgrade(&Upg.LutBuild1, "CEN08PU");
		RegisterUpgrade(&Upg.LutBuild2, "CEN47PU");
		RegisterUpgrade(&Upg.LutBuild3, "CEN48PU");
	}

	// S15
	{
		RegisterUpgrade(&Upg.S15Enable, "PueS15(PU)ENABLE");
		RegisterUpgrade(&Upg.S15Build1, "CEN07PU");
		RegisterUpgrade(&Upg.S15Build2, "CEN45PU");
		RegisterUpgrade(&Upg.S15Build3, "CEN46PU");

		RegisterUpgrade(&Upg.S15Att, "PueS15(PU)ATTACK");
		RegisterUpgrade(&Upg.S15Att3, "PueS15(PU)ATTACK3");
		RegisterUpgrade(&Upg.S15Att4, "PueS15(PU)ATTACK4");
		RegisterUpgrade(&Upg.S15Att5, "PueS15(PU)ATTACK5");
		RegisterUpgrade(&Upg.S15Att6, "PueS15(PU)ATTACK6");
		RegisterUpgrade(&Upg.S15Att7, "PueS15(PU)ATTACK7");

		RegisterUpgrade(&Upg.S15Def, "PueS15(PU)SHIELD");
		RegisterUpgrade(&Upg.S15Def3, "PueS15(PU)SHIELD3");
		RegisterUpgrade(&Upg.S15Def4, "PueS15(PU)SHIELD4");
		RegisterUpgrade(&Upg.S15Def5, "PueS15(PU)SHIELD5");
		RegisterUpgrade(&Upg.S15Def6, "PueS15(PU)SHIELD6");
		RegisterUpgrade(&Upg.S15Def7, "PueS15(PU)SHIELD7");
	}

	// Vsd
	{
		RegisterUpgrade(&Upg.VsdBuild1, "CEN09PU");
	}

	// Sha
	{
		RegisterUpgrade(&Upg.ShaLife1, "CEN15PU");
		RegisterUpgrade(&Upg.ShaMedik1, "CEN14PU");
		RegisterUpgrade(&Upg.ShaBuild1, "CEN13PU");
	}

	// Vog
	{
		RegisterUpgrade(&Upg.VogEnable, "PueVog(PU)ENABLE");
	}

	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102PU");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103PU");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104PU");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105PU");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106PU");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107PU");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96PU");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97PU");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98PU");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99PU");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100PU");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101PU");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90PU");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91PU");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92PU");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93PU");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94PU");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95PU");
	}

	//RegisterUpgrade(&Upg., "");
}

PueNation Pue;