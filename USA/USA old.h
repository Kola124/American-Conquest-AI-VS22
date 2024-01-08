#define CONQUEST
#include "..\Import.h"
#include "..\USANation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = USA.Unit.Kri.Index;
	city->Init(AiNat);

	city->NIndexBrb=USA.Unit.B17.Index;
	city->NIndexOff=USA.Unit.O17.Index;
	city->NIndexFlg=USA.Unit.F17.Index;

	city->CannonNIndex=USA.Unit.Can.Index;

}

void Script();
void WaterScript();
void WarriorsUpg();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	Script();

	int LAND=GetLandType();
	switch(LAND){
	case LT_LAND:
	case LT_CONTINENT:
	case LT_MEDITERRANEAN:		
		break;
	case LT_PENINSULAS:
	case LT_ISLANDS:
	case LT_CONTINENTS:
		city->DefenceLess=1;
		city->LandType=1;
		WaterScript();
		break;
	};
	
	city->Process();
	
	int Diff=GetDifficulty();
	switch(Diff){
	case 2:
		city->SetStartRes(0,4000,0,0,0,0);
		break;
	case 3:
		city->SetStartRes(0,8000,0,0,0,0);
		break;
	};
}

void WarriorsUpg(){
}

void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// flags
	const HorceBuild=0;
	const CanBuild=1;

	// script	
	if(GetReadyUnits(&USA.Build.Skl)){
		city->MinWooders = 10;
		city->MinFermers = 25;
		city->PKrepost = 3;
	}
	if(GetUnits(&USA.Unit.Kri)>40){
		city->MinWooders = 25;
		city->PKrepost = 10;
	}
	if(GetUnits(&USA.Unit.Kri)>100){
		city->MinWooders = 40;
		city->PKrepost = 30;
	}
	if(GetReadyUnits(&USA.Build.Mel)&&GetUnits(&USA.Unit.Kri)>22){
		if(!UpgIsRun(&USA.Upg.Mel_GETRES)){
			city->MinFermers = 30;
			city->PKrepost = 6;
		}else
		if(!UpgIsRun(&USA.Upg.Mel_GETRES2)){
			city->MinFermers = 30;
			city->PKrepost = 12;
		}else{
			city->PKrepost = 40;
		}
	}
	if(GetReadyUnits(&USA.Build.Do1)<3&&GetReadyUnits(&USA.Build.Skl)){
		city->MinFermers = 15;
		city->MinWooders = 10;
	}	

	// Role planing
	city->AddBranch(USA.Unit.Pik.Index,brBack,35,146);
	city->AddBranch(USA.Unit.S15.Index,brBack,35,146);
	city->AddBranch(USA.Unit.S17.Index,brBack,35,146);
	city->AddBranch(USA.Unit.D17.Index,brBack,39,189);

	Branch* Pik=city->AddBranch(USA.Unit.Pik.Index,0,0,0);
	Branch* S15=city->AddBranch(USA.Unit.S15.Index,0,0,0);
	Branch* S17=city->AddBranch(USA.Unit.S17.Index,0,0,0);
	Branch* D17=city->AddBranch(USA.Unit.D17.Index,0,0,0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 0;	Pik->Part[brCenter] = 0;
	Pik->Prio[brBack] = 2;		Pik->Part[brBack] = 1;
	Pik->Formation=1;
	//btStorm

	S15->Prio[brForward] = 0;	S15->Part[brForward] = 0;	S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 1;	S15->Part[brCenter] = 1;	S15->Type[brCenter] = btTomahawk;
	S15->Prio[brBack] = 2;		S15->Part[brBack] = 1;
	//S15->Formation=1;	

	S17->Prio[brForward] = 3;	S17->Part[brForward] = 1;	S17->Type[brForward] = btStorm;	
	S17->Prio[brCenter] = 2;	S17->Part[brCenter] = 0;
	S17->Prio[brBack] = 1;		S17->Part[brBack] = 1;	
	S17->Formation=1;

	D17->Prio[brForward] = 0;	D17->Part[brForward] = 0;
	D17->Prio[brCenter] = 1;	D17->Part[brCenter] = 1;	D17->Type[brForward] = btTomahawk;
	D17->Prio[brBack] = 0;		D17->Part[brBack] = 0;
	
	// Units in buildings
	city->NStrelok = 20;
	if(GetUnits(&USA.Build.Blg2)) city->NStrelok = 30;
	city->NUnits = 2;

	// Units
	TryUnit(&USA.Unit.Kri, 1000, 5, 100);

	TryUnit(&USA.Unit.Sha, 1000, 20, 100);

	TryUnit(&USA.Unit.Pik, 1000, 20, 100);
	if(GetUnits(&USA.Unit.Pik)<30){
		TryUnit(&USA.Unit.S15, 1000, 20, 100);
		TryUnit(&USA.Unit.S15, 1000, 20, 100);
		//TryUnit(&USA.Unit.S15, 1000, 20, 100);
	}
	TryUnit(&USA.Unit.S15, 1000, 20, 100);

	TryUnit(&USA.Unit.S17, 1000, 20, 100);	
	
	if(city->Flags[HorceBuild]){
		TryUnit(&USA.Unit.D17, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int D17Cost=GetUnitCost(AiNat,&USA.Unit.D17,FOOD)*41;
		if(D17Cost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&USA.Unit.Pik)+GetUnits(&USA.Unit.S17))/37;
	TryUnit(&USA.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&USA.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&USA.Unit.F17, NeedSquad, 50, 100);

	TryUnit(&USA.Unit.S18, 1000, 20, 100);
	//TryUnit(&USA.Unit.O18, 5, 20, 100);
	//TryUnit(&USA.Unit.B18, 5, 20, 100);
	//TryUnit(&USA.Unit.F18, 5, 20, 100);

	TryUnit(&USA.Unit.D17, 1000, 20, 100);
	//TryUnit(&USA.Unit.KO7, 5, 20, 100);

	TryUnit(&USA.Unit.D18, 1000, 20, 100);
	//TryUnit(&USA.Unit.KO8, 5, 20, 100);
	//TryUnit(&USA.Unit.KF8, 5, 20, 100);

	TryUpgrade(&USA.Upg.CanCost,95,100);
	TryUpgrade(&USA.Upg.CanCost3,95,100);
	TryUpgrade(&USA.Upg.CanCost4,95,100);
	TryUpgrade(&USA.Upg.CanCost5,95,100);
	TryUpgrade(&USA.Upg.CanCost6,95,100);
	TryUpgrade(&USA.Upg.CanCost7,95,100);
	TryUpgrade(&USA.Upg.CanBuild,95,100);
	TryUpgrade(&USA.Upg.CanBuild3,95,100);
	TryUpgrade(&USA.Upg.CanBuild4,95,100);
	TryUpgrade(&USA.Upg.CanBuild5,95,100);
	TryUpgrade(&USA.Upg.CanBuild6,95,100);
	TryUpgrade(&USA.Upg.CanBuild7,95,100);
	
	//for(i=0;i<6;i++){
	//}
	if(GetUnits(&USA.Unit.D17)>30){
		TryUnit(&USA.Unit.Can, 5, 80, 100);
	}

	// Buildings
	TryUnit(&USA.Build.Kr7, 1, 100, 70);
	
	TryUnit(&USA.Build.Mel, 2, 100, 95);	
	if(GetUnits(&USA.Build.Mel)){
		TryUnit(&USA.Build.Do1, 2, 100, 95);
		TryUnit(&USA.Build.Skl, 1, 100, 95);
		TryUnit(&USA.Build.Kuz, 1, 100, 95);
		if(GetReadyUnits(&USA.Build.Kuz) && GetUnits(&USA.Unit.Kri)>20 && GetMoney(STONE)<1000){
			TryUnit(&USA.Build.RudSt,1,100,100);
		}
	}

	if(UpgIsRun(&USA.Upg.Mel_GETRES)){
		TryUnit(&USA.Build.Do1, 4, 100, 95);
	}
	if(GetUnits(&USA.Build.Kuz)){
		TryUnit(&USA.Build.RudSt, 2, 100, 70);
		TryUnit(&USA.Build.Rud, 1, 100, 70);
		TryUnit(&USA.Build.RudCo, 1, 100, 70);
		TryUnit(&USA.Build.RudIr, 1, 100, 70);
		
		if(GetUnits(&USA.Unit.Kri)>80){
			TryUnit(&USA.Build.Rud, 3, 100, 70);
			TryUnit(&USA.Build.RudSt, 3, 100, 70);
		}
		if(GetUnits(&USA.Unit.Kri)>120||GetReadyUnits(&USA.Build.Kr8)){
			TryUnit(&USA.Build.Rud, 10, 100, 70);
			TryUnit(&USA.Build.RudCo, 10, 100, 70);
			TryUnit(&USA.Build.RudIr, 10, 100, 70);
			TryUnit(&USA.Build.RudSt, 10, 100, 70);
		}
	}
	
	TryUnit(&USA.Build.Kr8, 1, 100, 70);

	if(GetReadyUnits(&USA.Build.Do1)>3){
		TryUnit(&USA.Build.Blg, 2, 100, 70);
	}
	if(GetReadyUnits(&USA.Build.Kr8)){
		TryUnit(&USA.Build.Blg, 3, 100, 70);
	}

	TryUnit(&USA.Build.Cen, 1, 100, 70);
	if(GetReadyUnits(&USA.Build.Cen)){
		TryUnit(&USA.Build.Do1, 5, 100, 70);
		TryUnit(&USA.Build.Do2, 5, 100, 70);		
		TryUnit(&USA.Build.Blg2, 3, 100, 70);
	}
	
	TryUnit(&USA.Build.Hra, 1, 100, 70);	

	//TryUnit(&USA.Build.Ver, 2, 100, 70);

	// Upgrades
	// Mine
	TryUpgrade(&USA.Upg.Rud_INSIDE, 80, 100);
	TryUpgrade(&USA.Upg.RudSt_INSIDE, 80, 100);
	TryUpgrade(&USA.Upg.RudCo_INSIDE, 80, 100);	
	TryUpgrade(&USA.Upg.RudIr_INSIDE, 80, 100);

	// Fild
	TryUpgrade(&USA.Upg.CEN18, 90, 100);
	TryUpgrade(&USA.Upg.CEN52, 90, 100);
	TryUpgrade(&USA.Upg.CEN57, 90, 100);
	TryUpgrade(&USA.Upg.CEN55, 90, 100);

	// Food
	if(GetUnits(&USA.Unit.Kri)>30) TryUpgrade(&USA.Upg.Mel_GETRES, 90, 100);
	TryUpgrade(&USA.Upg.Mel_GETRES2, 90, 100);
	TryUpgrade(&USA.Upg.CEN19, 80, 100);
	TryUpgrade(&USA.Upg.CEN22, 80, 100);
	TryUpgrade(&USA.Upg.CEN23, 80, 100);

	// Stages
	TryUpgrade(&USA.Upg.Kr7_Stage0, 80, 100);
	TryUpgrade(&USA.Upg.Kr8_Stage0, 80, 100);
	//TryUpgrade(&USA.Upg.Kr8_Stage1, 80, 100);
	
	//
	TryUpgrade(&USA.Upg.Do2_ENABLE, 95, 100);
	TryUpgrade(&USA.Upg.Kre_RAZBROS, 80, 100);
	TryUpgrade(&USA.Upg.KreBuild, 80, 100);	

	// Wood
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
		TryUpgrade(&USA.Upg.WoodEffect1,80,70);
		TryUpgrade(&USA.Upg.WoodEffect2,80,70);
	}
	
	// Kri
	{
		TryUpgrade(&USA.Upg.KriBuild1,80,70);
		TryUpgrade(&USA.Upg.KriBuild2,80,70);
		TryUpgrade(&USA.Upg.KriBuild3,80,70);
	}

	// Mus
	{
		TryUpgrade(&USA.Upg.MusBuild1,80,70);
		TryUpgrade(&USA.Upg.MusBuild2,80,70);
	}

	// Pik
	if(GetUnits(&USA.Unit.Pik)>20){
		TryUpgrade(&USA.Upg.PikBuild1, 90, 100);
		if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
			TryUpgrade(&USA.Upg.PikBuild2, 90, 100);
			TryUpgrade(&USA.Upg.PikBuild3, 90, 100);
			TryUpgrade(&USA.Upg.PikBuild4, 90, 100);			
		}

		TryUpgrade(&USA.Upg.PikAttack, 90, 100);
		TryUpgrade(&USA.Upg.PikAttack3, 40, 100);
		if(GetUnits(&USA.Unit.Pik)>15){
			TryUpgrade(&USA.Upg.PikAttack4, 40, 100);
			TryUpgrade(&USA.Upg.PikAttack5, 40, 100);
			TryUpgrade(&USA.Upg.PikAttack6, 40, 100);
			TryUpgrade(&USA.Upg.PikAttack7, 40, 100);
		}
		
		TryUpgrade(&USA.Upg.PikProtect, 90, 100);
		TryUpgrade(&USA.Upg.PikProtect3, 90, 100);
		TryUpgrade(&USA.Upg.PikProtect4, 90, 100);
		TryUpgrade(&USA.Upg.PikProtect5, 40, 100);
		TryUpgrade(&USA.Upg.PikProtect6, 40, 100);
		TryUpgrade(&USA.Upg.PikProtect7, 40, 100);

	}

	// Cen
	{
		TryUpgrade(&USA.Upg.ArmShield1,90,100);
		TryUpgrade(&USA.Upg.ArmShield2,50,80);
		TryUpgrade(&USA.Upg.StrAttPause1,90,100);
	}

	// Mus
	{
		TryUpgrade(&USA.Upg.MusBuild1,80,70);
		TryUpgrade(&USA.Upg.MusBuild2,80,70);

		if(GetUnits(&USA.Unit.S17)>20){
			TryUpgrade(&USA.Upg.MusAttack, 90, 100);
			TryUpgrade(&USA.Upg.MusAttack3, 90, 100);
			TryUpgrade(&USA.Upg.MusAttack4, 90, 100);
		}
		if(GetUnits(&USA.Unit.S17)>40){
			TryUpgrade(&USA.Upg.MusAttack5, 90, 100);
			TryUpgrade(&USA.Upg.MusAttack6, 90, 100);
			TryUpgrade(&USA.Upg.MusAttack7, 90, 100);
		}
		
		if(GetUnits(&USA.Unit.S17)>20){
			TryUpgrade(&USA.Upg.MusProtect, 90, 100);
			TryUpgrade(&USA.Upg.MusProtect3, 90, 100);
			TryUpgrade(&USA.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&USA.Unit.S17)>40){
			TryUpgrade(&USA.Upg.MusProtect5, 90, 100);
			TryUpgrade(&USA.Upg.MusProtect6, 90, 100);
			TryUpgrade(&USA.Upg.MusProtect7, 90, 100);
		}
	}

	// S15
	{
		if(GetUnits(&USA.Unit.S15)>20){
			TryUpgrade(&USA.Upg.S15Attack, 90, 100);
			TryUpgrade(&USA.Upg.S15Attack3, 90, 100);
			TryUpgrade(&USA.Upg.S15Attack4, 90, 100);
		}
		if(GetUnits(&USA.Unit.S15)>40){
			TryUpgrade(&USA.Upg.S15Attack5, 90, 100);
			TryUpgrade(&USA.Upg.S15Attack6, 40, 100);
			TryUpgrade(&USA.Upg.S15Attack7, 40, 100);
		}
		
		if(GetUnits(&USA.Unit.S15)>20){
			TryUpgrade(&USA.Upg.S15Protect, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect3, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect4, 90, 100);
		}
		if(GetUnits(&USA.Unit.S15)>40){
			TryUpgrade(&USA.Upg.S15Protect5, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect6, 40, 100);
			TryUpgrade(&USA.Upg.S15Protect7, 40, 100);
		}
	}

	// D17
	{
		TryUpgrade(&USA.Upg.D17Build, 90, 100);		
		if(GetUnits(&USA.Unit.D17)>20){
			TryUpgrade(&USA.Upg.D17Attack, 90, 100);
			TryUpgrade(&USA.Upg.D17Attack3, 90, 100);
			TryUpgrade(&USA.Upg.D17Attack4, 90, 100);
		}
		if(GetUnits(&USA.Unit.D17)>40){
			TryUpgrade(&USA.Upg.D17Attack5, 90, 100);
			TryUpgrade(&USA.Upg.D17Attack6, 90, 100);
			TryUpgrade(&USA.Upg.D17Attack7, 90, 100);
		}
		
		if(GetUnits(&USA.Unit.D17)>20){
			TryUpgrade(&USA.Upg.D17Protect, 90, 100);
			TryUpgrade(&USA.Upg.D17Protect3, 90, 100);
			TryUpgrade(&USA.Upg.D17Protect4, 90, 100);
		}
		if(GetUnits(&USA.Unit.D17)>40){
			TryUpgrade(&USA.Upg.D17Protect5, 90, 100);
			TryUpgrade(&USA.Upg.D17Protect6, 90, 100);
			TryUpgrade(&USA.Upg.D17Protect7, 90, 100);
		}
	}

	if(GetDifficulty()>0 && UpgIsRun(&USA.Upg.Mel_GETRES2)) WarriorsUpg();

	// Enable warriors

}

void WaterScript(){
}

//----------------------------------------------//
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					   ){
	switch (ul_reason_for_call){
			case DLL_PROCESS_ATTACH:{
				//InitAI();
				break;
			};
			break;
	};
    return TRUE;
}
//----------------------------------------------//

#if !defined(AMERICAN_CONQUEST_USA_NATION)
#define AMERICAN_CONQUEST_USA_NATION

// USAoware nations header file

#include "..\Import.h"

class USAUnits {
public:	
	GAMEOBJ Kri;	// PEASANT
	GAMEOBJ Pik;	
	GAMEOBJ Sha;

	GAMEOBJ S15;

	GAMEOBJ S17;
	GAMEOBJ O17;
	GAMEOBJ B17;
	GAMEOBJ F17;

	GAMEOBJ S18;
	GAMEOBJ O18;
	GAMEOBJ B18;
	GAMEOBJ F18;

	GAMEOBJ D17;
	GAMEOBJ KO7;

	GAMEOBJ D18;
	GAMEOBJ KO8;
	GAMEOBJ KF8;

	GAMEOBJ Can;
};

class USABuildings {
public:
	GAMEOBJ Rud;
	GAMEOBJ RudIr;
	GAMEOBJ RudCo;
	GAMEOBJ RudSt;
	GAMEOBJ Do1;
	GAMEOBJ Do2;
	GAMEOBJ Mel;
	GAMEOBJ Skl;
	GAMEOBJ Hra;
	GAMEOBJ Cen;
	GAMEOBJ Kr7;
	GAMEOBJ Kr8;
	GAMEOBJ Kuz;
	GAMEOBJ Blg;
	GAMEOBJ Blg2;
	GAMEOBJ Ver;
};

class USAUpgrades {
public:
	GAMEOBJ Rud_INSIDE; //SINGLE_INSIDE USARud_ +5
	GAMEOBJ RudSt_INSIDE; //SINGLE_INSIDE USARud_ +5
	GAMEOBJ RudCo_INSIDE; //SINGLE_INSIDE USARud_ +5
	GAMEOBJ RudIr_INSIDE; //SINGLE_INSIDE USARud_ +5

	GAMEOBJ CEN18; //EFFECT_FOOD +2000
	GAMEOBJ CEN52; //EFFECT_FOOD +3000
	GAMEOBJ CEN57; //EFFECT_FOOD +2000
	GAMEOBJ CEN55; //EFFECT_FOOD +3000

	GAMEOBJ Mel_GETRES; //EFFECT_FOOD +14
	GAMEOBJ Mel_GETRES2; //EFFECT_FOOD +25
	GAMEOBJ CEN19; //EFFECT_FOOD +16
	GAMEOBJ CEN22; //EFFECT_FOOD +8
	GAMEOBJ CEN23; //EFFECT_FOOD +6

	GAMEOBJ Kr7_Stage0;
	GAMEOBJ Kr8_Stage0;

	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 ...Do2
	GAMEOBJ Kre_RAZBROS; //RAZBROS GRP 1 ...Mus -35%

	// Wood
	GAMEOBJ WoodEffect1; //CEN29SP
	GAMEOBJ WoodEffect2; //CEN30SP

	// Kri
	GAMEOBJ KriBuild1; //CEN24SP
	GAMEOBJ KriBuild2; //CEN36SP
	GAMEOBJ KriBuild3; //CEN48SP

	// Pik
	GAMEOBJ PikBuild1; //KUZ20(SP)
	GAMEOBJ PikBuild2; //CEN26SP
	GAMEOBJ PikBuild3; //CEN27SP
	GAMEOBJ PikBuild4; //CEN28SP

	GAMEOBJ PikAttack; //SpnAlb(SP)ATTACK
	GAMEOBJ PikAttack3;
	GAMEOBJ PikAttack4;
	GAMEOBJ PikAttack5;
	GAMEOBJ PikAttack6;
	GAMEOBJ PikAttack7;

	GAMEOBJ PikProtect; //SpnAlb(SP)SHIELD
	GAMEOBJ PikProtect3;
	GAMEOBJ PikProtect4;
	GAMEOBJ PikProtect5;
	GAMEOBJ PikProtect6;
	GAMEOBJ PikProtect7;

	// Krepost
	GAMEOBJ KreBuild; //CEN25SP

	// Can
	GAMEOBJ CanCost;
	GAMEOBJ CanCost3;
	GAMEOBJ CanCost4;
	GAMEOBJ CanCost5;
	GAMEOBJ CanCost6;
	GAMEOBJ CanCost7;

	GAMEOBJ CanBuild;
	GAMEOBJ CanBuild3;
	GAMEOBJ CanBuild4;
	GAMEOBJ CanBuild5;
	GAMEOBJ CanBuild6;
	GAMEOBJ CanBuild7;

	// Cen
	GAMEOBJ ArmShield1; //CEN47SP
	GAMEOBJ ArmShield2; //CEN08SP

	GAMEOBJ StrAttPause1; //CEN01SP

	// D17
	GAMEOBJ D17Build; //CEN39SP

	GAMEOBJ D17Attack; //SpnD17(SP)ATTACK
	GAMEOBJ D17Attack3;
	GAMEOBJ D17Attack4;
	GAMEOBJ D17Attack5;
	GAMEOBJ D17Attack6;
	GAMEOBJ D17Attack7;

	GAMEOBJ D17Protect; //SpnD17(SP)SHIELD
	GAMEOBJ D17Protect3;
	GAMEOBJ D17Protect4;
	GAMEOBJ D17Protect5;
	GAMEOBJ D17Protect6;
	GAMEOBJ D17Protect7;

	// S15
	GAMEOBJ S15Attack; //SpnS15(SP)ATTACK
	GAMEOBJ S15Attack3;
	GAMEOBJ S15Attack4;
	GAMEOBJ S15Attack5;
	GAMEOBJ S15Attack6;
	GAMEOBJ S15Attack7;

	GAMEOBJ S15Protect; //SpnS15(SP)SHIELD
	GAMEOBJ S15Protect3;
	GAMEOBJ S15Protect4;
	GAMEOBJ S15Protect5;
	GAMEOBJ S15Protect6;
	GAMEOBJ S15Protect7;

	// Mus
	GAMEOBJ MusBuild1; //CEN07SP
	GAMEOBJ MusBuild2; //CEN09SP

	GAMEOBJ MusAttack; //SpnMus(SP)ATTACK
	GAMEOBJ MusAttack3;
	GAMEOBJ MusAttack4;
	GAMEOBJ MusAttack5;
	GAMEOBJ MusAttack6;
	GAMEOBJ MusAttack7;

	GAMEOBJ MusProtect; //SpnMus(SP)SHIELD
	GAMEOBJ MusProtect3;
	GAMEOBJ MusProtect4;
	GAMEOBJ MusProtect5;
	GAMEOBJ MusProtect6;
	GAMEOBJ MusProtect7;

};

class USANation {
public:
	USANation();
	USAUnits Unit;
	USABuildings Build;
	USAUpgrades Upg;
};
extern USANation USA;

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "USANation.h"

USANation::USANation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "EngKri(US)");
	RegisterUnitType(&Unit.Pik, "EngPik(US)");	
	RegisterUnitType(&Unit.Sha, "SpnSha(US)");

	RegisterUnitType(&Unit.S15, "SpnS15(US)");

	RegisterUnitType(&Unit.S17, "EngMus(US)");
	RegisterUnitType(&Unit.O17, "EngOf17(US)");
	RegisterUnitType(&Unit.B17, "EngB17(US)");
	RegisterUnitType(&Unit.F17, "EngF17(US)");

	RegisterUnitType(&Unit.S18, "UsaM18(US)");
	RegisterUnitType(&Unit.O18, "UsaOf18(US)");
	RegisterUnitType(&Unit.B18, "UsaB18(US)");
	RegisterUnitType(&Unit.F18, "UsaF18(US)");

	RegisterUnitType(&Unit.D17, "EngD17(US)");
	RegisterUnitType(&Unit.KO7, "EngKOf17(US)");

	RegisterUnitType(&Unit.D18, "UsaD18(US)");
	RegisterUnitType(&Unit.KO8, "UsaKOf18(US)");
	RegisterUnitType(&Unit.KF8, "UsaKF18(US)");

	RegisterUnitType(&Unit.Can, "ArtPus(US)");	
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Rud, "SpnRud(US)");
	RegisterUnitType(&Build.RudIr, "SpnIro(US)");
	RegisterUnitType(&Build.RudCo, "SpnCoa(US)");
	RegisterUnitType(&Build.RudSt, "SpnStn(US)");
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
	RegisterUnitType(&Build.Ver, "EngVer(US)");
	//RegisterUnitType(&Build., "");
	
	// Upgrades
	RegisterUpgrade(&Upg.Rud_INSIDE, "SpnRud(US)INSIDE");
	RegisterUpgrade(&Upg.RudSt_INSIDE, "SpnRudSt(US)INSIDE");
	RegisterUpgrade(&Upg.RudCo_INSIDE, "SpnRudCo(US)INSIDE");
	RegisterUpgrade(&Upg.RudIr_INSIDE, "SpnRudIr(US)INSIDE");
	
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

	RegisterUpgrade(&Upg.Do2_ENABLE, "UsaDo2(US)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56US");	
	//RegisterUpgrade(&Upg., "");

	// Wood
	{
		RegisterUpgrade(&Upg.WoodEffect1, "CEN29US");
		RegisterUpgrade(&Upg.WoodEffect2, "CEN30US");
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

	// Krepost
	{
		RegisterUpgrade(&Upg.KreBuild, "CEN25US");
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
		RegisterUpgrade(&Upg.StrAttPause1, "CEN01US");
	}

	// D17
	{
		RegisterUpgrade(&Upg.D17Build, "CEN39US");

		RegisterUpgrade(&Upg.D17Attack, "EngD17(US)ATTACK");
		RegisterUpgrade(&Upg.D17Attack3, "EngD17(US)ATTACK3");
		RegisterUpgrade(&Upg.D17Attack4, "EngD17(US)ATTACK4");
		RegisterUpgrade(&Upg.D17Attack5, "EngD17(US)ATTACK5");
		RegisterUpgrade(&Upg.D17Attack6, "EngD17(US)ATTACK6");
		RegisterUpgrade(&Upg.D17Attack7, "EngD17(US)ATTACK7");
		
		RegisterUpgrade(&Upg.D17Protect, "EngD17(US)SHIELD");
		RegisterUpgrade(&Upg.D17Protect3, "EngD17(US)SHIELD3");
		RegisterUpgrade(&Upg.D17Protect4, "EngD17(US)SHIELD4");
		RegisterUpgrade(&Upg.D17Protect5, "EngD17(US)SHIELD5");
		RegisterUpgrade(&Upg.D17Protect6, "EngD17(US)SHIELD6");
		RegisterUpgrade(&Upg.D17Protect7, "EngD17(US)SHIELD7");
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
		RegisterUpgrade(&Upg.MusBuild1, "CEN07US");
		RegisterUpgrade(&Upg.MusBuild2, "CEN09US");

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

}

USANation USA;