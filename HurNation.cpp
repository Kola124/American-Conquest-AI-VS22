#include "HurNation.h"

HurNation::HurNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "DelKri(HU)");
	RegisterUnitType(&Unit.Tam, "IroTam(HU)");
	RegisterUnitType(&Unit.Lut, "HurLut(HU)");	
	RegisterUnitType(&Unit.Sha, "HurSha(HU)");
	RegisterUnitType(&Unit.S15, "HurS15(HU)");
	RegisterUnitType(&Unit.Vog, "HurVog(HU)");	
	RegisterUnitType(&Unit.Vsd, "PueVsd(HU)"); // vsadnik	
	{
		RegisterUnitType(&Unit.Ka1, "ShpKanoe1(HU)");
		RegisterUnitType(&Unit.Ka3, "ShpKanoe3(HU)");
		RegisterUnitType(&Unit.Par, "ShpParom(HU)");
	}
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Do1, "HurDo1(HU)");
	RegisterUnitType(&Build.Do2, "HurDo2(HU)");
	RegisterUnitType(&Build.Mel, "IroMel(HU)");
	RegisterUnitType(&Build.Skl, "IroSkl(HU)");
	RegisterUnitType(&Build.Hra, "HurHra(HU)");
	RegisterUnitType(&Build.Cen, "HurCen(HU)");
	RegisterUnitType(&Build.Kre, "SiuKre(HU)");
	RegisterUnitType(&Build.Pst, "SiuPst(HU)");
	RegisterUnitType(&Build.Kaz, "HurKaz(HU)");
	RegisterUnitType(&Build.Ver, "IroVer(HU)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades

	// Food
	RegisterUpgrade(&Upg.CEN01, "CEN01HU");
	RegisterUpgrade(&Upg.CEN02, "CEN02HU");
	RegisterUpgrade(&Upg.CEN03, "CEN03HU");
	RegisterUpgrade(&Upg.CEN10, "CEN10HU");	
	RegisterUpgrade(&Upg.Mel_GETRES, "IroMel(HU)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "IroMel(HU)GETRES2");
	RegisterUpgrade(&Upg.CEN52, "Hur52HU");
	RegisterUpgrade(&Upg.CEN12, "CEN12HU");

	// Wood
	RegisterUpgrade(&Upg.Wood1, "CEN29HU");
	RegisterUpgrade(&Upg.Wood2, "CEN30HU");	

	//
	RegisterUpgrade(&Upg.Do2_ENABLE, "HurDo2(HU)ENABLE");
	
	// Horces
	{
		RegisterUpgrade(&Upg.EnVsd, "SIUKRE(HU)ENABLE");
		// attack
		RegisterUpgrade(&Upg.VsdAtt, "PueVsd(HU)ATTACK");
		RegisterUpgrade(&Upg.VsdAtt3, "PueVsd(HU)ATTACK3");
		RegisterUpgrade(&Upg.VsdAtt4, "PueVsd(HU)ATTACK4");
		RegisterUpgrade(&Upg.VsdAtt5, "PueVsd(HU)ATTACK5");
		RegisterUpgrade(&Upg.VsdAtt6, "PueVsd(HU)ATTACK6");
		RegisterUpgrade(&Upg.VsdAtt7, "PueVsd(HU)ATTACK7");
		// deffence
		RegisterUpgrade(&Upg.VsdDef, "PueVsd(HU)SHIELD");
		RegisterUpgrade(&Upg.VsdDef3, "PueVsd(HU)SHIELD3");
		RegisterUpgrade(&Upg.VsdDef4, "PueVsd(HU)SHIELD4");
		RegisterUpgrade(&Upg.VsdDef5, "PueVsd(HU)SHIELD5");
		RegisterUpgrade(&Upg.VsdDef6, "PueVsd(HU)SHIELD6");
		RegisterUpgrade(&Upg.VsdDef7, "PueVsd(HU)SHIELD7");
	}
	// Peasant
	{
		// produce speed
		RegisterUpgrade(&Upg.KriBuildSpeed1, "CEN09HU");
		RegisterUpgrade(&Upg.KriBuildSpeed2, "CEN08HU");
		// life
		RegisterUpgrade(&Upg.KriIR, "CEN60HU");
		RegisterUpgrade(&Upg.KriIR3, "CEN60HU3");
		RegisterUpgrade(&Upg.KriIR4, "CEN60HU4");
		RegisterUpgrade(&Upg.KriIR5, "CEN60HU5");
		RegisterUpgrade(&Upg.KriIR6, "CEN60HU6");
		RegisterUpgrade(&Upg.KriIR7, "CEN60HU7");
		// attack
		RegisterUpgrade(&Upg.KriAtt, "DelKri(HU)ATTACK");
		RegisterUpgrade(&Upg.KriAtt3, "DelKri(HU)ATTACK3");
		RegisterUpgrade(&Upg.KriAtt4, "DelKri(HU)ATTACK4");
		RegisterUpgrade(&Upg.KriAtt5, "DelKri(HU)ATTACK5");
		RegisterUpgrade(&Upg.KriAtt6, "DelKri(HU)ATTACK6");
		RegisterUpgrade(&Upg.KriAtt7, "DelKri(HU)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.KriDef, "DelKri(HU)SHIELD");
		RegisterUpgrade(&Upg.KriDef3, "DelKri(HU)SHIELD3");
		RegisterUpgrade(&Upg.KriDef4, "DelKri(HU)SHIELD4");
		RegisterUpgrade(&Upg.KriDef5, "DelKri(HU)SHIELD5");
		RegisterUpgrade(&Upg.KriDef6, "DelKri(HU)SHIELD6");
		RegisterUpgrade(&Upg.KriDef7, "DelKri(HU)SHIELD7");
	}
	// Tam
	{
		RegisterUpgrade(&Upg.EnTam, "IroTam(HU)ENABLE");
		RegisterUpgrade(&Upg.TamStrike1, "CEN58HU");
		// attack
		RegisterUpgrade(&Upg.TamAtt, "IroTam(HU)ATTACK");
		RegisterUpgrade(&Upg.TamAtt3, "IroTam(HU)ATTACK3");
		RegisterUpgrade(&Upg.TamAtt4, "IroTam(HU)ATTACK4");
		RegisterUpgrade(&Upg.TamAtt5, "IroTam(HU)ATTACK5");
		RegisterUpgrade(&Upg.TamAtt6, "IroTam(HU)ATTACK6");
		RegisterUpgrade(&Upg.TamAtt7, "IroTam(HU)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.TamDef, "IroTam(HU)SHIELD");
		RegisterUpgrade(&Upg.TamDef3, "IroTam(HU)SHIELD3");
		RegisterUpgrade(&Upg.TamDef4, "IroTam(HU)SHIELD4");
		RegisterUpgrade(&Upg.TamDef5, "IroTam(HU)SHIELD5");
		RegisterUpgrade(&Upg.TamDef6, "IroTam(HU)SHIELD6");
		RegisterUpgrade(&Upg.TamDef7, "IroTam(HU)SHIELD7");
	}	
	// Lut
	{
		RegisterUpgrade(&Upg.EnLut, "HurLut(HU)ENABLE");	
		// precision
		RegisterUpgrade(&Upg.LutPerc1, "HurKaz(HU)RAZBROS");
		RegisterUpgrade(&Upg.LutPerc2, "HurKaz(HU)RAZBROS1");
		// more life
		RegisterUpgrade(&Upg.LutLife1, "CEN61HU");
		// attack
		RegisterUpgrade(&Upg.LutAtt, "HurLut(HU)ATTACK");
		RegisterUpgrade(&Upg.LutAtt3, "HurLut(HU)ATTACK3");
		RegisterUpgrade(&Upg.LutAtt4, "HurLut(HU)ATTACK4");
		RegisterUpgrade(&Upg.LutAtt5, "HurLut(HU)ATTACK5");
		RegisterUpgrade(&Upg.LutAtt6, "HurLut(HU)ATTACK6");
		RegisterUpgrade(&Upg.LutAtt7, "HurLut(HU)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.LutDef, "HurLut(HU)SHIELD");
		RegisterUpgrade(&Upg.LutDef3, "HurLut(HU)SHIELD3");
		RegisterUpgrade(&Upg.LutDef4, "HurLut(HU)SHIELD4");
		RegisterUpgrade(&Upg.LutDef5, "HurLut(HU)SHIELD5");
		RegisterUpgrade(&Upg.LutDef6, "HurLut(HU)SHIELD6");
		RegisterUpgrade(&Upg.LutDef7, "HurLut(HU)SHIELD7");
	}
	// Str
	{
		RegisterUpgrade(&Upg.EnStr, "HurS15(HU)ENABLE");
		// attack
		RegisterUpgrade(&Upg.StrAtt, "HurS15(HU)ATTACK");
		RegisterUpgrade(&Upg.StrAtt3, "HurS15(HU)ATTACK3");
		RegisterUpgrade(&Upg.StrAtt4, "HurS15(HU)ATTACK4");
		RegisterUpgrade(&Upg.StrAtt5, "HurS15(HU)ATTACK5");
		RegisterUpgrade(&Upg.StrAtt6, "HurS15(HU)ATTACK6");
		RegisterUpgrade(&Upg.StrAtt7, "HurS15(HU)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.StrDef, "HurLut(HU)SHIELD");
		RegisterUpgrade(&Upg.StrDef3, "HurLut(HU)SHIELD3");
		RegisterUpgrade(&Upg.StrDef4, "HurLut(HU)SHIELD4");
		RegisterUpgrade(&Upg.StrDef5, "HurLut(HU)SHIELD5");
		RegisterUpgrade(&Upg.StrDef6, "HurLut(HU)SHIELD6");
		RegisterUpgrade(&Upg.StrDef7, "HurLut(HU)SHIELD7");
	}	
	// Vog
	{
		RegisterUpgrade(&Upg.EnVog, "HurVog(HU)ENABLE");
	}
	// Sha
	{
		RegisterUpgrade(&Upg.ShaBuild1,"CEN13HU");
		RegisterUpgrade(&Upg.ShaMedic1,"CEN14HU");
		RegisterUpgrade(&Upg.ShaLife1,"CEN15HU");
	}

	// Parom
	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102HU");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103HU");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104HU");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105HU");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106HU");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107HU");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96HU");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97HU");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98HU");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99HU");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100HU");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101HU");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90HU");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91HU");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92HU");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93HU");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94HU");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95HU");
	}

}

HurNation Hur;