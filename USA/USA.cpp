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
void WarriorsUpg();
void MiniWaterScript();
void WaterScript();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	int LAND=GetLandType();
	switch(LAND){
	case LT_LAND:
		break;
	case LT_CONTINENT:
	case LT_MEDITERRANEAN:	
		MiniWaterScript();
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
	city->HuntNIndex=USA.Unit.Tap.Index;
	city->NeedHunt=0;

	city->ParomNIndex=USA.Unit.Parom.Index;
	
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
	const bool HorceBuild=0;
	const bool CanBuild=1;

	// Role planing

	Branch* Pik= city->AddBranch(USA.Unit.Pik.Index, brBack, 36, 1000);
	Branch* S15= city->AddBranch(USA.Unit.S15.Index, brBack, 36, 1000);
	Branch* S17= city->AddBranch(USA.Unit.S17.Index, brBack, 36, 120);
	Branch* S18= city->AddBranch(USA.Unit.S18.Index, brBack, 36, 120);
	Branch* Rei= city->AddBranch(USA.Unit.Rei.Index, brBack, 79, 1000);
	Branch* Sha=city->AddBranch(USA.Unit.Sha.Index, brBack, 400, 500);
	Branch* Tap= city->AddBranch(USA.Unit.Tap.Index, brBack, 100, 120);
	Branch* Mil= city->AddBranch(USA.Unit.Mil.Index, brBack, 50, 60);

	Branch* B17 = city->AddBranch(USA.Unit.B17.Index, brBack, 1, 5);
	Branch* F17 = city->AddBranch(USA.Unit.F17.Index, brBack, 1, 5);
	Branch* O17 = city->AddBranch(USA.Unit.O17.Index, brBack, 1, 5);

	Branch* B18 = city->AddBranch(USA.Unit.B18.Index, brBack, 1, 5);
	Branch* F18 = city->AddBranch(USA.Unit.F18.Index, brBack, 1, 5);
	Branch* O18 = city->AddBranch(USA.Unit.O18.Index, brBack, 1, 5);

	Pik->Prio[brForward] = 3;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 2;	Pik->Part[brCenter] = 0;	Pik->Type[brCenter] = btKillers;	
								if(GetDifficulty()<2) Pik->Part[brCenter] = 1;
	Pik->Prio[brBack] = 0;		Pik->Part[brBack] = 0;	Pik->Type[brBack] = btStorm;
	Pik->Formation = 1;

	S15->Prio[brForward] = 0;	S15->Part[brForward] = 0;
	S15->Prio[brCenter] = 1;	S15->Part[brCenter] = 1;	
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 0;
	
	S15->Strelok = 1;
	if (!GetUnits(&USA.Build.Kr8)) {
		S15->Formation = 1;
		S15->Type[brCenter] = btRifleman;
	}
	if (GetUnits(&USA.Build.Kr8)) {
		S15->Formation = 0;
		S15->BaseGuard = 1;
	}


	S17->Prio[brForward] = 3;	S17->Part[brForward] = 1;
	S17->Prio[brCenter] = 2;	S17->Part[brCenter] = 1;
	S17->Prio[brBack] = 0;		S17->Part[brBack] = 0;
	S17->Formation = 1;
	S17->Strelok = 1;
	if (!UpgIsDone(&USA.Upg.S18Unlock)) {
		S17->Type[brCenter] = btRifleman;
		S17->Type[brForward] = btRifleman;
		S17->Type[brBack] = btRifleman;
	}
	if (UpgIsDone(&USA.Upg.S18Unlock)) {
		S17->BaseGuard = 0;
		S17->Type[brBack] = btKillers;
	}

	S18->Prio[brForward] = 3;	S18->Part[brForward] = 0;	S18->Type[brForward] = btRifleman;
	S18->Prio[brCenter] = 2;	S18->Part[brCenter] = 1;	S18->Type[brCenter] = btRifleman;
	S18->Prio[brBack] = 0;		S18->Part[brBack] = 0;
	S18->Formation=1;
	S18->Strelok = 1;
	//S18->BaseGuard=1;


	O18->Prio[brCenter] = 1;	O18->Part[brCenter] = 1;
	F18->Prio[brCenter] = 1;	F18->Part[brCenter] = 1;
	B18->Prio[brCenter] = 1;	B18->Part[brCenter] = 1;

	Rei->Prio[brForward] = 0;	Rei->Part[brForward] = 0;
	Rei->Prio[brCenter] = 1;	Rei->Part[brCenter] = 1;	Rei->Type[brCenter] = btKillers;
	Rei->Prio[brBack] = 0;		Rei->Part[brBack] = 0;
	Rei->Domovoi=false;
	if (GetUnits(&USA.Unit.Rei) < 40) {
		Rei->BaseGuard = 1;
		Rei->Formation = 0;
	}
	else {
		Rei->BaseGuard = 0;
		Rei->Formation = 0;
	}

	Mil->Prio[brForward] = 3;	Mil->Part[brForward] = 1;	Mil->Type[brForward] = btStorm;	
	Mil->Prio[brCenter] = 2;	Mil->Part[brCenter] = 0;
	Mil->Prio[brBack] = 0;		Mil->Part[brBack] = 0;	
	//Mil->Formation=1;
	Mil->BaseGuard=1;

	Sha->BaseGuard=1;

	S18->Min=400;

	Tap->Hunter=1;

	if (UpgIsDone(&USA.Upg.S18Unlock)) {
		city->NIndexBrb = USA.Unit.B18.Index;
		city->NIndexOff = USA.Unit.O18.Index;
		city->NIndexFlg = USA.Unit.F18.Index;
	}
	
	// Units in buildings
	city->NStrelok = 5;
	if(!city->LandType){
		if(GetUnits(&USA.Build.Kr8)) city->NStrelok += 5;
		if(GetUnits(&USA.Build.Kr7)>1) city->NStrelok += 10;
	}
	city->NUnits = 2;

	// Units
	TryUnit(&USA.Unit.Kri, 800, 5, 100);
	TryUnit(&USA.Unit.Kri, 800, 3, 100);
	TryUnit(&USA.Unit.Kri, 800, 3, 100);
	TryUnit(&USA.Unit.Kri, 800, 3, 100);
	TryUnit(&USA.Unit.Kri, 800, 3, 100);

	TryUnit(&USA.Unit.Sha, 10, 20, 100);

	TryUnit(&USA.Unit.Pik, 400, 20, 100);
	TryUnit(&USA.Unit.Pik, 400, 10, 100);
	TryUnit(&USA.Unit.Pik, 400, 10, 100);
	if (!GetUnits(&USA.Build.Kr8)) {
		TryUnit(&USA.Unit.Pik, 400, 20, 100);
		TryUnit(&USA.Unit.Pik, 400, 10, 100);
		TryUnit(&USA.Unit.Pik, 400, 10, 100);
	}
	
	if (!UpgIsDone(&USA.Upg.S18Unlock)) {
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
		TryUnit(&USA.Unit.S15, 10000, 20, 100);
	}

	if(GetUnits(&USA.Build.Kr8)){
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S15, 650, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
		TryUnit(&USA.Unit.S17, 10000, 20, 100);
	}
	
	if(city->Flags[HorceBuild]){
		TryUnit(&USA.Unit.Rei, 1000, 95, 100);
		TryUnit(&USA.Unit.Rei, 1000, 95, 100);
		if(GetResource(AiNat,FOOD)<3000){
			city->Flags[HorceBuild]=0;
		}
	}else{
		int ReiCost=GetUnitCost(AiNat,&USA.Unit.Rei,FOOD)*41;
		if(ReiCost<GetResource(AiNat,FOOD)){
			city->Flags[HorceBuild]=1;
		}
	}
	
	if(GetUnits(&USA.Unit.O18)+GetUnits(&USA.Unit.O17)<5)
	{
		if (UpgIsDone(&USA.Upg.S18Unlock)) {
			TryUnit(&USA.Unit.O18, 5, 20, 100);
		}
		else {
			TryUnit(&USA.Unit.O17, 5, 20, 100);
		}
	}
	if (GetUnits(&USA.Unit.F18) + GetUnits(&USA.Unit.F17) < 5) {
		if (UpgIsDone(&USA.Upg.S18Unlock)) {
			TryUnit(&USA.Unit.F18, 5, 20, 100);
		}
		else {
			TryUnit(&USA.Unit.F17, 5, 20, 100);
		}
	}
	if (GetUnits(&USA.Unit.B18) + GetUnits(&USA.Unit.B17) < 5) {
		if (UpgIsDone(&USA.Upg.S18Unlock)) {
			TryUnit(&USA.Unit.B18, 5, 20, 100);
		}
		else {
			TryUnit(&USA.Unit.B17, 5, 20, 100);
		}
	}

	if(GetMoney(GOLD)>5000&&GetMoney(COAL)<100){
		SetResource(AiNat,GOLD,GetMoney(GOLD)-1000);
		SetResource(AiNat,COAL,GetMoney(COAL)+1000);
		SetResource(AiNat,IRON,GetMoney(IRON)+1000);
	}

	if(GetMoney(GetExtraction(GOLD)>39)){
		int MaxS18=GetExtraction(GOLD)*10;
		if (UpgIsDone(&USA.Upg.S18Build1)) {
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
		}
		if (UpgIsDone(&USA.Upg.S18Unlock)) {
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
		}
		if (UpgIsDone(&USA.Upg.S18Build2)) {
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
		}
		if (UpgIsDone(&USA.Upg.S18Build3)) {
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
			TryUnit(&USA.Unit.S18, MaxS18, 10, 100);
		}
		
	}

	//TryUnit(&USA.Unit.D17, 1000, 20, 100);
	//TryUnit(&USA.Unit.KO7, 5, 20, 100);

	//TryUnit(&USA.Unit.D18, 1000, 20, 100);
	//TryUnit(&USA.Unit.KO8, 5, 20, 100);
	//TryUnit(&USA.Unit.KF8, 5, 20, 100);
	
	//for(i=0;i<6;i++){
	//}
	if(UpgIsRun(&USA.Upg.CanBuild4)){
		TryUnit(&USA.Unit.Can, 1000, 90, 30);
	}

	// Peasat distribution
	int NU=GetUnits(&USA.Unit.Kri)+GetUnits(&USA.Unit.Pik)+GetUnits(&USA.Unit.S15)+GetUnits(&USA.Unit.S17);
	{ //500		
		// Krepost
		city->PKrepost=40;
		if(!(UpgIsRun(&USA.Upg.Mel_GETRES2)||GetMoney(FOOD)>12000)||NU<40) city->PKrepost=(NU>>4)-1;
		if(city->PKrepost>60) city->PKrepost=60;		
		// Field
		if(GetReadyUnits(&USA.Build.Mel)){
			city->MinFermers = NU/5;
			//if(UpgIsRun(&USA.Upg.VoiS7)) city->MinFermers = NU/10;
			if(!UpgIsRun(&USA.Upg.Mel_GETRES2)) city->MinFermers=NU/3+15;
			if(city->MinFermers>300) city->MinFermers = 300;
			//if(GetMoney(FOOD)>700000) city->MinFermers = 30;
		}
		// Forest
		if(GetUnits(&USA.Build.Skl)){
			city->MinWooders = NU/6;
			if(!UpgIsRun(&USA.Upg.Mel_GETRES2)) city->MinWooders=NU/5+5;
			if(city->MinWooders>200) city->MinWooders = 200;
			//if(GetMoney(WOOD)>350000) city->MinWooders = 30;
		}
	}
	if(city->MinFermers>250) TryUnit(&USA.Build.Mel, 3, 100, 95);
	if(city->MinWooders>70) TryUnit(&USA.Build.Skl, 2, 100, 60);

	// Buildings
	{
		TryUnit(&USA.Build.Kr7, 2, 100, 70);
		TryUnit(&USA.Build.Mel, 1, 100, 80);
		if(GetReadyUnits(&USA.Build.Mel)){
			TryUnit(&USA.Build.Skl, 1, 100, 80);
			TryUnit(&USA.Build.Do1, 2, 100, 60);			
		}
		if(UpgIsRun(&USA.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){
			TryUnit(&USA.Build.Do1, 4, 100, 95);
			TryUnit(&USA.Build.Kuz, 1, 100, 60);
		}

		TryUpgrade(&USA.Upg.Do2_ENABLE, 100, 100);
		TryUnit(&USA.Build.Do2, 6, 100, 60);
		
		if(UpgIsRun(&USA.Upg.Mel_GETRES2)/*||GetDifficulty()<3*/){
			TryUnit(&USA.Build.Kuz, 2, 100, 60);
			TryUnit(&USA.Build.Mel, 2, 100, 80);
			TryUnit(&USA.Build.Fer, 2, 100, 80);
			if(GetUnits(&USA.Build.Do2)) TryUnit(&USA.Unit.Tap, 5, 70, 80);
		}
		TryUnit(&USA.Build.Kr8, 3, 100, 100);
		TryUnit(&USA.Build.Cen, 2, 100, 80);
		if(GetReadyUnits(&USA.Build.Do2)){
			TryUnit(&USA.Build.Do1, 6, 100, 60);			
			TryUnit(&USA.Build.Kuz, 3, 100, 60);
		}
		
		TryUnit(&USA.Build.Hra, 2, 100, 70);
	}
	if (GetUnits(&USA.Build.Kr8)>=2) {
		TryUnit(&USA.Build.Do1, 8, 100, 60);
		TryUnit(&USA.Build.Do2, 7, 100, 60);
		TryUnit(&USA.Build.Kuz, 4, 100, 60);
		TryUnit(&USA.Build.Mel, 5, 100, 80);
	}
	// Blg
	int NBlg=GetUnits(&USA.Unit.S15)/90;
	{
		if(GetReadyUnits(&USA.Build.Do1)>3){
			TryUnit(&USA.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&USA.Build.Kr8)){
			TryUnit(&USA.Build.Blg, NBlg, 100, 70);
		}
		if(GetReadyUnits(&USA.Build.Cen)){
			TryUnit(&USA.Build.Blg2, NBlg, 100, 70);
		}
	}


	//TryUnit(&USA.Build.Ver, 2, 100, 70);

	// Upgrades

	// Fild
	TryUpgrade(&USA.Upg.CEN52, 95, 100);
	TryUpgrade(&USA.Upg.CEN57, 100, 100);
	if(GetUnits(&USA.Build.Do1)>2) TryUpgrade(&USA.Upg.CEN55, 60, 100);

	// Food
	TryUpgrade(&USA.Upg.Mel_GETRES, 80, 100);
	TryUpgrade(&USA.Upg.Mel_GETRES2, 90, 100);
	if(GetUnits(&USA.Build.Do2)){
		TryUpgrade(&USA.Upg.CEN18, 90, 100);
		TryUpgrade(&USA.Upg.CEN19, 90, 100);
		TryUpgrade(&USA.Upg.CEN22, 90, 100);
		TryUpgrade(&USA.Upg.CEN23, 90, 100);
	}

	// Wood
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
		TryUpgrade(&USA.Upg.Wood1,100,100);
		if(GetUnits(&USA.Build.Do2)){
			TryUpgrade(&USA.Upg.Wood2,100,100);
			TryUpgrade(&USA.Upg.Wood3,100,100);
		}
	}

	// Mine
	{

		TryUnit(&USA.Build.Rud, 2, 10, 90);
		TryUnit(&USA.Build.Stn, 2, 10, 85);
		TryUnit(&USA.Build.Iro, 2, 10, 80);
		TryUnit(&USA.Build.Coa, 2, 10, 75);

		//if (GetReadyUnits(&USA.Build.Kuz) && GetUnits(&USA.Unit.Kri) > 20 && GetMoney(STONE) < 1000) TryUnit(&USA.Build.Stn, 5, 100, 100);
		
		/*if (GetUnits(&USA.Unit.Kri)>120 && UpgIsRun(&USA.Upg.Mel_GETRES2)) {
			TryUnit(&USA.Build.Rud, 2, 100, 70);
			TryUnit(&USA.Build.Stn, 2, 95, 70);
			TryUnit(&USA.Build.Iro, 2, 90, 70);
			TryUnit(&USA.Build.Coa, 2, 90, 70);
			/*
			if(GetUnits(&USA.Unit.Kri)>220||GetReadyUnits(&USA.Build.Kr8)){
				TryUnit(&USA.Build.Rud, 3, 100, 70);
				TryUnit(&USA.Build.Stn, 3, 950, 70);
				TryUnit(&USA.Build.Iro, 3, 90, 70);
				TryUnit(&USA.Build.Coa, 3, 90, 70);
			}
			
		}*/

		TryUpgrade(&USA.Upg.Gld0, 100, 90);
		TryUpgrade(&USA.Upg.Stn0, 100, 90);
		TryUpgrade(&USA.Upg.Iro0, 100, 90);
		TryUpgrade(&USA.Upg.Coa0, 100, 90);

		TryUpgrade(&USA.Upg.MineEnable1, 100, 100);

		if(GetDifficulty()>1 && UpgIsRun(&USA.Upg.MineEnable1)){

			TryUpgrade(&USA.Upg.Gld1, 100, 100);
			TryUpgrade(&USA.Upg.Gld2, 100, 100);
			TryUpgrade(&USA.Upg.Gld3, 100, 100);
			TryUpgrade(&USA.Upg.Iro1, 100, 100);
			TryUpgrade(&USA.Upg.Iro2, 100, 100);
			TryUpgrade(&USA.Upg.Iro3, 100, 100);
			TryUpgrade(&USA.Upg.Coa1, 100, 100);
			TryUpgrade(&USA.Upg.Coa2, 100, 100);
			TryUpgrade(&USA.Upg.Coa3, 100, 100);
			TryUpgrade(&USA.Upg.Stn1, 100, 100);
			TryUpgrade(&USA.Upg.Stn2, 100, 100);
			TryUpgrade(&USA.Upg.Stn3, 100, 100);
			
			if (GetUnits(&USA.Build.Kr8)>=2) {
				
				if (GetMoney(FOOD) > 100000) {
					TryUpgrade(&USA.Upg.Gld4, 100, 100);
					TryUpgrade(&USA.Upg.Gld5, 100, 100);
					if (UpgIsDone(&USA.Upg.Gld5)) {
						TryUpgrade(&USA.Upg.Stn4, 100, 100);
						TryUpgrade(&USA.Upg.Stn5, 100, 100);
						if (UpgIsDone(&USA.Upg.Stn5)) {
							TryUpgrade(&USA.Upg.Coa4, 100, 100);
							TryUpgrade(&USA.Upg.Coa5, 100, 100);

							TryUpgrade(&USA.Upg.Iro4, 100, 100);
							TryUpgrade(&USA.Upg.Iro5, 100, 100);
						}
					}
				}
			}

			/*TryUpgradeEx(&USA.Upg.Gld2, 95, 100, 9000, 4000);
			TryUpgradeEx(&USA.Upg.Gld3, 95, 100, 9000, 4000);
			
			TryUpgradeEx(&USA.Upg.Stn1, 90, 100, 6000, 1000);
			TryUpgradeEx(&USA.Upg.Stn2, 90, 100, 6000, 1000);
			//if(UpgIsRun(&USA.Upg.EnDo1)){
				TTryUpgradeEx(&USA.Upg.Gld4, 95, 100, 9000, 4000);
				TryUpgradeEx(&USA.Upg.Gld5, 95, 100, 9000, 4000); 
				TryUpgradeEx(&USA.Upg.Stn3, 95, 100, 9000, 4000);
				TryUpgradeEx(&USA.Upg.Stn4, 90, 100, 6000, 1000);
				TryUpgradeEx(&USA.Upg.Stn5, 90, 100, 6000, 1000);
			//}*/
			/*TryUpgradeEx(&USA.Upg.Iro0, 80, 100, 9000, 4000);
			TryUpgradeEx(&USA.Upg.Iro1, 70, 100, 9000, 2000);
			TryUpgradeEx(&USA.Upg.Iro2, 60, 100, 9000, 1500);
			TryUpgradeEx(&USA.Upg.Iro3, 60, 100, 9000, 1000);
			TryUpgradeEx(&USA.Upg.Coa0, 80, 100, 9000, 4000);
			TryUpgradeEx(&USA.Upg.Coa1, 70, 100, 9000, 4000);
			TryUpgradeEx(&USA.Upg.Coa2, 60, 100, 9000, 4000);
			TryUpgradeEx(&USA.Upg.Coa3, 60, 100, 9000, 4000);
			*/
		}
	}

	// Stages
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
		TryUpgrade(&USA.Upg.Kr7_Stage0, 80, 100);
	}
	if(GetUnits(&USA.Build.Do2)){
		TryUpgrade(&USA.Upg.Kr8_Stage0, 90, 100);
	}
	if(GetUnits(&USA.Build.Do2)>1){
		TryUpgrade(&USA.Upg.BldBuild1, 90, 100);
		TryUpgrade(&USA.Upg.Kr8_Stage1, 90, 100);
		TryUpgrade(&USA.Upg.Kr8_Stage2, 90, 100);
		TryUpgrade(&USA.Upg.Kr8_Stage3, 90, 100);
	}
	
	//
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){		
		TryUpgrade(&USA.Upg.Kre_RAZBROS, 80, 100);
		TryUpgrade(&USA.Upg.KreBuild, 80, 100);
	}
	
	TryUpgrade(&USA.Upg.S18Unlock, 100, 100);

	if(GetUnits(&USA.Build.Kr8)){
		TryUpgrade(&USA.Upg.MuskSpeed, 20, 100);
	}

	if (GetUnits(&USA.Build.Blg2)>1) {
		TryUpgrade(&USA.Upg.LogDef, 20, 100);
	}

	TryUpgrade(&USA.Upg.S18RifFire, 80, 100);
	TryUpgrade(&USA.Upg.S18FusFire, 80, 100);
	TryUpgrade(&USA.Upg.S18Firepower, 80, 100);

	TryUpgrade(&USA.Upg.FindGeo, 80, 100);

	if(GetDifficulty()>0) WarriorsUpg();

	// Warriors speed

	// Kri
	if(GetUnits(&USA.Build.Do2)>1){
		TryUpgrade(&USA.Upg.KriBuild1,80,70);
		TryUpgrade(&USA.Upg.KriBuild2,80,70);
		TryUpgrade(&USA.Upg.KriBuild3,80,70);
	}
	// Pik
	TryUpgrade(&USA.Upg.PikBuild1, 90, 100);
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){		
		{
			TryUpgrade(&USA.Upg.PikBuild2, 90, 100);
			TryUpgrade(&USA.Upg.PikBuild3, 90, 100);
			TryUpgrade(&USA.Upg.PikBuild4, 90, 100);			
		}
	}

	TryUpgrade(&USA.Upg.S15Build1, 90, 100);
	TryUpgrade(&USA.Upg.S15Build2, 90, 100);
	TryUpgrade(&USA.Upg.S15Build3, 90, 100);

	TryUpgrade(&USA.Upg.S17Build1, 90, 100);

	TryUpgrade(&USA.Upg.S18Build1, 80, 100);
	TryUpgrade(&USA.Upg.S18Build2, 80, 100);
	TryUpgrade(&USA.Upg.S18Build3, 80, 100);

}

void WarriorsUpg(){

	// Cen
	{
		TryUpgrade(&USA.Upg.ArmShield1,90,100);
		TryUpgrade(&USA.Upg.ArmShield2,60,100);
		TryUpgrade(&USA.Upg.ArmShield3,60,100);
		
		TryUpgrade(&USA.Upg.StrAttPause1,90,100);

		TryUpgrade(&USA.Upg.StrDamage1,80,100);
		TryUpgrade(&USA.Upg.StrDamage2,80,100);

		if(GetUnits(&USA.Build.Kr8)>1){
			TryUpgrade(&USA.Upg.BldShield1,80,100);
			TryUpgrade(&USA.Upg.BldShield2,80,100);
		}
	}

	// Pik
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){		
		if (GetUnits(&USA.Unit.Pik) > 40) {
			TryUpgrade(&USA.Upg.PikAttack, 50, 100);
			TryUpgrade(&USA.Upg.PikAttack3, 50, 100);
			TryUpgrade(&USA.Upg.PikAttack4, 50, 100);
			TryUpgrade(&USA.Upg.PikAttack5, 50, 100);
			TryUpgrade(&USA.Upg.PikProtect, 50, 100);
			TryUpgrade(&USA.Upg.PikProtect3, 50, 100);
			TryUpgrade(&USA.Upg.PikProtect4, 50, 100);
			TryUpgrade(&USA.Upg.PikProtect5, 50, 100);
			if (GetMoney(GOLD) > 10000){
				TryUpgrade(&USA.Upg.PikAttack6, 50, 100);
				TryUpgrade(&USA.Upg.PikAttack7, 50, 100);	
				TryUpgrade(&USA.Upg.PikProtect6, 50, 100);
				TryUpgrade(&USA.Upg.PikProtect7, 50, 100);
			}
		}
	}

	// S15
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
		if (GetUnits(&USA.Unit.S15) > 40) {
			TryUpgrade(&USA.Upg.S15Attack, 20, 100);
			TryUpgrade(&USA.Upg.S15Attack3, 20, 100);
			TryUpgrade(&USA.Upg.S15Attack4, 20, 100);
			TryUpgrade(&USA.Upg.S15Attack5, 20, 100);
			TryUpgrade(&USA.Upg.S15Attack6, 20, 100);
			TryUpgrade(&USA.Upg.S15Attack7, 10, 100);
			TryUpgrade(&USA.Upg.S15Protect, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect3, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect4, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect5, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect6, 90, 100);
			TryUpgrade(&USA.Upg.S15Protect7, 90, 100);
			
		}
	}

	// Mus
	if(UpgIsRun(&USA.Upg.Mel_GETRES2)){
		if (GetUnits(&USA.Unit.S17) > 40) {
				TryUpgrade(&USA.Upg.MusAttack, 90, 100);
				TryUpgrade(&USA.Upg.MusAttack3, 90, 100);
				TryUpgrade(&USA.Upg.MusAttack4, 90, 100);
				TryUpgrade(&USA.Upg.MusAttack5, 30, 100);
				TryUpgrade(&USA.Upg.MusAttack6, 30, 100);
				TryUpgrade(&USA.Upg.MusProtect, 90, 100);
				TryUpgrade(&USA.Upg.MusProtect3, 90, 100);
				TryUpgrade(&USA.Upg.MusProtect4, 90, 100);
				TryUpgrade(&USA.Upg.MusProtect5, 90, 100);
				
				if (GetMoney(GOLD) > 10000) {
					
					
					TryUpgrade(&USA.Upg.MusAttack7, 10, 100);
					
					TryUpgrade(&USA.Upg.MusProtect6, 90, 100);
					TryUpgrade(&USA.Upg.MusProtect7, 50, 100);
				}
		}
	}

	// S18
	{	
		if (GetUnits(&USA.Unit.S18)>40) {
			TryUpgrade(&USA.Upg.S18Attack, 30, 100);
			TryUpgrade(&USA.Upg.S18Attack3, 30, 100);
			TryUpgrade(&USA.Upg.S18Attack4, 30, 100);
			TryUpgrade(&USA.Upg.S18Attack5, 30, 100);
			TryUpgrade(&USA.Upg.S18Protect, 90, 100);
			TryUpgrade(&USA.Upg.S18Protect3, 90, 100);
			TryUpgrade(&USA.Upg.S18Protect4, 90, 100);
			TryUpgrade(&USA.Upg.S18Protect5, 90, 100);
			if (GetMoney(GOLD) > 10000) {
				
				TryUpgrade(&USA.Upg.S18Attack6, 30, 100);
				TryUpgrade(&USA.Upg.S18Attack7, 30, 100);
				
				TryUpgrade(&USA.Upg.S18Protect6, 90, 100);
				TryUpgrade(&USA.Upg.S18Protect7, 90, 100);
			}
		}
	}

	// Officers
	{
		TryUpgrade(&USA.Upg.B17Protect, 50, 100);
		TryUpgrade(&USA.Upg.O17Damage, 50, 100);
		TryUpgrade(&USA.Upg.O17Protect, 50, 100);
		TryUpgrade(&USA.Upg.F17Protect, 50, 100);

		TryUpgrade(&USA.Upg.B18Protect, 50, 100);
		TryUpgrade(&USA.Upg.O18Damage, 50, 100);
		TryUpgrade(&USA.Upg.O18Protect, 50, 100);
		TryUpgrade(&USA.Upg.F18Protect, 50, 100);
	}

	// Rei
	{
		TryUpgrade(&USA.Upg.Horse17Build, 80, 100);
		TryUpgrade(&USA.Upg.Horse18Build, 90, 100);
		TryUpgrade(&USA.Upg.HorseAllBuild, 90, 100);

		if(GetUnits(&USA.Unit.Rei)>20){
			TryUpgrade(&USA.Upg.ReiAttack, 90, 100);
			TryUpgrade(&USA.Upg.ReiAttack3, 90, 100);
			TryUpgrade(&USA.Upg.ReiAttack4, 90, 100);
		}
		if(GetUnits(&USA.Unit.Rei)>40){
			if (GetMoney(GOLD) > 30000) {
				TryUpgrade(&USA.Upg.ReiAttack5, 90, 100);
				TryUpgrade(&USA.Upg.ReiAttack6, 90, 100);
				TryUpgrade(&USA.Upg.ReiAttack7, 90, 100);
			}
		}
		
		if(GetUnits(&USA.Unit.Rei)>20){
			TryUpgrade(&USA.Upg.ReiProtect, 90, 100);
			TryUpgrade(&USA.Upg.ReiProtect3, 90, 100);
			TryUpgrade(&USA.Upg.ReiProtect4, 90, 100);
		}
		if(GetUnits(&USA.Unit.Rei)>40){
			TryUpgrade(&USA.Upg.ReiProtect5, 90, 100);
			TryUpgrade(&USA.Upg.ReiProtect6, 90, 100);
			TryUpgrade(&USA.Upg.ReiProtect7, 90, 100);
		}
	}



	// Can
	{
		TryUpgrade(&USA.Upg.CanCost,95,60);
		TryUpgrade(&USA.Upg.CanCost3,95,60);
		TryUpgrade(&USA.Upg.CanCost4,95,60);
		TryUpgrade(&USA.Upg.CanCost5,95,100);
		TryUpgrade(&USA.Upg.CanCost6,95,100);
		TryUpgrade(&USA.Upg.CanCost7,95,100);
		TryUpgrade(&USA.Upg.CanBuild,95,60);
		TryUpgrade(&USA.Upg.CanBuild3,95,60);
		TryUpgrade(&USA.Upg.CanBuild4,95,60);
		TryUpgrade(&USA.Upg.CanBuild5,95,100);
		TryUpgrade(&USA.Upg.CanBuild6,95,100);
		TryUpgrade(&USA.Upg.CanBuild7,95,100);

		TryUpgrade(&USA.Upg.ARTACC1, 95, 60);
		TryUpgrade(&USA.Upg.ARTACC2, 95, 60);
		TryUpgrade(&USA.Upg.ARTRNG1, 95, 60);
		TryUpgrade(&USA.Upg.ARTRNG2, 95, 100);
		TryUpgrade(&USA.Upg.ARTROF1, 95, 100);
		TryUpgrade(&USA.Upg.ARTROF2, 95, 100);
	}

}


void MiniWaterScript() {

	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	if (GetUnits(&USA.Build.Skl)) TryUnit(&USA.Build.Ver, 1, 100, 90);
	if (GetUnits(&USA.Build.Cen)) TryUnit(&USA.Build.Ver, 3, 60, 60);

	TryUnit(&USA.Unit.Lodka, 5, 10, 100);
	TryUnit(&USA.Unit.Lodka, 5, 10, 100);
	TryUnit(&USA.Unit.Lodka, 5, 10, 100);
	TryUnit(&USA.Unit.Lodka, 5, 10, 100);
	TryUnit(&USA.Unit.Lodka, 5, 10, 100);

	TryUnit(&USA.Unit.Pinta, 1, 100, 100);
}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&USA.Build.Skl)) TryUnit(&USA.Build.Ver,1,100,90);
	if(GetUnits(&USA.Build.Cen)) TryUnit(&USA.Build.Ver,3,60,60);

	//int NU=GetUnits(&USA.Unit.Pik)+GetUnits(&USA.Unit.S15)+GetUnits(&USA.Unit.S17)+GetUnits(&USA.Unit.Rei);

	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&USA.Unit.Parom, NPar, 100, 100);

	if(TryUnit(&USA.Unit.Lodka, 10, 100, 100)){
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
		TryUnit(&USA.Unit.Lodka, 10, 10, 100);
	}
	
	TryUnit(&USA.Unit.Pinta, 5, 100, 100);
	TryUnit(&USA.Unit.Pinta, 5, 50, 100);
	TryUnit(&USA.Unit.Pinta, 5, 50, 100);
	TryUnit(&USA.Unit.Pinta, 5, 50, 100);
	TryUnit(&USA.Unit.Pinta, 5, 50, 100);

	TryUnit(&USA.Unit.Santa, 2, 100, 100);
	TryUnit(&USA.Unit.Santa, 2, 50, 100);

	TryUnit(&USA.Unit.Fregat, 2, 100, 100);
	TryUnit(&USA.Unit.Fregat, 2, 50, 100);

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