#include "EngNation.h"

EngNation::EngNation() {
	
	// Units	
	RegisterUnitType(&Unit.Pik, "EngPik(EN)");
	RegisterUnitType(&Unit.S15, "SpnS15(EN)");
	RegisterUnitType(&Unit.S17, "EngMus(EN)");
	RegisterUnitType(&Unit.S18, "EngM18(EN)");

	RegisterUnitType(&Unit.O17, "EngOf17(EN)");
	RegisterUnitType(&Unit.O18, "EngOf18(EN)");
	RegisterUnitType(&Unit.B17, "EngB17(EN)");
	RegisterUnitType(&Unit.B18, "EngB18(EN)");
	RegisterUnitType(&Unit.F17, "EngF17(EN)");
	RegisterUnitType(&Unit.F18, "EngF18(EN)");

	RegisterUnitType(&Unit.Rei, "EngD17(EN)");
	RegisterUnitType(&Unit.DO17, "EngKOf17(EN)");
	RegisterUnitType(&Unit.D18, "EngD18(EN)");
	RegisterUnitType(&Unit.DO18, "EngKOf18(EN)");
	RegisterUnitType(&Unit.DF18, "EngKF18(EN)");

	RegisterUnitType(&Unit.Lodka, "ShpLodka(EN)");
	RegisterUnitType(&Unit.Parom, "ShpParom(EN)");
	RegisterUnitType(&Unit.Pinta, "ShpPinta(EN)");
	RegisterUnitType(&Unit.Santa, "ShpSanta(EN)");
	RegisterUnitType(&Unit.Fregat, "ShpFregat(EN)");

	RegisterUnitType(&Unit.Kri, "EngKri(EN)");
	RegisterUnitType(&Unit.Tap, "EngTap(EN)");
	RegisterUnitType(&Unit.Sha, "SpnSha(EN)");
	RegisterUnitType(&Unit.Can, "ArtPus(EN)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings

	// Mine
	{
		RegisterUnitType(&Build.Rud, "SpnRud(EN)");
		RegisterUnitType(&Build.Iro, "SpnIro(EN)");
		RegisterUnitType(&Build.Coa, "SpnCoa(EN)");
		RegisterUnitType(&Build.Stn, "SpnStn(EN)");

		RegisterUpgrade(&Upg.MineEnable1, "CEN21EN(EN)SpnRudINS(EN)ENABLE");
		RegisterUpgrade(&Upg.Geology, "CEN21EN");

		RegisterUpgrade(&Upg.Gld0, "SpnRud(EN)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(EN)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(EN)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(EN)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(EN)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(EN)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(EN)INSIDE");	
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(EN)INSIDE2");	
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(EN)INSIDE3");	
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(EN)INSIDE4");	
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(EN)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(EN)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(EN)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(EN)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(EN)INSIDE3");
		RegisterUpgrade(&Upg.Iro3, "SpnRudIr(EN)INSIDE4");

		RegisterUpgrade(&Upg.Coa0, "SpnRudCo(EN)INSIDE");
		RegisterUpgrade(&Upg.Coa1, "SpnRudCo(EN)INSIDE2");
		RegisterUpgrade(&Upg.Coa2, "SpnRudCo(EN)INSIDE3");
		RegisterUpgrade(&Upg.Coa3, "SpnRudCo(EN)INSIDE4");
	}

	RegisterUnitType(&Build.Do1, "EngDo1(EN)");
	RegisterUnitType(&Build.Do2, "EngDo2(EN)");
	RegisterUnitType(&Build.Mel, "EngMel(EN)");
	RegisterUnitType(&Build.Skl, "EngSkl(EN)");
	RegisterUnitType(&Build.Hra, "EngHra(EN)");
	RegisterUnitType(&Build.Cen, "EngCen(EN)");
	RegisterUnitType(&Build.Kr7, "EngKre(EN)");
	RegisterUnitType(&Build.Kr8, "EngKre2(EN)");
	RegisterUnitType(&Build.Kuz, "EngKuz(EN)");
	RegisterUnitType(&Build.Blg, "EngBlg(EN)");
	RegisterUnitType(&Build.Blg2, "EngBlg2(EN)");

	RegisterUnitType(&Build.Fer, "EngFer(EN)");

	RegisterUnitType(&Build.Ver, "EngVer(EN)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.CEN18, "CEN18EN");
	RegisterUpgrade(&Upg.CEN52, "CEN52EN");
	RegisterUpgrade(&Upg.CEN57, "CEN57EN");
	RegisterUpgrade(&Upg.CEN55, "CEN55EN");

	RegisterUpgrade(&Upg.Mel_GETRES, "EngMel(EN)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "EngMel(EN)GETRES2");
	RegisterUpgrade(&Upg.CEN19, "CEN19EN");
	RegisterUpgrade(&Upg.CEN22, "CEN22EN");
	RegisterUpgrade(&Upg.CEN23, "CEN23EN");

	RegisterUpgrade(&Upg.Kr7_Stage0, "UPSTENGKRE(EN)0");
	RegisterUpgrade(&Upg.Kr8_Stage0, "UPSTENGKRE2(EN)0");

	RegisterUpgrade(&Upg.BldBuild1, "CEN53EN");	

	RegisterUpgrade(&Upg.Do2_ENABLE, "EngDo2(EN)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56EN");

	// Krepost
	{
		RegisterUpgrade(&Upg.KreBuild, "CEN25EN");
	}

	// Wood
	{
		RegisterUpgrade(&Upg.Wood1, "CEN29EN");
		RegisterUpgrade(&Upg.Wood2, "CEN30EN");
		RegisterUpgrade(&Upg.Wood3, "CEN31EN");
	}
	
	// Kri
	{
		RegisterUpgrade(&Upg.KriBuild1, "CEN24EN");
		RegisterUpgrade(&Upg.KriBuild2, "CEN36EN");
		RegisterUpgrade(&Upg.KriBuild3, "CEN48EN");
	}

	// Pik
	{
		RegisterUpgrade(&Upg.PikBuild1, "KUZ20(EN)");
		RegisterUpgrade(&Upg.PikBuild2, "CEN26EN");
		RegisterUpgrade(&Upg.PikBuild3, "CEN27EN");
		RegisterUpgrade(&Upg.PikBuild4, "CEN28EN");

		RegisterUpgrade(&Upg.PikAttack, "EngPik(EN)ATTACK");
		RegisterUpgrade(&Upg.PikAttack3, "EngPik(EN)ATTACK3");
		RegisterUpgrade(&Upg.PikAttack4, "EngPik(EN)ATTACK4");
		RegisterUpgrade(&Upg.PikAttack5, "EngPik(EN)ATTACK5");
		RegisterUpgrade(&Upg.PikAttack6, "EngPik(EN)ATTACK6");
		RegisterUpgrade(&Upg.PikAttack7, "EngPik(EN)ATTACK7");

		RegisterUpgrade(&Upg.PikProtect, "EngPik(EN)SHIELD");
		RegisterUpgrade(&Upg.PikProtect3, "EngPik(EN)SHIELD3");
		RegisterUpgrade(&Upg.PikProtect4, "EngPik(EN)SHIELD4");
		RegisterUpgrade(&Upg.PikProtect5, "EngPik(EN)SHIELD5");
		RegisterUpgrade(&Upg.PikProtect6, "EngPik(EN)SHIELD6");
		RegisterUpgrade(&Upg.PikProtect7, "EngPik(EN)SHIELD7");
	}

	// Can
	{
		RegisterUpgrade(&Upg.CanCost, "ArtPus(EN)COST");
		RegisterUpgrade(&Upg.CanCost3, "ArtPus(EN)COST3");
		RegisterUpgrade(&Upg.CanCost4, "ArtPus(EN)COST4");
		RegisterUpgrade(&Upg.CanCost5, "ArtPus(EN)COST5");
		RegisterUpgrade(&Upg.CanCost6, "ArtPus(EN)COST6");
		RegisterUpgrade(&Upg.CanCost7, "ArtPus(EN)COST7");

		RegisterUpgrade(&Upg.CanBuild, "ArtPus(EN)BUILD");
		RegisterUpgrade(&Upg.CanBuild3, "ArtPus(EN)BUILD3");
		RegisterUpgrade(&Upg.CanBuild4, "ArtPus(EN)BUILD4");
		RegisterUpgrade(&Upg.CanBuild5, "ArtPus(EN)BUILD5");
		RegisterUpgrade(&Upg.CanBuild6, "ArtPus(EN)BUILD6");
		RegisterUpgrade(&Upg.CanBuild7, "ArtPus(EN)BUILD7");
	}
	
	// Cen
	{
		RegisterUpgrade(&Upg.ArmShield1, "CEN47EN");
		RegisterUpgrade(&Upg.ArmShield2, "CEN08EN");
		RegisterUpgrade(&Upg.ArmShield3, "CEN49EN");

		RegisterUpgrade(&Upg.StrAttPause1, "CEN01EN");
		
		RegisterUpgrade(&Upg.StrDamage1, "CEN45EN");
		RegisterUpgrade(&Upg.StrDamage2, "CEN50ENA");

		RegisterUpgrade(&Upg.BldShield1, "CEN37EN");
		RegisterUpgrade(&Upg.BldShield2, "CEN47EN");
	}

	// Rei
	{

		RegisterUpgrade(&Upg.ReiAttack, "EngD17(EN)ATTACK");
		RegisterUpgrade(&Upg.ReiAttack3, "EngD17(EN)ATTACK3");
		RegisterUpgrade(&Upg.ReiAttack4, "EngD17(EN)ATTACK4");
		RegisterUpgrade(&Upg.ReiAttack5, "EngD17(EN)ATTACK5");
		RegisterUpgrade(&Upg.ReiAttack6, "EngD17(EN)ATTACK6");
		RegisterUpgrade(&Upg.ReiAttack7, "EngD17(EN)ATTACK7");
		
		RegisterUpgrade(&Upg.ReiProtect, "EngD17(EN)SHIELD");
		RegisterUpgrade(&Upg.ReiProtect3, "EngD17(EN)SHIELD3");
		RegisterUpgrade(&Upg.ReiProtect4, "EngD17(EN)SHIELD4");
		RegisterUpgrade(&Upg.ReiProtect5, "EngD17(EN)SHIELD5");
		RegisterUpgrade(&Upg.ReiProtect6, "EngD17(EN)SHIELD6");
		RegisterUpgrade(&Upg.ReiProtect7, "EngD17(EN)SHIELD7");
	}

	// S15
	{
		RegisterUpgrade(&Upg.S15Attack, "SpnS15(EN)ATTACK");
		RegisterUpgrade(&Upg.S15Attack3, "SpnS15(EN)ATTACK3");
		RegisterUpgrade(&Upg.S15Attack4, "SpnS15(EN)ATTACK4");
		RegisterUpgrade(&Upg.S15Attack5, "SpnS15(EN)ATTACK5");
		RegisterUpgrade(&Upg.S15Attack6, "SpnS15(EN)ATTACK6");
		RegisterUpgrade(&Upg.S15Attack7, "SpnS15(EN)ATTACK7");
		
		RegisterUpgrade(&Upg.S15Protect, "SpnS15(EN)SHIELD");
		RegisterUpgrade(&Upg.S15Protect3, "SpnS15(EN)SHIELD3");
		RegisterUpgrade(&Upg.S15Protect4, "SpnS15(EN)SHIELD4");
		RegisterUpgrade(&Upg.S15Protect5, "SpnS15(EN)SHIELD5");
		RegisterUpgrade(&Upg.S15Protect6, "SpnS15(EN)SHIELD6");
		RegisterUpgrade(&Upg.S15Protect7, "SpnS15(EN)SHIELD7");
	}

	// Mus
	{
		RegisterUpgrade(&Upg.MusAttack, "EngMus(EN)ATTACK");
		RegisterUpgrade(&Upg.MusAttack3, "EngMus(EN)ATTACK3");
		RegisterUpgrade(&Upg.MusAttack4, "EngMus(EN)ATTACK4");
		RegisterUpgrade(&Upg.MusAttack5, "EngMus(EN)ATTACK5");
		RegisterUpgrade(&Upg.MusAttack6, "EngMus(EN)ATTACK6");
		RegisterUpgrade(&Upg.MusAttack7, "EngMus(EN)ATTACK7");
		
		RegisterUpgrade(&Upg.MusProtect, "EngMus(EN)SHIELD");
		RegisterUpgrade(&Upg.MusProtect3, "EngMus(EN)SHIELD3");
		RegisterUpgrade(&Upg.MusProtect4, "EngMus(EN)SHIELD4");
		RegisterUpgrade(&Upg.MusProtect5, "EngMus(EN)SHIELD5");
		RegisterUpgrade(&Upg.MusProtect6, "EngMus(EN)SHIELD6");
		RegisterUpgrade(&Upg.MusProtect7, "EngMus(EN)SHIELD7");
	}

	// S18
	{
		RegisterUpgrade(&Upg.S18Build1, "CEN61EN");
		RegisterUpgrade(&Upg.S18Build2, "CEN62EN");
		RegisterUpgrade(&Upg.S18Build3, "CEN63EN");

		RegisterUpgrade(&Upg.S18Attack, "EngM18(EN)ATTACK");
		RegisterUpgrade(&Upg.S18Attack3, "EngM18(EN)ATTACK3");
		RegisterUpgrade(&Upg.S18Attack4, "EngM18(EN)ATTACK4");
		RegisterUpgrade(&Upg.S18Attack5, "EngM18(EN)ATTACK5");
		RegisterUpgrade(&Upg.S18Attack6, "EngM18(EN)ATTACK6");
		RegisterUpgrade(&Upg.S18Attack7, "EngM18(EN)ATTACK7");

		RegisterUpgrade(&Upg.S18Protect, "EngM18(EN)SHIELD");
		RegisterUpgrade(&Upg.S18Protect3, "EngM18(EN)SHIELD3");
		RegisterUpgrade(&Upg.S18Protect4, "EngM18(EN)SHIELD4");
		RegisterUpgrade(&Upg.S18Protect5, "EngM18(EN)SHIELD5");
		RegisterUpgrade(&Upg.S18Protect6, "EngM18(EN)SHIELD6");
		RegisterUpgrade(&Upg.S18Protect7, "EngM18(EN)SHIELD7");
	}

	// Officers
	{
		RegisterUpgrade(&Upg.B17Protect, "EngB17(EN)SHIELD7");
		RegisterUpgrade(&Upg.O17Damage, "EngOf17(EN)ATTACK7");
		RegisterUpgrade(&Upg.O17Protect, "EngOf17(EN)SHIELD7");
		RegisterUpgrade(&Upg.F17Protect, "EngF17(EN)SHIELD7");
	}

	//NEW STUFF 
	
	//Artileri
	RegisterUpgrade(&Upg.ARTROF1, "CEN03EN");
	RegisterUpgrade(&Upg.ARTROF2, "CEN04EN");
	RegisterUpgrade(&Upg.ARTRNG1, "CEN42EN");
	RegisterUpgrade(&Upg.ARTRNG2, "CEN43EN");
	RegisterUpgrade(&Upg.ARTACC1, "CEN02EN");
	RegisterUpgrade(&Upg.ARTACC2, "CEN06EN");

	//Fortress Upgrade
	RegisterUpgrade(&Upg.Kr8_Stage1, "VSEDIBILI1(EN)");
	RegisterUpgrade(&Upg.Kr8_Stage2, "VSEDIBILI2(EN)");
	RegisterUpgrade(&Upg.Kr8_Stage3, "VSEDIBILI3(EN)");

	//Mine 
	RegisterUpgrade(&Upg.Iro4, "SpnRudIr(EN)INSIDE5");
	RegisterUpgrade(&Upg.Iro5, "SpnRudIr(EN)INSIDE6");
	RegisterUpgrade(&Upg.Coa4, "SpnRudCo(EN)INSIDE5");
	RegisterUpgrade(&Upg.Coa5, "SpnRudCo(EN)INSIDE6");

	//Town Hall
	RegisterUpgrade(&Upg.LogDef, "CEN54EN");
	RegisterUpgrade(&Upg.FindGeo, "CEN21EN");
	RegisterUpgrade(&Upg.Horse17Build, "CEN39EN");
	RegisterUpgrade(&Upg.Horse18Build, "CEN40EN");
	RegisterUpgrade(&Upg.HorseAllBuild, "CEN41EN");
	RegisterUpgrade(&Upg.S15Build1, "CEN33EN");
	RegisterUpgrade(&Upg.S15Build2, "CEN34EN");
	RegisterUpgrade(&Upg.S15Build3, "CEN35EN");
	RegisterUpgrade(&Upg.S17Build1, "CEN60EN");
	RegisterUpgrade(&Upg.S18Unlock, "CEN50ENA");
	RegisterUpgrade(&Upg.S18RifFire, "CEN44EN");
	RegisterUpgrade(&Upg.S18FusFire, "CEN51ENA");
	RegisterUpgrade(&Upg.S18Firepower, "CEN46EN");

	//Combat Upg
	RegisterUpgrade(&Upg.B18Protect, "UsaB18(EN)SHIELD7");
	RegisterUpgrade(&Upg.O18Damage, "UsaOf18(EN)ATTACK7");
	RegisterUpgrade(&Upg.O18Protect, "UsaOf18(EN)SHIELD7");
	RegisterUpgrade(&Upg.F18Protect, "UsaF18(EN)SHIELD7");

	//RegisterUpgrade(&Upg., "");
}

EngNation Eng;