#define CONQUEST
#include "..\Import.h"
#include "..\AICity.h"
#include "..\AztNation.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Azt.Unit.Kri.Index;
	city->Init(AiNat);

	city->NIndexBrb=Azt.Unit.Sha.Index;
	city->NIndexFlg=Azt.Unit.Sha.Index;
	city->NIndexOff=Azt.Unit.Vog.Index;

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
	
	//city->DefenceLess=GetRND(2);
	city->Process();
	city->ParomNIndex=Azt.Unit.Par.Index;
	
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
	city->AddBranch(Azt.Unit.Met.Index,brBack,24,220);
	city->AddBranch(Azt.Unit.Lut.Index,brBack,48,220);
	city->AddBranch(Azt.Unit.Vog.Index,brBack,15,25);
	city->AddBranch(Azt.Unit.Sha.Index,brBack,85,125);

	Branch* Met=city->AddBranch(Azt.Unit.Met.Index,0,0,0);
	Branch* Lut=city->AddBranch(Azt.Unit.Lut.Index,0,0,0);
	Branch* Vog=city->AddBranch(Azt.Unit.Vog.Index,0,0,0);
	Branch* Sha=city->AddBranch(Azt.Unit.Sha.Index,0,0,0);

	Met->Prio[brForward] = 3;	Met->Part[brForward] = 0;	Met->Type[brForward] = btStorm;
	Met->Prio[brCenter] = 2;	Met->Part[brCenter] = 1;	Met->Type[brCenter] = btTomahawk;
	Met->Prio[brBack] = 0;
	Met->Formation=1;
	//Met->Domovoi=0;

	Lut->Prio[brForward] = 3;	Lut->Part[brForward] = 0;	Lut->Type[brForward] = btFire;
	Lut->Prio[brCenter] = 2;	Lut->Part[brCenter] = 1;	Lut->Type[brCenter] = btTomahawk;
	Lut->Prio[brBack] = 0;		Lut->Part[brBack] = 0;
	Lut->Formation=1;

	Vog->Prio[brForward] = 3;	Vog->Part[brForward] = 0;
	Vog->Prio[brCenter] = 2;	Vog->Part[brCenter] = 0;
	Vog->Prio[brBack] = 0;		Lut->Part[brBack] = 0;

	Sha->Prio[brForward] = 3;	Sha->Part[brForward] = 1;	Sha->Type[brForward] = btStorm;
	Sha->Prio[brCenter] = 2;	Sha->Part[brCenter] = 1;	Sha->Type[brCenter] = btKillers;
	Sha->Prio[brBack] = 0;
	Sha->Min=85;
	
	// Units in buildings	
	city->NUnits = 2;
	//if(GetUnits(&Azt.Unit.Met)>40&&GetUnits(&Azt.Unit.Met)<100) city->NUnits = 20;

	// Convertors
	city->PKrepost = 5+GetUnits(&Azt.Unit.Kri)/4;
	//if(GetUnits(&Azt.Unit.Met)) city->PKrepost = 5;
	//if(GetUnits(&Azt.Unit.Lut)) city->PKrepost = 15;

	// Units
	if(UpgIsRun(&Azt.Upg.Do2_ENABLE)){
		TryUnit(&Azt.Unit.Lut, 1000, 20, 100);
		TryUnit(&Azt.Unit.Lut, 1000, 10, 100);
		TryUnit(&Azt.Unit.Lut, 1000, 10, 100);
	}	
	TryUnit(&Azt.Unit.Lut, 1000, 20, 100);
	TryUnit(&Azt.Unit.Met, 1000, 20, 100);

	TryUnit(&Azt.Unit.Kri, 1000, 20, 100);
	TryUnit(&Azt.Unit.Kri, 1000, 10, 100);
	TryUnit(&Azt.Unit.Kri, 1000, 10, 100);
	if(GetUnits(&Azt.Unit.Sha)<20) TryUnit(&Azt.Unit.Sha, 1000, 20, 100);
	if(GetUnits(&Azt.Unit.Vog)<10) TryUnit(&Azt.Unit.Vog, 1000, 20, 100);

	int NeedSquad=(GetUnits(&Azt.Unit.Met)+GetUnits(&Azt.Unit.Lut))/50;
	TryUnit(&Azt.Unit.Vog, NeedSquad, 50, 100);
	TryUnit(&Azt.Unit.Sha, NeedSquad, 50, 100);

	// Buildings
	TryUnit(&Azt.Build.Mel, 1, 100, 70);
	if(GetUnits(&Azt.Build.Mel)){
		
		TryUnit(&Azt.Build.Do1, 1, 100, 40);
		TryUnit(&Azt.Build.Kre, 2, 100, 80);
		TryUnit(&Azt.Build.Skl, 1, 100, 70);

		if(GetReadyUnits(&Azt.Build.Skl)) TryUnit(&Azt.Build.Mel, 2, 100, 70);		
		
		TryUnit(&Azt.Build.Do1, 3, 60, 80);
		if(UpgIsRun(&Azt.Upg.Do2_ENABLE)) TryUnit(&Azt.Build.Do1, 3, 100, 80);
		TryUnit(&Azt.Build.Do2, 4, 100, 80);		

		if(GetUnits(&Azt.Build.Kre)>1){
			TryUpgrade(&Azt.Upg.MetBuild, 90, 100);		
		}
		
		if(UpgIsRun(&Azt.Upg.Mel_GETRES2)) TryUnit(&Azt.Build.Cen, 1, 100, 70);

		TryUpgrade(&Azt.Upg.UPSTATCKRE0, 80, 100);
	}
	
	if(GetReadyUnits(&Azt.Build.Do1)>1){
		if(GetReadyUnits(&Azt.Build.Cen)){
			TryUpgrade(&Azt.Upg.UPSTATCKRE1, 90, 100);
			TryUpgrade(&Azt.Upg.UPSTATCKRE2, 90, 100);
			TryUpgrade(&Azt.Upg.UPSTATCVER0, 90, 100);
			TryUpgrade(&Azt.Upg.UPSTATCVER1, 90, 100);
		}
		
		TryUnit(&Azt.Build.Hra, 1, 100, 70);
	}

	// Center
	if(UpgIsRun(&Azt.Upg.ShaLife1)){
		TryUpgrade(&Azt.Upg.ConstrBuild1,90,100);
	}

	// Do2Enable блоггаузы
	int MaxBlg=0;
	int MaxBl2=GetUnits(&Azt.Unit.Met)/30;	
	TryUpgrade(&Azt.Upg.Do2_ENABLE, 100, 100);
	if(UpgIsRun(&Azt.Upg.Do2_ENABLE)){
		TryUpgrade(&Azt.Upg.KriBu1,90,100);
		TryUpgrade(&Azt.Upg.KriBu2,90,100);

		if(GetUnits(&Azt.Build.Do2)>2){
			TryUpgrade(&Azt.Upg.CEN07, 80, 100);
			
			TryUpgrade(&Azt.Upg.BlgPrice,90,100);
			if(UpgIsDone(&Azt.Upg.BlgPrice)){
				MaxBlg=11;
				MaxBl2=13;
			}
			
			TryUnit(&Azt.Build.Skl,3,80,70);
			TryUnit(&Azt.Build.Hra,2,80,70);
			TryUnit(&Azt.Build.Cen,2,80,70);
		}
	}
	if(GetUnits(&Azt.Build.Do1)>1){
		int MaxBlg=2;
		int MaxBl2=5;
	}
	int NU=GetUnits(&Azt.Unit.Met)+GetUnits(&Azt.Unit.Lut)+GetUnits(&Azt.Unit.Sha);
	int NBlg=NU/40;
	if(NBlg>MaxBlg) NBlg=MaxBlg;
	int NBl2=NU/20;
	if(NBl2>MaxBl2) NBl2=MaxBl2;
	TryUnit(&Azt.Build.Blg, NBlg, 60, 70);
	TryUnit(&Azt.Build.Blg2, NBl2, 60, 70);

	//TryUnit(&Azt.Build.Ver, 2, 100, 70);
	
	// прочность зданий	
	TryUpgrade(&Azt.Upg.CEN02, 90, 100);
	TryUpgrade(&Azt.Upg.CEN03, 90, 100);

	// Peasat distribution
	NU=GetUnits(&Azt.Unit.Kri)+GetUnits(&Azt.Unit.Met)+GetUnits(&Azt.Unit.Lut)+GetUnits(&Azt.Unit.Sha);
	if(NU){ //500
		if(!UpgIsRun(&Azt.Upg.Mel_GETRES2)) city->PKrepost=NU>>4;
		// Fermers
		if(GetReadyUnits(&Azt.Build.Mel)){
			city->MinFermers = NU/5;
			if(GetMoney(FOOD)>120000) city->MinFermers = NU/10;
			if(!UpgIsRun(&Azt.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>100){
				city->MinFermers = 100;
				//if(UpgIsRun(&Azt.Upg.Mel_GETRES2)) city->MinFermers = 50;
			}
		}
		int NMeln=1+city->MinFermers/40;
		if(NMeln>3) NMeln=3;
		//TryUnit(&Azt.Build.Mel, NMeln, 100, 70);
		
		// Wooders
		if(GetUnits(&Azt.Build.Skl)){
			city->MinWooders = NU/4;
			if(!UpgIsRun(&Azt.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200){
				city->MinWooders = 200;
				if(GetUnits(&Azt.Build.Kre)>1) city->MinWooders = 80;
			}
		}
		int NSklad=1+(city->MinWooders+city->MinHuters)/50;
		if(NSklad>6) NSklad=6;
		//TryUnit(&Azt.Build.Skl, NSklad, 100, 70);
	}
	
	// Food & Field	
	TryUpgrade(&Azt.Upg.Mel_GETRES, 80, 100);
	TryUpgrade(&Azt.Upg.Mel_GETRES2, 95, 100);	
	
	TryUpgrade(&Azt.Upg.CEN01, 49, 100);
	TryUpgrade(&Azt.Upg.CEN10, 20, 100);
	TryUpgrade(&Azt.Upg.CEN12, 20, 100);
	TryUpgrade(&Azt.Upg.CEN52, 20, 100);

	if(GetUnits(&Azt.Build.Do1)>1){
		TryUpgrade(&Azt.Upg.CEN01, 90, 100);
	}
	if(UpgIsRun(&Azt.Upg.Do2_ENABLE)){
		TryUpgrade(&Azt.Upg.CEN10, 90, 90);
		TryUpgrade(&Azt.Upg.CEN12, 90, 90);
		TryUpgrade(&Azt.Upg.CEN52, 90, 90);
	}


	// Mine
	if(UpgIsRun(&Azt.Upg.Mel_GETRES2)||GetMoney(FOOD)>GetUpgradeCost(AiNat,&Azt.Upg.Mel_GETRES2,FOOD)+1000){
		TryUnit(&Azt.Build.Stn, 1, 100, 50);
		TryUnit(&Azt.Build.Rud, 1, 90, 30);
		if(GetReadyUnits(&Azt.Build.Do1)>1 && UpgIsRun(&Azt.Upg.Mel_GETRES2)){
			TryUnit(&Azt.Build.Stn, 4, 100, 50);
			TryUnit(&Azt.Build.Rud, 4, 90, 30);
		}
		if(GetReadyUnits(&Azt.Build.Cen)){
			TryUnit(&Azt.Build.Iro, 1, 80, 30);
		}

		if(GetDifficulty()>1 && GetUnits(&Azt.Build.Mel)>1 && UpgIsRun(&Azt.Upg.Mel_GETRES2)){
			TryUpgradeEx(&Azt.Upg.Stn0, 100, 100, 9000, 4000);
			TryUpgradeEx(&Azt.Upg.Stn1, 95, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Stn2, 90, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Stn3, 90, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Stn4, 90, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Stn5, 90, 100, 6000, 1000);

			TryUpgradeEx(&Azt.Upg.Gld0, 92, 100, 9000, 4000);
			TryUpgradeEx(&Azt.Upg.Gld1, 90, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Gld2, 85, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Gld3, 85, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Gld4, 90, 100, 6000, 1000);
			TryUpgradeEx(&Azt.Upg.Gld5, 90, 100, 6000, 1000);
			if(GetReadyUnits(&Azt.Build.Do1)>1){
				TryUpgradeEx(&Azt.Upg.Iro0, 90, 100, 9000, 4000);
				TryUpgradeEx(&Azt.Upg.Iro1, 88, 100, 6000, 1000);
				TryUpgradeEx(&Azt.Upg.Iro2, 85, 100, 6000, 1000);
			}
		}
	}

	if(GetMoney(FOOD)>5000 && GetDifficulty()>0) WarriorsUpg();

}

void WarriorsUpg(){

	if(GetUnits(&Azt.Unit.Sha)>20) TryUpgrade(&Azt.Upg.WarLife,80,80);

	// Met
	if(GetUnits(&Azt.Unit.Met)>40){
		TryUpgrade(&Azt.Upg.Met_ATTACK, 81, 100);
		TryUpgrade(&Azt.Upg.Met_ATTACK3, 81, 100);
		if(GetUnits(&Azt.Unit.Met)>60){
			TryUpgrade(&Azt.Upg.Met_ATTACK4, 81, 100);
			TryUpgrade(&Azt.Upg.Met_ATTACK5, 81, 100);
			TryUpgrade(&Azt.Upg.Met_ATTACK6, 81, 100);
			TryUpgrade(&Azt.Upg.Met_ATTACK7, 81, 100);
		}
		TryUpgrade(&Azt.Upg.Met_SHIELD, 81, 100);
		TryUpgrade(&Azt.Upg.Met_SHIELD3, 81, 100);
		TryUpgrade(&Azt.Upg.Met_SHIELD4, 81, 100);
		if(GetUnits(&Azt.Unit.Met)>60){			
			TryUpgrade(&Azt.Upg.Met_SHIELD5, 81, 100);
			TryUpgrade(&Azt.Upg.Met_SHIELD6, 81, 100);
			TryUpgrade(&Azt.Upg.Met_SHIELD7, 81, 100);
		}

		TryUpgrade(&Azt.Upg.MetProtArrow,90,80);
		TryUpgrade(&Azt.Upg.MetPika1,90,80);
	}

	// Lut
	if(GetUnits(&Azt.Unit.Lut)>30){
		TryUpgrade(&Azt.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&Azt.Upg.Kre_RAZBROS1, 80, 100);
		
		TryUpgrade(&Azt.Upg.Lut_SHIELD, 79, 100);
		TryUpgrade(&Azt.Upg.Lut_SHIELD3, 79, 100);
		TryUpgrade(&Azt.Upg.Lut_SHIELD4, 79, 100);
		TryUpgrade(&Azt.Upg.Lut_SHIELD5, 79, 100);
		TryUpgrade(&Azt.Upg.Lut_SHIELD6, 79, 100);
		TryUpgrade(&Azt.Upg.Lut_SHIELD7, 79, 100);

		TryUpgrade(&Azt.Upg.LutProtPika,80,80);
	}

	// Vog
	
	{
		//TryUpgrade(&Azt.Upg.UPSTATCKRE2, 90, 100);

		TryUpgrade(&Azt.Upg.Vog_ATTACK, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_ATTACK3, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_ATTACK4, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_ATTACK5, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_ATTACK6, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD3, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD4, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD5, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD6, 80, 100);
		TryUpgrade(&Azt.Upg.Vog_SHIELD7, 80, 100);
	}
	

	// Sha
	{
		TryUpgrade(&Azt.Upg.ShaBuild1, 50, 100);
		if(GetExtraction(GOLD)>38){
			TryUpgrade(&Azt.Upg.ShaMedik1, 95, 100);
		}
		if(GetExtraction(STONE)>74){
			TryUpgrade(&Azt.Upg.ShaLife1, 95, 100);
		}
	}

}

void WaterScript(){
	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Azt.Build.Skl)) TryUnit(&Azt.Build.Ver,1,100,90);
	if(GetUnits(&Azt.Build.Kre)>1) TryUnit(&Azt.Build.Ver,3,60,60);

	int NU=GetUnits(&Azt.Unit.Met)+GetUnits(&Azt.Unit.Lut)+city->NFirers;

	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&Azt.Unit.Par, NPar, 100, 100);
	
	TryUnit(&Azt.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&Azt.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
		TryUnit(&Azt.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Azt.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Azt.Upg.Ka3Build6)){
		TryUnit(&Azt.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Azt.Upg.ParSpeed1,100,100);
	TryUpgrade(&Azt.Upg.ParSpeed2,100,100);
	TryUpgrade(&Azt.Upg.ParSpeed3,100,100);
	TryUpgrade(&Azt.Upg.ParSpeed4,100,100);
	TryUpgrade(&Azt.Upg.ParSpeed5,100,100);
	TryUpgrade(&Azt.Upg.ParSpeed6,100,100);

	TryUpgrade(&Azt.Upg.Ka3Build1,100,100);
	TryUpgrade(&Azt.Upg.Ka3Build2,100,100);
	TryUpgrade(&Azt.Upg.Ka3Build3,100,100);
	TryUpgrade(&Azt.Upg.Ka3Build4,100,100);
	TryUpgrade(&Azt.Upg.Ka3Build5,100,100);
	TryUpgrade(&Azt.Upg.Ka3Build6,100,100);

	if(GetUnits(&Azt.Unit.Ka1)>3){
		TryUpgrade(&Azt.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Azt.Upg.Ka1Fishing2,90,100);
		TryUpgrade(&Azt.Upg.Ka1Fishing3,80,100);
		TryUpgrade(&Azt.Upg.Ka1Fishing4,70,100);
		TryUpgrade(&Azt.Upg.Ka1Fishing5,60,100);
		TryUpgrade(&Azt.Upg.Ka1Fishing6,70,100);
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