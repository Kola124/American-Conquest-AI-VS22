#define CONQUEST
#include "..\Import.h"
#include "..\HurNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Hur.Unit.Kri.Index;
	city->Init(AiNat);

	city->FirersType=Hur.Unit.Kri.Index;
	city->NIndexBrb=Hur.Unit.Sha.Index;
	city->NIndexFlg=Hur.Unit.Sha.Index;
	city->NIndexOff=Hur.Unit.Vog.Index;
}

void Script();
void WarriorsUpg();
void WaterScript();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;
	
	if(GetDifficulty()>1) city->HuntNIndex=Hur.Unit.Kri.Index;

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
	Script();
	
	city->DefenceLess=1;
	city->Process();
	city->ParomNIndex=Hur.Unit.Par.Index;
	
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
	city->AddBranch(Hur.Unit.Tam.Index,brBack,10,40);
	city->AddBranch(Hur.Unit.Lut.Index,brBack,30,360);
	city->AddBranch(Hur.Unit.S15.Index,brBack,60,80);
	city->AddBranch(Hur.Unit.Sha.Index,brBack,100,120);
	city->AddBranch(Hur.Unit.Vog.Index,brBack,60,120);
	city->AddBranch(Hur.Unit.Vsd.Index,brBack,40,100);

	Branch* Tom=city->AddBranch(Hur.Unit.Tam.Index,0,0,0);
	Branch* Lut=city->AddBranch(Hur.Unit.Lut.Index,0,0,0);
	Branch* S15=city->AddBranch(Hur.Unit.S15.Index,0,0,0);
	Branch* Sha=city->AddBranch(Hur.Unit.Sha.Index,0,0,0);
	Branch* Vog=city->AddBranch(Hur.Unit.Vog.Index,0,0,0);
	Branch* Vsd=city->AddBranch(Hur.Unit.Vsd.Index,0,0,0);

	Tom->Prio[brForward] = 3;	Tom->Part[brForward] = 1;	Tom->Type[brForward] = btStorm;	
	Tom->Prio[brCenter] = 0;	Tom->Part[brCenter] = 1;	Tom->Type[brCenter] = btTomahawk;	
	Tom->Prio[brBack] = 2;		Tom->Part[brBack] = 0;
	Tom->Formation=1;
	if(GetUnits(&Hur.Unit.S15)) Tom->Max=260;

	Lut->Prio[brForward] = 3;	Lut->Part[brForward] = 1;	Lut->Type[brForward] = btTomahawk;
	Lut->Prio[brCenter] = 0;	Lut->Part[brCenter] = 0;
	Lut->Prio[brBack] = 2;		Lut->Part[brBack] = 0;
	Lut->Formation=1;

	S15->Prio[brForward] = 3;	S15->Part[brForward] = 1;	S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 0;	S15->Part[brCenter] = 0;
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 0;
	S15->Formation=1;

	Sha->Prio[brForward] = 0;	Sha->Part[brForward] = 0;	//Sha->Type[brForward] = btStorm;	
	Sha->Prio[brCenter] = 1;	Sha->Part[brCenter] = 1;	Sha->Type[brCenter] = btStorm;	
	Sha->Prio[brBack] = 0;		Sha->Part[brBack] = 0;
	Sha->BaseGuard=1;

	Vog->Prio[brForward] = 0;	Vog->Part[brForward] = 0;	//Vog->Type[brForward] = btStorm;	
	Vog->Prio[brCenter] = 1;	Vog->Part[brCenter] = 1;	Vog->Type[brCenter] = btStorm;	
	Vog->Prio[brBack] = 0;		Vog->Part[brBack] = 0;
	Vog->BaseGuard=1;

	Vsd->Prio[brForward] = 0;	Vsd->Part[brForward] = 0;	//Vsd->Type[brForward] = btStorm;	
	Vsd->Prio[brCenter] = 1;	Vsd->Part[brCenter] = 1;	Vsd->Type[brCenter] = btKillers;	
	Vsd->Prio[brBack] = 0;		Vsd->Part[brBack] = 0;
	Vsd->Domovoi=0;

	// Units in buildings
	city->NStrelok = 25;
	city->NUnits = 2;
	if(GetUnits(&Hur.Unit.Tam)>60&&GetUnits(&Hur.Unit.Tam)<120) city->NUnits = 20;

	// Units
	if(GetMoney(FOOD)>300){
		TryUnit(&Hur.Unit.Kri, 10000, 5, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
		TryUnit(&Hur.Unit.Kri, 10000, 3, 100);
	}

	TryUnit(&Hur.Unit.Tam, 10000, 20, 100);
	TryUnit(&Hur.Unit.Tam, 10000, 10, 60);
	TryUnit(&Hur.Unit.Tam, 10000, 10, 30);

	TryUnit(&Hur.Unit.Lut, 10000, 20, 100);
	TryUnit(&Hur.Unit.Lut, 10000, 10, 100);
	TryUnit(&Hur.Unit.Lut, 10000, 10, 50);

	TryUnit(&Hur.Unit.S15, 1000, 20, 90);
	TryUnit(&Hur.Unit.S15, 1000, 20, 90);

	if(GetUnits(&Hur.Unit.Sha)<20)TryUnit(&Hur.Unit.Sha, 10000, 20, 100);
	if(GetUnits(&Hur.Unit.Vog)<10)TryUnit(&Hur.Unit.Vog, 10000, 20, 70);
	TryUnit(&Hur.Unit.Vsd, 10000, 20, 100);

	

	// Convertors
	city->PKrepost = 0;
	if((UpgIsRun(&Hur.Upg.Mel_GETRES)||GetMoney(FOOD)>2000)&&GetReadyUnits(&Hur.Build.Skl)){
		city->PKrepost = 5;
		if(GetUnits(&Hur.Unit.Lut)){
			city->PKrepost = 20;
		}
	}

	// Buildings
	TryUnit(&Hur.Build.Mel, 1, 100, 70);
	TryUnit(&Hur.Build.Skl, 1, 100, 70);
	TryUnit(&Hur.Build.Do1, 2, 100, 70);
	if(GetUnits(&Hur.Build.Do1)>1) TryUnit(&Hur.Build.Kaz, 1, 100, 70);

	if(UpgIsRun(&Hur.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){		
		TryUnit(&Hur.Build.Pst, 2, 100, 70);
		TryUnit(&Hur.Build.Kaz, 2, 100, 70);
		TryUnit(&Hur.Build.Mel, 2, 100, 70);
		TryUnit(&Hur.Build.Cen, 1, 100, 70);
		TryUnit(&Hur.Build.Do1, 5, 100, 70);
		if(GetUnits(&Hur.Build.Kaz)>2 && GetUnits(&Hur.Build.Do2)>4) TryUnit(&Hur.Build.Do1, 1000, 100, 70);
		TryUnit(&Hur.Build.Do2, 5, 100, 70);
		TryUnit(&Hur.Build.Hra, 1, 100, 70);
		TryUnit(&Hur.Build.Kre, 2, 100, 80);				
	}
	
	//TryUnit(&Hur.Build.Ver, 2, 100, 70);

	if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
		TryUnit(&Hur.Build.Pst, 3, 100, 70);
		TryUnit(&Hur.Build.Kaz, 3, 100, 70);
		TryUnit(&Hur.Build.Kre, 3, 100, 50);
		TryUnit(&Hur.Build.Cen, 3, 100, 50);
	}

	// Upgrades
	// Food
	TryUpgrade(&Hur.Upg.CEN01, 80, 100);
	TryUpgrade(&Hur.Upg.CEN02, 80, 100);
	TryUpgrade(&Hur.Upg.CEN03, 80, 100);
	TryUpgrade(&Hur.Upg.CEN10, 80, 100);

	if(GetUnits(&Hur.Unit.Kri)>50) TryUpgrade(&Hur.Upg.Mel_GETRES, 80, 100);
	if(UpgIsRun(&Hur.Upg.KriDef7))  TryUpgrade(&Hur.Upg.Mel_GETRES2, 95, 100);

	TryUpgrade(&Hur.Upg.CEN52, 80, 100);
	TryUpgrade(&Hur.Upg.CEN12, 80, 100);

	// Wood
	if(GetDifficulty()>0){
		TryUpgrade(&Hur.Upg.Wood1, 80, 100);
		TryUpgrade(&Hur.Upg.Wood2, 80, 100);
	}

	//
	TryUpgrade(&Hur.Upg.Do2_ENABLE, 100, 100);

	// Market
	if(GetReadyUnits(&Hur.Build.Pst)){

		// Parom prepare
		if(city->LandType&&GetMoney(IRON)<51){
			if(GetMoney(WOOD)>500){
				AI_Torg(WOOD,IRON,500);
			}else
			if(GetMoney(FOOD)>3000){
				AI_Torg(FOOD,IRON,1000);
			}
		}

		// голод
		if(GetMoney(FOOD)<2){
			if(GetMoney(GOLD)>500){
				AI_Torg(GOLD,FOOD,5000);
			}else
			if(GetMoney(WOOD)>1000){
				AI_Torg(WOOD,FOOD,10000);
			}
		}

		int FR=GetResource(AiNat,FOOD);
		int GR=GetResource(AiNat,GOLD);
		int IR=GetResource(AiNat,IRON);
		int CR=GetResource(AiNat,COAL);
		int WR=GetResource(AiNat,WOOD);

		/*
		if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
			if(!UpgIsRun(&Hur.Upg.Mel_GETRES2)&&GetResource(AiNat,IRON)<200&&GetResource(AiNat,WOOD)>2000){
				AI_Torg(WOOD,IRON,2000);
			}
		}	

		if(!(UpgIsRun(&Hur.Upg.Mel_GETRES2)&&UpgIsRun(&Hur.Upg.Do2_ENABLE))){
			if(FR>450000&&GR<5000){
				AI_Torg(WOOD,FOOD,5000);
				AI_Torg(FOOD,GOLD,FR-20000);
			}
		}else{
			int nir=12500;
			int ngr=35500;
			if(UpgIsRun(&Hur.Upg.LutLife1)){
				nir=2000;
				ngr=2000;
				if(GR>50000){
					AI_Torg(FOOD,GOLD,5000);
					AI_Torg(WOOD,GOLD,5000);
					AI_Torg(GOLD,WOOD,GR-5000);
				}
			}
			if(FR>600000&&IR<nir){
				AI_Torg(WOOD,FOOD,5000);
				AI_Torg(FOOD,IRON,FR-5000);
			}			
			if(FR>1000000&&GR<ngr){
				AI_Torg(WOOD,FOOD,5000);
				AI_Torg(GOLD,FOOD,500);
				AI_Torg(GOLD,FOOD,500);
				AI_Torg(FOOD,GOLD,FR-5000);
			}
			if(FR>1000000&&GR>ngr){
				AI_Torg(GOLD,FOOD,3000);
				AI_Torg(WOOD,FOOD,3000);
				AI_Torg(FOOD,WOOD,FR-5000);
			}
		}
		*/
		
		// патроны
		int FoodTrade=FR;
		if(FoodTrade>10000) FoodTrade=8000;
		if(GetResource(AiNat,STONE)<200&&FR>10000){
			AI_Torg(STONE,FOOD,100);
			AI_Torg(FOOD,STONE,FoodTrade);
		}else
		if(GetResource(AiNat,IRON)<200&&FR>10000){
			AI_Torg(IRON,FOOD,100);
			AI_Torg(FOOD,IRON,FoodTrade);
		}else
		if(GetResource(AiNat,COAL)<200&&FR>10000){
			AI_Torg(COAL,FOOD,100);
			AI_Torg(FOOD,COAL,FoodTrade);
		}
		// Prepare
		if(GetUnits(&Hur.Build.Do1)>4) PrepareUpgrade(AiNat,FOOD,GOLD,&Hur.Upg.Do2_ENABLE);
	}

	// Peasat distribution
	int NU=GetUnits(&Hur.Unit.Tam)+GetUnits(&Hur.Unit.Kri)+GetUnits(&Hur.Unit.Lut);//+GetUnits(&May.Unit.Voi);	
	if(NU){ //500
		// Hunters
		if(NU>30) city->MinHuters=5+NU/9;
		// Fermers
		if(GetReadyUnits(&Hur.Build.Mel)){
			city->MinFermers = NU/8;
			if(GetMoney(FOOD)<700) city->MinFermers = NU/6;
			if(!UpgIsRun(&Hur.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinFermers = NU/4+30;

			int NHunt=GetNUnits(&city->HuntGroup);
			if(NHunt>20&&GetMoney(FOOD)>60000||GetMoney(FOOD)>120000){
				city->MinFermers -= NHunt;
				if(city->MinFermers<20) city->MinFermers=20;
			}

			if(city->MinFermers>200) city->MinFermers = 200;
			if(UpgIsRun(&Hur.Upg.Mel_GETRES2)) city->MinFermers = 50;
		}		
		int NMeln=2+city->MinFermers/120;
		if(NMeln>3) NMeln=3;
		if(UpgIsRun(&Hur.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Hur.Build.Mel, NMeln, 100, 70);
		// Wooders
		if(GetUnits(&Hur.Build.Skl)){
			city->MinWooders = NU/5;
			if(!UpgIsRun(&Hur.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinWooders = NU/4+5;
			if(city->MinWooders>300) city->MinWooders = 300;
			if(GetUnits(&Hur.Build.Do1)>20) city->MinWooders = 100;
		}
		int NSklad=1+(city->MinWooders+city->MinHuters)/50;
		int MaxSkl=6;
		if(!UpgIsRun(&Hur.Upg.Do2_ENABLE)) MaxSkl=4;

		if(NSklad>MaxSkl) NSklad=MaxSkl;
		if(UpgIsRun(&Hur.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Hur.Build.Skl, NSklad, 100, 70);
		// Firers
		city->NFirers=0;
		if(NU>50) city->NFirers=NU/5;
		if(NU>200) city->NFirers=NU/10;
		if(city->NFirers>90) city->NFirers=90;
		
	}

	if(GetDifficulty()>0) WarriorsUpg();

	// Enable warriors
	TryUpgrade(&Hur.Upg.EnTam, 90, 100);
	if(UpgIsRun(&Hur.Upg.Mel_GETRES)) TryUpgrade(&Hur.Upg.EnLut, 90, 100);
	TryUpgrade(&Hur.Upg.EnStr, 90, 100);
	if(GetUnits(&Hur.Unit.Tam)+GetUnits(&Hur.Unit.Lut)+GetUnits(&Hur.Unit.S15)>120) TryUpgrade(&Hur.Upg.EnVog, 90, 100);
	if(UpgIsRun(&Hur.Upg.Do2_ENABLE)) TryUpgrade(&Hur.Upg.EnVsd, 90, 100);

}

void WarriorsUpg(){

	// Horces	
	if(GetUnits(&Hur.Unit.Vsd)>15){		
		// attack
		TryUpgrade(&Hur.Upg.VsdAtt, 90, 100);
		TryUpgrade(&Hur.Upg.VsdAtt3, 90, 100);
		TryUpgrade(&Hur.Upg.VsdAtt4, 85, 100);
		TryUpgrade(&Hur.Upg.VsdAtt5, 80, 100);
		TryUpgrade(&Hur.Upg.VsdAtt6, 70, 100);
		TryUpgrade(&Hur.Upg.VsdAtt7, 60, 100);
		// deffence
		TryUpgrade(&Hur.Upg.VsdDef, 90, 100);
		TryUpgrade(&Hur.Upg.VsdDef3, 90, 100);
		TryUpgrade(&Hur.Upg.VsdDef4, 85, 100);
		TryUpgrade(&Hur.Upg.VsdDef5, 80, 100);
		TryUpgrade(&Hur.Upg.VsdDef6, 70, 100);
		TryUpgrade(&Hur.Upg.VsdDef7, 60, 100);
	}

	// Peasant
	if(UpgIsRun(&Hur.Upg.Mel_GETRES)){
		// produce speed
		TryUpgrade(&Hur.Upg.KriBuildSpeed1, 95, 100);
		TryUpgrade(&Hur.Upg.KriBuildSpeed2, 95, 100);
		// life
		TryUpgrade(&Hur.Upg.KriIR, 90, 100);
		TryUpgrade(&Hur.Upg.KriIR3, 90, 100);
		TryUpgrade(&Hur.Upg.KriIR4, 90, 100);
		if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
			TryUpgrade(&Hur.Upg.KriIR5, 90, 100);
			if(UpgIsRun(&Hur.Upg.Mel_GETRES2)){
				TryUpgrade(&Hur.Upg.KriIR6, 90, 100);				
			}
			if(UpgIsRun(&Hur.Upg.LutLife1)) TryUpgrade(&Hur.Upg.KriIR7, 90, 100);
		}
		// attack
		if(UpgIsRun(&Hur.Upg.TamStrike1)){
			TryUpgrade(&Hur.Upg.KriAtt, 90, 100);		
			TryUpgrade(&Hur.Upg.KriAtt3, 90, 100);
			TryUpgrade(&Hur.Upg.KriAtt4, 90, 100);
			if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
				TryUpgrade(&Hur.Upg.KriAtt5, 90, 100);
				TryUpgrade(&Hur.Upg.KriAtt6, 90, 50);
				TryUpgrade(&Hur.Upg.KriAtt7, 50, 50);
			}
		}
		// defence
		TryUpgrade(&Hur.Upg.KriDef, 90, 100);
		TryUpgrade(&Hur.Upg.KriDef3, 90, 100);
		TryUpgrade(&Hur.Upg.KriDef4, 90, 100);
		if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
			TryUpgrade(&Hur.Upg.KriDef5, 90, 100);
			TryUpgrade(&Hur.Upg.KriDef6, 90, 100);
			TryUpgrade(&Hur.Upg.KriDef7, 95, 100);
		}
	}

	// Tam
	{		
		TryUpgrade(&Hur.Upg.TamStrike1, 95, 100);
		// attack
		if(GetReadyUnits(&Hur.Unit.Tam)>30){
			TryUpgrade(&Hur.Upg.TamAtt, 90, 100);
			TryUpgrade(&Hur.Upg.TamAtt3, 90, 100);
			TryUpgrade(&Hur.Upg.TamAtt4, 90, 100);
		}
		if(GetReadyUnits(&Hur.Unit.Tam)>65){
			TryUpgrade(&Hur.Upg.TamAtt5, 90, 100);
			TryUpgrade(&Hur.Upg.TamAtt6, 90, 100);
			if(UpgIsRun(&Hur.Upg.TamStrike1)) TryUpgrade(&Hur.Upg.TamAtt7, 20, 100);
		}
		// defence
		if(GetReadyUnits(&Hur.Unit.Tam)>30){
			TryUpgrade(&Hur.Upg.TamDef, 90, 100);
			TryUpgrade(&Hur.Upg.TamDef3, 90, 100);
			TryUpgrade(&Hur.Upg.TamDef4, 90, 100);
		}
		if(GetReadyUnits(&Hur.Unit.Tam)>65){
			TryUpgrade(&Hur.Upg.TamDef5, 90, 100);
			if(UpgIsRun(&Hur.Upg.TamStrike1)){
				TryUpgrade(&Hur.Upg.TamDef6, 90, 100);
				TryUpgrade(&Hur.Upg.TamDef7, 90, 100);
			}
		}
	}

	// Lut
	{		
		// precision
		if(GetReadyUnits(&Hur.Unit.Lut)>35){
			TryUpgrade(&Hur.Upg.LutPerc1, 90, 100);
			if(UpgIsRun(&Hur.Upg.Do2_ENABLE)&&UpgIsRun(&Hur.Upg.KriDef7)) TryUpgrade(&Hur.Upg.LutPerc2, 90, 100);
		}
		// attack
		//if(UpgIsRun())
		if(GetReadyUnits(&Hur.Unit.Lut)>35){
			TryUpgrade(&Hur.Upg.LutAtt, 90, 100);
			TryUpgrade(&Hur.Upg.LutAtt3, 90, 100);
		}
		if(GetReadyUnits(&Hur.Unit.Lut)>65){
			TryUpgrade(&Hur.Upg.LutAtt4, 90, 100);
			TryUpgrade(&Hur.Upg.LutAtt5, 20, 100);
		}
		// defence
		if(GetReadyUnits(&Hur.Unit.Lut)>35){
			TryUpgrade(&Hur.Upg.LutDef, 90, 100);
			TryUpgrade(&Hur.Upg.LutDef3, 90, 100);
			TryUpgrade(&Hur.Upg.LutDef4, 90, 100);
		}
		if(GetReadyUnits(&Hur.Unit.Lut)>65){
			TryUpgrade(&Hur.Upg.LutDef5, 90, 100);
			TryUpgrade(&Hur.Upg.LutDef6, 90, 100);
			TryUpgrade(&Hur.Upg.LutDef7, 20, 100);
		}
		TryUpgrade(&Hur.Upg.LutLife1, 95, 100);
		
	}
	
	// Str
	{		
		// attack
		if(GetReadyUnits(&Hur.Unit.S15)>35){
			TryUpgrade(&Hur.Upg.StrAtt, 10, 100);
			TryUpgrade(&Hur.Upg.StrAtt3, 10, 100);
		}
		if(GetReadyUnits(&Hur.Unit.S15)>65){
			TryUpgrade(&Hur.Upg.StrAtt4, 10, 100);
			TryUpgrade(&Hur.Upg.StrAtt5, 10, 100);
			TryUpgrade(&Hur.Upg.StrAtt6, 10, 100);
			TryUpgrade(&Hur.Upg.StrAtt7, 10, 100);
		}
		// defence
		if(GetReadyUnits(&Hur.Unit.S15)>35){
			TryUpgrade(&Hur.Upg.StrDef, 10, 100);
			TryUpgrade(&Hur.Upg.StrDef3, 10, 100);
			TryUpgrade(&Hur.Upg.StrDef4, 10, 100);
		}
		if(GetReadyUnits(&Hur.Unit.S15)>65){
			TryUpgrade(&Hur.Upg.StrDef5, 10, 100);
			TryUpgrade(&Hur.Upg.StrDef6, 10, 100);
			TryUpgrade(&Hur.Upg.StrDef7, 10, 100);
		}
	}

	// Vog
	{		
	}

	// Sha
	{
		TryUpgrade(&Hur.Upg.ShaBuild1,35,100);
		if(UpgIsRun(&Hur.Upg.Do2_ENABLE)){
			TryUpgrade(&Hur.Upg.ShaBuild1,100,100);
			if(UpgIsRun(&Hur.Upg.Mel_GETRES2)){
				TryUpgrade(&Hur.Upg.ShaMedic1,100,20);
				TryUpgrade(&Hur.Upg.ShaLife1,100,20);
			}
		}
	}
}

void WaterScript(){
	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Hur.Build.Skl)) TryUnit(&Hur.Build.Ver,1,100,90);
	if(GetUnits(&Hur.Build.Kre)>1) TryUnit(&Hur.Build.Ver,3,60,60);

	int NU=GetUnits(&Hur.Unit.Tam)+GetUnits(&Hur.Unit.Lut)+GetUnits(&Hur.Unit.S15)+city->NFirers;
	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&Hur.Unit.Par, NPar, 100, 100);
	
	TryUnit(&Hur.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&Hur.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
		TryUnit(&Hur.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Hur.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Hur.Upg.Ka3Build6)){
		TryUnit(&Hur.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Hur.Upg.ParSpeed1,100,100);
	TryUpgrade(&Hur.Upg.ParSpeed2,100,100);
	TryUpgrade(&Hur.Upg.ParSpeed3,100,100);
	TryUpgrade(&Hur.Upg.ParSpeed4,100,100);
	TryUpgrade(&Hur.Upg.ParSpeed5,100,100);
	TryUpgrade(&Hur.Upg.ParSpeed6,100,100);

	TryUpgrade(&Hur.Upg.Ka3Build1,100,100);
	TryUpgrade(&Hur.Upg.Ka3Build2,100,100);
	TryUpgrade(&Hur.Upg.Ka3Build3,100,100);
	TryUpgrade(&Hur.Upg.Ka3Build4,100,100);
	TryUpgrade(&Hur.Upg.Ka3Build5,100,100);
	TryUpgrade(&Hur.Upg.Ka3Build6,100,100);

	if(GetUnits(&Hur.Unit.Ka1)>3){
		TryUpgrade(&Hur.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Hur.Upg.Ka1Fishing2,100,100);
		TryUpgrade(&Hur.Upg.Ka1Fishing3,100,100);
		TryUpgrade(&Hur.Upg.Ka1Fishing4,100,100);
		TryUpgrade(&Hur.Upg.Ka1Fishing5,100,100);
		TryUpgrade(&Hur.Upg.Ka1Fishing6,100,100);
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
