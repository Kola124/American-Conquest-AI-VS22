#define CONQUEST
#include "..\Import.h"
#include "..\IncNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Inc.Unit.Kri.Index;
	city->NIndexBrb = Inc.Unit.Sha.Index;
	city->NIndexFlg = Inc.Unit.Sha.Index;
	city->NIndexOff = Inc.Unit.Vog.Index;
	city->Init(AiNat);
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
		city->DefenceLess=1;
		city->LandType=1;
		WaterScript();
		break;
	};
	Script();
	
	city->Process();
	city->ParomNIndex=Inc.Unit.Par.Index;
	
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

	// Role planing
	city->AddBranch(Inc.Unit.Pik.Index,brBack,16,140);
	city->AddBranch(Inc.Unit.Lut.Index,brBack,20,360);
	city->AddBranch(Inc.Unit.Trb.Index,brBack,10,260);
	//city->AddBranch(Inc.Unit.Sha.Index,brBack,50,120);
	city->AddBranch(Inc.Unit.Pra.Index,brBack,40,340);
	//city->AddBranch(Inc.Unit.Vog.Index, brBack, 15, 25);

	Branch* Pik=city->AddBranch(Inc.Unit.Pik.Index,0,0,0);
	Branch* Lut=city->AddBranch(Inc.Unit.Lut.Index,0,0,0);
	Branch* Trb=city->AddBranch(Inc.Unit.Trb.Index,0,0,0);
	Branch* Pra=city->AddBranch(Inc.Unit.Pra.Index,0,0,0);
	//Branch* Sha = city->AddBranch(Inc.Unit.Sha.Index, 0, 0, 0);
	//Branch* Vog = city->AddBranch(Inc.Unit.Vog.Index, 0, 0, 0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;
	Pik->Prio[brCenter] = 2;	Pik->Part[brCenter] = 0;	Pik->Type[brCenter] = btKillers;
	Pik->Prio[brBack] = 1;		Pik->Part[brBack] = 0;
	Pik->Formation = 1;
	if(GetDifficulty()<2) Pik->Part[brCenter] = 1;

	Lut->Prio[brForward] = 3;	Lut->Part[brForward] = 0;	Lut->Type[brForward] = btFire;
	Lut->Prio[brCenter] = 2;	Lut->Part[brCenter] = 2;	Lut->Type[brCenter] = btTomahawk;
	Lut->Prio[brBack] = 1;		Lut->Part[brBack] = 1;
	Lut->Formation = 1;
	if(GetDifficulty()<2) Lut->Part[brForward] = 1;
	if(GetDifficulty()==0) Lut->Part[brCenter] = 0;

	Trb->Prio[brForward] = 3;	Trb->Part[brForward] = 0;	//Trb->Type[brForward] = btStorm;
	Trb->Prio[brCenter] = 2;	Trb->Part[brCenter] = 1;	Trb->Type[brCenter] = btTomahawk;
	Trb->Prio[brBack] = 1;		Trb->Part[brBack] = 0;
	Trb->Formation = 1;

	Pra->Prio[brForward] = 3;	Pra->Part[brForward] = 1;	Pra->Type[brForward] = btTomahawk;
	Pra->Prio[brCenter] = 2;	Pra->Part[brCenter] = 1;	Pra->Type[brCenter] = btKillers;
	Pra->Prio[brBack] = 1;		Pra->Part[brBack] = 0;

	// Units in buildings
	city->NUnits = 2;
	if(GetUnits(&Inc.Unit.Pik)>100) city->NUnits = 5;
	//if(GetUnits(&May.Unit.Voi)>100) city->NUnits = 15;
	//if(GetUnits(&May.Unit.Voi)>250) city->NUnits = 25;	

	// Producing: Units & Convertors
	city->PKrepost=0;

	int NPeas;
	if(UpgIsRun(&Inc.Upg.Mel_GETRES2)){
		NPeas=800;
	}else{
		NPeas=80-10*GetDifficulty();
	}
	TryUnit(&Inc.Unit.Kri, NPeas, 20, 100);
	TryUnit(&Inc.Unit.Kri, NPeas, 10, 100);
	TryUnit(&Inc.Unit.Kri, NPeas, 10, 100);
	TryUnit(&Inc.Unit.Kri, NPeas, 10, 100);
	TryUnit(&Inc.Unit.Kri, NPeas, 10, 100);
	TryUnit(&Inc.Unit.Kri, NPeas, 10, 100);

	if(UpgIsRun(&Inc.Upg.Mel_GETRES2)||GetPeaceTimeLeft()<2){
						
		TryUnit(&Inc.Unit.Pra, 100000, 20, 100);
		TryUnit(&Inc.Unit.Pra, 100000, 10, 100);
		city->PKrepost = 50;
		if(UpgIsRun(&Inc.Upg.Do2_ENABLE)){
			TryUnit(&Inc.Unit.Pra, 100000, 20, 100);
			TryUnit(&Inc.Unit.Pra, 100000, 10, 100);
			TryUnit(&Inc.Unit.Pra, 100000, 10, 100);
			TryUnit(&Inc.Unit.Pra, 100000, 10, 100);
			TryUnit(&Inc.Unit.Pra, 100000, 10, 100);			
		}

		TryUnit(&Inc.Unit.Pik, 100000, 20, 100);
		if(GetUnits(&Inc.Unit.Kri)<700){		
			TryUnit(&Inc.Unit.Pik, 100000, 20, 100);
			TryUnit(&Inc.Unit.Pik, 100000, 10, 100);
			city->PKrepost = 25;
		}

		if(GetUnits(&Inc.Unit.Kri)<500){
			TryUnit(&Inc.Unit.Lut, 100000, 20, 50);
			city->PKrepost = 15;			
		}
		TryUnit(&Inc.Unit.Lut, 100000, 20, 40);
		if(GetUnits(&Inc.Unit.Pik)>80) TryUnit(&Inc.Unit.Lut, 100000, 20, 60);
		if(GetUnits(&Inc.Unit.Pik)>140) TryUnit(&Inc.Unit.Lut, 100000, 20, 80);		
		
		if(GetUnits(&Inc.Unit.Sha)<5) TryUnit(&Inc.Unit.Sha, 1000, 20, 100);
		if(GetUnits(&Inc.Unit.Vog)<5) TryUnit(&Inc.Unit.Vog, 1000, 20, 100);
	}

	int NeedSquad = (GetUnits(&Inc.Unit.Pik)+GetUnits(&Inc.Unit.Lut)+GetUnits(&Inc.Unit.Trb)) / 5;
	//TryUnit(&Inc.Unit.Vog, NeedSquad, 50, 100);
	//TryUnit(&Inc.Unit.Sha, NeedSquad, 50, 100);

	// Dom & Kre & Blg ...
	{
		if(GetReadyUnits(&Inc.Build.Mel)){
			TryUnit(&Inc.Build.Do1, 2, 100, 50);
			if(GetUnits(&Inc.Build.Skl)) TryUnit(&Inc.Build.Do1, 4, 100, 50);
			TryUnit(&Inc.Build.Kre, 1, 100, 80);
			if(UpgIsRun(&Inc.Upg.Do3_ENABLE)) TryUnit(&Inc.Build.Kre, 3, 100, 80);
			
			if(UpgIsRun(&Inc.Upg.Do3_ENABLE)){
				TryUnit(&Inc.Build.Do1, 6, 30, 70);
				TryUnit(&Inc.Build.Do3, 3, 100, 70);
				TryUnit(&Inc.Build.Do2, 5, 30, 70);
				if(GetUnits(&Inc.Build.Kre)>1){
					TryUnit(&Inc.Build.Do1, 6, 100, 70);
					TryUnit(&Inc.Build.Do3, 7, 100, 70);
					TryUnit(&Inc.Build.Do2, 5, 100, 70);
				}
			}			
			
			TryUpgrade(&Inc.Upg.Do2_ENABLE, 90, 100);			
			TryUpgrade(&Inc.Upg.Do3_ENABLE, 100, 100);
		}
		
		// Stages
		if(UpgIsRun(&Inc.Upg.Mel_GETRES2)){		
			TryUpgrade(&Inc.Upg.KreStage0, 90, 100);
			TryUpgrade(&Inc.Upg.KreStage1, 90, 100);
			if(GetUnits(&Inc.Build.Do3)>1) TryUpgrade(&Inc.Upg.KreStage2, 90, 100);
		}

		// More Farms
		if(GetMaxUnits(AiNat)-GetCurrentUnits(AiNat)<120){
			if(GetUnits(&Inc.Build.Kre)>1) TryUpgrade(&Inc.Upg.Do3Farms1, 90, 100);
			TryUpgrade(&Inc.Upg.Do3Farms2, 90, 100);
		}
		
		// Blg
		if(GetReadyUnits(&Inc.Build.Kre)>1){
			TryUnit(&Inc.Build.Blg, 5, 100, 70);
		}

		//TryUnit(&Inc.Build.Ver, 2, 100, 70);
	}

	
	// Economica: добыча ресурсов
	{
		// Peasat distribution
		int NU=GetUnits(&Inc.Unit.Kri)+GetUnits(&Inc.Unit.Pik)+GetUnits(&Inc.Unit.Lut);
		if(NU){ //500
			if(GetReadyUnits(&Inc.Build.Mel)){
				city->MinFermers = NU/4;
				if(GetMoney(FOOD)>120000) city->MinFermers = NU/10;
				if(!UpgIsRun(&Inc.Upg.Mel_GETRES2)) city->MinFermers=NU/3+30;
				if(city->MinFermers>300) city->MinFermers = 300;
				if(GetMoney(FOOD)>1000000) city->MinFermers = 30;
			}		
			if(GetUnits(&Inc.Build.Skl)){
				city->MinWooders = NU/7;
				if(!UpgIsRun(&Inc.Upg.Mel_GETRES2)) city->MinWooders=NU/5;
				if(city->MinWooders>200) city->MinWooders = 200;
				if(GetMoney(WOOD)>500000) city->MinWooders = 30;
			}
		}

		// Mel & Skl
		{
			TryUnit(&Inc.Build.Mel, 2, 100, 95);
			TryUnit(&Inc.Build.Skl, 1, 100, 80);
			if(GetUnits(&Inc.Build.Kre)>1){
				if(city->MinFermers>70) TryUnit(&Inc.Build.Mel, 2, 100, 95);
				if(city->MinFermers>140) TryUnit(&Inc.Build.Mel, 3, 100, 95);
				if(city->MinWooders>70) TryUnit(&Inc.Build.Mel, 2, 100, 95);
			}			
		}

		// Food & field
		{
			TryUpgrade(&Inc.Upg.CEN10, 100, 100);
			//TryUpgrade(&Inc.Upg.CEN52, 80, 100);
			//TryUpgrade(&Inc.Upg.CEN12, 80, 100);

			if(UpgIsRun(&Inc.Upg.CEN10)&&UpgIsRun(&Inc.Upg.Do3_ENABLE)){
				TryUpgrade(&Inc.Upg.CEN01, 80, 100);
				TryUpgrade(&Inc.Upg.CEN02, 80, 100);
				TryUpgrade(&Inc.Upg.CEN03, 80, 100);
			}
			
			TryUpgrade(&Inc.Upg.Mel_GETRES, 90, 100);
			TryUpgrade(&Inc.Upg.Mel_GETRES2, 90, 100);
		}
		
		// Mine
		if(GetMoney(FOOD)>1500){
			TryUnit(&Inc.Build.Stn, 1, 100, 80);
			TryUnit(&Inc.Build.Rud, 1, 80, 30);
			if(UpgIsRun(&Inc.Upg.Mel_GETRES2)){
				TryUnit(&Inc.Build.Stn, 4, 100, 50);
				TryUnit(&Inc.Build.Rud, 4, 90, 30);
				//TryUnit(&Inc.Build.Coa, 1, 80, 30);
				TryUnit(&Inc.Build.Iro, 1, 80, 30);

				if(GetDifficulty()>1){
					TryUpgradeEx(&Inc.Upg.Stn0, 100, 100, 9000, 4000);
					TryUpgradeEx(&Inc.Upg.Stn1, 100, 100, 6000, 1000);
					TryUpgradeEx(&Inc.Upg.Stn2, 100, 100, 6000, 1000);
					TryUpgradeEx(&Inc.Upg.Stn3, 100, 100, 6000, 1000);
					
					TryUpgradeEx(&Inc.Upg.Gld0, 95, 60, 9000, 4000);
					TryUpgradeEx(&Inc.Upg.Gld1, 95, 60, 6000, 1000);
					TryUpgradeEx(&Inc.Upg.Gld2, 95, 60, 6000, 1000);
					TryUpgradeEx(&Inc.Upg.Gld3, 95, 60, 6000, 1000);
					/*
					if(UpgIsRun(&Inc.Upg.EnDo1)){
						TryUpgrade(&Inc.Upg.Gld4, 100, 100);
						TryUpgrade(&Inc.Upg.Gld5, 100, 100);
						TryUpgrade(&Inc.Upg.Stn3, 100, 100);
						TryUpgrade(&Inc.Upg.Stn4, 90, 100);
						TryUpgrade(&Inc.Upg.Stn5, 90, 100);
					}
					*/
					TryUpgradeEx(&Inc.Upg.Iro0, 90, 20, 9000, 4000);
					TryUpgradeEx(&Inc.Upg.Iro1, 80, 20, 6000, 1000);
					//TryUpgrade(&Inc.Upg.Iro2, 70, 100);
					//TryUpgrade(&Inc.Upg.Coa0, 90, 100);
					//TryUpgrade(&Inc.Upg.Coa1, 80, 100);
					//TryUpgrade(&Inc.Upg.Coa2, 70, 100);
				}
			}
		}
	}

	if(GetDifficulty()>0 && UpgIsRun(&Inc.Upg.Mel_GETRES2)) WarriorsUpg();

	// Enable warriors

}

void WarriorsUpg(){
	
	// Kri
	if(GetUnits(&Inc.Build.Kre)>2){
		TryUpgrade(&Inc.Upg.KriBu1,95,100);
		TryUpgrade(&Inc.Upg.KriBu2,95,100);
	}

	int NU=GetUnits(&Inc.Unit.Pik)+GetUnits(&Inc.Unit.Lut)+GetUnits(&Inc.Unit.Pra);
	
	// Warriors
	if(NU>50){
		TryUpgrade(&Inc.Upg.WarLife, 30, 100);
		TryUpgrade(&Inc.Upg.Strike1, 90, 100);
	}

	// Pik
	if(GetUnits(&Inc.Unit.Pik)>30){
		TryUpgrade(&Inc.Upg.PikBuild, 90, 100);
		TryUpgrade(&Inc.Upg.PikAtt, 90, 100);		
		if(UpgIsRun(&Inc.Upg.Mel_GETRES2)&&GetMoney(GOLD)>3000){
			TryUpgrade(&Inc.Upg.PikAtt3, 90, 100);
			TryUpgrade(&Inc.Upg.PikAtt4, 90, 100);
			TryUpgrade(&Inc.Upg.PikAtt5, 90, 100);
			TryUpgrade(&Inc.Upg.PikAtt6, 90, 100);
			TryUpgrade(&Inc.Upg.PikAtt7, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi3, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi4, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi5, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi6, 90, 100);
			TryUpgrade(&Inc.Upg.PikShi7, 90, 100);
		}
	}

	// Lut
	if(GetUnits(&Inc.Unit.Lut)>30){
		if(GetUnits(&Inc.Unit.Lut)>50 && GetUnits(&Inc.Build.Kre)>1){
			TryUpgrade(&Inc.Upg.LutRaz1, 100, 100);
			TryUpgrade(&Inc.Upg.LutRaz2, 100, 100);
		}
		// attack
		if(UpgIsRun(&Inc.Upg.PraShi7)&&UpgIsRun(&Inc.Upg.PraShi7)){
			TryUpgrade(&Inc.Upg.LutAtt, 90, 100);
			TryUpgrade(&Inc.Upg.LutAtt3, 90, 100);
			TryUpgrade(&Inc.Upg.LutAtt4, 90, 100);
			TryUpgrade(&Inc.Upg.LutAtt5, 90, 100);
			TryUpgrade(&Inc.Upg.LutAtt6, 90, 100);
			TryUpgrade(&Inc.Upg.LutAtt7, 90, 100);
		}
		// defence
		TryUpgrade(&Inc.Upg.LutDef, 90, 100);
		TryUpgrade(&Inc.Upg.LutDef3, 90, 100);
		TryUpgrade(&Inc.Upg.LutDef4, 90, 100);
		if(UpgIsRun(&Inc.Upg.PraShi7)&&UpgIsRun(&Inc.Upg.PraShi7)){
			TryUpgrade(&Inc.Upg.LutDef5, 90, 100);
			TryUpgrade(&Inc.Upg.LutDef6, 90, 100);
			TryUpgrade(&Inc.Upg.LutDef7, 90, 100);
		}
	}

	// Pra
	if(GetUnits(&Inc.Unit.Pra)>50){
		// build speed
		TryUpgrade(&Inc.Upg.PraBuild, 90, 100);
		// attack
		TryUpgrade(&Inc.Upg.PraShi, 90, 100);
		TryUpgrade(&Inc.Upg.PraShi3, 90, 100);
		TryUpgrade(&Inc.Upg.PraShi4, 90, 100);
		if(GetUnits(&Inc.Unit.Pra)>75&&(GetExtraction(GOLD)>20||GetMoney(GOLD)>4000)){
			TryUpgrade(&Inc.Upg.PraShi5, 90, 100);
			TryUpgrade(&Inc.Upg.PraShi6, 90, 100);
			TryUpgrade(&Inc.Upg.PraShi7, 90, 100);
		}
		// defence
		TryUpgrade(&Inc.Upg.PraAtt, 90, 100);
		TryUpgrade(&Inc.Upg.PraAtt3, 90, 100);
		TryUpgrade(&Inc.Upg.PraAtt4, 90, 100);
		if(GetUnits(&Inc.Unit.Pra)>85&&(GetExtraction(GOLD)>20||GetMoney(GOLD)>4000)){
			TryUpgrade(&Inc.Upg.PraAtt5, 90, 100);
			TryUpgrade(&Inc.Upg.PraAtt6, 90, 100);
			TryUpgrade(&Inc.Upg.PraAtt7, 90, 100);
		}
	}

	// Trb
	{
	}

	//Vog
	{
		// defence
		if(UpgIsRun(&Inc.Upg.Mel_GETRES2)){
			TryUpgrade(&Inc.Upg.VogDef, 90, 100);
			TryUpgrade(&Inc.Upg.VogDef3, 50, 100);
			TryUpgrade(&Inc.Upg.VogDef4, 50, 100);
		}
	}
}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Inc.Build.Skl)) TryUnit(&Inc.Build.Ver,1,100,90);
	if(GetUnits(&Inc.Build.Kre)>1) TryUnit(&Inc.Build.Ver,3,60,60);

	int NU=GetUnits(&Inc.Unit.Pik)+GetUnits(&Inc.Unit.Lut)+GetUnits(&Inc.Unit.Pra)+city->NFirers;
	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&Inc.Unit.Par, NPar, 100, 100);
	
	TryUnit(&Inc.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&Inc.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
		TryUnit(&Inc.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Inc.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Inc.Upg.Ka3Build6)){
		TryUnit(&Inc.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Inc.Upg.ParSpeed1,100,100);
	TryUpgrade(&Inc.Upg.ParSpeed2,100,100);
	TryUpgrade(&Inc.Upg.ParSpeed3,100,100);
	TryUpgrade(&Inc.Upg.ParSpeed4,100,100);
	TryUpgrade(&Inc.Upg.ParSpeed5,100,100);
	TryUpgrade(&Inc.Upg.ParSpeed6,100,100);

	TryUpgrade(&Inc.Upg.Ka3Build1,100,100);
	TryUpgrade(&Inc.Upg.Ka3Build2,100,100);
	TryUpgrade(&Inc.Upg.Ka3Build3,100,100);
	TryUpgrade(&Inc.Upg.Ka3Build4,100,100);
	TryUpgrade(&Inc.Upg.Ka3Build5,100,100);
	TryUpgrade(&Inc.Upg.Ka3Build6,100,100);

	if(GetUnits(&Inc.Unit.Ka1)>3){
		TryUpgrade(&Inc.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Inc.Upg.Ka1Fishing2,90,100);
		TryUpgrade(&Inc.Upg.Ka1Fishing3,80,100);
		TryUpgrade(&Inc.Upg.Ka1Fishing4,70,100);
		TryUpgrade(&Inc.Upg.Ka1Fishing5,60,100);
		TryUpgrade(&Inc.Upg.Ka1Fishing6,70,100);
	}

};

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