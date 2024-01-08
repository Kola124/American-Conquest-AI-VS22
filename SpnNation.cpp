#include "SpnNation.h"

SpnNation::SpnNation() {
	
	// Units	
	
	RegisterUnitType(&Unit.Pik, "SpnAlb(SP)");	
	RegisterUnitType(&Unit.S15, "SpnS15(SP)");
	RegisterUnitType(&Unit.S17, "SpnMus(SP)");
	RegisterUnitType(&Unit.S18, "SpnM18(SP)");

	RegisterUnitType(&Unit.O17, "SpnOf17(SP)");
	RegisterUnitType(&Unit.O18, "SpnOf18(SP)");
	RegisterUnitType(&Unit.B17, "SpnB17(SP)");
	RegisterUnitType(&Unit.B18, "SpnB18(SP)");
	RegisterUnitType(&Unit.F17, "SpnF17(SP)");
	RegisterUnitType(&Unit.F18, "SpnF18(SP)");

	RegisterUnitType(&Unit.Rei, "SpnRei(SP)");
	RegisterUnitType(&Unit.D17, "SpnD17(SP)");
	RegisterUnitType(&Unit.KO7, "SpnKOf17(SP)");
	RegisterUnitType(&Unit.D18, "SpnD18(SP)");
	RegisterUnitType(&Unit.KO8, "SpnKOf18(SP)");
	RegisterUnitType(&Unit.KF8, "SpnKF18(SP)");

	RegisterUnitType(&Unit.Kri, "SpnKri(SP)");
	RegisterUnitType(&Unit.Sha, "SpnSha(SP)");
	RegisterUnitType(&Unit.Can, "ArtPus(SP)");	

	RegisterUnitType(&Unit.Lodka, "ShpLodka(SP)");
	RegisterUnitType(&Unit.Parom, "ShpParom(SP)");
	RegisterUnitType(&Unit.Pinta, "ShpPinta(SP)");
	RegisterUnitType(&Unit.Santa, "ShpSanta(SP)");
	RegisterUnitType(&Unit.Fregat, "ShpFregat(SP)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings

	// Mine
	{
		RegisterUnitType(&Build.Rud, "SpnRud(SP)");
		RegisterUnitType(&Build.Iro, "SpnIro(SP)");
		RegisterUnitType(&Build.Coa, "SpnCoa(SP)");
		RegisterUnitType(&Build.Stn, "SpnStn(SP)");

		RegisterUpgrade(&Upg.MineEnable1, "CEN21SP(SP)SpnRudINS(SP)ENABLE");
		RegisterUpgrade(&Upg.Geology, "CEN21SP");

		RegisterUpgrade(&Upg.Gld0, "SpnRud(SP)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(SP)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(SP)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(SP)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(SP)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(SP)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(SP)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(SP)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(SP)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(SP)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(SP)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(SP)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(SP)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(SP)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(SP)INSIDE3");
		RegisterUpgrade(&Upg.Iro3, "SpnRudIr(SP)INSIDE4");

		RegisterUpgrade(&Upg.Coa0, "SpnRudCo(SP)INSIDE");
		RegisterUpgrade(&Upg.Coa1, "SpnRudCo(SP)INSIDE2");
		RegisterUpgrade(&Upg.Coa2, "SpnRudCo(SP)INSIDE3");
		RegisterUpgrade(&Upg.Coa3, "SpnRudCo(SP)INSIDE4");
	}

	RegisterUnitType(&Build.Do1, "SpnDo1(SP)");
	RegisterUnitType(&Build.Do2, "SpnDo2(SP)");
	RegisterUnitType(&Build.Mel, "SpnMel(SP)");
	RegisterUnitType(&Build.Skl, "SpnSkl(SP)");
	RegisterUnitType(&Build.Hra, "SpnHra(SP)");
	RegisterUnitType(&Build.Cen, "SpnCen(SP)");
	RegisterUnitType(&Build.Kr7, "EngKre(SP)");
	RegisterUnitType(&Build.Kr8, "SpnKre(SP)");
	RegisterUnitType(&Build.Kuz, "SpnKuz(SP)");
	RegisterUnitType(&Build.Blg, "EngBlg(SP)");
	RegisterUnitType(&Build.Blg2, "EngBlg2(SP)");
	RegisterUnitType(&Build.Ver, "SpnVer(SP)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.CEN18, "CEN18SP");
	RegisterUpgrade(&Upg.CEN52, "CEN52SP");
	RegisterUpgrade(&Upg.CEN57, "CEN57SP");
	RegisterUpgrade(&Upg.CEN55, "CEN55SP");

	RegisterUpgrade(&Upg.Mel_GETRES, "SpnMel(SP)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "SpnMel(SP)GETRES2");
	RegisterUpgrade(&Upg.CEN19, "CEN19SP");
	RegisterUpgrade(&Upg.CEN22, "CEN22SP");
	RegisterUpgrade(&Upg.CEN23, "CEN23SP");

	RegisterUpgrade(&Upg.Kr7_Stage0, "UPSTENGKRE(SP)0");
	RegisterUpgrade(&Upg.Kr8_Stage0, "UPSTSPNKRE0(SP)");
	RegisterUpgrade(&Upg.Kr8_Stage1, "UPSTSPNKRE1(SP)");

	RegisterUpgrade(&Upg.BldBuild1, "CEN53SP");	

	RegisterUpgrade(&Upg.Do2_ENABLE, "SpnDo2(SP)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56SP");

	// Krepost
	{
		RegisterUpgrade(&Upg.KreBuild, "CEN25SP");
	}

	// Wood
	{
		RegisterUpgrade(&Upg.Wood1, "CEN29SP");
		RegisterUpgrade(&Upg.Wood2, "CEN30SP");
		RegisterUpgrade(&Upg.Wood3, "CEN31SP");
	}
	
	// Kri
	{
		RegisterUpgrade(&Upg.KriBuild1, "CEN24SP");
		RegisterUpgrade(&Upg.KriBuild2, "CEN36SP");
		RegisterUpgrade(&Upg.KriBuild3, "CEN48SP");
	}

	// Pik
	{
		RegisterUpgrade(&Upg.PikBuild1, "KUZ20(SP)");
		RegisterUpgrade(&Upg.PikBuild2, "CEN26SP");
		RegisterUpgrade(&Upg.PikBuild3, "CEN27SP");
		RegisterUpgrade(&Upg.PikBuild4, "CEN28SP");

		RegisterUpgrade(&Upg.PikAttack, "SpnAlb(SP)ATTACK");
		RegisterUpgrade(&Upg.PikAttack3, "SpnAlb(SP)ATTACK3");
		RegisterUpgrade(&Upg.PikAttack4, "SpnAlb(SP)ATTACK4");
		RegisterUpgrade(&Upg.PikAttack5, "SpnAlb(SP)ATTACK5");
		RegisterUpgrade(&Upg.PikAttack6, "SpnAlb(SP)ATTACK6");
		RegisterUpgrade(&Upg.PikAttack7, "SpnAlb(SP)ATTACK7");

		RegisterUpgrade(&Upg.PikProtect, "SpnAlb(SP)SHIELD");
		RegisterUpgrade(&Upg.PikProtect3, "SpnAlb(SP)SHIELD3");
		RegisterUpgrade(&Upg.PikProtect4, "SpnAlb(SP)SHIELD4");
		RegisterUpgrade(&Upg.PikProtect5, "SpnAlb(SP)SHIELD5");
		RegisterUpgrade(&Upg.PikProtect6, "SpnAlb(SP)SHIELD6");
		RegisterUpgrade(&Upg.PikProtect7, "SpnAlb(SP)SHIELD7");
	}

	// Can
	{
		RegisterUpgrade(&Upg.CanCost, "ArtPus(SP)COST");
		RegisterUpgrade(&Upg.CanCost3, "ArtPus(SP)COST3");
		RegisterUpgrade(&Upg.CanCost4, "ArtPus(SP)COST4");
		RegisterUpgrade(&Upg.CanCost5, "ArtPus(SP)COST5");
		RegisterUpgrade(&Upg.CanCost6, "ArtPus(SP)COST6");
		RegisterUpgrade(&Upg.CanCost7, "ArtPus(SP)COST7");

		RegisterUpgrade(&Upg.CanBuild, "ArtPus(SP)BUILD");
		RegisterUpgrade(&Upg.CanBuild3, "ArtPus(SP)BUILD3");
		RegisterUpgrade(&Upg.CanBuild4, "ArtPus(SP)BUILD4");
		RegisterUpgrade(&Upg.CanBuild5, "ArtPus(SP)BUILD5");
		RegisterUpgrade(&Upg.CanBuild6, "ArtPus(SP)BUILD6");
		RegisterUpgrade(&Upg.CanBuild7, "ArtPus(SP)BUILD7");
	}
	
	// Cen
	{
		RegisterUpgrade(&Upg.ArmShield1, "CEN47SP");
		RegisterUpgrade(&Upg.ArmShield2, "CEN08SP");
		RegisterUpgrade(&Upg.ArmShield3, "CEN49SP");

		RegisterUpgrade(&Upg.StrAttPause1, "CEN01SP");
		
		RegisterUpgrade(&Upg.StrDamage1, "CEN45SP");
		RegisterUpgrade(&Upg.StrDamage2, "CEN50SPA");

		RegisterUpgrade(&Upg.BldShield1, "CEN37SP");
		RegisterUpgrade(&Upg.BldShield2, "CEN47SP");
	}

	// Rei
	{
		RegisterUpgrade(&Upg.ReiBuild, "CEN39SP");

		RegisterUpgrade(&Upg.ReiAttack, "SpnRei(SP)ATTACK");
		RegisterUpgrade(&Upg.ReiAttack3, "SpnRei(SP)ATTACK3");
		RegisterUpgrade(&Upg.ReiAttack4, "SpnRei(SP)ATTACK4");
		RegisterUpgrade(&Upg.ReiAttack5, "SpnRei(SP)ATTACK5");
		RegisterUpgrade(&Upg.ReiAttack6, "SpnRei(SP)ATTACK6");
		RegisterUpgrade(&Upg.ReiAttack7, "SpnRei(SP)ATTACK7");
		
		RegisterUpgrade(&Upg.ReiProtect, "SpnRei(SP)SHIELD");
		RegisterUpgrade(&Upg.ReiProtect3, "SpnRei(SP)SHIELD3");
		RegisterUpgrade(&Upg.ReiProtect4, "SpnRei(SP)SHIELD4");
		RegisterUpgrade(&Upg.ReiProtect5, "SpnRei(SP)SHIELD5");
		RegisterUpgrade(&Upg.ReiProtect6, "SpnRei(SP)SHIELD6");
		RegisterUpgrade(&Upg.ReiProtect7, "SpnRei(SP)SHIELD7");
	}

	// S15
	{
		RegisterUpgrade(&Upg.S15Attack, "SpnS15(SP)ATTACK");
		RegisterUpgrade(&Upg.S15Attack3, "SpnS15(SP)ATTACK3");
		RegisterUpgrade(&Upg.S15Attack4, "SpnS15(SP)ATTACK4");
		RegisterUpgrade(&Upg.S15Attack5, "SpnS15(SP)ATTACK5");
		RegisterUpgrade(&Upg.S15Attack6, "SpnS15(SP)ATTACK6");
		RegisterUpgrade(&Upg.S15Attack7, "SpnS15(SP)ATTACK7");
		
		RegisterUpgrade(&Upg.S15Protect, "SpnS15(SP)SHIELD");
		RegisterUpgrade(&Upg.S15Protect3, "SpnS15(SP)SHIELD3");
		RegisterUpgrade(&Upg.S15Protect4, "SpnS15(SP)SHIELD4");
		RegisterUpgrade(&Upg.S15Protect5, "SpnS15(SP)SHIELD5");
		RegisterUpgrade(&Upg.S15Protect6, "SpnS15(SP)SHIELD6");
		RegisterUpgrade(&Upg.S15Protect7, "SpnS15(SP)SHIELD7");
	}

	// Mus
	{
		RegisterUpgrade(&Upg.MusAttack, "SpnMus(SP)ATTACK");
		RegisterUpgrade(&Upg.MusAttack3, "SpnMus(SP)ATTACK3");
		RegisterUpgrade(&Upg.MusAttack4, "SpnMus(SP)ATTACK4");
		RegisterUpgrade(&Upg.MusAttack5, "SpnMus(SP)ATTACK5");
		RegisterUpgrade(&Upg.MusAttack6, "SpnMus(SP)ATTACK6");
		RegisterUpgrade(&Upg.MusAttack7, "SpnMus(SP)ATTACK7");
		
		RegisterUpgrade(&Upg.MusProtect, "SpnMus(SP)SHIELD");
		RegisterUpgrade(&Upg.MusProtect3, "SpnMus(SP)SHIELD3");
		RegisterUpgrade(&Upg.MusProtect4, "SpnMus(SP)SHIELD4");
		RegisterUpgrade(&Upg.MusProtect5, "SpnMus(SP)SHIELD5");
		RegisterUpgrade(&Upg.MusProtect6, "SpnMus(SP)SHIELD6");
		RegisterUpgrade(&Upg.MusProtect7, "SpnMus(SP)SHIELD7");
	}

	// S18
	{
		RegisterUpgrade(&Upg.S18Build1, "CEN61SP");
		RegisterUpgrade(&Upg.S18Build2, "CEN62SP");
		RegisterUpgrade(&Upg.S18Build3, "CEN63SP");

		RegisterUpgrade(&Upg.S18Attack, "SpnM18(SP)ATTACK");
		RegisterUpgrade(&Upg.S18Attack3, "SpnM18(SP)ATTACK3");
		RegisterUpgrade(&Upg.S18Attack4, "SpnM18(SP)ATTACK4");
		RegisterUpgrade(&Upg.S18Attack5, "SpnM18(SP)ATTACK5");
		RegisterUpgrade(&Upg.S18Attack6, "SpnM18(SP)ATTACK6");
		RegisterUpgrade(&Upg.S18Attack7, "SpnM18(SP)ATTACK7");

		RegisterUpgrade(&Upg.S18Protect, "SpnM18(SP)SHIELD");
		RegisterUpgrade(&Upg.S18Protect3, "SpnM18(SP)SHIELD3");
		RegisterUpgrade(&Upg.S18Protect4, "SpnM18(SP)SHIELD4");
		RegisterUpgrade(&Upg.S18Protect5, "SpnM18(SP)SHIELD5");
		RegisterUpgrade(&Upg.S18Protect6, "SpnM18(SP)SHIELD6");
		RegisterUpgrade(&Upg.S18Protect7, "SpnM18(SP)SHIELD7");
	}

	// Officers
	{
		RegisterUpgrade(&Upg.B17Protect, "SpnB17(SP)SHIELD7");
		RegisterUpgrade(&Upg.O17Damage, "SpnOf17(SP)ATTACK7");
		RegisterUpgrade(&Upg.O17Protect, "SpnOf17(SP)SHIELD7");
		RegisterUpgrade(&Upg.F17Protect, "SpnF17(SP)SHIELD7");
	}

	//NEW STUFF 

	//Artileri
	RegisterUpgrade(&Upg.ARTROF1, "CEN03SP");
	RegisterUpgrade(&Upg.ARTROF2, "CEN04SP");
	RegisterUpgrade(&Upg.ARTRNG1, "CEN42SP");
	RegisterUpgrade(&Upg.ARTRNG2, "CEN43SP");
	RegisterUpgrade(&Upg.ARTACC1, "CEN02SP");
	RegisterUpgrade(&Upg.ARTACC2, "CEN06SP");

	//Fortress Upgrade
	RegisterUpgrade(&Upg.Kr8_Stage1, "VSEDIBILI1(SP)");
	RegisterUpgrade(&Upg.Kr8_Stage2, "VSEDIBILI2(SP)");
	RegisterUpgrade(&Upg.Kr8_Stage3, "VSEDIBILI3(SP)");

	//Mine 
	RegisterUpgrade(&Upg.Iro4, "SpnRudIr(SP)INSIDE5");
	RegisterUpgrade(&Upg.Iro5, "SpnRudIr(SP)INSIDE6");
	RegisterUpgrade(&Upg.Coa4, "SpnRudCo(SP)INSIDE5");
	RegisterUpgrade(&Upg.Coa5, "SpnRudCo(SP)INSIDE6");

	//Town Hall
	RegisterUpgrade(&Upg.LogDef, "CEN54SP");
	RegisterUpgrade(&Upg.FindGeo, "CEN21SP");
	RegisterUpgrade(&Upg.Horse17Build, "CEN39SP");
	RegisterUpgrade(&Upg.Horse18Build, "CEN40SP");
	RegisterUpgrade(&Upg.HorseAllBuild, "CEN41SP");
	RegisterUpgrade(&Upg.S15Build1, "CEN33SP");
	RegisterUpgrade(&Upg.S15Build2, "CEN34SP");
	RegisterUpgrade(&Upg.S15Build3, "CEN35SP");
	RegisterUpgrade(&Upg.S17Build1, "CEN60SP");
	RegisterUpgrade(&Upg.S18Unlock, "CEN50SP");
	RegisterUpgrade(&Upg.S18RifFire, "CEN44SP");
	RegisterUpgrade(&Upg.S18FusFire, "CEN51SP");
	RegisterUpgrade(&Upg.S18Firepower, "CEN46SP");

	//Combat Upg
	RegisterUpgrade(&Upg.B18Protect, "UsaB18(SP)SHIELD7");
	RegisterUpgrade(&Upg.O18Damage, "UsaOf18(SP)ATTACK7");
	RegisterUpgrade(&Upg.O18Protect, "UsaOf18(SP)SHIELD7");
	RegisterUpgrade(&Upg.F18Protect, "UsaF18(SP)SHIELD7");
	//RegisterUpgrade(&Upg., "");
}

SpnNation Spn;