#include "IroNation.h"

IroNation::IroNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "DelKri(IR)");
	RegisterUnitType(&Unit.Tam, "IroTam(IR)");
	RegisterUnitType(&Unit.Lut, "IroLut(IR)");	
	RegisterUnitType(&Unit.Sha, "IroSha(IR)");
	RegisterUnitType(&Unit.S15, "IroStr(IR)");
	RegisterUnitType(&Unit.Vog, "IroVog(IR)");	
	RegisterUnitType(&Unit.Vsd, "PueVsd(IR)"); // vsadnik	

	RegisterUnitType(&Unit.Ka1, "ShpKanoe1(IR)");
	RegisterUnitType(&Unit.Ka3, "ShpKanoe3(IR)");
	RegisterUnitType(&Unit.Par, "ShpParom(IR)");
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Do1, "IroDo1(IR)");
	RegisterUnitType(&Build.Do2, "IroDo2(IR)");
	RegisterUnitType(&Build.Mel, "IroMel(IR)");
	RegisterUnitType(&Build.Skl, "IroSkl(IR)");
	RegisterUnitType(&Build.Hra, "IroHra(IR)");
	RegisterUnitType(&Build.Cen, "IroCen(IR)");
	RegisterUnitType(&Build.Kre, "IroKre(IR)");
	RegisterUnitType(&Build.Stb, "SiuKre(IR)");	
	RegisterUnitType(&Build.Pst, "SiuPst(IR)");
	RegisterUnitType(&Build.Ver, "IroVer(IR)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	// Food
	RegisterUpgrade(&Upg.CEN01, "CEN01IR");
	RegisterUpgrade(&Upg.CEN02, "CEN02IR");
	RegisterUpgrade(&Upg.CEN03, "CEN03IR");
	RegisterUpgrade(&Upg.CEN10, "CEN10IR");
	
	RegisterUpgrade(&Upg.Mel_GETRES, "IroMel(IR)GETRES");
	RegisterUpgrade(&Upg.Mel_GETRES2, "IroMel(IR)GETRES2");

	RegisterUpgrade(&Upg.CEN52, "IRO52IR");
	RegisterUpgrade(&Upg.CEN12, "CEN12IR");	

	// Wood
	RegisterUpgrade(&Upg.Wood1, "CEN29IR");
	RegisterUpgrade(&Upg.Wood2, "CEN30IR");	

	// Dom 2
	RegisterUpgrade(&Upg.EnDo2, "IroDo2(IR)ENABLE");

	// Horces
	{
		RegisterUpgrade(&Upg.EnVsd, "SIUKRE(IR)ENABLE");
		// attack
		RegisterUpgrade(&Upg.VsdAtt, "PueVsd(IR)ATTACK");
		RegisterUpgrade(&Upg.VsdAtt3, "PueVsd(IR)ATTACK3");
		RegisterUpgrade(&Upg.VsdAtt4, "PueVsd(IR)ATTACK4");
		RegisterUpgrade(&Upg.VsdAtt5, "PueVsd(IR)ATTACK5");
		RegisterUpgrade(&Upg.VsdAtt6, "PueVsd(IR)ATTACK6");
		RegisterUpgrade(&Upg.VsdAtt7, "PueVsd(IR)ATTACK7");
		// deffence
		RegisterUpgrade(&Upg.VsdDef, "PueVsd(IR)SHIELD");
		RegisterUpgrade(&Upg.VsdDef3, "PueVsd(IR)SHIELD3");
		RegisterUpgrade(&Upg.VsdDef4, "PueVsd(IR)SHIELD4");
		RegisterUpgrade(&Upg.VsdDef5, "PueVsd(IR)SHIELD5");
		RegisterUpgrade(&Upg.VsdDef6, "PueVsd(IR)SHIELD6");
		RegisterUpgrade(&Upg.VsdDef7, "PueVsd(IR)SHIELD7");
	}
	
	// Peasant
	{
		// produce speed
		RegisterUpgrade(&Upg.KriBuildSpeed1, "CEN09IR");
		RegisterUpgrade(&Upg.KriBuildSpeed2, "CEN08IR");
		// life
		RegisterUpgrade(&Upg.KriIR, "CEN60IR");
		RegisterUpgrade(&Upg.KriIR3, "CEN60IR3");
		RegisterUpgrade(&Upg.KriIR4, "CEN60IR4");
		RegisterUpgrade(&Upg.KriIR5, "CEN60IR5");
		RegisterUpgrade(&Upg.KriIR6, "CEN60IR6");
		RegisterUpgrade(&Upg.KriIR7, "CEN60IR7");
		// attack
		RegisterUpgrade(&Upg.KriAtt, "DelKri(IR)ATTACK");
		RegisterUpgrade(&Upg.KriAtt3, "DelKri(IR)ATTACK3");
		RegisterUpgrade(&Upg.KriAtt4, "DelKri(IR)ATTACK4");
		RegisterUpgrade(&Upg.KriAtt5, "DelKri(IR)ATTACK5");
		RegisterUpgrade(&Upg.KriAtt6, "DelKri(IR)ATTACK6");
		RegisterUpgrade(&Upg.KriAtt7, "DelKri(IR)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.KriDef, "DelKri(IR)SHIELD");
		RegisterUpgrade(&Upg.KriDef3, "DelKri(IR)SHIELD3");
		RegisterUpgrade(&Upg.KriDef4, "DelKri(IR)SHIELD4");
		RegisterUpgrade(&Upg.KriDef5, "DelKri(IR)SHIELD5");
		RegisterUpgrade(&Upg.KriDef6, "DelKri(IR)SHIELD6");
		RegisterUpgrade(&Upg.KriDef7, "DelKri(IR)SHIELD7");
	}

	// Tam
	{
		RegisterUpgrade(&Upg.EnTam, "IroTam(IR)ENABLE");

		RegisterUpgrade(&Upg.Strike1, "CEN58IR");
		// attack
		RegisterUpgrade(&Upg.TamAtt, "IroTam(IR)ATTACK");
		RegisterUpgrade(&Upg.TamAtt3, "IroTam(IR)ATTACK3");
		RegisterUpgrade(&Upg.TamAtt4, "IroTam(IR)ATTACK4");
		RegisterUpgrade(&Upg.TamAtt5, "IroTam(IR)ATTACK5");
		RegisterUpgrade(&Upg.TamAtt6, "IroTam(IR)ATTACK6");
		RegisterUpgrade(&Upg.TamAtt7, "IroTam(IR)ATTACK7");		
		// defence
		RegisterUpgrade(&Upg.TamDef, "IroTam(IR)SHIELD");
		RegisterUpgrade(&Upg.TamDef3, "IroTam(IR)SHIELD3");
		RegisterUpgrade(&Upg.TamDef4, "IroTam(IR)SHIELD4");
		RegisterUpgrade(&Upg.TamDef5, "IroTam(IR)SHIELD5");
		RegisterUpgrade(&Upg.TamDef6, "IroTam(IR)SHIELD6");
		RegisterUpgrade(&Upg.TamDef7, "IroTam(IR)SHIELD7");
	}	
	// Lut
	{
		RegisterUpgrade(&Upg.EnLut, "IroLut(IR)ENABLE");		
		// precision
		RegisterUpgrade(&Upg.LutPerc1, "IroKre(IR)RAZBROS");
		RegisterUpgrade(&Upg.LutPerc2, "IroKre(IR)RAZBROS1");
		// more life
		RegisterUpgrade(&Upg.LutLife1, "CEN61IR");
		// attack
		RegisterUpgrade(&Upg.LutAtt, "IroLut(IR)ATTACK");
		RegisterUpgrade(&Upg.LutAtt3, "IroLut(IR)ATTACK3");
		RegisterUpgrade(&Upg.LutAtt4, "IroLut(IR)ATTACK4");
		RegisterUpgrade(&Upg.LutAtt5, "IroLut(IR)ATTACK5");
		RegisterUpgrade(&Upg.LutAtt6, "IroLut(IR)ATTACK6");
		RegisterUpgrade(&Upg.LutAtt7, "IroLut(IR)ATTACK7");
		// defence
		RegisterUpgrade(&Upg.LutDef, "IroLut(IR)SHIELD");
		RegisterUpgrade(&Upg.LutDef3, "IroLut(IR)SHIELD3");
		RegisterUpgrade(&Upg.LutDef4, "IroLut(IR)SHIELD4");
		RegisterUpgrade(&Upg.LutDef5, "IroLut(IR)SHIELD5");
		RegisterUpgrade(&Upg.LutDef6, "IroLut(IR)SHIELD6");
		RegisterUpgrade(&Upg.LutDef7, "IroLut(IR)SHIELD7");
	}
	// Str
	{
		RegisterUpgrade(&Upg.EnStr, "IroStr(IR)ENABLE");
	}	
	// Vog
	{
		RegisterUpgrade(&Upg.EnVog, "IroVog(IR)ENABLE");
	}
	
	// Sha
	{
		RegisterUpgrade(&Upg.ShaBuild1,"CEN13IR");
		RegisterUpgrade(&Upg.ShaMedic1,"CEN14IR");
		RegisterUpgrade(&Upg.ShaLife1,"CEN15IR");
	}

	{
		RegisterUpgrade(&Upg.ParSpeed1,"CEN102IR");
		RegisterUpgrade(&Upg.ParSpeed2,"CEN103IR");
		RegisterUpgrade(&Upg.ParSpeed3,"CEN104IR");
		RegisterUpgrade(&Upg.ParSpeed4,"CEN105IR");
		RegisterUpgrade(&Upg.ParSpeed5,"CEN106IR");
		RegisterUpgrade(&Upg.ParSpeed6,"CEN107IR");
	}

	// Kanoe 3 build speed
	{
		RegisterUpgrade(&Upg.Ka3Build1,"CEN96IR");
		RegisterUpgrade(&Upg.Ka3Build2,"CEN97IR");
		RegisterUpgrade(&Upg.Ka3Build3,"CEN98IR");
		RegisterUpgrade(&Upg.Ka3Build4,"CEN99IR");
		RegisterUpgrade(&Upg.Ka3Build5,"CEN100IR");
		RegisterUpgrade(&Upg.Ka3Build6,"CEN101IR");
	}

	// Fishing
	{
		RegisterUpgrade(&Upg.Ka1Fishing1,"CEN90IR");
		RegisterUpgrade(&Upg.Ka1Fishing2,"CEN91IR");
		RegisterUpgrade(&Upg.Ka1Fishing3,"CEN92IR");
		RegisterUpgrade(&Upg.Ka1Fishing4,"CEN93IR");
		RegisterUpgrade(&Upg.Ka1Fishing5,"CEN94IR");
		RegisterUpgrade(&Upg.Ka1Fishing6,"CEN95IR");
	}

	//RegisterUpgrade(&Upg., "");
}

IroNation Iro;