#define CONQUEST
#include "..\Import.h"
#include "..\MayNation.h"
#include "..\AICity.h"
#include <crtdbg.h>
#include <assert.h>

DLLEXPORT
void InitAI(){	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	city->Peasant = May.Unit.Kri.Index;
	city->Init(AiNat);
	city->NIndexBrb = May.Unit.Sha.Index;
	city->NIndexFlg = May.Unit.Sha.Index;
	city->NIndexOff = May.Unit.Vog.Index;
	city->Flags[0]=GetRND(100);
}

void Script();
void WaterScript();
void WarriorsUpg();

DLLEXPORT
void ProcessAI(){
	rando();
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
	
	rando();	
	city->Process();
	city->ParomNIndex=May.Unit.Par.Index;
	rando();
	
	int Diff=GetDifficulty();
	switch(Diff){
	case 2:
		city->SetStartRes(0,4000,0,0,0,0);
		break;
	case 3:
		city->SetStartRes(0,8000,0,0,0,0);
		break;
	};
	rando();	
}

void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// Role planing
	city->AddBranch(May.Unit.Pik.Index,brBack,37,148);
	city->AddBranch(May.Unit.Lut.Index,brBack,49,360);
	city->AddBranch(May.Unit.Voi.Index,brBack,79,289);

	Branch* Pik=city->AddBranch(May.Unit.Pik.Index,0,0,0);
	Branch* Lut=city->AddBranch(May.Unit.Lut.Index,0,0,0);
	Branch* Mak=city->AddBranch(May.Unit.Voi.Index,0,0,0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 2;	Pik->Part[brCenter] = 0;	Pik->Type[brCenter] = btKillers;
	Pik->Prio[brBack] = 1;		Pik->Part[brBack] = 0;
	Pik->Formation=1;
	if(GetDifficulty()<2) Pik->Part[brCenter] = 1;

	Lut->Prio[brForward] = 3;	Lut->Part[brForward] = 0;	Lut->Type[brForward] = btFire; //btFire;
	Lut->Prio[brCenter] = 2;	Lut->Part[brCenter] = 2;	Lut->Type[brCenter] = btTomahawk;
	Lut->Prio[brBack] = 1;		Lut->Part[brBack] = 0;
	Lut->Formation=1;
	if(GetDifficulty()<2) Lut->Part[brForward] = 1;
	if(GetDifficulty()==0) Lut->Part[brCenter] = 0;

	Mak->Prio[brForward] = 3;	Mak->Part[brForward] = 2;	Mak->Type[brForward] = btKillers;
	Mak->Prio[brCenter] = 2;	Mak->Part[brCenter] = 1;	Mak->Type[brCenter] = btStorm;
	Mak->Prio[brBack] = 1;		Mak->Part[brBack] = 0;
	Mak->Formation=1;

	// Buildings
	TryUnit(&May.Build.Mel, 1, 100, 80);

	if(GetReadyUnits(&May.Build.Mel)){
		
		TryUnit(&May.Build.Do3, 4, 100, 80);
		
		if(GetUnits(&May.Build.Do3)>2){
			TryUnit(&May.Build.Kre, 1, 100, 85);
			TryUnit(&May.Build.Mel, 2, 100, 60);
		}		
		if(GetUnits(&May.Build.Do2)) TryUnit(&May.Build.Kre, 3, 100, 85);
		
		TryUnit(&May.Build.Skl, 1, 100, 60);

		if(GetUnits(&May.Build.Do3)>3){
			TryUnit(&May.Build.Mel, 3, 100, 70);
		}
	}
	if(GetUnits(&May.Build.Mel)>1) TryUnit(&May.Build.Cen, 1, 100, 70);
	if(GetUnits(&May.Build.Kre)>1){
		TryUnit(&May.Build.Skl, 2, 30, 30);
	}
	
	int NU=GetUnits(&May.Unit.Pik)+GetUnits(&May.Unit.Lut)+GetUnits(&May.Unit.Voi);
	
	if(GetReadyUnits(&May.Build.Cen)){
		int MaxBlg=0;
		int MaxBl2=3;
		if(Pik->Min>20){
			if(UpgIsRun(&May.Upg.EnDo2)){
			}
			if(GetUnits(&May.Build.Kre)>1){
				MaxBlg=6;
				MaxBl2=10;
			}
			if(GetUnits(&May.Build.Kre)>2){
				MaxBlg=9;
				MaxBl2=14;
			}
		}

		int NBlg=NU/90;
		if(NBlg>MaxBlg) NBlg=MaxBlg;
		int NBl2=NU/40;
		if(NBl2>MaxBl2) NBl2=MaxBl2;

		TryUnit(&May.Build.Blg, NBlg, 60, 30);
		TryUnit(&May.Build.Bl2, NBl2, 60, 30);
	}
	if(UpgIsRun(&May.Upg.CEN10MA)){
		TryUnit(&May.Build.Do3, 5, 50, 30);		
	}

	if(GetUnits(&May.Build.Kre)){
		TryUpgrade(&May.Upg.EnDo2, 100, 100);
	}

	// Dom
	TryUpgrade(&May.Upg.EnDo1, 100, 100);
	TryUpgrade(&May.Upg.EnDo2, 60, 100);	
	TryUnit(&May.Build.Do2, 4, 60, 30);
	if(GetReadyUnits(&May.Build.Do2)>1){
		if(GetUnits(&May.Build.Kre)>1){
			TryUnit(&May.Build.Do1, 5, 100, 40);
			TryUnit(&May.Build.Do2, 6, 100, 40);		
			TryUnit(&May.Build.Do3, 6, 100, 40);
			if(GetUnits(&May.Build.Kre)>2&&UpgIsRun(&May.Upg.PikBuild1)){
				TryUnit(&May.Build.Do1, 10, 100, 40);
				TryUnit(&May.Build.Do2, 10, 100, 40);		
				TryUnit(&May.Build.Do3, 10, 100, 40);
			}
		}
	}

	if(GetReadyUnits(&May.Build.Kre)>1){
		TryUnit(&May.Build.Hra, 1, 100, 40);
	}

	// Food & Field
	TryUpgrade(&May.Upg.Mel_GETRES, 90, 100);
	TryUpgrade(&May.Upg.Mel_GETRES2, 90, 100);
	TryUpgrade(&May.Upg.CEN10MA, 95, 100);
	TryUpgrade(&May.Upg.CEN12MA, 95, 100);
	if(GetUnits(&May.Build.Kre)>1){
		TryUpgrade(&May.Upg.MAY52MA, 95, 100);
	}
	if(UpgIsDone(&May.Upg.EnDo2)){
		if(GetUnits(&May.Build.Kre)>1){
			TryUpgrade(&May.Upg.CEN01MA, 95, 100);
			TryUpgrade(&May.Upg.CEN02MA, 95, 100);
			TryUpgrade(&May.Upg.CEN03MA, 95, 100);
		}else{
			TryUpgrade(&May.Upg.CEN01MA, 60, 100);
			TryUpgrade(&May.Upg.CEN02MA, 60, 100);
			TryUpgrade(&May.Upg.CEN03MA, 60, 100);
		}
	}
	
	if(GetReadyUnits(&May.Build.Hra)){
		TryUpgrade(&May.Upg.ShaSpd, 95, 100);
		TryUpgrade(&May.Upg.ShaHeal, 95, 100);
		TryUpgrade(&May.Upg.ShaLife, 95, 100);
	}

	TryUpgrade(&May.Upg.BldSpd, 100, 100);
	
	TryUpgrade(&May.Upg.FieldDur3, 100, 100);

	// Units in buildings
	city->NUnits = 2;
	if(GetUnits(&May.Unit.Pik)>100) city->NUnits = 5;
	//if(GetUnits(&May.Unit.Voi)>100) city->NUnits = 15;
	//if(GetUnits(&May.Unit.Voi)>250) city->NUnits = 25;	

	// Producing: Units & Convertors
	city->PKrepost=0;
	// Kri
	if(UpgIsRun(&May.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){
		TryUnit(&May.Unit.Kri, 800, 20, 100);
		TryUnit(&May.Unit.Kri, 800, 10, 100);
		TryUnit(&May.Unit.Kri, 800, 10, 100);
		TryUnit(&May.Unit.Kri, 800, 10, 100);
		TryUnit(&May.Unit.Kri, 800, 10, 100);
	}else{
		TryUnit(&May.Unit.Kri, 80-10*GetDifficulty(), 20, 100);
	}
	// Warriors
	if(UpgIsRun(&May.Upg.Mel_GETRES2)||GetPeaceTimeLeft()<2||GetMoney(FOOD)>15000){		
		TryUnit(&May.Unit.Voi, 3000, 20, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 80);
		TryUnit(&May.Unit.Voi, 3000, 10, 60);
		TryUnit(&May.Unit.Voi, 3000, 20, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 80);
		TryUnit(&May.Unit.Voi, 3000, 10, 60);
		TryUnit(&May.Unit.Voi, 3000, 20, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 100);
		TryUnit(&May.Unit.Voi, 3000, 10, 80);
		TryUnit(&May.Unit.Voi, 3000, 10, 60);
		
		city->PKrepost=40;
		if(GetUnits(&May.Unit.Lut)) city->PKrepost=50;
		if(GetUnits(&May.Unit.Voi)) city->PKrepost=75;		

		if(GetUnits(&May.Unit.Kri)<700){
			TryUnit(&May.Unit.Lut, 3000, 20, 100);
			TryUnit(&May.Unit.Lut, 3000, 10, 90);
			TryUnit(&May.Unit.Lut, 3000, 10, 80);			
			city->PKrepost-=8;
		}	
		if(GetUnits(&May.Unit.Lut)){
			TryUnit(&May.Unit.Lut, 3000, 20, 100);
			TryUnit(&May.Unit.Lut, 3000, 10, 30);
			TryUnit(&May.Unit.Lut, 3000, 10, 15);
			city->PKrepost-=3;
		}

		if(GetUnits(&May.Unit.Kri)<500||GetUnits(&May.Unit.Pik)<200||UpgIsRun(&May.Upg.PikBuild1)){
			TryUnit(&May.Unit.Pik, 10000, 10, 100);
			if(GetUnits(&May.Unit.Pik)<80) city->PKrepost-=10;
		}
		if(!GetUnits(&May.Unit.Voi)){
			TryUnit(&May.Unit.Pik, 10000, 10, 80);
			TryUnit(&May.Unit.Pik, 10000, 10, 80);
		}

		TryUnit(&May.Unit.Sha, 10, 20, 100);
		TryUnit(&May.Unit.Vog, 10, 20, 100);

	}

	// Mine
	if(GetMoney(FOOD)>1500){
		TryUnit(&May.Build.Stn, 1, 100, 50);
		TryUnit(&May.Build.Rud, 1, 90, 30);
		if(GetReadyUnits(&May.Build.Cen)){
			//TryUnit(&May.Build.Coa, 1, 80, 30);
			TryUnit(&May.Build.Iro, 1, 80, 30);
		}
		if(UpgIsRun(&May.Upg.Mel_GETRES2)&&UpgIsRun(&May.Upg.CEN10MA)){
			TryUnit(&May.Build.Stn, 4, 100, 50);
			TryUnit(&May.Build.Rud, 4, 90, 30);
			
			if(GetDifficulty()>1){
				TryUpgradeEx(&May.Upg.Stn0, 100, 100, 9000, 4000);
				TryUpgradeEx(&May.Upg.Stn1, 100, 100, 6000, 1000);
				TryUpgradeEx(&May.Upg.Stn2, 100, 100, 6000, 1000);
				TryUpgradeEx(&May.Upg.Stn3, 90, 100, 6000, 1000);
				TryUpgradeEx(&May.Upg.Gld0, 95, 100, 9000, 4000);
				TryUpgradeEx(&May.Upg.Gld1, 95, 100, 6000, 1000);
				TryUpgradeEx(&May.Upg.Gld2, 95, 100, 6000, 1000);
				TryUpgradeEx(&May.Upg.Gld3, 100, 100, 6000, 1000);
				if(UpgIsRun(&May.Upg.EnDo1)){
					TryUpgradeEx(&May.Upg.Stn4, 100, 100, 6000, 1000);
					TryUpgradeEx(&May.Upg.Stn5, 100, 100, 6000, 1000);
					TryUpgradeEx(&May.Upg.Gld4, 90, 100, 6000, 1000);
					TryUpgradeEx(&May.Upg.Gld5, 90, 100, 6000, 1000);				
				}
				TryUpgradeEx(&May.Upg.Iro0, 90, 100, 9000, 4000);
				//TryUpgradeEx(&May.Upg.Iro1, 80, 100, 6000, 1000);
				//TryUpgrade(&May.Upg.Iro2, 70, 100);
				//TryUpgrade(&May.Upg.Coa0, 90, 100);
				//TryUpgrade(&May.Upg.Coa1, 80, 100);
				//TryUpgrade(&May.Upg.Coa2, 70, 100);
			}
		}
	}

	// Peasat distribution
	NU=GetUnits(&May.Unit.Pik)+GetUnits(&May.Unit.Kri)+GetUnits(&May.Unit.Lut)+GetUnits(&May.Unit.Voi);
	if(NU){ //500
		if(GetReadyUnits(&May.Build.Mel)){
			city->MinFermers = NU/4;
			if(UpgIsRun(&May.Upg.VoiS7)&&GetMoney(FOOD)>60000) city->MinFermers = NU/10;
			if(!UpgIsRun(&May.Upg.Mel_GETRES2)) city->MinFermers=NU/3+30;
			if(city->MinFermers>300) city->MinFermers = 300;
			if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		if(GetUnits(&May.Build.Skl)){
			city->MinWooders = NU/7;
			if(!UpgIsRun(&May.Upg.Mel_GETRES2)) city->MinWooders=NU/5;
			if(city->MinWooders>200) city->MinWooders = 200;
			if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}

	if(GetDifficulty()>0) WarriorsUpg();

	// Enable warriors
	if(UpgIsRun(&May.Upg.Mel_GETRES2) && GetUnits(&May.Unit.Pik)>30) TryUpgrade(&May.Upg.EnLut, 100, 100);
	if(GetUnits(&May.Unit.Pik)>100||city->Flags[0]>40) TryUpgrade(&May.Upg.EnVoi, 100, 100);
	TryUpgrade(&May.Upg.EnVog, 100, 100);
	
}

void WarriorsUpg(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// Kri
	if(GetUnits(&May.Build.Kre)>1){
		TryUpgrade(&May.Upg.KriBu1,90,100);
		TryUpgrade(&May.Upg.KriBu2,90,100);
	}

	// Pik
	TryUpgrade(&May.Upg.PikBuild1,100,100);

	int NPikUpg=30+GetRND(30);
	if(GetUnits(&May.Unit.Pik)>50){
		TryUpgrade(&May.Upg.PikA2, 50, 100);
		if(GetUnits(&May.Unit.Pik)>75&&UpgIsRun(&May.Upg.Mel_GETRES2)&&GetUnits(&May.Unit.Pik)>NPikUpg){		
			TryUpgrade(&May.Upg.PikA3, 30, 100);
			TryUpgrade(&May.Upg.PikA4, 30, 100);
			TryUpgrade(&May.Upg.PikS2, 50, 100);
			TryUpgrade(&May.Upg.PikS3, 50, 100);
			TryUpgrade(&May.Upg.PikS4, 50, 100);
			if(GetUnits(&May.Unit.Pik)>100&&GetUnits(&May.Unit.Voi)){
				TryUpgrade(&May.Upg.PikA5, 50, 100);
				TryUpgrade(&May.Upg.PikA6, 60, 100);
				TryUpgrade(&May.Upg.PikA7, 70, 100);
				TryUpgrade(&May.Upg.PikS5, 70, 100);
				TryUpgrade(&May.Upg.PikS6, 90, 100);
				TryUpgrade(&May.Upg.PikS7, 70, 100);
			}
		}
	}

	// Lut
	if(GetUnits(&May.Unit.Lut)>50){
		TryUpgrade(&May.Upg.LutS2, 50, 100);
		TryUpgrade(&May.Upg.LutS3, 60, 100);
		TryUpgrade(&May.Upg.LutS4, 70, 100);
		if(GetUnits(&May.Unit.Voi)&&GetUnits(&May.Unit.Lut)>100){
			TryUpgrade(&May.Upg.LutS5, 50, 100);
			TryUpgrade(&May.Upg.LutS6, 50, 100);
			TryUpgrade(&May.Upg.LutS7, 50, 100);
		}

		TryUpgrade(&May.Upg.LutRaz1, 50, 100);
		if(GetUnits(&May.Unit.Lut)>60 && GetUnits(&May.Build.Kre)>1){
			TryUpgrade(&May.Upg.LutRaz1, 95, 100);
			TryUpgrade(&May.Upg.LutRaz2, 95, 100);
		}
	}

	// Voi	
	if(GetUnits(&May.Unit.Voi)>60){
		TryUpgrade(&May.Upg.Life1,80,100);

		TryUpgrade(&May.Upg.VoiS2, 50, 100);
		TryUpgrade(&May.Upg.VoiS3, 60, 100);
		TryUpgrade(&May.Upg.VoiS4, 70, 100);
		if(GetUnits(&May.Unit.Voi)>120){
			TryUpgrade(&May.Upg.VoiS5, 80, 100);
			TryUpgrade(&May.Upg.VoiS6, 90, 100);
			TryUpgrade(&May.Upg.VoiS7, 80, 100);
		}

		if(UpgIsRun(&May.Upg.Strike1)){
			TryUpgrade(&May.Upg.VoiA2, 50, 100);
			TryUpgrade(&May.Upg.VoiA3, 50, 100);
			TryUpgrade(&May.Upg.VoiA4, 60, 100);
			TryUpgrade(&May.Upg.VoiA5, 70, 100);
			TryUpgrade(&May.Upg.VoiA6, 80, 100);
			TryUpgrade(&May.Upg.VoiA7, 90, 100);
		}

		TryUpgrade(&May.Upg.VoiSh1, 100, 100);
		TryUpgrade(&May.Upg.VoiSh2, 80, 100);

		TryUpgrade(&May.Upg.Strike1, 90, 100);
	}

}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&May.Build.Skl)) TryUnit(&May.Build.Ver,1,100,90);
	if(GetUnits(&May.Build.Kre)>1) TryUnit(&May.Build.Ver,3,60,60);

	int NU=GetUnits(&May.Unit.Pik)+GetUnits(&May.Unit.Lut)+GetUnits(&May.Unit.Voi)+city->NFirers;

	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&May.Unit.Par, NPar, 100, 100);
	
	TryUnit(&May.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&May.Unit.Ka1, 10, 10, 100)){
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
		TryUnit(&May.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&May.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&May.Upg.Ka3Build5)){
		TryUnit(&May.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&May.Upg.ParSpeed1,100,100);
	TryUpgrade(&May.Upg.ParSpeed2,100,100);
	TryUpgrade(&May.Upg.ParSpeed3,100,100);
	TryUpgrade(&May.Upg.ParSpeed4,100,100);
	TryUpgrade(&May.Upg.ParSpeed5,100,100);
	TryUpgrade(&May.Upg.ParSpeed6,100,100);

	TryUpgrade(&May.Upg.Ka3Build1,100,100);
	TryUpgrade(&May.Upg.Ka3Build2,100,100);
	TryUpgrade(&May.Upg.Ka3Build3,100,100);
	TryUpgrade(&May.Upg.Ka3Build4,100,100);
	TryUpgrade(&May.Upg.Ka3Build5,100,100);
	TryUpgrade(&May.Upg.Ka3Build6,100,100);

	if(GetUnits(&May.Unit.Ka1)>3){
		TryUpgrade(&May.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&May.Upg.Ka1Fishing2,90,100);
		TryUpgrade(&May.Upg.Ka1Fishing3,80,100);
		TryUpgrade(&May.Upg.Ka1Fishing4,70,100);
		TryUpgrade(&May.Upg.Ka1Fishing5,60,100);
		TryUpgrade(&May.Upg.Ka1Fishing6,70,100);
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
