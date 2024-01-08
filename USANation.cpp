#include "UsaNation.h"

USANation::USANation() {
	
	// Units
	// Infantry
	RegisterUnitType(&Unit.Pik, "EngPik(US)");
	RegisterUnitType(&Unit.S15, "SpnS15(US)");
	RegisterUnitType(&Unit.S17, "EngMus(US)");
	RegisterUnitType(&Unit.S18, "UsaM18(US)");
	RegisterUnitType(&Unit.Mil, "UsaMil(US)");

	RegisterUnitType(&Unit.O17, "EngOf17(US)");
	RegisterUnitType(&Unit.O18, "UsaOf18(US)");
	RegisterUnitType(&Unit.B17, "EngB17(US)");
	RegisterUnitType(&Unit.B18, "UsaB18(US)");
	RegisterUnitType(&Unit.F17, "EngF17(US)");
	RegisterUnitType(&Unit.F18, "UsaF18(US)");

	//Horses
	RegisterUnitType(&Unit.Rei, "EngD17(US)");
	RegisterUnitType(&Unit.DO17, "EngKOf17(US)");
	RegisterUnitType(&Unit.D18, "UsaD18(US)");
	RegisterUnitType(&Unit.DO18, "UsaKOf18(US)");
	RegisterUnitType(&Unit.DF18, "UsaKF18(US)");

	//Ships
	RegisterUnitType(&Unit.Lodka, "ShpLodka(US)");
	RegisterUnitType(&Unit.Parom, "ShpParom(US)");
	RegisterUnitType(&Unit.Pinta, "ShpPinta(US)");
	RegisterUnitType(&Unit.Santa, "ShpSanta(US)");
	RegisterUnitType(&Unit.Fregat, "ShpFregat(US)");

	//Rest
	RegisterUnitType(&Unit.Kri, "EngKri(US)"); //Pesant
	RegisterUnitType(&Unit.Tap, "EngTap(US)"); //Hunter
	RegisterUnitType(&Unit.Sha, "SpnSha(US)"); //Priest
	RegisterUnitType(&Unit.Can, "ArtPus(US)");

	//RegisterUnitType(&Unit., "");
	
	// Buildings

	// Mine
	{
		RegisterUnitType(&Build.Rud, "SpnRud(US)");
		RegisterUnitType(&Build.Iro, "SpnIro(US)");
		RegisterUnitType(&Build.Coa, "SpnCoa(US)");
		RegisterUnitType(&Build.Stn, "SpnStn(US)");

		RegisterUpgrade(&Upg.MineEnable1, "CEN21US(US)SpnRudINS(US)ENABLE");
		RegisterUpgrade(&Upg.Geology, "CEN21US");

		RegisterUpgrade(&Upg.Gld0, "SpnRud(US)INSIDE");
		RegisterUpgrade(&Upg.Gld1, "SpnRud(US)INSIDE2");
		RegisterUpgrade(&Upg.Gld2, "SpnRud(US)INSIDE3");
		RegisterUpgrade(&Upg.Gld3, "SpnRud(US)INSIDE4");
		RegisterUpgrade(&Upg.Gld4, "SpnRud(US)INSIDE5");
		RegisterUpgrade(&Upg.Gld5, "SpnRud(US)INSIDE6");

		RegisterUpgrade(&Upg.Stn0, "SpnRudSt(US)INSIDE");
		RegisterUpgrade(&Upg.Stn1, "SpnRudSt(US)INSIDE2");
		RegisterUpgrade(&Upg.Stn2, "SpnRudSt(US)INSIDE3");
		RegisterUpgrade(&Upg.Stn3, "SpnRudSt(US)INSIDE4");
		RegisterUpgrade(&Upg.Stn4, "SpnRudSt(US)INSIDE5");
		RegisterUpgrade(&Upg.Stn5, "SpnRudSt(US)INSIDE6");

		RegisterUpgrade(&Upg.Iro0, "SpnRudIr(US)INSIDE");
		RegisterUpgrade(&Upg.Iro1, "SpnRudIr(US)INSIDE2");
		RegisterUpgrade(&Upg.Iro2, "SpnRudIr(US)INSIDE3");
		RegisterUpgrade(&Upg.Iro3, "SpnRudIr(US)INSIDE4");
		
		RegisterUpgrade(&Upg.Coa0, "SpnRudCo(US)INSIDE");
		RegisterUpgrade(&Upg.Coa1, "SpnRudCo(US)INSIDE2");
		RegisterUpgrade(&Upg.Coa2, "SpnRudCo(US)INSIDE3");
		RegisterUpgrade(&Upg.Coa3, "SpnRudCo(US)INSIDE4");
	}

	RegisterUnitType(&Build.Do1, "UsaDo1(US)");
	RegisterUnitType(&Build.Do2, "UsaDo2(US)");
	RegisterUnitType(&Build.Mel, "EngMel(US)");
	RegisterUnitType(&Build.Skl, "UsaSkl(US)");
	RegisterUnitType(&Build.Hra, "UsaHra(US)");
	RegisterUnitType(&Build.Cen, "UsaCen(US)");
	RegisterUnitType(&Build.Kr7, "EngKre(US)");
	RegisterUnitType(&Build.Kr8, "UsaKre(US)");
	RegisterUnitType(&Build.Kuz, "UsaKuz(US)");
	RegisterUnitType(&Build.Blg, "EngBlg(US)");
	RegisterUnitType(&Build.Blg2, "EngBlg2(US)");
	RegisterUnitType(&Build.Fer, "EngFer(US)");

	RegisterUnitType(&Build.Ver, "EngVer(US)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.CEN18, "CEN18US");
	RegisterUpgrade(&Upg.CEN52, "CEN52US");
	RegisterUpgrade(&Upg.CEN57, "CEN57US");
	RegisterUpgrade(&Upg.CEN55, "CEN55US");

	RegisterUpgrade(&Upg.Mel_GETRES, "EngMel(US)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "EngMel(US)GETRES2");
	RegisterUpgrade(&Upg.CEN19, "CEN19US");
	RegisterUpgrade(&Upg.CEN22, "CEN22US");
	RegisterUpgrade(&Upg.CEN23, "CEN23US");

	RegisterUpgrade(&Upg.Kr7_Stage0, "UPSTENGKRE(US)0");
	RegisterUpgrade(&Upg.Kr8_Stage0, "UPSTUSAKRE(US)0");

	RegisterUpgrade(&Upg.BldBuild1, "CEN53US");	

	RegisterUpgrade(&Upg.Do2_ENABLE, "UsaDo2(US)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56US");

	// Krepost
	{
		RegisterUpgrade(&Upg.KreBuild, "CEN25US");
	}

	// Wood
	{
		RegisterUpgrade(&Upg.Wood1, "CEN29US");
		RegisterUpgrade(&Upg.Wood2, "CEN30US");
		RegisterUpgrade(&Upg.Wood3, "CEN31US");
	}
	
	// Kri
	{
		RegisterUpgrade(&Upg.KriBuild1, "CEN24US");
		RegisterUpgrade(&Upg.KriBuild2, "CEN36US");
		RegisterUpgrade(&Upg.KriBuild3, "CEN48US");
	}

	// Pik
	{
		RegisterUpgrade(&Upg.PikBuild1, "KUZ20(US)");
		RegisterUpgrade(&Upg.PikBuild2, "CEN26US");
		RegisterUpgrade(&Upg.PikBuild3, "CEN27US");
		RegisterUpgrade(&Upg.PikBuild4, "CEN28US");

		RegisterUpgrade(&Upg.PikAttack, "EngPik(US)ATTACK");
		RegisterUpgrade(&Upg.PikAttack3, "EngPik(US)ATTACK3");
		RegisterUpgrade(&Upg.PikAttack4, "EngPik(US)ATTACK4");
		RegisterUpgrade(&Upg.PikAttack5, "EngPik(US)ATTACK5");
		RegisterUpgrade(&Upg.PikAttack6, "EngPik(US)ATTACK6");
		RegisterUpgrade(&Upg.PikAttack7, "EngPik(US)ATTACK7");

		RegisterUpgrade(&Upg.PikProtect, "EngPik(US)SHIELD");
		RegisterUpgrade(&Upg.PikProtect3, "EngPik(US)SHIELD3");
		RegisterUpgrade(&Upg.PikProtect4, "EngPik(US)SHIELD4");
		RegisterUpgrade(&Upg.PikProtect5, "EngPik(US)SHIELD5");
		RegisterUpgrade(&Upg.PikProtect6, "EngPik(US)SHIELD6");
		RegisterUpgrade(&Upg.PikProtect7, "EngPik(US)SHIELD7");
	}

	// Can
	{
		RegisterUpgrade(&Upg.CanCost, "ArtPus(US)COST");
		RegisterUpgrade(&Upg.CanCost3, "ArtPus(US)COST3");
		RegisterUpgrade(&Upg.CanCost4, "ArtPus(US)COST4");
		RegisterUpgrade(&Upg.CanCost5, "ArtPus(US)COST5");
		RegisterUpgrade(&Upg.CanCost6, "ArtPus(US)COST6");
		RegisterUpgrade(&Upg.CanCost7, "ArtPus(US)COST7");

		RegisterUpgrade(&Upg.CanBuild, "ArtPus(US)BUILD");
		RegisterUpgrade(&Upg.CanBuild3, "ArtPus(US)BUILD3");
		RegisterUpgrade(&Upg.CanBuild4, "ArtPus(US)BUILD4");
		RegisterUpgrade(&Upg.CanBuild5, "ArtPus(US)BUILD5");
		RegisterUpgrade(&Upg.CanBuild6, "ArtPus(US)BUILD6");
		RegisterUpgrade(&Upg.CanBuild7, "ArtPus(US)BUILD7");
	}
	
	// Cen
	{
		RegisterUpgrade(&Upg.ArmShield1, "CEN47US");
		RegisterUpgrade(&Upg.ArmShield2, "CEN08US");
		RegisterUpgrade(&Upg.ArmShield3, "CEN49US");
		
		RegisterUpgrade(&Upg.StrAttPause1, "CEN01US");
		
		RegisterUpgrade(&Upg.StrDamage1, "CEN45US");
		RegisterUpgrade(&Upg.StrDamage2, "CEN50USA");

		RegisterUpgrade(&Upg.BldShield1, "CEN37US");
		RegisterUpgrade(&Upg.BldShield2, "CEN47US");
	}

	// Rei
	{

		RegisterUpgrade(&Upg.ReiAttack, "EngD17(US)ATTACK");
		RegisterUpgrade(&Upg.ReiAttack3, "EngD17(US)ATTACK3");
		RegisterUpgrade(&Upg.ReiAttack4, "EngD17(US)ATTACK4");
		RegisterUpgrade(&Upg.ReiAttack5, "EngD17(US)ATTACK5");
		RegisterUpgrade(&Upg.ReiAttack6, "EngD17(US)ATTACK6");
		RegisterUpgrade(&Upg.ReiAttack7, "EngD17(US)ATTACK7");
		
		RegisterUpgrade(&Upg.ReiProtect, "EngD17(US)SHIELD");
		RegisterUpgrade(&Upg.ReiProtect3, "EngD17(US)SHIELD3");
		RegisterUpgrade(&Upg.ReiProtect4, "EngD17(US)SHIELD4");
		RegisterUpgrade(&Upg.ReiProtect5, "EngD17(US)SHIELD5");
		RegisterUpgrade(&Upg.ReiProtect6, "EngD17(US)SHIELD6");
		RegisterUpgrade(&Upg.ReiProtect7, "EngD17(US)SHIELD7");
	}

	// S15
	{
		RegisterUpgrade(&Upg.S15Attack, "SpnS15(US)ATTACK");
		RegisterUpgrade(&Upg.S15Attack3, "SpnS15(US)ATTACK3");
		RegisterUpgrade(&Upg.S15Attack4, "SpnS15(US)ATTACK4");
		RegisterUpgrade(&Upg.S15Attack5, "SpnS15(US)ATTACK5");
		RegisterUpgrade(&Upg.S15Attack6, "SpnS15(US)ATTACK6");
		RegisterUpgrade(&Upg.S15Attack7, "SpnS15(US)ATTACK7");
		
		RegisterUpgrade(&Upg.S15Protect, "SpnS15(US)SHIELD");
		RegisterUpgrade(&Upg.S15Protect3, "SpnS15(US)SHIELD3");
		RegisterUpgrade(&Upg.S15Protect4, "SpnS15(US)SHIELD4");
		RegisterUpgrade(&Upg.S15Protect5, "SpnS15(US)SHIELD5");
		RegisterUpgrade(&Upg.S15Protect6, "SpnS15(US)SHIELD6");
		RegisterUpgrade(&Upg.S15Protect7, "SpnS15(US)SHIELD7");
	}

	// Mus
	{
		RegisterUpgrade(&Upg.MusAttack, "EngMus(US)ATTACK");
		RegisterUpgrade(&Upg.MusAttack3, "EngMus(US)ATTACK3");
		RegisterUpgrade(&Upg.MusAttack4, "EngMus(US)ATTACK4");
		RegisterUpgrade(&Upg.MusAttack5, "EngMus(US)ATTACK5");
		RegisterUpgrade(&Upg.MusAttack6, "EngMus(US)ATTACK6");
		RegisterUpgrade(&Upg.MusAttack7, "EngMus(US)ATTACK7");
		
		RegisterUpgrade(&Upg.MusProtect, "EngMus(US)SHIELD");
		RegisterUpgrade(&Upg.MusProtect3, "EngMus(US)SHIELD3");
		RegisterUpgrade(&Upg.MusProtect4, "EngMus(US)SHIELD4");
		RegisterUpgrade(&Upg.MusProtect5, "EngMus(US)SHIELD5");
		RegisterUpgrade(&Upg.MusProtect6, "EngMus(US)SHIELD6");
		RegisterUpgrade(&Upg.MusProtect7, "EngMus(US)SHIELD7");
	}

	// S18
	{

		RegisterUpgrade(&Upg.S18Build1, "CEN61US");
		RegisterUpgrade(&Upg.S18Build2, "CEN62US");
		RegisterUpgrade(&Upg.S18Build3, "CEN63US");

		RegisterUpgrade(&Upg.S18Attack, "UsaM18(US)ATTACK");
		RegisterUpgrade(&Upg.S18Attack3, "UsaM18(US)ATTACK3");
		RegisterUpgrade(&Upg.S18Attack4, "UsaM18(US)ATTACK4");
		RegisterUpgrade(&Upg.S18Attack5, "UsaM18(US)ATTACK5");
		RegisterUpgrade(&Upg.S18Attack6, "UsaM18(US)ATTACK6");
		RegisterUpgrade(&Upg.S18Attack7, "UsaM18(US)ATTACK7");

		RegisterUpgrade(&Upg.S18Protect, "UsaM18(US)SHIELD");
		RegisterUpgrade(&Upg.S18Protect3, "UsaM18(US)SHIELD3");
		RegisterUpgrade(&Upg.S18Protect4, "UsaM18(US)SHIELD4");
		RegisterUpgrade(&Upg.S18Protect5, "UsaM18(US)SHIELD5");
		RegisterUpgrade(&Upg.S18Protect6, "UsaM18(US)SHIELD6");
		RegisterUpgrade(&Upg.S18Protect7, "UsaM18(US)SHIELD7");
	}

	// Officers
	{
		RegisterUpgrade(&Upg.B17Protect, "EngB17(US)SHIELD7");
		RegisterUpgrade(&Upg.O17Damage, "EngOf17(US)ATTACK7");
		RegisterUpgrade(&Upg.O17Protect, "EngOf17(US)SHIELD7");
		RegisterUpgrade(&Upg.F17Protect, "EngF17(US)SHIELD7");
	}
	//RegisterUpgrade(&Upg., "");

	//NEW STUFF 
	// 
	//Artileri
	RegisterUpgrade(&Upg.ARTROF1,"CEN03US");
	RegisterUpgrade(&Upg.ARTROF2,"CEN04US");
	RegisterUpgrade(&Upg.ARTRNG1,"CEN42US");
	RegisterUpgrade(&Upg.ARTRNG2,"CEN43US");
	RegisterUpgrade(&Upg.ARTACC1,"CEN02US");
	RegisterUpgrade(&Upg.ARTACC2,"CEN06US");
	
	//Fortress Upgrade
	RegisterUpgrade(&Upg.Kr8_Stage1,"VSEDIBILI1(US)");
	RegisterUpgrade(&Upg.Kr8_Stage2, "VSEDIBILI2(US)");
	RegisterUpgrade(&Upg.Kr8_Stage3, "VSEDIBILI3(US)");

	//Mine
	RegisterUpgrade(&Upg.Iro4, "SpnRudIr(US)INSIDE5");
	RegisterUpgrade(&Upg.Iro5, "SpnRudIr(US)INSIDE6");
	RegisterUpgrade(&Upg.Coa4, "SpnRudCo(US)INSIDE5");
	RegisterUpgrade(&Upg.Coa5, "SpnRudCo(US)INSIDE6");

	//Town Hall
	RegisterUpgrade(&Upg.LogDef, "CEN54US");
	RegisterUpgrade(&Upg.FindGeo, "CEN21US");
	RegisterUpgrade(&Upg.Horse17Build, "CEN39US");
	RegisterUpgrade(&Upg.Horse18Build, "CEN40US");
	RegisterUpgrade(&Upg.HorseAllBuild, "CEN41US");
	RegisterUpgrade(&Upg.S15Build1, "CEN33US");
	RegisterUpgrade(&Upg.S15Build2, "CEN34US");
	RegisterUpgrade(&Upg.S15Build3, "CEN35US");
	RegisterUpgrade(&Upg.S17Build1, "CEN60US");
	RegisterUpgrade(&Upg.S18Unlock, "CEN50USA");
	RegisterUpgrade(&Upg.S18RifFire, "CEN44US");
	RegisterUpgrade(&Upg.S18FusFire, "CEN51USA");
	RegisterUpgrade(&Upg.S18Firepower, "CEN46US");

	//Combat Upg
	RegisterUpgrade(&Upg.B18Protect, "UsaB18(US)SHIELD7");
	RegisterUpgrade(&Upg.O18Damage, "UsaOf18(US)ATTACK7");
	RegisterUpgrade(&Upg.O18Protect, "UsaOf18(US)SHIELD7");
	RegisterUpgrade(&Upg.F18Protect, "UsaF18(US)SHIELD7");
}

USANation USA;