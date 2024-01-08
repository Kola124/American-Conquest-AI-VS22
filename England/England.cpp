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
	city->HuntNIndex=Eng.Unit.Tap.Index;
	city->NeedHunt=0;

	city->ParomNIndex=Eng.Unit.Parom.Index;
	
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
	city->AddBranch(Eng.Unit.Pik.Index,brBack,35,226);
	city->AddBranch(Eng.Unit.S15.Index,brBack,35,306);
	city->AddBranch(Eng.Unit.S17.Index,brBack,35,346);
	city->AddBranch(Eng.Unit.S18.Index,brBack,600,500);
	city->AddBranch(Eng.Unit.Rei.Index,brBack,79,132);
	city->AddBranch(Eng.Unit.Sha.Index,brBack,600,500);
	city->AddBranch(Eng.Unit.Tap.Index,brBack,100,120);

	Branch* Pik=city->AddBranch(Eng.Unit.Pik.Index,0,0,0);
	Branch* S15=city->AddBranch(Eng.Unit.S15.Index,0,0,0);
	Branch* S17=city->AddBranch(Eng.Unit.S17.Index,0,0,0);
	Branch* S18=city->AddBranch(Eng.Unit.S18.Index,0,0,0);
	Branch* Rei=city->AddBranch(Eng.Unit.Rei.Index,0,0,0);
	Branch* Sha=city->AddBranch(Eng.Unit.Sha.Index,0,0,0);
	Branch* Tap=city->AddBranch(Eng.Unit.Tap.Index,0,0,0);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;
	Pik->Prio[brCenter] = 2;	Pik->Part[brCenter] = 0;	Pik->Type[brCenter] = btKillers;								
	Pik->Prio[brBack] = 0;		Pik->Part[brBack] = 0;
	Pik->Formation=1;
	if(GetDifficulty()<2) Pik->Part[brCenter] = 1;

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
		if(GetUnits(&Eng.Build.Kr8)) city->NStrelok += 5;
		if(GetUnits(&Eng.Build.Kr7)>1) city->NStrelok += 10;
	}
	city->NUnits = 2;

	// Units
	TryUnit(&Eng.Unit.Kri, 800, 5, 100);
	TryUnit(&Eng.Unit.Kri, 800, 3, 100);
	TryUnit(&Eng.Unit.Kri, 800, 3, 100);
	TryUnit(&Eng.Unit.Kri, 800, 3, 100);
	TryUnit(&Eng.Unit.Kri, 800, 3, 100);

	TryUnit(&Eng.Unit.Sha, 1000, 20, 100);

	int PikBuild=0;
	if(!GetUnits(&Eng.Unit.S15)||GetUnits(&Eng.Unit.S15)>60){
		TryUnit(&Eng.Unit.Pik, 10000, 20, 100);
		TryUnit(&Eng.Unit.Pik, 10000, 10, 100);
		TryUnit(&Eng.Unit.Pik, 10000, 10, 100);
		PikBuild=1;
	}
	
	int S15Perc=100;
	if(GetUnits(&Eng.Build.Kr8)) S15Perc=50;

	TryUnit(&Eng.Unit.S15, 10000, 20, S15Perc);
	TryUnit(&Eng.Unit.S15, 10000, 10, S15Perc);
	TryUnit(&Eng.Unit.S15, 10000, 10, S15Perc);

	TryUnit(&Eng.Unit.S17, 10000, 20, 100);
	TryUnit(&Eng.Unit.S17, 10000, 10, 100);
	TryUnit(&Eng.Unit.S17, 10000, 10, 100);
	
	if(city->Flags[HorceBuild]){
		TryUnit(&Eng.Unit.Rei, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int ReiCost=GetUnitCost(AiNat,&Eng.Unit.Rei,FOOD)*41;
		if(ReiCost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&Eng.Unit.Pik)+GetUnits(&Eng.Unit.S17))/50;
	TryUnit(&Eng.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&Eng.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&Eng.Unit.F17, NeedSquad, 50, 100);

	if(GetMoney(GOLD)>5000&&GetMoney(COAL)<100){
		SetResource(AiNat,GOLD,GetMoney(GOLD)-1000);
		SetResource(AiNat,COAL,GetMoney(COAL)+1000);
		SetResource(AiNat,IRON,GetMoney(IRON)+1000);
	}

	if(GetMoney(GOLD)>8000||GetExtraction(GOLD)>39){
		int MaxS18=GetExtraction(GOLD)*10;	
		TryUnit(&Eng.Unit.S18, MaxS18, 20, 100);
		TryUnit(&Eng.Unit.S18, MaxS18, 10, 100);
		TryUnit(&Eng.Unit.S18, MaxS18, 10, 100);
	}

	//TryUnit(&Eng.Unit.O18, 5, 20, 100);
	//TryUnit(&Eng.Unit.B18, 5, 20, 100);
	//TryUnit(&Eng.Unit.F18, 5, 20, 100);

	//TryUnit(&Eng.Unit.D17, 1000, 20, 100);
	//TryUnit(&Eng.Unit.KO7, 5, 20, 100);

	//TryUnit(&Eng.Unit.D18, 1000, 20, 100);
	//TryUnit(&Eng.Unit.KO8, 5, 20, 100);
	//TryUnit(&Eng.Unit.KF8, 5, 20, 100);
	
	//for(i=0;i<6;i++){
	//}
	if(UpgIsRun(&Eng.Upg.CanBuild4)){
		TryUnit(&Eng.Unit.Can, 1000, 90, 100);
	}

	// Peasat distribution
	int NU=GetUnits(&Eng.Unit.Kri)+GetUnits(&Eng.Unit.Pik)+GetUnits(&Eng.Unit.S15)+GetUnits(&Eng.Unit.S17);
	{ //500		
		// Krepost
		city->PKrepost=40;
		if(!(UpgIsRun(&Eng.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000)||NU<40) city->PKrepost=(NU>>4)-1;
		if(city->PKrepost>60) city->PKrepost=60;		
		// Field
		if(GetReadyUnits(&Eng.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&Eng.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		// Forest
		if(GetUnits(&Eng.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&Eng.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}
	if(city->MinFermers>250) TryUnit(&Eng.Build.Mel, 3, 100, 95);
	if(city->MinWooders>70) TryUnit(&Eng.Build.Skl, 2, 100, 60);

	// Buildings
	{
		TryUnit(&Eng.Build.Kr7, 2, 100, 70);
		TryUnit(&Eng.Build.Mel, 1, 100, 80);
		if(GetReadyUnits(&Eng.Build.Mel)){
			TryUnit(&Eng.Build.Skl, 1, 100, 80);
			TryUnit(&Eng.Build.Do1, 2, 100, 60);			
		}
		if(UpgIsRun(&Eng.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){
			TryUnit(&Eng.Build.Do1, 4, 100, 95);
			TryUnit(&Eng.Build.Kuz, 1, 100, 60);
		}

		TryUpgrade(&Eng.Upg.Do2_ENABLE, 100, 100);
		TryUnit(&Eng.Build.Do2, 5, 100, 60);
		
		if(UpgIsRun(&Eng.Upg.Mel_GETRES2)/*||GetDifficulty()<3*/){
			TryUnit(&Eng.Build.Kuz, 2, 100, 60);
			TryUnit(&Eng.Build.Mel, 2, 100, 80);
			TryUnit(&Eng.Build.Fer, 2, 100, 80);
			if(GetUnits(&Eng.Build.Do2)) TryUnit(&Eng.Unit.Tap, 5, 70, 80);
		}
		TryUnit(&Eng.Build.Kr8, 2, 100, 80);
		TryUnit(&Eng.Build.Cen, 1, 100, 80);
		if(GetReadyUnits(&Eng.Build.Do2)){
			TryUnit(&Eng.Build.Do1, 6, 100, 60);			
			TryUnit(&Eng.Build.Kuz, 3, 100, 60);
		}
		
		TryUnit(&Eng.Build.Hra, 1, 100, 70);
	}

	// Blg
	int NBlg=GetUnits(&Eng.Unit.S15)/60;
	{
		if(GetReadyUnits(&Eng.Build.Do1)>3){
			TryUnit(&Eng.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Eng.Build.Kr8)){
			TryUnit(&Eng.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Eng.Build.Cen)){
			TryUnit(&Eng.Build.Blg2, NBlg, 100, 70);
		}
	}


	//TryUnit(&Eng.Build.Ver, 2, 100, 70);

	// Upgrades

	// Fild
	if(GetUnits(&Eng.Build.Do2)>1) TryUpgrade(&Eng.Upg.CEN52, 95, 100);
	TryUpgrade(&Eng.Upg.CEN57, 100, 100);
	if(GetUnits(&Eng.Build.Do1)>2) TryUpgrade(&Eng.Upg.CEN55, 60, 100);

	// Food
	TryUpgrade(&Eng.Upg.Mel_GETRES, 80, 100);
	TryUpgrade(&Eng.Upg.Mel_GETRES2, 90, 100);
	if(GetUnits(&Eng.Build.Do2)){
		TryUpgrade(&Eng.Upg.CEN19, 90, 100);
		TryUpgrade(&Eng.Upg.CEN22, 90, 100);
		TryUpgrade(&Eng.Upg.CEN23, 90, 100);
	}

	// Wood
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		TryUpgrade(&Eng.Upg.Wood1,100,100);
		if(GetUnits(&Eng.Build.Do2)){
			TryUpgrade(&Eng.Upg.Wood2,100,100);
			TryUpgrade(&Eng.Upg.Wood3,100,100);
		}
	}

	// Mine
	{
		TryUnit(&Eng.Build.Rud, 1, 100, 70);
		TryUnit(&Eng.Build.Stn,1,95,80);
		if(GetReadyUnits(&Eng.Build.Kuz) && GetUnits(&Eng.Unit.Kri)>20 && GetMoney(STONE)<1000) TryUnit(&Eng.Build.Stn, 2, 95, 70);
		TryUnit(&Eng.Build.Iro, 1, 90, 70);
		TryUnit(&Eng.Build.Coa, 1, 90, 70);		
		
		if(GetUnits(&Eng.Unit.Kri)>120 && UpgIsRun(&Eng.Upg.Mel_GETRES2)){
			TryUnit(&Eng.Build.Rud, 2, 100, 70);
			TryUnit(&Eng.Build.Stn, 2, 95, 70);
			TryUnit(&Eng.Build.Iro, 2, 90, 70);
			TryUnit(&Eng.Build.Coa, 2, 90, 70);
			/*
			if(GetUnits(&Eng.Unit.Kri)>220||GetReadyUnits(&Eng.Build.Kr8)){
				TryUnit(&Eng.Build.Rud, 3, 100, 70);
				TryUnit(&Eng.Build.Stn, 3, 950, 70);
				TryUnit(&Eng.Build.Iro, 3, 90, 70);
				TryUnit(&Eng.Build.Coa, 3, 90, 70);
			}
			*/
		}
		if(UpgIsRun(&Eng.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000){
			TryUpgradeEx(&Eng.Upg.Gld0, 90, 100, 9000, 4000);
			TryUpgradeEx(&Eng.Upg.Stn0, 85, 80, 9000, 4000);			
			TryUpgradeEx(&Eng.Upg.Iro0, 80, 40, 9000, 4000);
			TryUpgradeEx(&Eng.Upg.Coa0, 75, 60, 9000, 4000);				
		}
		TryUpgrade(&Eng.Upg.MineEnable1, 100, 100);
		if(GetDifficulty()>1 && UpgIsRun(&Eng.Upg.Mel_GETRES2)){
			TryUpgradeEx(&Eng.Upg.Gld1, 95, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Gld2, 95, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Gld3, 95, 100, 6000, 1000);
			
			TryUpgradeEx(&Eng.Upg.Stn1, 90, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Stn2, 90, 100, 6000, 1000);
			//if(UpgIsRun(&Eng.Upg.EnDo1)){
				//TryUpgrade(&Eng.Upg.Gld4, 95, 100, 6000, 1000);
				//TryUpgrade(&Eng.Upg.Gld5, 95, 100, 6000, 1000);
				TryUpgradeEx(&Eng.Upg.Stn3, 95, 100, 6000, 1000);
				//TryUpgrade(&Eng.Upg.Stn4, 90, 100, 6000, 1000);
				//TryUpgrade(&Eng.Upg.Stn5, 90, 100, 6000, 1000);
			//}
			TryUpgradeEx(&Eng.Upg.Iro0, 80, 100, 9000, 4000);
			TryUpgradeEx(&Eng.Upg.Iro1, 70, 100, 9000, 2000);
			TryUpgradeEx(&Eng.Upg.Iro2, 60, 100, 9000, 1500);
			TryUpgradeEx(&Eng.Upg.Iro3, 60, 100, 9000, 1000);
			TryUpgradeEx(&Eng.Upg.Coa0, 80, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Coa1, 70, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Coa2, 60, 100, 6000, 1000);
			TryUpgradeEx(&Eng.Upg.Coa3, 60, 100, 6000, 1000);
		}
	}

	// Stages
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		TryUpgrade(&Eng.Upg.Kr7_Stage0, 80, 100);
	}
	if(GetUnits(&Eng.Build.Do2)){
		TryUpgrade(&Eng.Upg.Kr8_Stage0, 90, 100);
	}
	if(GetUnits(&Eng.Build.Do2)>1){
		TryUpgrade(&Eng.Upg.BldBuild1, 90, 100);		
	}
	
	//
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){		
		TryUpgrade(&Eng.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&Eng.Upg.KreBuild, 80, 100);
	}
	
	if(GetDifficulty()>0) WarriorsUpg();

	// Warriors speed

	// Kri
	if(GetUnits(&Eng.Build.Do2)>1){
		TryUpgrade(&Eng.Upg.KriBuild1,80,70);
		TryUpgrade(&Eng.Upg.KriBuild2,80,70);
		TryUpgrade(&Eng.Upg.KriBuild3,80,70);
	}
	// Pik
	TryUpgrade(&Eng.Upg.PikBuild1, 90, 100);
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){		
		{
			TryUpgrade(&Eng.Upg.PikBuild2, 90, 100);
			TryUpgrade(&Eng.Upg.PikBuild3, 90, 100);
			TryUpgrade(&Eng.Upg.PikBuild4, 90, 100);			
		}
	}
	// S18
	if(GetUnits(&Eng.Build.Kr8)>1){
		TryUpgrade(&Eng.Upg.S18Build1,80,100);
		TryUpgrade(&Eng.Upg.S18Build2,80,100);
		TryUpgrade(&Eng.Upg.S18Build3,80,100);
	}
	// Rei
	TryUpgrade(&Eng.Upg.Horse17Build, 90, 100);


}

void WarriorsUpg(){

	// Cen
	{
		TryUpgrade(&Eng.Upg.ArmShield1,90,100);
		TryUpgrade(&Eng.Upg.ArmShield2,60,100);
		TryUpgrade(&Eng.Upg.ArmShield3,60,100);
		
		TryUpgrade(&Eng.Upg.StrAttPause1,90,100);

		TryUpgrade(&Eng.Upg.StrDamage1,80,100);
		TryUpgrade(&Eng.Upg.StrDamage2,80,100);

		if(GetUnits(&Eng.Build.Kr8)>1){
			TryUpgrade(&Eng.Upg.BldShield1,80,100);
			TryUpgrade(&Eng.Upg.BldShield2,80,100);
		}
	}

	// Pik
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){		
		if(GetUnits(&Eng.Unit.Pik)>40){
			TryUpgrade(&Eng.Upg.PikAttack, 90, 100);
			TryUpgrade(&Eng.Upg.PikAttack3, 90, 100);
			TryUpgrade(&Eng.Upg.PikAttack4, 90, 100);
			TryUpgrade(&Eng.Upg.PikAttack5, 80, 100);
			TryUpgrade(&Eng.Upg.PikAttack6, 80, 100);
			TryUpgrade(&Eng.Upg.PikAttack7, 80, 100);
			
			TryUpgrade(&Eng.Upg.PikProtect, 90, 100);
			TryUpgrade(&Eng.Upg.PikProtect3, 90, 100);
			TryUpgrade(&Eng.Upg.PikProtect4, 90, 100);
			TryUpgrade(&Eng.Upg.PikProtect5, 80, 100);
			TryUpgrade(&Eng.Upg.PikProtect6, 80, 100);
			TryUpgrade(&Eng.Upg.PikProtect7, 80, 100);
		}
	}

	// S15
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)){
		if(UpgIsRun(&Eng.Upg.S15Protect7)&&GetUnits(&Eng.Unit.S15)>60){
			TryUpgrade(&Eng.Upg.S15Attack, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack3, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack4, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack5, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack6, 20, 100);
			TryUpgrade(&Eng.Upg.S15Attack7, 10, 100);
		}
		
		if(GetUnits(&Eng.Unit.S15)>60){
			TryUpgrade(&Eng.Upg.S15Protect, 90, 100);
			TryUpgrade(&Eng.Upg.S15Protect3, 90, 100);			
			TryUpgrade(&Eng.Upg.S15Protect4, 90, 100);
			TryUpgrade(&Eng.Upg.S15Protect5, 90, 100);
			TryUpgrade(&Eng.Upg.S15Protect6, 90, 100);
			TryUpgrade(&Eng.Upg.S15Protect7, 90, 100);
		}
	}

	// Mus
	if(UpgIsRun(&Eng.Upg.Mel_GETRES2)&&GetMoney(GOLD)>4000){
		if(UpgIsRun(&Eng.Upg.MusProtect6)&&GetUnits(&Eng.Unit.S17)>40){
			TryUpgrade(&Eng.Upg.MusAttack, 30, 100);
			TryUpgrade(&Eng.Upg.MusAttack3, 30, 100);
			TryUpgrade(&Eng.Upg.MusAttack4, 30, 100);
			TryUpgrade(&Eng.Upg.MusAttack5, 30, 100);
			TryUpgrade(&Eng.Upg.MusAttack6, 30, 100);
			TryUpgrade(&Eng.Upg.MusAttack7, 10, 100);
		}
		
		if(GetUnits(&Eng.Unit.S17)>40){
			TryUpgrade(&Eng.Upg.MusProtect, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect3, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.S17)>80){
			TryUpgrade(&Eng.Upg.MusProtect5, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect6, 90, 100);
			TryUpgrade(&Eng.Upg.MusProtect7, 50, 100);
		}
	}

	// S18
	{
		if(GetUnits(&Eng.Unit.S18)){
			TryUpgrade(&Eng.Upg.S18Attack, 30, 100);
			TryUpgrade(&Eng.Upg.S18Attack3, 30, 100);
			TryUpgrade(&Eng.Upg.S18Attack4, 30, 100);
			TryUpgrade(&Eng.Upg.S18Attack5, 30, 100);
			TryUpgrade(&Eng.Upg.S18Attack6, 30, 100);
			TryUpgrade(&Eng.Upg.S18Attack7, 30, 100);
			
			TryUpgrade(&Eng.Upg.S18Protect, 90, 100);
			TryUpgrade(&Eng.Upg.S18Protect3, 90, 100);
			TryUpgrade(&Eng.Upg.S18Protect4, 90, 100);
			TryUpgrade(&Eng.Upg.S18Protect5, 90, 100);
			TryUpgrade(&Eng.Upg.S18Protect6, 90, 100);
			TryUpgrade(&Eng.Upg.S18Protect7, 90, 100);
		}
	}

	// Officers
	{
		TryUpgrade(&Eng.Upg.B17Protect, 50, 100);
		TryUpgrade(&Eng.Upg.O17Damage, 50, 100);
		TryUpgrade(&Eng.Upg.O17Protect, 50, 100);
		TryUpgrade(&Eng.Upg.F17Protect, 50, 100);
	}

	// Rei
	{
		if(GetUnits(&Eng.Unit.Rei)>20){
			TryUpgrade(&Eng.Upg.ReiAttack, 90, 100);
			TryUpgrade(&Eng.Upg.ReiAttack3, 90, 100);
			TryUpgrade(&Eng.Upg.ReiAttack4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.Rei)>40){
			TryUpgrade(&Eng.Upg.ReiAttack5, 90, 100);
			TryUpgrade(&Eng.Upg.ReiAttack6, 90, 100);
			TryUpgrade(&Eng.Upg.ReiAttack7, 90, 100);
		}
		
		if(GetUnits(&Eng.Unit.Rei)>20){
			TryUpgrade(&Eng.Upg.ReiProtect, 90, 100);
			TryUpgrade(&Eng.Upg.ReiProtect3, 90, 100);
			TryUpgrade(&Eng.Upg.ReiProtect4, 90, 100);
		}
		if(GetUnits(&Eng.Unit.Rei)>40){
			TryUpgrade(&Eng.Upg.ReiProtect5, 90, 100);
			TryUpgrade(&Eng.Upg.ReiProtect6, 90, 100);
			TryUpgrade(&Eng.Upg.ReiProtect7, 90, 100);
		}
	}

	// Can
	{
		TryUpgrade(&Eng.Upg.CanCost,95,60);
		TryUpgrade(&Eng.Upg.CanCost3,95,60);
		TryUpgrade(&Eng.Upg.CanCost4,95,60);
		//TryUpgrade(&Eng.Upg.CanCost5,95,100);
		//TryUpgrade(&Eng.Upg.CanCost6,95,100);
		//TryUpgrade(&Eng.Upg.CanCost7,95,100);
		TryUpgrade(&Eng.Upg.CanBuild,95,60);
		TryUpgrade(&Eng.Upg.CanBuild3,95,60);
		TryUpgrade(&Eng.Upg.CanBuild4,95,60);
		//TryUpgrade(&Eng.Upg.CanBuild5,95,100);
		//TryUpgrade(&Eng.Upg.CanBuild6,95,100);
		//TryUpgrade(&Eng.Upg.CanBuild7,95,100);
	}

}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Eng.Build.Skl)) TryUnit(&Eng.Build.Ver,1,100,90);
	if(GetUnits(&Eng.Build.Cen)) TryUnit(&Eng.Build.Ver,3,60,60);

	//int NU=GetUnits(&Eng.Unit.Pik)+GetUnits(&Eng.Unit.S15)+GetUnits(&Eng.Unit.S17)+GetUnits(&Eng.Unit.Rei);

	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&Eng.Unit.Parom, NPar, 100, 100);

	if(TryUnit(&Eng.Unit.Lodka, 10, 100, 100)){
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
		TryUnit(&Eng.Unit.Lodka, 10, 10, 100);
	}
	
	TryUnit(&Eng.Unit.Pinta, 5, 100, 100);
	TryUnit(&Eng.Unit.Pinta, 5, 50, 100);
	TryUnit(&Eng.Unit.Pinta, 5, 50, 100);
	TryUnit(&Eng.Unit.Pinta, 5, 50, 100);
	TryUnit(&Eng.Unit.Pinta, 5, 50, 100);

	TryUnit(&Eng.Unit.Santa, 2, 100, 100);
	TryUnit(&Eng.Unit.Santa, 2, 50, 100);

	TryUnit(&Eng.Unit.Fregat, 2, 100, 100);
	TryUnit(&Eng.Unit.Fregat, 2, 50, 100);

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