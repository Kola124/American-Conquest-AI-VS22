#include "DelNation.h"

DelNation::DelNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "DelKri(DE)");
	RegisterUnitType(&Unit.Lut, "DelLut(DE)");	
	RegisterUnitType(&Unit.Pik, "DelPik(DE)");	
	RegisterUnitType(&Unit.Sha, "DelSha(DE)");
	RegisterUnitType(&Unit.S15, "DelS15(DE)");
	RegisterUnitType(&Unit.Vog, "DelVog(DE)");	
	RegisterUnitType(&Unit.Vsd, "PueVsd(DE)"); // vsadnik
	
	RegisterUnitType(&Unit.Ka1, "ShpKanoe1(DE)");
	RegisterUnitType(&Unit.Ka3, "ShpKanoe3(DE)");
	RegisterUnitType(&Unit.Par, "ShpParom(DE)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Do1, "DelDo1(DE)");
	RegisterUnitType(&Build.Do2, "DelDo2(DE)");
	RegisterUnitType(&Build.Mel, "IroMel(DE)");
	RegisterUnitType(&Build.Skl, "IroSkl(DE)");
	RegisterUnitType(&Build.Hra, "DelHra(DE)");
	RegisterUnitType(&Build.Cen, "DelCen(DE)");
	RegisterUnitType(&Build.Kre, "SiuKre(DE)");
	RegisterUnitType(&Build.Pst, "SiuPst(DE)");
	RegisterUnitType(&Build.Kaz, "DelKaz(DE)");
	RegisterUnitType(&Build.Ver, "IroVer(DE)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.Mel_GETRES, "IroMel(DE)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "IroMel(DE)GETRES2");
	RegisterUpgrade(&Upg.CEN10, "CEN10DE");
	RegisterUpgrade(&Upg.CEN12, "CEN12DE");
	RegisterUpgrade(&Upg.FOOD52, "Del52DE");
	RegisterUpgrade(&Upg.CEN01, "CEN01DE");
	RegisterUpgrade(&Upg.CEN02, "CEN02DE");
	RegisterUpgrade(&Upg.CEN03, "CEN03DE");
	
	RegisterUpgrade(&Upg.EnDo2, "DelDo2(DE)ENABLE");
	RegisterUpgrade(&Upg.EnKre, "SIUKRE(DE)ENABLE");

	// Wood
	RegisterUpgrade(&Upg.Wood1, "CEN29DE");
	RegisterUpgrade(&Upg.Wood2, "CEN30DE");	

	RegisterUpgrade(&Upg.EnS15, "DelS15(DE)ENABLE");
	RegisterUpgrade(&Upg.EnVog, "DelVog(DE)ENABLE");
	RegisterUpgrade(&Upg.EnLut, "DelLut(DE)ENABLE");

	// Kri
	{
		RegisterUpgrade(&Upg.KriBu1, "CEN09DE");
		RegisterUpgrade(&Upg.KriBu2, "CEN08DE");
	}

	// Warriors

	// Pik
	{
		RegisterUpgrade(&Upg.PikLife1, "CEN58DE"); //MORELIFE +1000%

		RegisterUpgrade(&Upg.PikA2, "DelPik(DE)ATTACK");
		RegisterUpgrade(&Upg.PikA3, "DelPik(DE)ATTACK3");
		RegisterUpgrade(&Upg.PikA4, "DelPik(DE)ATTACK4");
		RegisterUpgrade(&Upg.PikA5, "DelPik(DE)ATTACK5");
		RegisterUpgrade(&Upg.PikA6, "DelPik(DE)ATTACK6");
		RegisterUpgrade(&Upg.PikA7, "DelPik(DE)ATTACK7");
		RegisterUpgrade(&Upg.PikS2, "DelPik(DE)SHIELD");
		RegisterUpgrade(&Upg.PikS3, "DelPik(DE)SHIELD3");
		RegisterUpgrade(&Upg.PikS4, "DelPik(DE)SHIELD4");
		RegisterUpgrade(&Upg.PikS5, "DelPik(DE)SHIELD5");
		RegisterUpgrade(&Upg.PikS6, "DelPik(DE)SHIELD6");
		RegisterUpgrade(&Upg.PikS7, "DelPik(DE)SHIELD7");
	}
	
	// Lut
	{
		RegisterUpgrade(&Upg.LutRaz1, "DelKaz(DE)RAZBROS");
		RegisterUpgrade(&Upg.LutRaz2, "DelKaz(DE)RAZBROS1");
		RegisterUpgrade(&Upg.LutStrike1, "CEN61DE"); //DAMAGE +5

		RegisterUpgrade(&Upg.LutA2, "DelLut(DE)ATTACK");
		RegisterUpgrade(&Upg.LutA3, "DelLut(DE)ATTACK3");
		RegisterUpgrade(&Upg.LutA4, "DelLut(DE)ATTACK4");
		RegisterUpgrade(&Upg.LutA5, "DelLut(DE)ATTACK5");
		RegisterUpgrade(&Upg.LutA6, "DelLut(DE)ATTACK6");
		RegisterUpgrade(&Upg.LutA7, "DelLut(DE)ATTACK7");

		RegisterUpgrade(&Upg.LutS2, "DelLut(DE)SHIELD");
		RegisterUpgrade(&Upg.LutS3, "DelLut(DE)SHIELD3");
		RegisterUpgrade(&Upg.LutS4, "DelLut(DE)SHIELD4");
		RegisterUpgrade(&Upg.LutS5, "DelLut(DE)SHIELD5");
		RegisterUpgrade(&Upg.LutS6, "DelLut(DE)SHIELD6");
		RegisterUpgrade(&Upg.LutS7, "DelLut(DE)SHIELD7");
	}

	// Str
	{
		RegisterUpgrade(&Upg.EnStr, "DelS15(DE)ENABLE");
		// attack
		RegisterUpgrade(&Upg.StrAtt, "DelS15(DE)ATTACK");
		RegisterUpgrade(&Upg.StrAtt3, "DelS15(DE)ATTACK3");
		RegisterUpgrade(&Upg.StrAtt4, "DelS15(DE)ATTACK4");
		RegisterUpgrade(&Upg.StrAtt5, "DelS15(DE)ATTACK5");
		RegisterUpgrade(&Upg.StrAtt6, "DelS15(DE)ATTACK6");
		RegisterUpgrade(&Upg.StrAtt7, "DelS15(DE)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.StrDef, "DelLut(DE)SHIELD");
		RegisterUpgrade(&Upg.StrDef3, "DelLut(DE)SHIELD3");
		RegisterUpgrade(&Upg.StrDef4, "DelLut(DE)SHIELD4");
		RegisterUpgrade(&Upg.StrDef5, "DelLut(DE)SHIELD5");
		RegisterUpgrade(&Upg.StrDef6, "DelLut(DE)SHIELD6");
		RegisterUpgrade(&Upg.StrDef7, "DelLut(DE)SHIELD7");
	}	

	// Sha
	{
		RegisterUpgrade(&Upg.ShaBuild1,"CEN13DE");
		RegisterUpgrade(&Upg.ShaMedic1,"CEN14DE");
		RegisterUpgrade(&Upg.ShaLife1,"CEN15DE");
	}

	// Horces
	{
		RegisterUpgrade(&Upg.EnVsd, "SIUKRE(DE)ENABLE");
		// attack
		RegisterUpgrade(&Upg.VsdAtt, "PueVsd(DE)ATTACK");
		RegisterUpgrade(&Upg.VsdAtt3, "PueVsd(DE)ATTACK3");
		RegisterUpgrade(&Upg.VsdAtt4, "PueVsd(DE)ATTACK4");
		RegisterUpgrade(&Upg.VsdAtt5, "PueVsd(DE)ATTACK5");
		RegisterUpgrade(&Upg.VsdAtt6, "PueVsd(DE)ATTACK6");
		RegisterUpgrade(&Upg.VsdAtt7, "PueVsd(DE)ATTACK7");
		// deffence
		RegisterUpgrade(&Upg.VsdDef, "PueVsd(DE)SHIELD");
		RegisterUpgrade(&Upg.VsdDef3, "PueVsd(DE)SHIELD3");
		RegisterUpgrade(&Upg.VsdDef4, "PueVsd(DE)SHIELD4");
		RegisterUpgrade(&Upg.VsdDef5, "PueVsd(DE)SHIELD5");
		RegisterUpgrade(&Upg.VsdDef6, "PueVsd(DE)SHIELD6");
		RegisterUpgrade(&Upg.VsdDef7, "PueVsd(DE)SHIELD7");
	}

	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102DE");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103DE");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104DE");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105DE");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106DE");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107DE");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96DE");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97DE");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98DE");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99DE");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100DE");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101DE");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90DE");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91DE");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92DE");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93DE");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94DE");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95DE");
	}
	//RegisterUpgrade(&Upg., "");
}

DelNation Del;