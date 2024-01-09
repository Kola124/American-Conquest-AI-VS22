#define CONQUEST
#include "..\Import.h"
#include "..\SpnNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Spn.Unit.Kri.Index;
	city->Init(AiNat);

	city->NIndexBrb=Spn.Unit.B17.Index;
	city->NIndexOff=Spn.Unit.O17.Index;
	city->NIndexFlg=Spn.Unit.F17.Index;

	city->CannonNIndex=Spn.Unit.Can.Index;
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
	city->NeedHunt=0;

	city->ParomNIndex=Spn.Unit.Parom.Index;
	
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
	/*city->AddBranch(Spn.Unit.Pik.Index, brBack, 35, 226);
	city->AddBranch(Spn.Unit.S15.Index,brBack,35,306);
	city->AddBranch(Spn.Unit.S17.Index,brBack,35,346);
	city->AddBranch(Spn.Unit.S18.Index,brBack,600,500);
	city->AddBranch(Spn.Unit.Rei.Index,brBack,79,132);
	city->AddBranch(Spn.Unit.Sha.Index,brBack,600,500);*/

	Branch* Pik= city->AddBranch(Spn.Unit.Pik.Index, brBack, 35, 226);
	Branch* S15= city->AddBranch(Spn.Unit.S15.Index, brBack, 35, 306);
	Branch* S17= city->AddBranch(Spn.Unit.S17.Index, brBack, 35, 346);
	Branch* S18= city->AddBranch(Spn.Unit.S18.Index, brBack, 600, 500);
	Branch* Rei= city->AddBranch(Spn.Unit.Rei.Index, brBack, 79, 132);
	Branch* Sha= city->AddBranch(Spn.Unit.Sha.Index, brBack, 600, 500);

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

	S18->Min=400;
	Sha->Min=400;
	
	// Units in buildings
	city->NStrelok = 5;
	if(!city->LandType){
		if(GetUnits(&Spn.Build.Kr8)) city->NStrelok += 5;
		if(GetUnits(&Spn.Build.Kr7)>1) city->NStrelok += 10;
	}
	city->NUnits = 2;

	// Units
	TryUnit(&Spn.Unit.Kri, 800, 5, 100);
	TryUnit(&Spn.Unit.Kri, 800, 3, 100);
	TryUnit(&Spn.Unit.Kri, 800, 3, 100);
	TryUnit(&Spn.Unit.Kri, 800, 3, 100);
	TryUnit(&Spn.Unit.Kri, 800, 3, 100);

	TryUnit(&Spn.Unit.Sha, 1000, 20, 100);

	int PikBuild=0;
	if(!GetUnits(&Spn.Unit.S15)||GetUnits(&Spn.Unit.S15)>60){
		TryUnit(&Spn.Unit.Pik, 10000, 20, 100);
		TryUnit(&Spn.Unit.Pik, 10000, 10, 100);
		TryUnit(&Spn.Unit.Pik, 10000, 10, 100);
		PikBuild=1;
	}
	
	int S15Perc=100;
	if(GetUnits(&Spn.Build.Kr8)) S15Perc=50;

	TryUnit(&Spn.Unit.S15, 10000, 20, S15Perc);
	TryUnit(&Spn.Unit.S15, 10000, 10, S15Perc);
	TryUnit(&Spn.Unit.S15, 10000, 10, S15Perc);

	TryUnit(&Spn.Unit.S17, 10000, 20, 100);
	TryUnit(&Spn.Unit.S17, 10000, 10, 100);
	TryUnit(&Spn.Unit.S17, 10000, 10, 100);
	
	if(city->Flags[HorceBuild]){
		TryUnit(&Spn.Unit.Rei, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int ReiCost=GetUnitCost(AiNat,&Spn.Unit.Rei,FOOD)*41;
		if(ReiCost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	int NeedSquad=(GetUnits(&Spn.Unit.Pik)+GetUnits(&Spn.Unit.S17))/50;
	TryUnit(&Spn.Unit.O17, NeedSquad, 50, 100);
	TryUnit(&Spn.Unit.B17, NeedSquad, 50, 100);
	TryUnit(&Spn.Unit.F17, NeedSquad, 50, 100);

	if(GetMoney(GOLD)>5000&&GetMoney(COAL)<100){
		SetResource(AiNat,GOLD,GetMoney(GOLD)-1000);
		SetResource(AiNat,COAL,GetMoney(COAL)+1000);
		SetResource(AiNat,IRON,GetMoney(IRON)+1000);
	}

	if(GetMoney(GOLD)>8000||GetExtraction(GOLD)>39){
		int MaxS18=GetExtraction(GOLD)*10;
		TryUnit(&Spn.Unit.S18, MaxS18, 20, 100);
		TryUnit(&Spn.Unit.S18, MaxS18, 10, 100);
		TryUnit(&Spn.Unit.S18, MaxS18, 10, 100);
	}

	//TryUnit(&Spn.Unit.O18, 5, 20, 100);
	//TryUnit(&Spn.Unit.B18, 5, 20, 100);
	//TryUnit(&Spn.Unit.F18, 5, 20, 100);

	//TryUnit(&Spn.Unit.D17, 1000, 20, 100);
	//TryUnit(&Spn.Unit.KO7, 5, 20, 100);

	//TryUnit(&Spn.Unit.D18, 1000, 20, 100);
	//TryUnit(&Spn.Unit.KO8, 5, 20, 100);
	//TryUnit(&Spn.Unit.KF8, 5, 20, 100);
	
	//for(i=0;i<6;i++){
	//}
	if(UpgIsRun(&Spn.Upg.CanBuild4)){
		TryUnit(&Spn.Unit.Can, 1000, 90, 100);
	}

	// Peasat distribution
	int NU=GetUnits(&Spn.Unit.Kri)+GetUnits(&Spn.Unit.Pik)+GetUnits(&Spn.Unit.S15)+GetUnits(&Spn.Unit.S17);
	{ //500		
		// Krepost
		city->PKrepost=40;
		if(!(UpgIsRun(&Spn.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000)||NU<40) city->PKrepost=(NU>>4)-1;
		if(city->PKrepost>60) city->PKrepost=60;		
		// Field
		if(GetReadyUnits(&Spn.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&Spn.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&Spn.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		// Forest
		if(GetUnits(&Spn.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&Spn.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}
	if(city->MinFermers>250) TryUnit(&Spn.Build.Mel, 3, 100, 95);
	if(city->MinWooders>70) TryUnit(&Spn.Build.Skl, 2, 100, 60);

	// Buildings
	{
		TryUnit(&Spn.Build.Kr7, 2, 100, 70);
		TryUnit(&Spn.Build.Mel, 1, 100, 80);
		if(GetReadyUnits(&Spn.Build.Mel)){
			TryUnit(&Spn.Build.Skl, 1, 100, 80);
			TryUnit(&Spn.Build.Do1, 2, 100, 60);			
		}
		if(UpgIsRun(&Spn.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){
			TryUnit(&Spn.Build.Do1, 4, 100, 95);
			TryUnit(&Spn.Build.Kuz, 1, 100, 60);
		}

		TryUpgrade(&Spn.Upg.Do2_ENABLE, 100, 100);
		TryUnit(&Spn.Build.Do2, 5, 100, 60);
		
		if(UpgIsRun(&Spn.Upg.Mel_GETRES2)/*||GetDifficulty()<3*/){
			TryUnit(&Spn.Build.Kuz, 2, 100, 60);
			TryUnit(&Spn.Build.Mel, 2, 100, 80);
		}
		TryUnit(&Spn.Build.Kr8, 2, 100, 80);
		TryUnit(&Spn.Build.Cen, 1, 100, 80);
		if(GetReadyUnits(&Spn.Build.Do2)){
			TryUnit(&Spn.Build.Do1, 6, 100, 60);			
			TryUnit(&Spn.Build.Kuz, 3, 100, 60);
		}
		
		TryUnit(&Spn.Build.Hra, 1, 100, 70);
	}

	// Blg
	int NBlg=GetUnits(&Spn.Unit.S15)/60;
	{
		if(GetReadyUnits(&Spn.Build.Do1)>3){
			TryUnit(&Spn.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Spn.Build.Kr8)){
			TryUnit(&Spn.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&Spn.Build.Cen)){
			TryUnit(&Spn.Build.Blg2, NBlg, 100, 70);
		}
	}


	//TryUnit(&Spn.Build.Ver, 2, 100, 70);

	// Upgrades

	// Fild
	if(GetUnits(&Spn.Build.Do2)>1) TryUpgrade(&Spn.Upg.CEN52, 95, 100);
	TryUpgrade(&Spn.Upg.CEN57, 100, 100);
	if(GetUnits(&Spn.Build.Do1)>2) TryUpgrade(&Spn.Upg.CEN55, 60, 100);

	// Food
	TryUpgrade(&Spn.Upg.Mel_GETRES, 80, 100);
	TryUpgrade(&Spn.Upg.Mel_GETRES2, 90, 100);
	if(GetUnits(&Spn.Build.Do2)){
		TryUpgrade(&Spn.Upg.CEN19, 90, 100);
		TryUpgrade(&Spn.Upg.CEN22, 90, 100);
		TryUpgrade(&Spn.Upg.CEN23, 90, 100);
	}

	// Wood
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)){
		TryUpgrade(&Spn.Upg.Wood1,100,100);
		if(GetUnits(&Spn.Build.Do2)){
			TryUpgrade(&Spn.Upg.Wood2,100,100);
			TryUpgrade(&Spn.Upg.Wood3,100,100);
		}
	}

	// Mine
	{
		TryUnit(&Spn.Build.Rud, 1, 100, 70);
		TryUnit(&Spn.Build.Stn,1,95,80);
		if(GetReadyUnits(&Spn.Build.Kuz) && GetUnits(&Spn.Unit.Kri)>20 && GetMoney(STONE)<1000) TryUnit(&Spn.Build.Stn, 2, 95, 70);
		TryUnit(&Spn.Build.Iro, 1, 90, 70);
		TryUnit(&Spn.Build.Coa, 1, 90, 70);		
		
		if(GetUnits(&Spn.Unit.Kri)>120 && UpgIsRun(&Spn.Upg.Mel_GETRES2)){
			TryUnit(&Spn.Build.Rud, 2, 100, 70);
			TryUnit(&Spn.Build.Stn, 2, 95, 70);
			TryUnit(&Spn.Build.Iro, 2, 90, 70);
			TryUnit(&Spn.Build.Coa, 2, 90, 70);
			/*
			if(GetUnits(&Spn.Unit.Kri)>220||GetReadyUnits(&Spn.Build.Kr8)){
				TryUnit(&Spn.Build.Rud, 3, 100, 70);
				TryUnit(&Spn.Build.Stn, 3, 950, 70);
				TryUnit(&Spn.Build.Iro, 3, 90, 70);
				TryUnit(&Spn.Build.Coa, 3, 90, 70);
			}
			*/
		}
		if(UpgIsRun(&Spn.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000){
			TryUpgradeEx(&Spn.Upg.Gld0, 90, 100, 9000, 4000);
			TryUpgradeEx(&Spn.Upg.Stn0, 85, 80, 9000, 4000);			
			TryUpgradeEx(&Spn.Upg.Iro0, 80, 40, 9000, 4000);
			TryUpgradeEx(&Spn.Upg.Coa0, 75, 60, 9000, 4000);				
		}
		TryUpgrade(&Spn.Upg.MineEnable1, 100, 100);
		if(GetDifficulty()>1 && UpgIsRun(&Spn.Upg.Mel_GETRES2)){
			TryUpgradeEx(&Spn.Upg.Gld1, 95, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Gld2, 95, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Gld3, 95, 100, 6000, 1000);
			
			TryUpgradeEx(&Spn.Upg.Stn1, 90, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Stn2, 90, 100, 6000, 1000);
			//if(UpgIsRun(&Spn.Upg.EnDo1)){
				//TryUpgrade(&Spn.Upg.Gld4, 95, 100, 6000, 1000);
				//TryUpgrade(&Spn.Upg.Gld5, 95, 100, 6000, 1000);
				TryUpgradeEx(&Spn.Upg.Stn3, 95, 100, 6000, 1000);
				//TryUpgrade(&Spn.Upg.Stn4, 90, 100, 6000, 1000);
				//TryUpgrade(&Spn.Upg.Stn5, 90, 100, 6000, 1000);
			//}
			TryUpgradeEx(&Spn.Upg.Iro0, 80, 100, 9000, 4000);
			TryUpgradeEx(&Spn.Upg.Iro1, 70, 100, 9000, 2000);
			TryUpgradeEx(&Spn.Upg.Iro2, 60, 100, 9000, 1500);
			TryUpgradeEx(&Spn.Upg.Iro3, 60, 100, 9000, 1000);
			TryUpgradeEx(&Spn.Upg.Coa0, 80, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Coa1, 70, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Coa2, 60, 100, 6000, 1000);
			TryUpgradeEx(&Spn.Upg.Coa3, 60, 100, 6000, 1000);
		}
	}

	// Stages
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)){
		TryUpgrade(&Spn.Upg.Kr7_Stage0, 80, 100);
	}
	if(GetUnits(&Spn.Build.Do2)){
		TryUpgrade(&Spn.Upg.Kr8_Stage0, 90, 100);
	}
	if(GetUnits(&Spn.Build.Do2)>1){
		TryUpgrade(&Spn.Upg.BldBuild1, 90, 100);		
	}
	
	//
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)){		
		TryUpgrade(&Spn.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&Spn.Upg.KreBuild, 80, 100);
	}
	
	if(GetDifficulty()>0) WarriorsUpg();

	// Warriors speed

	// Kri
	if(GetUnits(&Spn.Build.Do2)>1){
		TryUpgrade(&Spn.Upg.KriBuild1,80,70);
		TryUpgrade(&Spn.Upg.KriBuild2,80,70);
		TryUpgrade(&Spn.Upg.KriBuild3,80,70);
	}
	// Pik
	TryUpgrade(&Spn.Upg.PikBuild1, 90, 100);
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){		
		{
			TryUpgrade(&Spn.Upg.PikBuild2, 90, 100);
			TryUpgrade(&Spn.Upg.PikBuild3, 90, 100);
			TryUpgrade(&Spn.Upg.PikBuild4, 90, 100);			
		}
	}
	// S18
	if(GetUnits(&Spn.Build.Kr8)>1){
		TryUpgrade(&Spn.Upg.S18Build1,80,100);
		TryUpgrade(&Spn.Upg.S18Build2,80,100);
		TryUpgrade(&Spn.Upg.S18Build3,80,100);
	}
	// Rei
	TryUpgrade(&Spn.Upg.ReiBuild, 90, 100);


}

void WarriorsUpg(){

	// Cen
	{
		TryUpgrade(&Spn.Upg.ArmShield1,90,100);
		TryUpgrade(&Spn.Upg.ArmShield2,60,100);
		TryUpgrade(&Spn.Upg.ArmShield3,60,100);
		
		TryUpgrade(&Spn.Upg.StrAttPause1,90,100);

		TryUpgrade(&Spn.Upg.StrDamage1,80,100);
		TryUpgrade(&Spn.Upg.StrDamage2,80,100);

		if(GetUnits(&Spn.Build.Kr8)>1){
			TryUpgrade(&Spn.Upg.BldShield1,80,100);
			TryUpgrade(&Spn.Upg.BldShield2,80,100);
		}
	}

	// Pik
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)){		
		if(GetUnits(&Spn.Unit.Pik)>40){
			TryUpgrade(&Spn.Upg.PikAttack, 90, 100);
			TryUpgrade(&Spn.Upg.PikAttack3, 90, 100);
			TryUpgrade(&Spn.Upg.PikAttack4, 90, 100);
			TryUpgrade(&Spn.Upg.PikAttack5, 80, 100);
			TryUpgrade(&Spn.Upg.PikAttack6, 80, 100);
			TryUpgrade(&Spn.Upg.PikAttack7, 80, 100);
			
			TryUpgrade(&Spn.Upg.PikProtect, 90, 100);
			TryUpgrade(&Spn.Upg.PikProtect3, 90, 100);
			TryUpgrade(&Spn.Upg.PikProtect4, 90, 100);
			TryUpgrade(&Spn.Upg.PikProtect5, 80, 100);
			TryUpgrade(&Spn.Upg.PikProtect6, 80, 100);
			TryUpgrade(&Spn.Upg.PikProtect7, 80, 100);
		}
	}

	// S15
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)){
		if(UpgIsRun(&Spn.Upg.S15Protect7)&&GetUnits(&Spn.Unit.S15)>60){
			TryUpgrade(&Spn.Upg.S15Attack, 20, 100);
			TryUpgrade(&Spn.Upg.S15Attack3, 20, 100);
			TryUpgrade(&Spn.Upg.S15Attack4, 20, 100);
			TryUpgrade(&Spn.Upg.S15Attack5, 20, 100);
			TryUpgrade(&Spn.Upg.S15Attack6, 20, 100);
			TryUpgrade(&Spn.Upg.S15Attack7, 10, 100);
		}
		
		if(GetUnits(&Spn.Unit.S15)>60){
			TryUpgrade(&Spn.Upg.S15Protect, 90, 100);
			TryUpgrade(&Spn.Upg.S15Protect3, 90, 100);			
			TryUpgrade(&Spn.Upg.S15Protect4, 90, 100);
			TryUpgrade(&Spn.Upg.S15Protect5, 90, 100);
			TryUpgrade(&Spn.Upg.S15Protect6, 90, 100);
			TryUpgrade(&Spn.Upg.S15Protect7, 90, 100);
		}
	}

	// Mus
	if(UpgIsRun(&Spn.Upg.Mel_GETRES2)&&GetMoney(GOLD)>4000){
		if(UpgIsRun(&Spn.Upg.MusProtect6)&&GetUnits(&Spn.Unit.S17)>40){
			TryUpgrade(&Spn.Upg.MusAttack, 30, 100);
			TryUpgrade(&Spn.Upg.MusAttack3, 30, 100);
			TryUpgrade(&Spn.Upg.MusAttack4, 30, 100);
			TryUpgrade(&Spn.Upg.MusAttack5, 30, 100);
			TryUpgrade(&Spn.Upg.MusAttack6, 30, 100);
			TryUpgrade(&Spn.Upg.MusAttack7, 10, 100);
		}
		
		if(GetUnits(&Spn.Unit.S17)>40){
			TryUpgrade(&Spn.Upg.MusProtect, 90, 100);
			TryUpgrade(&Spn.Upg.MusProtect3, 90, 100);
			TryUpgrade(&Spn.Upg.MusProtect4, 90, 100);
		}
		if(GetUnits(&Spn.Unit.S17)>80){
			TryUpgrade(&Spn.Upg.MusProtect5, 90, 100);
			TryUpgrade(&Spn.Upg.MusProtect6, 90, 100);
			TryUpgrade(&Spn.Upg.MusProtect7, 50, 100);
		}
	}

	// S18
	{
		if(GetUnits(&Spn.Unit.S18)){
			TryUpgrade(&Spn.Upg.S18Attack, 30, 100);
			TryUpgrade(&Spn.Upg.S18Attack3, 30, 100);
			TryUpgrade(&Spn.Upg.S18Attack4, 30, 100);
			TryUpgrade(&Spn.Upg.S18Attack5, 30, 100);
			TryUpgrade(&Spn.Upg.S18Attack6, 30, 100);
			TryUpgrade(&Spn.Upg.S18Attack7, 30, 100);
			
			TryUpgrade(&Spn.Upg.S18Protect, 90, 100);
			TryUpgrade(&Spn.Upg.S18Protect3, 90, 100);
			TryUpgrade(&Spn.Upg.S18Protect4, 90, 100);
			TryUpgrade(&Spn.Upg.S18Protect5, 90, 100);
			TryUpgrade(&Spn.Upg.S18Protect6, 90, 100);
			TryUpgrade(&Spn.Upg.S18Protect7, 90, 100);
		}
	}

	// Officers
	{
		TryUpgrade(&Spn.Upg.B17Protect, 50, 100);
		TryUpgrade(&Spn.Upg.O17Damage, 50, 100);
		TryUpgrade(&Spn.Upg.O17Protect, 50, 100);
		TryUpgrade(&Spn.Upg.F17Protect, 50, 100);
	}

	// Rei
	{
		if(GetUnits(&Spn.Unit.Rei)>20){
			TryUpgrade(&Spn.Upg.ReiAttack, 90, 100);
			TryUpgrade(&Spn.Upg.ReiAttack3, 90, 100);
			TryUpgrade(&Spn.Upg.ReiAttack4, 90, 100);
		}
		if(GetUnits(&Spn.Unit.Rei)>40){
			TryUpgrade(&Spn.Upg.ReiAttack5, 90, 100);
			TryUpgrade(&Spn.Upg.ReiAttack6, 90, 100);
			TryUpgrade(&Spn.Upg.ReiAttack7, 90, 100);
		}
		
		if(GetUnits(&Spn.Unit.Rei)>20){
			TryUpgrade(&Spn.Upg.ReiProtect, 90, 100);
			TryUpgrade(&Spn.Upg.ReiProtect3, 90, 100);
			TryUpgrade(&Spn.Upg.ReiProtect4, 90, 100);
		}
		if(GetUnits(&Spn.Unit.Rei)>40){
			TryUpgrade(&Spn.Upg.ReiProtect5, 90, 100);
			TryUpgrade(&Spn.Upg.ReiProtect6, 90, 100);
			TryUpgrade(&Spn.Upg.ReiProtect7, 90, 100);
		}
	}

	// Can
	{
		TryUpgrade(&Spn.Upg.CanCost,95,60);
		TryUpgrade(&Spn.Upg.CanCost3,95,60);
		TryUpgrade(&Spn.Upg.CanCost4,95,60);
		//TryUpgrade(&Spn.Upg.CanCost5,95,100);
		//TryUpgrade(&Spn.Upg.CanCost6,95,100);
		//TryUpgrade(&Spn.Upg.CanCost7,95,100);
		TryUpgrade(&Spn.Upg.CanBuild,95,60);
		TryUpgrade(&Spn.Upg.CanBuild3,95,60);
		TryUpgrade(&Spn.Upg.CanBuild4,95,60);
		//TryUpgrade(&Spn.Upg.CanBuild5,95,100);
		//TryUpgrade(&Spn.Upg.CanBuild6,95,100);
		//TryUpgrade(&Spn.Upg.CanBuild7,95,100);
	}

}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Spn.Build.Skl)) TryUnit(&Spn.Build.Ver,1,100,90);
	if(GetUnits(&Spn.Build.Cen)) TryUnit(&Spn.Build.Ver,3,60,60);

	//int NU=GetUnits(&Spn.Unit.Pik)+GetUnits(&Spn.Unit.S15)+GetUnits(&Spn.Unit.S17)+GetUnits(&Spn.Unit.Rei);

	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&Spn.Unit.Parom, NPar, 100, 100);

	if(TryUnit(&Spn.Unit.Lodka, 10, 100, 100)){
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
		TryUnit(&Spn.Unit.Lodka, 10, 10, 100);
	}
	
	TryUnit(&Spn.Unit.Pinta, 5, 100, 100);
	TryUnit(&Spn.Unit.Pinta, 5, 50, 100);
	TryUnit(&Spn.Unit.Pinta, 5, 50, 100);
	TryUnit(&Spn.Unit.Pinta, 5, 50, 100);
	TryUnit(&Spn.Unit.Pinta, 5, 50, 100);

	TryUnit(&Spn.Unit.Santa, 2, 100, 100);
	TryUnit(&Spn.Unit.Santa, 2, 50, 100);

	TryUnit(&Spn.Unit.Fregat, 2, 100, 100);
	TryUnit(&Spn.Unit.Fregat, 2, 50, 100);

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