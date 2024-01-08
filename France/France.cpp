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
	city->HuntNIndex=Fra.Unit.Tap.Index;
	city->NeedHunt=0;

	city->ParomNIndex=Fra.Unit.Parom.Index;
	
	int Diff=GetDifficulty();
	switch(Diff){
	case 2:
		city->SetStartRes(1000,4000,0,0,0,0);
		break;
	case 3:
		city->SetStartRes(2000,8000,0,0,0,0);
		break;
	default:
		break;		
	};
}

void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// flags
	const int HorceBuild=0;
	const int CanBuild=1;

	// Role planing
	city->AddBranch(Fra.Unit.Pik.Index,brBack,35,226);
	city->AddBranch(Fra.Unit.S15.Index,brBack,35,306);
	city->AddBranch(Fra.Unit.S17.Index,brBack,35,346);
	city->AddBranch(Fra.Unit.S18.Index,brBack,600,500);
	city->AddBranch(Fra.Unit.Rei.Index,brBack,79,132);
	city->AddBranch(Fra.Unit.Sha.Index,brBack,600,500);
	city->AddBranch(Fra.Unit.Tap.Index,brBack,100,120);

	Branch* Pik=city->AddBranch(Fra.Unit.Pik.Index,0,0,0);
	Branch* S15=city->AddBranch(Fra.Unit.S15.Index,0,0,0);
	Branch* S17=city->AddBranch(Fra.Unit.S17.Index,0,0,0);
	Branch* S18=city->AddBranch(Fra.Unit.S18.Index,0,0,0);
	Branch* Rei=city->AddBranch(Fra.Unit.Rei.Index,0,0,0);
	Branch* Sha=city->AddBranch(Fra.Unit.Sha.Index,0,0,0);
	Branch* Tap=city->AddBranch(Fra.Unit.Tap.Index,0,0,0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 2;	Pik->Part[brCenter] = 0;	Pik->Type[brCenter] = btKillers;	
								if(GetDifficulty()<2) Pik->Part[brCenter] = 1;
	Pik->Prio[brBack] = 0;		Pik->Part[brBack] = 0;
	Pik->Formation=1;

	S15->Prio[brForward] = 0;	S15->Part[brForward] = 0;
	S15->Prio[brCenter] = 1;	S15->Part[brCenter] = 1;	S15->Type[brCenter] = btTomahawk;
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 0;
	

	S17->Prio[brForward] = 3;	S17->Part[brForward] = 1;	S17->Type[brForward] = btTomahawk;	
	S17->Prio[brCenter] = 2;	S17->Part[brCenter] = 0;
	S17->Prio[brBack] = 0;		S17->Part[brBack] = 0;	
	S17->Formation=1;

	S18->Prio[brForward] = 3;	S18->Part[brForward] = 1;	S18->Type[brForward] = btStorm;	
	S18->Prio[brCenter] = 2;	S18->Part[brCenter] = 0;
	S18->Prio[brBack] = 0;		S18->Part[brBack] = 0;	
	//S18->Formation=1;
	S18->BaseGuard=1;

	Rei->Prio[brForward] = 0;	Rei->Part[brForward] = 0;
	Rei->Prio[brCenter] = 1;	Rei->Part[brCenter] = 1;	Rei->Type[brCenter] = btTomahawk;
	Rei->Prio[brBack] = 0;		Rei->Part[brBack] = 0;
	Rei->Domovoi=false;

	Sha->BaseGuard=1;
	Tap->Hunter=1;

	S18->Min=400;
	Sha->Min=400;
	
	// Units in buildings
	city->NStrelok = 5;
	if(!city->LandType){
		if(GetUnits(&Fra.Build.Kr8)) city->NStrelok += 5;
		if(GetUnits(&Fra.Build.Kr7)>1) city->NStrelok += 10;
	}
	city->NUnits = 2;

	// Units
	TryUnit(&Fra.Unit.Kri, 800, 5, 100);
	TryUnit(&Fra.Unit.Kri, 800, 3, 100);
	TryUnit(&Fra.Unit.Kri, 800, 3, 100);
	TryUnit(&Fra.Unit.Kri, 800, 3, 100);
	TryUnit(&Fra.Unit.Kri, 800, 3, 100);

	TryUnit(&Fra.Unit.Sha, 1000, 20, 100);

	int PikBuild=0;
	if(!GetUnits(&Fra.Unit.S15)||GetUnits(&Fra.Unit.S15)>60){
		TryUnit(&Fra.Unit.Pik, 10000, 20, 100);
		TryUnit(&Fra.Unit.Pik, 10000, 10, 100);
		TryUnit(&Fra.Unit.Pik, 10000, 10, 100);
		PikBuild=1;
	}
	
	int S15Perc=100;
	if(GetUnits(&Fra.Build.Kr8)) S15Perc=50;

	TryUnit(&Fra.Unit.S15, 10000, 20, S15Perc);
	TryUnit(&Fra.Unit.S15, 10000, 10, S15Perc);
	TryUnit(&Fra.Unit.S15, 10000, 10, S15Perc);

	TryUnit(&Fra.Unit.S17, 10000, 20, 100);
	TryUnit(&Fra.Unit.S17, 10000, 10, 100);
	TryUnit(&Fra.Unit.S17, 10000, 10, 100);
	
	if(city->Flags[HorceBuild]){
		TryUnit(&Fra.Unit.Rei, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int ReiCost=GetUnitCost(AiNat,&Fra.Unit.Rei,FOOD)*41;
		if(ReiCost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S17))/50;
	TryUnit(&Fra.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&Fra.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&Fra.Unit.F17, NeedSquad, 50, 100);

	if(GetMoney(GOLD)>5000&&GetMoney(COAL)<100){
		SetResource(AiNat,GOLD,GetMoney(GOLD)-1000);
		SetResource(AiNat,COAL,GetMoney(COAL)+1000);
		SetResource(AiNat,IRON,GetMoney(IRON)+1000);
	}

	if(GetMoney(GOLD)>8000||GetExtraction(GOLD)>39){
		int MaxS18=GetExtraction(GOLD)*10;	
		TryUnit(&Fra.Unit.S18, MaxS18, 20, 100);
		TryUnit(&Fra.Unit.S18, MaxS18, 10, 100);
		TryUnit(&Fra.Unit.S18, MaxS18, 10, 100);
	}

	//TryUnit(&Fra.Unit.O18, 5, 20, 100);
	//TryUnit(&Fra.Unit.B18, 5, 20, 100);
	//TryUnit(&Fra.Unit.F18, 5, 20, 100);

	//TryUnit(&Fra.Unit.D17, 1000, 20, 100);
	//TryUnit(&Fra.Unit.KO7, 5, 20, 100);

	//TryUnit(&Fra.Unit.D18, 1000, 20, 100);
	//TryUnit(&Fra.Unit.KO8, 5, 20, 100);
	//TryUnit(&Fra.Unit.KF8, 5, 20, 100);
	
	//for(i=0;i<6;i++){
	//}
	if(UpgIsRun(&Fra.Upg.CanBuild4)){
		TryUnit(&Fra.Unit.Can, 1000, 90, 100);
	}

	// Peasat distribution
	int NU=GetUnits(&Fra.Unit.Kri)+GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S15)+GetUnits(&Fra.Unit.S17);
	{ //500		
		// Krepost
		city->PKrepost=40;
		if(!(UpgIsRun(&Fra.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000)||NU<40) city->PKrepost=(NU>>4)-1;
		if(city->PKrepost>60) city->PKrepost=60;		
		// Field
		if(GetReadyUnits(&Fra.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&Fra.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&Fra.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		// Forest
		if(GetUnits(&Fra.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&Fra.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}
	if(city->MinFermers>250) TryUnit(&Fra.Build.Mel, 3, 100, 95);
	if(city->MinWooders>70) TryUnit(&Fra.Build.Skl, 2, 100, 60);

	// Buildings
	{
		TryUnit(&Fra.Build.Kr7, 2, 100, 70);
		TryUnit(&Fra.Build.Mel, 1, 100, 80);
		if(GetReadyUnits(&Fra.Build.Mel)){
			TryUnit(&Fra.Build.Skl, 1, 100, 80);
			TryUnit(&Fra.Build.Do1, 1, 100, 60);
			TryUnit(&Fra.Build.Kuz, 1, 100, 60);
		}
		if(UpgIsRun(&Fra.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){
			TryUnit(&Fra.Build.Do1, 4, 100, 95);			
		}

		TryUpgrade(&Fra.Upg.Do2_ENABLE, 100, 100);
		TryUnit(&Fra.Build.Do2, 5, 100, 60);
		
		if(UpgIsRun(&Fra.Upg.Mel_GETRES2)/*||GetDifficulty()<3*/){
			TryUnit(&Fra.Build.Kuz, 2, 100, 60);
			TryUnit(&Fra.Build.Mel, 2, 100, 80);
			TryUnit(&Fra.Build.Fer, 2, 100, 80);
			if(GetUnits(&Fra.Build.Do2)) TryUnit(&Fra.Unit.Tap, 5, 70, 80);
		}
		TryUnit(&Fra.Build.Kr8, 2, 100, 80);
		TryUnit(&Fra.Build.Cen, 1, 100, 80);
		if(GetReadyUnits(&Fra.Build.Do2)){
			TryUnit(&Fra.Build.Do1, 6, 100, 60);			
			TryUnit(&Fra.Build.Kuz, 3, 100, 60);
		}
		
		TryUnit(&Fra.Build.Hra, 1, 100, 70);
	}

	// Blg
	int NBlg=GetUnits(&Fra.Unit.S15)/60;
	{
		if(GetReadyUnits(&Fra.Build.Do1)>3){
			TryUnit(&Fra.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Fra.Build.Kr8)){
			TryUnit(&Fra.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Fra.Build.Cen)){
			TryUnit(&Fra.Build.Blg2, NBlg, 100, 70);
		}
	}


	//TryUnit(&Fra.Build.Ver, 2, 100, 70);

	// Upgrades

	// Fild
	if(GetUnits(&Fra.Build.Do2)>1) TryUpgrade(&Fra.Upg.CEN52, 95, 100);
	TryUpgrade(&Fra.Upg.CEN57, 100, 100);
	if(GetUnits(&Fra.Build.Do1)>2) TryUpgrade(&Fra.Upg.CEN55, 60, 100);

	// Food
	TryUpgrade(&Fra.Upg.Mel_GETRES, 80, 100);
	TryUpgrade(&Fra.Upg.Mel_GETRES2, 90, 100);
	if(GetUnits(&Fra.Build.Do2)){
		TryUpgrade(&Fra.Upg.CEN19, 90, 100);
		TryUpgrade(&Fra.Upg.CEN22, 90, 100);
		TryUpgrade(&Fra.Upg.CEN23, 90, 100);
	}

	// Wood
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){
		TryUpgrade(&Fra.Upg.Wood1,100,100);
		if(GetUnits(&Fra.Build.Do2)){
			TryUpgrade(&Fra.Upg.Wood2,100,100);
			TryUpgrade(&Fra.Upg.Wood3,100,100);
		}
	}

	// Mine
	{
		TryUnit(&Fra.Build.Rud, 1, 100, 70);
		TryUnit(&Fra.Build.Stn,1,95,80);
		if(GetReadyUnits(&Fra.Build.Kuz) && GetUnits(&Fra.Unit.Kri)>20 && GetMoney(STONE)<1000) TryUnit(&Fra.Build.Stn, 2, 95, 70);
		TryUnit(&Fra.Build.Iro, 1, 90, 70);
		TryUnit(&Fra.Build.Coa, 1, 90, 70);		
		
		if(GetUnits(&Fra.Unit.Kri)>120 && UpgIsRun(&Fra.Upg.Mel_GETRES2)){
			TryUnit(&Fra.Build.Rud, 2, 100, 70);
			TryUnit(&Fra.Build.Stn, 2, 95, 70);
			TryUnit(&Fra.Build.Iro, 2, 90, 70);
			TryUnit(&Fra.Build.Coa, 2, 90, 70);
			/*
			if(GetUnits(&Fra.Unit.Kri)>220||GetReadyUnits(&Fra.Build.Kr8)){
				TryUnit(&Fra.Build.Rud, 3, 100, 70);
				TryUnit(&Fra.Build.Stn, 3, 950, 70);
				TryUnit(&Fra.Build.Iro, 3, 90, 70);
				TryUnit(&Fra.Build.Coa, 3, 90, 70);
			}
			*/
		}
		if(UpgIsRun(&Fra.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000){
			TryUpgradeEx(&Fra.Upg.Gld0, 90, 100, 9000, 4000);
			TryUpgradeEx(&Fra.Upg.Stn0, 85, 80, 9000, 4000);			
			TryUpgradeEx(&Fra.Upg.Iro0, 80, 40, 9000, 4000);
			TryUpgradeEx(&Fra.Upg.Coa0, 75, 60, 9000, 4000);				
		}
		TryUpgrade(&Fra.Upg.MineEnable1, 100, 100);
		if(GetDifficulty()>1 && UpgIsRun(&Fra.Upg.Mel_GETRES2)){
			TryUpgradeEx(&Fra.Upg.Gld1, 95, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Gld2, 95, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Gld3, 95, 100, 6000, 1000);
			
			TryUpgradeEx(&Fra.Upg.Stn1, 90, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Stn2, 90, 100, 6000, 1000);
			//if(UpgIsRun(&Fra.Upg.EnDo1)){
				//TryUpgrade(&Fra.Upg.Gld4, 95, 100, 6000, 1000);
				//TryUpgrade(&Fra.Upg.Gld5, 95, 100, 6000, 1000);
				TryUpgradeEx(&Fra.Upg.Stn3, 95, 100, 6000, 1000);
				//TryUpgrade(&Fra.Upg.Stn4, 90, 100, 6000, 1000);
				//TryUpgrade(&Fra.Upg.Stn5, 90, 100, 6000, 1000);
			//}
			TryUpgradeEx(&Fra.Upg.Iro0, 80, 100, 9000, 4000);
			TryUpgradeEx(&Fra.Upg.Iro1, 70, 100, 9000, 2000);
			TryUpgradeEx(&Fra.Upg.Iro2, 60, 100, 9000, 1500);
			TryUpgradeEx(&Fra.Upg.Iro3, 60, 100, 9000, 1000);
			TryUpgradeEx(&Fra.Upg.Coa0, 80, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Coa1, 70, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Coa2, 60, 100, 6000, 1000);
			TryUpgradeEx(&Fra.Upg.Coa3, 60, 100, 6000, 1000);
		}
	}

	// Stages
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){
		TryUpgrade(&Fra.Upg.Kr7_Stage0, 80, 100);
	}
	if(GetUnits(&Fra.Build.Do2)){
		TryUpgrade(&Fra.Upg.Kr8_Stage0, 90, 100);
	}
	if(GetUnits(&Fra.Build.Do2)>1){
		TryUpgrade(&Fra.Upg.BldBuild1, 90, 100);		
	}
	
	//
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){		
		TryUpgrade(&Fra.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&Fra.Upg.KreBuild, 80, 100);
	}
	
	if(GetDifficulty()>0) WarriorsUpg();

	// Warriors speed

	// Kri
	if(GetUnits(&Fra.Build.Do2)>1){
		TryUpgrade(&Fra.Upg.KriBuild1,80,70);
		TryUpgrade(&Fra.Upg.KriBuild2,80,70);
		TryUpgrade(&Fra.Upg.KriBuild3,80,70);
	}
	// Pik
	TryUpgrade(&Fra.Upg.PikBuild1, 90, 100);
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){		
		{
			TryUpgrade(&Fra.Upg.PikBuild2, 90, 100);
			TryUpgrade(&Fra.Upg.PikBuild3, 90, 100);
			TryUpgrade(&Fra.Upg.PikBuild4, 90, 100);			
		}
	}
	// S18
	if(GetUnits(&Fra.Build.Kr8)>1){
		TryUpgrade(&Fra.Upg.S18Build1,80,100);
		TryUpgrade(&Fra.Upg.S18Build2,80,100);
		TryUpgrade(&Fra.Upg.S18Build3,80,100);
	}
	// Rei
	TryUpgrade(&Fra.Upg.ReiBuild, 90, 100);


}

void WarriorsUpg(){

	// Cen
	{
		TryUpgrade(&Fra.Upg.ArmShield1,90,100);
		TryUpgrade(&Fra.Upg.ArmShield2,60,100);
		TryUpgrade(&Fra.Upg.ArmShield3,60,100);
		
		TryUpgrade(&Fra.Upg.StrAttPause1,90,100);

		TryUpgrade(&Fra.Upg.StrDamage1,80,100);
		TryUpgrade(&Fra.Upg.StrDamage2,80,100);

		if(GetUnits(&Fra.Build.Kr8)>1){
			TryUpgrade(&Fra.Upg.BldShield1,80,100);
			TryUpgrade(&Fra.Upg.BldShield2,80,100);
		}
	}

	// Pik
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){		
		if(GetUnits(&Fra.Unit.Pik)>40){
			TryUpgrade(&Fra.Upg.PikAttack, 90, 100);
			TryUpgrade(&Fra.Upg.PikAttack3, 90, 100);
			TryUpgrade(&Fra.Upg.PikAttack4, 90, 100);
			TryUpgrade(&Fra.Upg.PikAttack5, 80, 100);
			TryUpgrade(&Fra.Upg.PikAttack6, 80, 100);
			TryUpgrade(&Fra.Upg.PikAttack7, 80, 100);
			
			TryUpgrade(&Fra.Upg.PikProtect, 90, 100);
			TryUpgrade(&Fra.Upg.PikProtect3, 90, 100);
			TryUpgrade(&Fra.Upg.PikProtect4, 90, 100);
			TryUpgrade(&Fra.Upg.PikProtect5, 80, 100);
			TryUpgrade(&Fra.Upg.PikProtect6, 80, 100);
			TryUpgrade(&Fra.Upg.PikProtect7, 80, 100);
		}
	}

	// S15
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)){
		if(UpgIsRun(&Fra.Upg.S15Protect7)&&GetUnits(&Fra.Unit.S15)>60){
			TryUpgrade(&Fra.Upg.S15Attack, 20, 100);
			TryUpgrade(&Fra.Upg.S15Attack3, 20, 100);
			TryUpgrade(&Fra.Upg.S15Attack4, 20, 100);
			TryUpgrade(&Fra.Upg.S15Attack5, 20, 100);
			TryUpgrade(&Fra.Upg.S15Attack6, 20, 100);
			TryUpgrade(&Fra.Upg.S15Attack7, 10, 100);
		}
		
		if(GetUnits(&Fra.Unit.S15)>60){
			TryUpgrade(&Fra.Upg.S15Protect, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect3, 90, 100);			
			TryUpgrade(&Fra.Upg.S15Protect4, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect5, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect6, 90, 100);
			TryUpgrade(&Fra.Upg.S15Protect7, 90, 100);
		}
	}

	// Mus
	if(UpgIsRun(&Fra.Upg.Mel_GETRES2)&&GetMoney(GOLD)>4000){
		if(UpgIsRun(&Fra.Upg.MusProtect6)&&GetUnits(&Fra.Unit.S17)>40){
			TryUpgrade(&Fra.Upg.MusAttack, 30, 100);
			TryUpgrade(&Fra.Upg.MusAttack3, 30, 100);
			TryUpgrade(&Fra.Upg.MusAttack4, 30, 100);
			TryUpgrade(&Fra.Upg.MusAttack5, 30, 100);
			TryUpgrade(&Fra.Upg.MusAttack6, 30, 100);
			TryUpgrade(&Fra.Upg.MusAttack7, 10, 100);
		}
		
		if(GetUnits(&Fra.Unit.S17)>40){
			TryUpgrade(&Fra.Upg.MusProtect, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect3, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.S17)>80){
			TryUpgrade(&Fra.Upg.MusProtect5, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect6, 90, 100);
			TryUpgrade(&Fra.Upg.MusProtect7, 50, 100);
		}
	}

	// S18
	{
		if(GetUnits(&Fra.Unit.S18)){
			TryUpgrade(&Fra.Upg.S18Attack, 30, 100);
			TryUpgrade(&Fra.Upg.S18Attack3, 30, 100);
			TryUpgrade(&Fra.Upg.S18Attack4, 30, 100);
			TryUpgrade(&Fra.Upg.S18Attack5, 30, 100);
			TryUpgrade(&Fra.Upg.S18Attack6, 30, 100);
			TryUpgrade(&Fra.Upg.S18Attack7, 30, 100);
			
			TryUpgrade(&Fra.Upg.S18Protect, 90, 100);
			TryUpgrade(&Fra.Upg.S18Protect3, 90, 100);
			TryUpgrade(&Fra.Upg.S18Protect4, 90, 100);
			TryUpgrade(&Fra.Upg.S18Protect5, 90, 100);
			TryUpgrade(&Fra.Upg.S18Protect6, 90, 100);
			TryUpgrade(&Fra.Upg.S18Protect7, 90, 100);
		}
	}

	// Officers
	{
		TryUpgrade(&Fra.Upg.B17Protect, 50, 100);
		TryUpgrade(&Fra.Upg.O17Damage, 50, 100);
		TryUpgrade(&Fra.Upg.O17Protect, 50, 100);
		TryUpgrade(&Fra.Upg.F17Protect, 50, 100);
	}

	// Rei
	{
		if(GetUnits(&Fra.Unit.Rei)>20){
			TryUpgrade(&Fra.Upg.ReiAttack, 90, 100);
			TryUpgrade(&Fra.Upg.ReiAttack3, 90, 100);
			TryUpgrade(&Fra.Upg.ReiAttack4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.Rei)>40){
			TryUpgrade(&Fra.Upg.ReiAttack5, 90, 100);
			TryUpgrade(&Fra.Upg.ReiAttack6, 90, 100);
			TryUpgrade(&Fra.Upg.ReiAttack7, 90, 100);
		}
		
		if(GetUnits(&Fra.Unit.Rei)>20){
			TryUpgrade(&Fra.Upg.ReiProtect, 90, 100);
			TryUpgrade(&Fra.Upg.ReiProtect3, 90, 100);
			TryUpgrade(&Fra.Upg.ReiProtect4, 90, 100);
		}
		if(GetUnits(&Fra.Unit.Rei)>40){
			TryUpgrade(&Fra.Upg.ReiProtect5, 90, 100);
			TryUpgrade(&Fra.Upg.ReiProtect6, 90, 100);
			TryUpgrade(&Fra.Upg.ReiProtect7, 90, 100);
		}
	}

	// Can
	{
		TryUpgrade(&Fra.Upg.CanCost,95,60);
		TryUpgrade(&Fra.Upg.CanCost3,95,60);
		TryUpgrade(&Fra.Upg.CanCost4,95,60);
		//TryUpgrade(&Fra.Upg.CanCost5,95,100);
		//TryUpgrade(&Fra.Upg.CanCost6,95,100);
		//TryUpgrade(&Fra.Upg.CanCost7,95,100);
		TryUpgrade(&Fra.Upg.CanBuild,95,60);
		TryUpgrade(&Fra.Upg.CanBuild3,95,60);
		TryUpgrade(&Fra.Upg.CanBuild4,95,60);
		//TryUpgrade(&Fra.Upg.CanBuild5,95,100);
		//TryUpgrade(&Fra.Upg.CanBuild6,95,100);
		//TryUpgrade(&Fra.Upg.CanBuild7,95,100);
	}

}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Fra.Build.Skl)) TryUnit(&Fra.Build.Ver,1,100,90);
	if(GetUnits(&Fra.Build.Cen)) TryUnit(&Fra.Build.Ver,3,60,60);

	//int NU=GetUnits(&Fra.Unit.Pik)+GetUnits(&Fra.Unit.S15)+GetUnits(&Fra.Unit.S17)+GetUnits(&Fra.Unit.Rei);

	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&Fra.Unit.Parom, NPar, 100, 100);

	if(TryUnit(&Fra.Unit.Lodka, 10, 100, 100)){
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
		TryUnit(&Fra.Unit.Lodka, 10, 10, 100);
	}
	
	TryUnit(&Fra.Unit.Pinta, 5, 100, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 50, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 50, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 50, 100);
	TryUnit(&Fra.Unit.Pinta, 5, 50, 100);

	TryUnit(&Fra.Unit.Santa, 2, 100, 100);
	TryUnit(&Fra.Unit.Santa, 2, 50, 100);

	TryUnit(&Fra.Unit.Fregat, 2, 100, 100);
	TryUnit(&Fra.Unit.Fregat, 2, 50, 100);

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