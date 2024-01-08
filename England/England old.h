#define CONQUEST
#include "..\Import.h"
#include "..\EngNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Eng.Unit.Kri.Index;
	city->Init(AiNat);

	city->NIndexBrb=Eng.Unit.B17.Index;
	city->NIndexOff=Eng.Unit.O17.Index;
	city->NIndexFlg=Eng.Unit.F17.Index;

	city->CannonNIndex=Eng.Unit.Can.Index;

}

void Script();
void WarriorsUpg();
void WaterScript();

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

void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// flags
	const HorceBuild=0;
	const CanBuild=1;

	// script	
	if(GetReadyUnits(&Eng.Build.Skl)){
		city->MinWooders = 10;
		city->MinFermers = 25;
		city->PKrepost = 3;
	}
	if(GetUnits(&Eng.Unit.Kri)>40){
		city->MinWooders = 25;
		city->PKrepost = 10;
	}
	if(GetUnits(&Eng.Unit.Kri)>100){
		city->MinWooders = 40;
		city->PKrepost = 30;
	}
	if(GetReadyUnits(&Eng.Build.Mel)&&GetUnits(&Eng.Unit.Kri)>22){
		if(!UpgIsRun(&Eng.Upg.Mel_GETRES)){
			city->MinFermers = 30;
			city->PKrepost = 6;
		}else
		if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)){
			city->MinFermers = 30;
			city->PKrepost = 12;
		}else{
			city->PKrepost = 40;
		}
	}
	if(GetReadyUnits(&Eng.Build.Do1)<3&&GetReadyUnits(&Eng.Build.Skl)){
		city->MinFermers = 15;
		city->MinWooders = 10;
	}	

	// Role planing
	city->AddBranch(Eng.Unit.Pik.Index,brBack,2,290);
	city->AddBranch(Eng.Unit.S15.Index,brBack,120,360);
	city->AddBranch(Eng.Unit.S17.Index,brBack,120,360);
	city->AddBranch(Eng.Unit.D17.Index,brBack,20,180);

	Branch* Pik=city->AddBranch(Eng.Unit.Pik.Index,0,0,0);
	Branch* S15=city->AddBranch(Eng.Unit.S15.Index,0,0,0);
	Branch* S17=city->AddBranch(Eng.Unit.S17.Index,0,0,0);
	Branch* D17=city->AddBranch(Eng.Unit.D17.Index,0,0,0);

	Pik->Prio[brForward] = 2;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 3;	Pik->Part[brCenter] = 2;	Pik->Type[brForward] = btKillers;
	Pik->Prio[brBack] = 0;		Pik->Part[brBack] = 0;
	Pik->Formation=1;

	S15->Prio[brForward] = 0;	S15->Part[brForward] = 0;	//S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 1;	S15->Part[brCenter] = 1;	S15->Type[brCenter] = btTomahawk;
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 0;
	//S15->Formation=1;	

	S17->Prio[brForward] = 3;	S17->Part[brForward] = 1;	S17->Type[brForward] = btTomahawk;
	S17->Prio[brCenter] = 2;	S17->Part[brCenter] = 1;	S17->Type[brCenter] = btKillers;	
	S17->Prio[brBack] = 0;		S17->Part[brBack] = 0;	
	S17->Formation=1;

	D17->Prio[brForward] = 0;	D17->Part[brForward] = 0;
	D17->Prio[brCenter] = 1;	D17->Part[brCenter] = 1;	D17->Type[brForward] = btTomahawk;
	D17->Prio[brBack] = 0;		D17->Part[brBack] = 0;
	
	// Units in buildings
	city->NStrelok = 20;
	if(GetUnits(&Eng.Build.Blg2)) city->NStrelok = 30;
	city->NUnits = 2;

	// Units
	TryUnit(&Eng.Unit.Kri, 1000, 5, 100);
	TryUnit(&Eng.Unit.Kri, 1000, 5, 100);
	TryUnit(&Eng.Unit.Kri, 1000, 5, 100);
	TryUnit(&Eng.Unit.Kri, 1000, 5, 100);

	TryUnit(&Eng.Unit.Sha, 1000, 20, 100);

	TryUnit(&Eng.Unit.Pik, 1000, 20, 100);
	
	if(GetUnits(&Eng.Unit.Pik)<30){
		//TryUnit(&Eng.Unit.S15, 1000, 20, 100);
		//TryUnit(&Eng.Unit.S15, 1000, 20, 100);
		//TryUnit(&Eng.Unit.S15, 1000, 20, 100);
	}
	if(!GetReadyUnits(&Eng.Build.Kr8)) TryUnit(&Eng.Unit.S15, 1000, 20, 100);

	TryUnit(&Eng.Unit.S17, 1000, 20, 100);	
	
	if(city->Flags[HorceBuild]){
		TryUnit(&Eng.Unit.D17, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int D17Cost=GetUnitCost(AiNat,&Eng.Unit.D17,FOOD)*41;
		if(D17Cost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&Eng.Unit.Pik)+GetUnits(&Eng.Unit.S17))/37;
	TryUnit(&Eng.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&Eng.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&Eng.Unit.F17, NeedSquad, 50, 100);

	TryUnit(&Eng.Unit.S18, 1000, 20, 100);
	//TryUnit(&Eng.Unit.O18, 5, 20, 100);
	//TryUnit(&Eng.Unit.B18, 5, 20, 100);
	//TryUnit(&Eng.Unit.F18, 5, 20, 100);

	TryUnit(&Eng.Unit.D17, 1000, 20, 100);
	//TryUnit(&Eng.Unit.KO7, 5, 20, 100);

	TryUnit(&Eng.Unit.D18, 1000, 20, 100);
	//TryUnit(&Eng.Unit.KO8, 5, 20, 100);
	//TryUnit(&Eng.Unit.KF8, 5, 20, 100);

	TryUpgrade(&Eng.Upg.CanCost,95,100);
	TryUpgrade(&Eng.Upg.CanCost3,95,100);
	TryUpgrade(&Eng.Upg.CanCost4,95,100);
	TryUpgrade(&Eng.Upg.CanCost5,95,100);
	TryUpgrade(&Eng.Upg.CanCost6,95,100);
	TryUpgrade(&Eng.Upg.CanCost7,95,100);
	TryUpgrade(&Eng.Upg.CanBuild,95,100);
	TryUpgrade(&Eng.Upg.CanBuild3,95,100);
	TryUpgrade(&Eng.Upg.CanBuild4,95,100);
	TryUpgrade(&Eng.Upg.CanBuild5,95,100);
	TryUpgrade(&Eng.Upg.CanBuild6,95,100);
	TryUpgrade(&Eng.Upg.CanBuild7,95,100);
	
	//for(i=0;i<6;i++){
	//}
	if(GetUnits(&Eng.Unit.D17)>30){
		TryUnit(&Eng.Unit.Can, 5, 80, 100);
	}

	// Peasat distribution
	int NU=GetUnits(&Eng.Unit.Kri)+GetUnits(&Eng.Unit.Pik)+GetUnits(&Eng.Unit.S15)+GetUnits(&Eng.Unit.S17);
	{ //500
		if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)) city->PKrepost=NU>>4;
		if(GetReadyUnits(&Eng.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&Eng.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		if(GetUnits(&Eng.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}
	if(city->MinFermers>250) TryUnit(&Eng.Build.Mel, 3, 100, 95);
	if(city->MinWooders>150) TryUnit(&Eng.Build.Skl, 2, 100, 95);

	// Buildings
	TryUnit(&Eng.Build.Fer, 1, 100, 60);
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)) TryUnit(&Eng.Build.Fer, 3, 100, 60);
	
	TryUnit(&Eng.Build.Kr7, 2, 100, 70);
	
	TryUnit(&Eng.Build.Mel, 2, 100, 95);	
	if(GetUnits(&Eng.Build.Mel)){
		TryUnit(&Eng.Build.Do1, 2, 100, 95);
		TryUnit(&Eng.Build.Skl, 1, 100, 95);
		TryUnit(&Eng.Build.Kuz, 1, 100, 95);
	}

	if(UpgIsRun(&Eng.Upg.Mel_GETRES)){
		TryUnit(&Eng.Build.Do1, 4, 100, 95);
	}
	
	TryUnit(&Eng.Build.Kr8, 2, 100, 70);

	if(GetReadyUnits(&Eng.Build.Do1)>3){
		TryUnit(&Eng.Build.Blg, 1, 100, 70);
	}
	if(GetReadyUnits(&Eng.Build.Kr8)){
		TryUnit(&Eng.Build.Blg, 3, 100, 70);
	}

	TryUnit(&Eng.Build.Cen, 1, 100, 80);
	if(GetReadyUnits(&Eng.Build.Cen)){
		TryUnit(&Eng.Build.Do1, 5, 100, 70);
		TryUnit(&Eng.Build.Do2, 4, 100, 70);		
		TryUnit(&Eng.Build.Blg2, 3, 100, 70);
	}
	if(GetUnits(&Eng.Build.Kr7)>1){
		TryUpgrade(&Eng.Upg.KreCost1, 95, 100);		
	}
	
	TryUnit(&Eng.Build.Hra, 1, 100, 80);	

	//TryUnit(&Eng.Build.Ver, 2, 100, 70);

	// Mine	
	TryUpgrade(&Eng.Upg.MineEnable1, 95, 100);
	TryUnit(&Eng.Build.Stn, 2, 100, 50);
	TryUnit(&Eng.Build.Rud, 1, 90, 30);
	if(GetUnits(&Eng.Build.Kr8)){
		TryUnit(&Eng.Build.Stn, 3, 100, 50);
		TryUnit(&Eng.Build.Rud, 3, 90, 30);
	}
	//if(GetReadyUnits(&Eng.Build.Cen)){
		TryUnit(&Eng.Build.Coa, 1, 80, 30);
		TryUnit(&Eng.Build.Iro, 1, 80, 30);
	//}

	if(GetDifficulty()>1 && UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		TryUpgrade(&Eng.Upg.Gld0, 95, 100);
		TryUpgrade(&Eng.Upg.Gld1, 95, 100);
		TryUpgrade(&Eng.Upg.Gld2, 95, 100);
		TryUpgrade(&Eng.Upg.Gld3, 95, 100);
		TryUpgrade(&Eng.Upg.Stn0, 100, 100);
		TryUpgrade(&Eng.Upg.Stn1, 100, 100);
		TryUpgrade(&Eng.Upg.Stn2, 100, 100);
		//if(UpgIsRun(&Eng.Upg.EnDo1)){
			TryUpgrade(&Eng.Upg.Gld4, 100, 100);
			TryUpgrade(&Eng.Upg.Gld5, 100, 100);
			TryUpgrade(&Eng.Upg.Stn3, 100, 100);
			TryUpgrade(&Eng.Upg.Stn4, 90, 100);
			TryUpgrade(&Eng.Upg.Stn5, 90, 100);
		//}
		TryUpgrade(&Eng.Upg.Iro0, 80, 100);
		TryUpgrade(&Eng.Upg.Iro1, 70, 100);
		TryUpgrade(&Eng.Upg.Iro2, 60, 100);
		TryUpgrade(&Eng.Upg.Iro3, 60, 100);
		TryUpgrade(&Eng.Upg.Coa0, 80, 100);
		TryUpgrade(&Eng.Upg.Coa1, 70, 100);
		TryUpgrade(&Eng.Upg.Coa2, 60, 100);
		TryUpgrade(&Eng.Upg.Coa3, 60, 100);
	}

	// Fild
	//TryUpgrade(&Eng.Upg.CEN52, 90, 100);
	TryUpgrade(&Eng.Upg.CEN57, 90, 100);
	TryUpgrade(&Eng.Upg.CEN55, 90, 100);

	// Food
	if(GetUnits(&Eng.Unit.Kri)>30) TryUpgrade(&Eng.Upg.Mel_GETRES, 90, 100);
	TryUpgrade(&Eng.Upg.Mel_GETRES2, 90, 100);
	TryUpgrade(&Eng.Upg.CEN19, 80, 100);
	TryUpgrade(&Eng.Upg.CEN22, 80, 100);
	TryUpgrade(&Eng.Upg.CEN23, 80, 100);

	// Stages
	TryUpgrade(&Eng.Upg.Kr7_Stage0, 80, 100);
	TryUpgrade(&Eng.Upg.Kr8_Stage0, 80, 100);
	//TryUpgrade(&Eng.Upg.Kr8_Stage1, 80, 100);
	
	//
	TryUpgrade(&Eng.Upg.Do2_ENABLE, 95, 100);
	TryUpgrade(&Eng.Upg.Kre_RAZBROS, 80, 100);	

	// Wood
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		TryUpgrade(&Eng.Upg.WoodEffect1,80,70);
		TryUpgrade(&Eng.Upg.WoodEffect2,80,70);
	}

	if(GetDifficulty()>0 && UpgIsRun(&Eng.Upg.Mel_GETRES2)) WarriorsUpg();

	// Enable warriors

}

void WarriorsUpg(){

	// Kri
	{
		TryUpgrade(&Eng.Upg.KriBuild1,80,70);
		TryUpgrade(&Eng.Upg.KriBuild2,80,70);
		TryUpgrade(&Eng.Upg.KriBuild3,80,70);
	}

	// Mus
	{
		TryUpgrade(&Eng.Upg.MusBuild1,90,70);
		TryUpgrade(&Eng.Upg.MusBuild2,90,70);
	}

	// Pik
	TryUpgrade(&Eng.Upg.PikBuild1, 90, 100);
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		TryUpgrade(&Eng.Upg.PikBuild2, 90, 100);
		TryUpgrade(&Eng.Upg.PikBuild3, 90, 100);
		TryUpgrade(&Eng.Upg.PikBuild4, 90, 100);			
	}
	if(GetUnits(&Eng.Unit.Pik)>50){		

		if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){			
			TryUpgrade(&Eng.Upg.PikAttack, 90, 100);
			TryUpgrade(&Eng.Upg.PikAttack3, 40, 100);
			if(GetUnits(&Eng.Unit.Pik)>70){
				TryUpgrade(&Eng.Upg.PikAttack4, 40, 100);
				TryUpgrade(&Eng.Upg.PikAttack5, 40, 100);
				TryUpgrade(&Eng.Upg.PikAttack6, 40, 100);
				TryUpgrade(&Eng.Upg.PikAttack7, 40, 100);				
			}		
			if(GetUnits(&Eng.Unit.Pik)>70){
				TryUpgrade(&Eng.Upg.PikProtect, 90, 100);
				TryUpgrade(&Eng.Upg.PikProtect3, 90, 100);
				TryUpgrade(&Eng.Upg.PikProtect4, 90, 100);
				TryUpgrade(&Eng.Upg.PikProtect5, 40, 100);
				TryUpgrade(&Eng.Upg.PikProtect6, 40, 100);
				TryUpgrade(&Eng.Upg.PikProtect7, 40, 100);
			}
		}

	}

	// Cen
	{
		TryUpgrade(&Eng.Upg.ArmShield1,90,100);
		TryUpgrade(&Eng.Upg.ArmShield2,50,80);
		TryUpgrade(&Eng.Upg.StrAttPause1,90,100);
	}

	// Mus
	{
		TryUpgrade(&Eng.Upg.MusBuild1,90,70);
		TryUpgrade(&Eng.Upg.MusBuild2,90,70);

		if(GetUnits(&Eng.Unit.S17)>20){
			TryUpgrade(&Eng.Upg.MusAttack, 90, 100);
			TryUpgrade(&Eng.Upg.MusAttack3, 70, 100);
			TryUpgrade(&Eng.Upg.MusAttack4, 50, 100);
		}
		if(GetUnits(&Eng.Unit.S17)>40){
			TryUpgrade(&Eng.Upg.MusAttack5, 50, 100);
			TryUpgrade(&Eng.Upg.MusAttack6, 50, 100);
			TryUpgrade(&Eng.Upg.MusAttack7, 10, 100);
		}
		
		if(GetUnits(&Eng.Unit.S17)>20){
			TryUpgrade(&Eng.Upg.MusProtect, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect3, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.S17)>40){
			TryUpgrade(&Eng.Upg.MusProtect5, 80, 100);
			TryUpgrade(&Eng.Upg.MusProtect6, 80, 100);
			TryUpgrade(&Eng.Upg.MusProtect7, 80, 100);
		}
	}

	// S15
	{
		if(GetUnits(&Eng.Unit.S15)>50){
			TryUpgrade(&Eng.Upg.S15Attack, 90, 100);
			TryUpgrade(&Eng.Upg.S15Attack3, 70, 100);
			TryUpgrade(&Eng.Upg.S15Attack4, 50, 100);
		}
		if(GetUnits(&Eng.Unit.S15)>70){
			TryUpgrade(&Eng.Upg.S15Attack5, 50, 100);
			TryUpgrade(&Eng.Upg.S15Attack6, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack7, 10, 100);
		}
		if(GetUnits(&Eng.Unit.S15)>50){
			TryUpgrade(&Eng.Upg.S15Protect, 30, 100);
			TryUpgrade(&Eng.Upg.S15Protect3, 30, 100);
			TryUpgrade(&Eng.Upg.S15Protect4, 30, 100);
		}
		if(GetUnits(&Eng.Unit.S15)>70){
			TryUpgrade(&Eng.Upg.S15Protect5, 30, 100);
			TryUpgrade(&Eng.Upg.S15Protect6, 30, 100);
			TryUpgrade(&Eng.Upg.S15Protect7, 5, 100);
		}
	}

	// D17
	{
		TryUpgrade(&Eng.Upg.D17Build, 90, 100);		
		if(GetUnits(&Eng.Unit.D17)>20){
			TryUpgrade(&Eng.Upg.D17Attack, 90, 100);
			TryUpgrade(&Eng.Upg.D17Attack3, 90, 100);
			TryUpgrade(&Eng.Upg.D17Attack4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.D17)>40){
			TryUpgrade(&Eng.Upg.D17Attack5, 90, 100);
			TryUpgrade(&Eng.Upg.D17Attack6, 90, 100);
			TryUpgrade(&Eng.Upg.D17Attack7, 90, 100);
		}
		
		if(GetUnits(&Eng.Unit.D17)>20){
			TryUpgrade(&Eng.Upg.D17Protect, 90, 100);
			TryUpgrade(&Eng.Upg.D17Protect3, 90, 100);
			TryUpgrade(&Eng.Upg.D17Protect4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.D17)>40){
			TryUpgrade(&Eng.Upg.D17Protect5, 90, 100);
			TryUpgrade(&Eng.Upg.D17Protect6, 90, 100);
			TryUpgrade(&Eng.Upg.D17Protect7, 90, 100);
		}
	}

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


#if !defined(AMERICAN_CONQUEST_Eng_NATION)
#define AMERICAN_CONQUEST_Eng_NATION

// Engoware nations header file

#include "..\Import.h"

class EngUnits {
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

class EngBuildings {
public:
	GAMEOBJ Rud;
	GAMEOBJ Iro;
	GAMEOBJ Coa;
	GAMEOBJ Stn;

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
	GAMEOBJ Fer;
};

class EngUpgrades {
public:

	//Mine
	GAMEOBJ MineEnable1; //CEN21EN(EN)SpnRudINS(EN)ENABLE
	GAMEOBJ Geology; //CEN21EN

	GAMEOBJ Gld0;
	GAMEOBJ Gld1;
	GAMEOBJ Gld2;
	GAMEOBJ Gld3;
	GAMEOBJ Gld4;
	GAMEOBJ Gld5;

	GAMEOBJ Stn0;
	GAMEOBJ Stn1;
	GAMEOBJ Stn2;
	GAMEOBJ Stn3;
	GAMEOBJ Stn4;
	GAMEOBJ Stn5;

	GAMEOBJ Iro0;
	GAMEOBJ Iro1;
	GAMEOBJ Iro2;
	GAMEOBJ Iro3;

	GAMEOBJ Coa0;
	GAMEOBJ Coa1;
	GAMEOBJ Coa2;
	GAMEOBJ Coa3;

	// Food
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
	GAMEOBJ Kr8_Stage1;

	GAMEOBJ Do2_ENABLE; //ENABLE UNITS GRP 1 ...Do2
	GAMEOBJ Kre_RAZBROS; //RAZBROS GRP 1 ...Mus -35%
	
	// Wood
	GAMEOBJ WoodEffect1; //CEN29SP
	GAMEOBJ WoodEffect2; //CEN30SP
	
	// Kri
	GAMEOBJ KriBuild1; //CEN24SP
	GAMEOBJ KriBuild2; //CEN36SP
	GAMEOBJ KriBuild3; //CEN25SP

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
	GAMEOBJ KreCost1; //CEN25EN

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

class EngNation {
public:
	EngNation();
	EngUnits Unit;
	EngBuildings Build;
	EngUpgrades Upg;
};
extern EngNation Eng;

#endif

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "EngNation.h"

EngNation::EngNation() {
	
	// Units	
	RegisterUnitType(&Unit.Kri, "EngKri(EN)");
	RegisterUnitType(&Unit.Pik, "EngPik(EN)");	
	RegisterUnitType(&Unit.Sha, "SpnSha(EN)");

	RegisterUnitType(&Unit.S15, "SpnS15(EN)");

	RegisterUnitType(&Unit.S17, "EngMus(EN)");
	RegisterUnitType(&Unit.O17, "EngOf17(EN)");
	RegisterUnitType(&Unit.B17, "EngB17(EN)");
	RegisterUnitType(&Unit.F17, "EngF17(EN)");

	RegisterUnitType(&Unit.S18, "EngM18(EN)");
	RegisterUnitType(&Unit.O18, "EngOf18(EN)");
	RegisterUnitType(&Unit.B18, "EngB18(EN)");
	RegisterUnitType(&Unit.F18, "EngF18(EN)");

	RegisterUnitType(&Unit.D17, "EngD17(EN)");
	RegisterUnitType(&Unit.KO7, "EngKOf17(EN)");

	RegisterUnitType(&Unit.D18, "EngD18(EN)");
	RegisterUnitType(&Unit.KO8, "EngKOf18(EN)");
	RegisterUnitType(&Unit.KF8, "EngKF18(EN)");

	RegisterUnitType(&Unit.Can, "ArtPus(EN)");	
	//RegisterUnitType(&Unit., "");
	
	// Buildings
	RegisterUnitType(&Build.Rud, "SpnRud(EN)");
	RegisterUnitType(&Build.Iro, "SpnIro(EN)");
	RegisterUnitType(&Build.Coa, "SpnCoa(EN)");
	RegisterUnitType(&Build.Stn, "SpnStn(EN)");

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
	RegisterUnitType(&Build.Ver, "EngVer(EN)");
	RegisterUnitType(&Build.Fer, "EngFer(EN)");	
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
	//RegisterUpgrade(&Upg.Kr8_Stage1, "UPSTENGKRE21");

	RegisterUpgrade(&Upg.Do2_ENABLE, "EngDo2(EN)ENABLE");

	RegisterUpgrade(&Upg.Kre_RAZBROS, "CEN56EN");

	// Wood
	{
		RegisterUpgrade(&Upg.WoodEffect1, "CEN29EN");
		RegisterUpgrade(&Upg.WoodEffect2, "CEN30EN");
	}
	
	// Mine
	{
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

	// Cen
	{
		RegisterUpgrade(&Upg.KreCost1, "CEN25EN");
	}

	// Kri
	{
		RegisterUpgrade(&Upg.KriBuild1, "CEN48EN");
		RegisterUpgrade(&Upg.KriBuild2, "CEN36EN");		
		RegisterUpgrade(&Upg.KriBuild3, "CEN24EN");
	}

	// Mus
	{
		RegisterUpgrade(&Upg.MusBuild1, "CEN07EN");
		RegisterUpgrade(&Upg.MusBuild2, "CEN09EN");
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
	
	// Krepost
	{
		RegisterUpgrade(&Upg.KreCost1, "CEN25EN");
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
		RegisterUpgrade(&Upg.StrAttPause1, "CEN01EN");
	}

	// D17
	{
		RegisterUpgrade(&Upg.D17Build, "CEN39EN");

		RegisterUpgrade(&Upg.D17Attack, "EngD17(EN)ATTACK");
		RegisterUpgrade(&Upg.D17Attack3, "EngD17(EN)ATTACK3");
		RegisterUpgrade(&Upg.D17Attack4, "EngD17(EN)ATTACK4");
		RegisterUpgrade(&Upg.D17Attack5, "EngD17(EN)ATTACK5");
		RegisterUpgrade(&Upg.D17Attack6, "EngD17(EN)ATTACK6");
		RegisterUpgrade(&Upg.D17Attack7, "EngD17(EN)ATTACK7");
		
		RegisterUpgrade(&Upg.D17Protect, "EngD17(EN)SHIELD");
		RegisterUpgrade(&Upg.D17Protect3, "EngD17(EN)SHIELD3");
		RegisterUpgrade(&Upg.D17Protect4, "EngD17(EN)SHIELD4");
		RegisterUpgrade(&Upg.D17Protect5, "EngD17(EN)SHIELD5");
		RegisterUpgrade(&Upg.D17Protect6, "EngD17(EN)SHIELD6");
		RegisterUpgrade(&Upg.D17Protect7, "EngD17(EN)SHIELD7");
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
		RegisterUpgrade(&Upg.MusBuild1, "CEN07EN");
		RegisterUpgrade(&Upg.MusBuild2, "CEN09EN");

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


	
	//RegisterUpgrade(&Upg., "");
}

EngNation Eng;