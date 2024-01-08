#include "SiuNation.h"

SiuNation::SiuNation() {
	
	// Units	
	RegisterUnitType(&Unit.KPik, "SiuKPik(SI)");
	RegisterUnitType(&Unit.KLut, "SiuKLut(SI)");
	RegisterUnitType(&Unit.KVog, "SiuKVog(SI)");
	RegisterUnitType(&Unit.KStr, "SiuKStr(SI)");
	RegisterUnitType(&Unit.Kri, "SiuKri(SI)");
	RegisterUnitType(&Unit.Lut, "SiuLut(SI)");	
	RegisterUnitType(&Unit.Sha, "DelSha(SI)");
	{
		RegisterUnitType(&Unit.Ka1, "ShpKanoe1(SI)");
		RegisterUnitType(&Unit.Ka3, "ShpKanoe3(SI)");
		RegisterUnitType(&Unit.Par, "ShpParom(SI)");
	}
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Do1, "SiuDo1(SI)");
	RegisterUnitType(&Build.Do2, "SiuDo2(SI)");
	RegisterUnitType(&Build.Mel, "SiuMel(SI)");
	RegisterUnitType(&Build.Skl, "IroSkl(SI)");
	RegisterUnitType(&Build.Hra, "SiuHra(SI)");
	RegisterUnitType(&Build.Cen, "SiuCen(SI)");
	RegisterUnitType(&Build.Kre, "SiuKre(SI)");
	RegisterUnitType(&Build.Pst, "SiuPst(SI)");
	RegisterUnitType(&Build.Ver, "IroVer(SI)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.CEN01, "CEN01SI");
	RegisterUpgrade(&Upg.CEN02, "CEN02SI");
	RegisterUpgrade(&Upg.CEN03, "CEN03SI");
	
	RegisterUpgrade(&Upg.Do2_ENABLE, "SiuDo2(SI)ENABLE");

	RegisterUpgrade(&Upg.Mel_GETRES, "SiuMel(SI)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "SiuMel(SI)GETRES2");

	// Wood
	RegisterUpgrade(&Upg.Wood1, "CEN30SI");	

	// Pika
	{
		RegisterUpgrade(&Upg.KPikCenDamage1, "CEN05SI");
	}

	// KPik
	{
		RegisterUpgrade(&Upg.KPikBuild1, "CEN07SI");		
		RegisterUpgrade(&Upg.KPikCenProtect1, "SiuKPikS");

		RegisterUpgrade(&Upg.KPikDamage, "SiuKPik(SI)ATTACK");
		RegisterUpgrade(&Upg.KPikDamage3, "SiuKPik(SI)ATTACK3");
		RegisterUpgrade(&Upg.KPikDamage4, "SiuKPik(SI)ATTACK4");
		RegisterUpgrade(&Upg.KPikDamage5, "SiuKPik(SI)ATTACK5");
		RegisterUpgrade(&Upg.KPikDamage6, "SiuKPik(SI)ATTACK6");
		RegisterUpgrade(&Upg.KPikDamage7, "SiuKPik(SI)ATTACK7");

		RegisterUpgrade(&Upg.KPikProtect, "SiuKPik(SI)SHIELD");
		RegisterUpgrade(&Upg.KPikProtect3, "SiuKPik(SI)SHIELD3");
		RegisterUpgrade(&Upg.KPikProtect4, "SiuKPik(SI)SHIELD4");
		RegisterUpgrade(&Upg.KPikProtect5, "SiuKPik(SI)SHIELD5");
		RegisterUpgrade(&Upg.KPikProtect6, "SiuKPik(SI)SHIELD6");
		RegisterUpgrade(&Upg.KPikProtect7, "SiuKPik(SI)SHIELD7");
	}

	// KLut
	{
		RegisterUpgrade(&Upg.KLutEnable, "VSEDEBILI(SI)0");

		RegisterUpgrade(&Upg.KLutRazbros1, "SiuKre(SI)RAZBROS");
		RegisterUpgrade(&Upg.KLutRazbros2, "SiuKre(SI)RAZBROS1");
		
		RegisterUpgrade(&Upg.KLutBuild1, "CEN70SI");
		RegisterUpgrade(&Upg.KLutBuild2, "CEN50SI");
	}

	// KStr
	{
		RegisterUpgrade(&Upg.KStrEnable, "VSEDEBILI(SI)1");
	}

	// KVog
	{
		RegisterUpgrade(&Upg.KVogEnable, "VSEDEBILI(SI)2");

		RegisterUpgrade(&Upg.KVogDamage, "SiuKVog(SI)ATTACK");
		RegisterUpgrade(&Upg.KVogDamage3, "SiuKVog(SI)ATTACK3");
		RegisterUpgrade(&Upg.KVogDamage4, "SiuKVog(SI)ATTACK4");
		RegisterUpgrade(&Upg.KVogDamage5, "SiuKVog(SI)ATTACK5");
		RegisterUpgrade(&Upg.KVogDamage7, "SiuKVog(SI)ATTACK6");
		RegisterUpgrade(&Upg.KVogDamage6, "SiuKVog(SI)ATTACK7");

		RegisterUpgrade(&Upg.KVogProtect, "SiuKVog(SI)SHIELD");
		RegisterUpgrade(&Upg.KVogProtect3, "SiuKVog(SI)SHIELD3");
		RegisterUpgrade(&Upg.KVogProtect4, "SiuKVog(SI)SHIELD4");
		RegisterUpgrade(&Upg.KVogProtect5, "SiuKVog(SI)SHIELD5");
		RegisterUpgrade(&Upg.KVogProtect6, "SiuKVog(SI)SHIELD6");
		RegisterUpgrade(&Upg.KVogProtect7, "SiuKVog(SI)SHIELD7");
	}

	// Sha
	{
		RegisterUpgrade(&Upg.ShaBuild1, "CEN13SI");
	}

	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102SI");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103SI");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104SI");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105SI");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106SI");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107SI");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96SI");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97SI");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98SI");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99SI");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100SI");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101SI");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90SI");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91SI");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92SI");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93SI");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94SI");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95SI");
	}

	//RegisterUpgrade(&Upg., "");
}

SiuNation Siu;