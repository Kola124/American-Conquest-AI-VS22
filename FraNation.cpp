#include "FraNation.h"

FraNation::FraNation() {
	
	// Units	
	RegisterUnitType(&Unit.Pik, "FrnPik(FR)");	
	RegisterUnitType(&Unit.S15, "FrnS15(FR)");
	RegisterUnitType(&Unit.S17, "FrnS17(FR)");
	RegisterUnitType(&Unit.S18, "FrnM18(FR)");

	RegisterUnitType(&Unit.O17, "FrnOf17(FR)");
	RegisterUnitType(&Unit.B17, "FrnB17(FR)");
	RegisterUnitType(&Unit.F17, "FrnF17(FR)");
	RegisterUnitType(&Unit.O18, "FrnOf18(FR)");
	RegisterUnitType(&Unit.B18, "FrnB18(FR)");
	RegisterUnitType(&Unit.F18, "FrnF18(FR)");

	RegisterUnitType(&Unit.Rei, "FrnD17(FR)");
	RegisterUnitType(&Unit.KO7, "FrnKOf17(FR)");
	RegisterUnitType(&Unit.D18, "FrnD18(FR)");
	RegisterUnitType(&Unit.KO8, "FrnKOf18(FR)");
	RegisterUnitType(&Unit.KF8, "FrnKF18(FR)");

	RegisterUnitType(&Unit.Lodka, "ShpLodka(FR)");
	RegisterUnitType(&Unit.Parom, "ShpParom(FR)");
	RegisterUnitType(&Unit.Pinta, "ShpPinta(FR)");
	RegisterUnitType(&Unit.Santa, "ShpSanta(FR)");
	RegisterUnitType(&Unit.Fregat, "ShpFregat(FR)");

	RegisterUnitType(&Unit.Kri, "FrnKri(FR)");
	RegisterUnitType(&Unit.Tap, "FrnBuk(FR)");
	RegisterUnitType(&Unit.Sha, "SpnSha(FR)");
	RegisterUnitType(&Unit.Can, "ArtPus(FR)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	
	// Mine
	{
		RegisterUnitType(&Build.Rud, "SpnRud(FR)");
		RegisterUnitType(&Build.Iro, "SpnIro(FR)");
		RegisterUnitType(&Build.Coa, "SpnCoa(FR)");
		RegisterUnitType(&Build.Stn, "SpnStn(FR)");

		RegisterUpgrade(&Upg.MineEnable1, "CEN21FR(FR)SpnRudINS(FR)ENABLE");
		RegisterUpgrade(&Upg.Geology, "CEN21EN");

		RegisterUpgrade(&Upg.Gld0, "SpnRud(FR)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(FR)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(FR)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(FR)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(FR)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(FR)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(FR)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(FR)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(FR)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(FR)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(FR)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(FR)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(FR)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(FR)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(FR)INSIDE3");
		RegisterUpgrade(&Upg.Iro3, "SpnRudIr(FR)INSIDE4");

		RegisterUpgrade(&Upg.Coa0, "SpnRudCo(FR)INSIDE");
		RegisterUpgrade(&Upg.Coa1, "SpnRudCo(FR)INSIDE2");
		RegisterUpgrade(&Upg.Coa2, "SpnRudCo(FR)INSIDE3");
		RegisterUpgrade(&Upg.Coa3, "SpnRudCo(FR)INSIDE4");
	}

	RegisterUnitType(&Build.Do1, "EngDo1(FR)");
	RegisterUnitType(&Build.Do2, "FrnDo2(FR)");
	RegisterUnitType(&Build.Mel, "EngMel(FR)");
	RegisterUnitType(&Build.Skl, "EngSkl(FR)");
	RegisterUnitType(&Build.Hra, "FrnHra(FR)");
	RegisterUnitType(&Build.Cen, "FrnCen(FR)");
	RegisterUnitType(&Build.Kr7, "EngKre(FR)");
	RegisterUnitType(&Build.Kr8, "FrnKre2(FR)");
	RegisterUnitType(&Build.Kuz, "FrnKuz(FR)");
	RegisterUnitType(&Build.Blg, "EngBlg(FR)");
	RegisterUnitType(&Build.Blg2, "EngBlg2(FR)");

	RegisterUnitType(&Build.Fer, "EngFer(EN)");

	RegisterUnitType(&Build.Ver, "FrnVer(FR)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.CEN18, "CEN18FR");
	RegisterUpgrade(&Upg.CEN52, "CEN52FR");
	RegisterUpgrade(&Upg.CEN57, "CEN57FR");
	RegisterUpgrade(&Upg.CEN55, "CEN55FR");

	RegisterUpgrade(&Upg.Mel_GETRES, "EngMel(FR)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "EngMel(FR)GETRES2");
	RegisterUpgrade(&Upg.CEN19, "CEN19FR");
	RegisterUpgrade(&Upg.CEN22, "CEN22FR");
	RegisterUpgrade(&Upg.CEN23, "CEN23FR");

	RegisterUpgrade(&Upg.Kr7_Stage0, "UPSTENGKRE(FR)0");
	RegisterUpgrade(&Upg.Kr8_Stage0, "UPSTFRNKRE2(FR)0");

	RegisterUpgrade(&Upg.BldBuild1, "CEN53FR");	

	RegisterUpgrade(&Upg.Do2_ENABLE, "FrnDo2(FR)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56FR");

	// Krepost
	{
		RegisterUpgrade(&Upg.KreBuild, "CEN25FR");
	}

	// Wood
	{
		RegisterUpgrade(&Upg.Wood1, "CEN29FR");
		RegisterUpgrade(&Upg.Wood2, "CEN30FR");
		RegisterUpgrade(&Upg.Wood3, "CEN31FR");
	}
	
	// Kri
	{
		RegisterUpgrade(&Upg.KriBuild1, "CEN24FR");
		RegisterUpgrade(&Upg.KriBuild2, "CEN36FR");
		RegisterUpgrade(&Upg.KriBuild3, "CEN48FR");
	}

	// Pik
	{
		RegisterUpgrade(&Upg.PikBuild1, "KUZ20(FR)");
		RegisterUpgrade(&Upg.PikBuild2, "CEN26FR");
		RegisterUpgrade(&Upg.PikBuild3, "CEN27FR");
		RegisterUpgrade(&Upg.PikBuild4, "CEN28FR");

		RegisterUpgrade(&Upg.PikAttack, "FrnPik(FR)ATTACK");
		RegisterUpgrade(&Upg.PikAttack3, "FrnPik(FR)ATTACK3");
		RegisterUpgrade(&Upg.PikAttack4, "FrnPik(FR)ATTACK4");
		RegisterUpgrade(&Upg.PikAttack5, "FrnPik(FR)ATTACK5");
		RegisterUpgrade(&Upg.PikAttack6, "FrnPik(FR)ATTACK6");
		RegisterUpgrade(&Upg.PikAttack7, "FrnPik(FR)ATTACK7");

		RegisterUpgrade(&Upg.PikProtect, "FrnPik(FR)SHIELD");
		RegisterUpgrade(&Upg.PikProtect3, "FrnPik(FR)SHIELD3");
		RegisterUpgrade(&Upg.PikProtect4, "FrnPik(FR)SHIELD4");
		RegisterUpgrade(&Upg.PikProtect5, "FrnPik(FR)SHIELD5");
		RegisterUpgrade(&Upg.PikProtect6, "FrnPik(FR)SHIELD6");
		RegisterUpgrade(&Upg.PikProtect7, "FrnPik(FR)SHIELD7");
	}
	
	// Can
	{
		RegisterUpgrade(&Upg.CanCost, "ArtPus(FR)COST");
		RegisterUpgrade(&Upg.CanCost3, "ArtPus(FR)COST3");
		RegisterUpgrade(&Upg.CanCost4, "ArtPus(FR)COST4");
		RegisterUpgrade(&Upg.CanCost5, "ArtPus(FR)COST5");
		RegisterUpgrade(&Upg.CanCost6, "ArtPus(FR)COST6");
		RegisterUpgrade(&Upg.CanCost7, "ArtPus(FR)COST7");

		RegisterUpgrade(&Upg.CanBuild, "ArtPus(FR)BUILD");
		RegisterUpgrade(&Upg.CanBuild3, "ArtPus(FR)BUILD3");
		RegisterUpgrade(&Upg.CanBuild4, "ArtPus(FR)BUILD4");
		RegisterUpgrade(&Upg.CanBuild5, "ArtPus(FR)BUILD5");
		RegisterUpgrade(&Upg.CanBuild6, "ArtPus(FR)BUILD6");
		RegisterUpgrade(&Upg.CanBuild7, "ArtPus(FR)BUILD7");
	}
	
	// Cen
	{
		RegisterUpgrade(&Upg.ArmShield1, "CEN47FR");
		RegisterUpgrade(&Upg.ArmShield2, "CEN08FR");
		RegisterUpgrade(&Upg.ArmShield3, "CEN49FR");

		RegisterUpgrade(&Upg.StrAttPause1, "CEN01FR");
		
		RegisterUpgrade(&Upg.StrDamage1, "CEN45FR");
		RegisterUpgrade(&Upg.StrDamage2, "CEN50FRA");

		RegisterUpgrade(&Upg.BldShield1, "CEN37FR");
		RegisterUpgrade(&Upg.BldShield2, "CEN47FR");
	}

	// Rei
	{
		RegisterUpgrade(&Upg.ReiBuild, "CEN39EN");

		RegisterUpgrade(&Upg.ReiAttack, "FrnD17(FR)ATTACK");
		RegisterUpgrade(&Upg.ReiAttack3, "FrnD17(FR)ATTACK3");
		RegisterUpgrade(&Upg.ReiAttack4, "FrnD17(FR)ATTACK4");
		RegisterUpgrade(&Upg.ReiAttack5, "FrnD17(FR)ATTACK5");
		RegisterUpgrade(&Upg.ReiAttack6, "FrnD17(FR)ATTACK6");
		RegisterUpgrade(&Upg.ReiAttack7, "FrnD17(FR)ATTACK7");
		
		RegisterUpgrade(&Upg.ReiProtect, "FrnD17(FR)SHIELD");
		RegisterUpgrade(&Upg.ReiProtect3, "FrnD17(FR)SHIELD3");
		RegisterUpgrade(&Upg.ReiProtect4, "FrnD17(FR)SHIELD4");
		RegisterUpgrade(&Upg.ReiProtect5, "FrnD17(FR)SHIELD5");
		RegisterUpgrade(&Upg.ReiProtect6, "FrnD17(FR)SHIELD6");
		RegisterUpgrade(&Upg.ReiProtect7, "FrnD17(FR)SHIELD7");
	}

	// S15
	{
		RegisterUpgrade(&Upg.S15Attack, "FrnS15(FR)ATTACK");
		RegisterUpgrade(&Upg.S15Attack3, "FrnS15(FR)ATTACK3");
		RegisterUpgrade(&Upg.S15Attack4, "FrnS15(FR)ATTACK4");
		RegisterUpgrade(&Upg.S15Attack5, "FrnS15(FR)ATTACK5");
		RegisterUpgrade(&Upg.S15Attack6, "FrnS15(FR)ATTACK6");
		RegisterUpgrade(&Upg.S15Attack7, "FrnS15(FR)ATTACK7");
		
		RegisterUpgrade(&Upg.S15Protect, "FrnS15(FR)SHIELD");
		RegisterUpgrade(&Upg.S15Protect3, "FrnS15(FR)SHIELD3");
		RegisterUpgrade(&Upg.S15Protect4, "FrnS15(FR)SHIELD4");
		RegisterUpgrade(&Upg.S15Protect5, "FrnS15(FR)SHIELD5");
		RegisterUpgrade(&Upg.S15Protect6, "FrnS15(FR)SHIELD6");
		RegisterUpgrade(&Upg.S15Protect7, "FrnS15(FR)SHIELD7");
	}

	// Mus
	{
		RegisterUpgrade(&Upg.MusAttack, "FrnS17(FR)ATTACK");
		RegisterUpgrade(&Upg.MusAttack3, "FrnS17(FR)ATTACK3");
		RegisterUpgrade(&Upg.MusAttack4, "FrnS17(FR)ATTACK4");
		RegisterUpgrade(&Upg.MusAttack5, "FrnS17(FR)ATTACK5");
		RegisterUpgrade(&Upg.MusAttack6, "FrnS17(FR)ATTACK6");
		RegisterUpgrade(&Upg.MusAttack7, "FrnS17(FR)ATTACK7");
		
		RegisterUpgrade(&Upg.MusProtect, "FrnS17(FR)SHIELD");
		RegisterUpgrade(&Upg.MusProtect3, "FrnS17(FR)SHIELD3");
		RegisterUpgrade(&Upg.MusProtect4, "FrnS17(FR)SHIELD4");
		RegisterUpgrade(&Upg.MusProtect5, "FrnS17(FR)SHIELD5");
		RegisterUpgrade(&Upg.MusProtect6, "FrnS17(FR)SHIELD6");
		RegisterUpgrade(&Upg.MusProtect7, "FrnS17(FR)SHIELD7");
	}

	// S18
	{
		RegisterUpgrade(&Upg.S18Build1, "CEN61SP");
		RegisterUpgrade(&Upg.S18Build2, "CEN62SP");
		RegisterUpgrade(&Upg.S18Build3, "CEN63SP");

		RegisterUpgrade(&Upg.S18Attack, "FrnM18(FR)ATTACK");
		RegisterUpgrade(&Upg.S18Attack3, "FrnM18(FR)ATTACK3");
		RegisterUpgrade(&Upg.S18Attack4, "FrnM18(FR)ATTACK4");
		RegisterUpgrade(&Upg.S18Attack5, "FrnM18(FR)ATTACK5");
		RegisterUpgrade(&Upg.S18Attack6, "FrnM18(FR)ATTACK6");
		RegisterUpgrade(&Upg.S18Attack7, "FrnM18(FR)ATTACK7");

		RegisterUpgrade(&Upg.S18Protect, "FrnM18(FR)SHIELD");
		RegisterUpgrade(&Upg.S18Protect3, "FrnM18(FR)SHIELD3");
		RegisterUpgrade(&Upg.S18Protect4, "FrnM18(FR)SHIELD4");
		RegisterUpgrade(&Upg.S18Protect5, "FrnM18(FR)SHIELD5");
		RegisterUpgrade(&Upg.S18Protect6, "FrnM18(FR)SHIELD6");
		RegisterUpgrade(&Upg.S18Protect7, "FrnM18(FR)SHIELD7");
	}

	// Officers
	{
		RegisterUpgrade(&Upg.B17Protect, "FrnB17(FR)SHIELD7");
		RegisterUpgrade(&Upg.O17Damage, "FrnOf17(FR)ATTACK7");
		RegisterUpgrade(&Upg.O17Protect, "FrnOf17(FR)SHIELD7");
		RegisterUpgrade(&Upg.F17Protect, "FrnF17(FR)SHIELD7");
	}

	//NEW STUFF 

	//Artileri
	RegisterUpgrade(&Upg.ARTROF1, "CEN03FR");
	RegisterUpgrade(&Upg.ARTROF2, "CEN04FR");
	RegisterUpgrade(&Upg.ARTRNG1, "CEN42FR");
	RegisterUpgrade(&Upg.ARTRNG2, "CEN43FR");
	RegisterUpgrade(&Upg.ARTACC1, "CEN02FR");
	RegisterUpgrade(&Upg.ARTACC2, "CEN06FR");

	//Fortress Upgrade
	RegisterUpgrade(&Upg.Kr8_Stage1, "VSEDIBILI1(FR)");
	RegisterUpgrade(&Upg.Kr8_Stage2, "VSEDIBILI2(FR)");
	RegisterUpgrade(&Upg.Kr8_Stage3, "VSEDIBILI3(FR)");

	//Mine 
	RegisterUpgrade(&Upg.Iro4, "SpnRudIr(FR)INSIDE5");
	RegisterUpgrade(&Upg.Iro5, "SpnRudIr(FR)INSIDE6");
	RegisterUpgrade(&Upg.Coa4, "SpnRudCo(FR)INSIDE5");
	RegisterUpgrade(&Upg.Coa5, "SpnRudCo(FR)INSIDE6");

	//Town Hall
	RegisterUpgrade(&Upg.LogDef, "CEN54FR");
	RegisterUpgrade(&Upg.FindGeo, "CEN21FR");
	RegisterUpgrade(&Upg.Horse17Build, "CEN39FR");
	RegisterUpgrade(&Upg.Horse18Build, "CEN40FR");
	RegisterUpgrade(&Upg.HorseAllBuild, "CEN41FR");
	RegisterUpgrade(&Upg.S15Build1, "CEN33FR");
	RegisterUpgrade(&Upg.S15Build2, "CEN34FR");
	RegisterUpgrade(&Upg.S15Build3, "CEN35FR");
	RegisterUpgrade(&Upg.S17Build1, "CEN60FR");
	RegisterUpgrade(&Upg.S18Unlock, "CEN50FRA");
	RegisterUpgrade(&Upg.S18RifFire, "CEN44FR");
	RegisterUpgrade(&Upg.S18FusFire, "CEN51FRA");
	RegisterUpgrade(&Upg.S18Firepower, "CEN46FR");

	//Combat Upg
	RegisterUpgrade(&Upg.B18Protect, "UsaB18(FR)SHIELD7");
	RegisterUpgrade(&Upg.O18Damage, "UsaOf18(FR)ATTACK7");
	RegisterUpgrade(&Upg.O18Protect, "UsaOf18(FR)SHIELD7");
	RegisterUpgrade(&Upg.F18Protect, "UsaF18(FR)SHIELD7");

	//RegisterUpgrade(&Upg., "");
}

FraNation Fra;