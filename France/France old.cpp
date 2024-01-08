#define CONQUEST
#include "..\Import.h"
#include "..\FraNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Fra.Unit.Kri.Index;
	city->Init(AiNat);

	city->NIndexBrb=Fra.Unit.B17.Index;
	city->NIndexOff=Fra.Unit.O17.Index;
	city->NIndexFlg=Fra.Unit.F17.Index;

	city->CannonNIndex=Fra.Unit.Can.Index;
	city->ParomNIndex=Fra.Unit.Parom.Index;
}

void Script();
void WarriorsUpg();
void WaterScript();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	int LAND=GetLandType();
	switch(LAND){
	case LT_LAND:
	case LT_CONTINENT:
	case LT_MEDITERRANEAN:		
		break;
	case LT_PENINSULAS:
	case LT_ISLANDS:
	case LT_CONTINENTS:
		city->LandType=1;
		city->DefenceLess=1;
		WaterScript();
		break;
	};
	Script();	

	city->Process();
	
	int Diff=GetDifficulty();
	switch(Diff){
	case 2:
		city->SetStartRes(1000,4000,0,0,0,0);
		break;
	case 3:
		city->SetStartRes(2000,8000,0,0,0,0);
		break;
	};
}

void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// flags
	const HorceBuild=0;
	const CanBuild=1;

	// Role planing
	city->AddBranch(Fra.Unit.Pik.Index,brBack,35,146);
	city->AddBranch(Fra.Unit.S15.Index,brBack,35,146);
	city->AddBranch(Fra.Unit.S17.Index,brBack,35,146);
	city->AddBranch(Fra.Unit.D17.Index,brBack,59,189);

	Branch* Pik=city->AddBranch(Fra.Unit.Pik.Index,0,0,0);
	Branch* S15=city->AddBranch(Fra.Unit.S15.Index,0,0,0);
	Branch* S17=city->AddBranch(Fra.Unit.S17.Index,0,0,0);
	Branch* D17=city->AddBranch(Fra.Unit.D17.Index,0,0,0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1; Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 0;	Pik->Part[brCenter] = 0;	
	Pik->Prio[brBack] = 2;		Pik->Part[brBack] = 0;	Pik->Type[brBack] = btKillers;
								if(GetDifficulty()<2) Pik->Part[brBack] = 1;
	Pik->Formation=1;

	S15->Prio[brForward] = 0;	S15->Part[brForward] = 0;	S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 1;	S15->Part[brCenter] = 1;	S15->Type[brCenter] = btTomahawk;
	S15->Prio[brBack] = 2;		S15->Part[brBack] = 0;

	S17->Prio[brForward] = 3;	S17->Part[brForward] = 1;	S17->Type[brForward] = btTomahawk;	
	S17->Prio[brCenter] = 2;	S17->Part[brCenter] = 0;
	S17->Prio[brBack] = 1;		S17->Part[brBack] = 0;	
	S17->Formation=1;

	D17->Prio[brForward] = 0;	D17->Part[brForward] = 0;
	D17->Prio[brCenter] = 1;	D17->Part[brCenter] = 1;	D17->Type[brForward] = btTomahawk;
	D17->Prio[brBack] = 0;		D17->Part[brBack] = 0;
	
	// Units in buildings
	city->NStrelok = 20;
	if(GetUnits(&Fra.Build.Blg2)) city->NStrelok = 30;
	city->NUnits = 2;
	
	city->PKrepost = 20;
	
	// Producing
	TryUnit(&Fra.Unit.Kri, 10000, 5, 100);
	TryUnit(&Fra.Unit.Kri, 10000, 5, 100);
	TryUnit(&Fra.Unit.Kri, 10000, 5, 100);

	TryUnit(&Fra.Unit.Sha, 10000, 20, 100);

	TryUnit(&Fra.Unit.Pik, 10000, 20, 100);
	if(GetUnits(&Fra.Unit.Pik)<30){
		TryUnit(&Fra.Unit.S15, 10000, 20, 100);
		TryUnit(&Fra.Unit.S15, 10000, 20, 100);
		//TryUnit(&Fra.Unit.S15, 1000, 20, 100);
	}
	TryUnit(&Fra.Unit.S15, 10000, 20, 100);

	TryUnit(&Fra.Unit.S17, 10000, 20, 100);	
	
	if(city->Flags[HorceBuild]){
		TryUnit(&Fra.Unit.D17, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int D17Cost=GetUnitCost(AiNat,&Fra.Unit.D17,FOOD)*41;
		if(D17Cost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S17))/37;
	TryUnit(&Fra.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&Fra.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&Fra.Unit.F17, NeedSquad, 50, 100);

	TryUnit(&Fra.Unit.S18, 1000, 20, 100);
	//TryUnit(&Fra.Unit.O18, 5, 20, 100);
	//TryUnit(&Fra.Unit.B18, 5, 20, 100);
	//TryUnit(&Fra.Unit.F18, 5, 20, 100);

	TryUnit(&Fra.Unit.D17, 1000, 20, 100);
	//TryUnit(&Fra.Unit.KO7, 5, 20, 100);

	TryUnit(&Fra.Unit.D18, 1000, 20, 100);
	//TryUnit(&Fra.Unit.KO8, 5, 20, 100);
	//TryUnit(&Fra.Unit.KF8, 5, 20, 100);

	TryUpgrade(&Fra.Upg.CanCost,95,100);
	TryUpgrade(&Fra.Upg.CanCost3,95,100);
	TryUpgrade(&Fra.Upg.CanCost4,95,100);
	TryUpgrade(&Fra.Upg.CanCost5,95,100);
	TryUpgrade(&Fra.Upg.CanCost6,95,100);
	TryUpgrade(&Fra.Upg.CanCost7,95,100);
	TryUpgrade(&Fra.Upg.CanBuild,95,100);
	TryUpgrade(&Fra.Upg.CanBuild3,95,100);
	TryUpgrade(&Fra.Upg.CanBuild4,95,100);
	TryUpgrade(&Fra.Upg.CanBuild5,95,100);
	TryUpgrade(&Fra.Upg.CanBuild6,95,100);
	TryUpgrade(&Fra.Upg.CanBuild7,95,100);
	
	//for(i=0;i<6;i++){
	//}
	if(GetUnits(&Fra.Unit.D17)>30){
		TryUnit(&Fra.Unit.Can, 5, 80, 100);
	}

	// Buildings
	TryUnit(&Fra.Build.Cen, 1, 100, 70);
	TryUnit(&Fra.Build.Kr7, 2, 100, 70);
	
	TryUnit(&Fra.Build.Mel, 1, 100, 80);
	if(city->MinFermers>100) TryUnit(&Fra.Build.Mel, 2, 100, 80);
	if(GetUnits(&Fra.Build.Mel)){
		TryUnit(&Fra.Build.Do1, 2, 100, 60);
		TryUnit(&Fra.Build.Skl, 1, 100, 80);
		if(city->MinWooders>100) TryUnit(&Fra.Build.Skl, 2, 100, 80);
		TryUnit(&Fra.Build.Kuz, 1, 100, 70);
		if(GetReadyUnits(&Fra.Build.Kuz) && GetUnits(&Fra.Unit.Kri)>20 && GetMoney(STONE)<1000){
			TryUnit(&Fra.Build.RudSt,1,100, 70);
		}
	}

	if(UpgIsRun(&Fra.Upg.Mel_GETRES)){
		TryUnit(&Fra.Build.Do1, 4, 100, 80);
	}
	if(GetUnits(&Fra.Build.Kuz)){
		TryUnit(&Fra.Build.Rud, 1, 100, 70);
		TryUnit(&Fra.Build.RudCo, 1, 100, 70);
		TryUnit(&Fra.Build.RudIr, 1, 100, 70);
		TryUnit(&Fra.Build.RudSt, 2, 100, 70);
		if(GetUnits(&Fra.Unit.Kri)>80){
			TryUnit(&Fra.Build.Rud, 3, 100, 70);
			TryUnit(&Fra.Build.RudSt, 3, 100, 70);
		}
		if(GetUnits(&Fra.Unit.Kri)>120||GetReadyUnits(&Fra.Build.Kr8)){
			TryUnit(&Fra.Build.Rud, 10, 100, 70);
			TryUnit(&Fra.Build.RudCo, 10, 100, 70);
			TryUnit(&Fra.Build.RudIr, 10, 100, 70);
			TryUnit(&Fra.Build.RudSt, 10, 100, 70);
		}
	}
	
	TryUnit(&Fra.Build.Kr8, 1, 100, 80);

	if(GetReadyUnits(&Fra.Build.Do1)>3){
		TryUnit(&Fra.Build.Blg, 2, 100, 70);
	}
	if(GetReadyUnits(&Fra.Build.Kr8)){
		TryUnit(&Fra.Build.Blg, 3, 100, 70);
	}
	
	if(GetReadyUnits(&Fra.Build.Cen)){
		TryUnit(&Fra.Build.Do1, 5, 100, 70);
		TryUnit(&Fra.Build.Do2, 5, 100, 70);		
		TryUnit(&Fra.Build.Blg2, 3, 100, 70);
	}
	
	TryUnit(&Fra.Build.Hra, 1, 100, 70);	

	//TryUnit(&Fra.Build.Ver, 2, 100, 70);

	// Upgrades	

	// Food
	if(GetUnits(&Fra.Unit.Kri)>30) TryUpgrade(&Fra.Upg.Mel_GETRES, 90, 100);
	TryUpgrade(&Fra.Upg.Mel_GETRES2, 90, 100);

	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){
		// Mine
		TryUpgrade(&Fra.Upg.Rud_INSIDE, 80, 100);
		TryUpgrade(&Fra.Upg.RudSt_INSIDE, 80, 100);
		TryUpgrade(&Fra.Upg.RudCo_INSIDE, 80, 100);	
		TryUpgrade(&Fra.Upg.RudIr_INSIDE, 80, 100);

		// Fild
		//TryUpgrade(&Fra.Upg.CEN18, 90, 100);
		//TryUpgrade(&Fra.Upg.CEN52, 90, 100);
		TryUpgrade(&Fra.Upg.CEN57, 90, 100);
		TryUpgrade(&Fra.Upg.CEN55, 90, 100);

		// Food
		TryUpgrade(&Fra.Upg.CEN19, 80, 100);
		TryUpgrade(&Fra.Upg.CEN22, 80, 100);
		TryUpgrade(&Fra.Upg.CEN23, 80, 100);
		
		//
		TryUpgrade(&Fra.Upg.Do2_ENABLE, 95, 100);
		TryUpgrade(&Fra.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&Fra.Upg.KreBuild, 80, 100);	

		// Stages
		TryUpgrade(&Fra.Upg.Kr7_Stage0, 80, 100);
		TryUpgrade(&Fra.Upg.Kr8_Stage0, 80, 100);
		//TryUpgrade(&Fra.Upg.Kr8_Stage1, 80, 100);

		// Wood
		TryUpgrade(&Fra.Upg.WoodEffect1,80,70);
		TryUpgrade(&Fra.Upg.WoodEffect2,80,70);
	}
	
	// Peasat distribution
	int NU=GetUnits(&Fra.Unit.Kri)+GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S15)+GetUnits(&Fra.Unit.S17);
	{ //500
		if(!UpgIsRun(&Fra.Upg.Mel_GETRES2)) city->PKrepost=NU>>4;
		if(GetReadyUnits(&Fra.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&Fra.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&Fra.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		if(GetUnits(&Fra.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&Fra.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}

	if(GetDifficulty()>0 && UpgIsRun(&Fra.Upg.Mel_GETRES2)) WarriorsUpg();

	// Enable warriors

}

void WarriorsUpg(){

	// Kri
	{
		TryUpgrade(&Fra.Upg.KriBuild1,80,70);
		TryUpgrade(&Fra.Upg.KriBuild2,80,70);
		TryUpgrade(&Fra.Upg.KriBuild3,80,70);
	}

	// Mus
	{
		TryUpgrade(&Fra.Upg.MusBuild1,80,70);
		TryUpgrade(&Fra.Upg.MusBuild2,80,70);
	}

	// Pik
	if(GetUnits(&Fra.Unit.Pik)>20){
		TryUpgrade(&Fra.Upg.PikBuild1, 90, 100);
		if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){
			TryUpgrade(&Fra.Upg.PikBuild2, 90, 100);
			TryUpgrade(&Fra.Upg.PikBuild3, 90, 100);
			TryUpgrade(&Fra.Upg.PikBuild4, 90, 100);			
		}

		TryUpgrade(&Fra.Upg.PikAttack, 90, 100);
		TryUpgrade(&Fra.Upg.PikAttack3, 40, 100);
		if(GetUnits(&Fra.Unit.Pik)>45){
			TryUpgrade(&Fra.Upg.PikAttack4, 40, 100);
			TryUpgrade(&Fra.Upg.PikAttack5, 40, 100);
			TryUpgrade(&Fra.Upg.PikAttack6, 40, 100);
			TryUpgrade(&Fra.Upg.PikAttack7, 40, 100);
		}
		
		TryUpgrade(&Fra.Upg.PikProtect, 90, 100);
		TryUpgrade(&Fra.Upg.PikProtect3, 90, 100);
		TryUpgrade(&Fra.Upg.PikProtect4, 90, 100);
		TryUpgrade(&Fra.Upg.PikProtect5, 40, 100);
		TryUpgrade(&Fra.Upg.PikProtect6, 40, 100);
		TryUpgrade(&Fra.Upg.PikProtect7, 40, 100);

	}

	// Cen
	{
		TryUpgrade(&Fra.Upg.ArmShield1,90,100);
		TryUpgrade(&Fra.Upg.ArmShield2,50,80);
		TryUpgrade(&Fra.Upg.StrAttPause1,90,100);
	}

	// Mus
	if(GetUnits(&Fra.Unit.S17)>20){
		TryUpgrade(&Fra.Upg.MusBuild1,80,70);
		TryUpgrade(&Fra.Upg.MusBuild2,80,70);

		if(GetUnits(&Fra.Unit.S17)>20){
			TryUpgrade(&Fra.Upg.MusAttack, 90, 100);
			TryUpgrade(&Fra.Upg.MusAttack3, 90, 100);
			TryUpgrade(&Fra.Upg.MusAttack4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.S17)>55){
			TryUpgrade(&Fra.Upg.MusAttack5, 90, 100);
			TryUpgrade(&Fra.Upg.MusAttack6, 90, 100);
			TryUpgrade(&Fra.Upg.MusAttack7, 90, 100);
		}
		
		if(GetUnits(&Fra.Unit.S17)>20){
			TryUpgrade(&Fra.Upg.MusProtect, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect3, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.S17)>55){
			TryUpgrade(&Fra.Upg.MusProtect5, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect6, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect7, 90, 100);
		}
	}

	// S15
	{
		if(GetUnits(&Fra.Unit.S15)>20){
			TryUpgrade(&Fra.Upg.S15Attack, 90, 100);
			TryUpgrade(&Fra.Upg.S15Attack3, 90, 100);
			TryUpgrade(&Fra.Upg.S15Attack4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.S15)>100){
			TryUpgrade(&Fra.Upg.S15Attack5, 90, 100);
			TryUpgrade(&Fra.Upg.S15Attack6, 40, 100);
			TryUpgrade(&Fra.Upg.S15Attack7, 40, 100);
		}
		
		if(GetUnits(&Fra.Unit.S15)>20){
			TryUpgrade(&Fra.Upg.S15Protect, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect3, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.S15)>100){
			TryUpgrade(&Fra.Upg.S15Protect5, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect6, 40, 100);
			TryUpgrade(&Fra.Upg.S15Protect7, 40, 100);
		}
	}

	// D17
	{
		TryUpgrade(&Fra.Upg.D17Build, 90, 100);		
		if(GetUnits(&Fra.Unit.D17)>20){
			TryUpgrade(&Fra.Upg.D17Attack, 90, 100);
			TryUpgrade(&Fra.Upg.D17Attack3, 90, 100);
			TryUpgrade(&Fra.Upg.D17Attack4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.D17)>40){
			TryUpgrade(&Fra.Upg.D17Attack5, 90, 100);
			TryUpgrade(&Fra.Upg.D17Attack6, 90, 100);
			TryUpgrade(&Fra.Upg.D17Attack7, 90, 100);
		}
		
		if(GetUnits(&Fra.Unit.D17)>20){
			TryUpgrade(&Fra.Upg.D17Protect, 90, 100);
			TryUpgrade(&Fra.Upg.D17Protect3, 90, 100);
			TryUpgrade(&Fra.Upg.D17Protect4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.D17)>40){
			TryUpgrade(&Fra.Upg.D17Protect5, 90, 100);
			TryUpgrade(&Fra.Upg.D17Protect6, 90, 100);
			TryUpgrade(&Fra.Upg.D17Protect7, 90, 100);
		}
	}

}

void WaterScript(){
	
	TryUnit(&Fra.Build.Ver,1,100,90);
	if(GetUnits(&Fra.Build.Kr8)>1) TryUnit(&Fra.Build.Ver,3,60,60);

	int NU=GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S15);
	TryUnit(&Fra.Unit.Parom, 1+NU/100, 100, 100);
	
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);

	TryUnit(&Fra.Unit.Santa, 2, 100, 100);
	TryUnit(&Fra.Unit.Santa, 2, 100, 100);

	TryUnit(&Fra.Unit.Fregat, 2, 100, 100);
	TryUnit(&Fra.Unit.Fregat, 2, 100, 100);
	
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