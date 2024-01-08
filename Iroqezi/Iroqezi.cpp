#define CONQUEST

#include "..\Import.h"
#include "..\IroNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Iro.Unit.Kri.Index;	
	city->Init(AiNat);

	city->FirersType=Iro.Unit.Kri.Index;
	city->NIndexBrb=Iro.Unit.Sha.Index;
	city->NIndexFlg=Iro.Unit.Sha.Index;
	city->NIndexOff=Iro.Unit.Vog.Index;
}

void Script();
void WaterScript();
void WarriorsUpg();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	if(GetDifficulty()>1) city->HuntNIndex=Iro.Unit.Kri.Index;
	//city->CoolHuntNIndex=Iro.Unit.Tam.Index;
	
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
	city->ParomNIndex=Iro.Unit.Par.Index;
	
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
	city->AddBranch(Iro.Unit.Tam.Index,brBack,10,360);
	city->AddBranch(Iro.Unit.Lut.Index,brBack,30,598);
	city->AddBranch(Iro.Unit.Sha.Index,brBack,80,125);
	city->AddBranch(Iro.Unit.S15.Index,brBack,60,80);
	city->AddBranch(Iro.Unit.Vog.Index,brBack,60,120);
	city->AddBranch(Iro.Unit.Vsd.Index,brBack,50,100);

	Branch* Tom=city->AddBranch(Iro.Unit.Tam.Index,0,0,0);
	Branch* Lut=city->AddBranch(Iro.Unit.Lut.Index,0,0,0);
	Branch* Sha=city->AddBranch(Iro.Unit.Sha.Index,0,0,0);
	Branch* Vog=city->AddBranch(Iro.Unit.Vog.Index,0,0,0);
	Branch* S15=city->AddBranch(Iro.Unit.S15.Index,0,0,0);
	Branch* Vsd=city->AddBranch(Iro.Unit.Vsd.Index,0,0,0);

	Tom->Prio[brForward] = 3;	Tom->Part[brForward] = 1;	Tom->Type[brForward] = btStorm;	
	Tom->Prio[brCenter] = 0;	Tom->Part[brCenter] = 1;	Tom->Type[brCenter] = btTomahawk;	
	Tom->Prio[brBack] = 0;		Tom->Part[brBack] = 0;
	Tom->Formation=1;

	Lut->Prio[brForward] = 1;	Lut->Part[brForward] = 0;	Lut->Type[brForward] = btStorm;	
	Lut->Prio[brCenter] = 1;	Lut->Part[brCenter] = 1;	Lut->Type[brCenter] = btTomahawk;	
	Lut->Prio[brBack] = 0;		Lut->Part[brBack] = 0;
	Lut->Formation=1;

	S15->Prio[brForward] = 3;	S15->Part[brForward] = 1;	S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 0;	S15->Part[brCenter] = 0;
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 0;
	S15->Formation=1;

	Sha->Prio[brForward] = 2;	Sha->Part[brForward] = 1;	Sha->Type[brForward] = btStorm;
	Sha->Prio[brCenter] = 0;	Sha->Part[brCenter] = 0;
	Sha->Prio[brBack] = 0;		Sha->Part[brBack] = 0;
	Sha->BaseGuard=1;

	Vsd->Prio[brForward] = 0;	Vsd->Part[brForward] = 0;	//Vsd->Type[brForward] = btStorm;	
	Vsd->Prio[brCenter] = 1;	Vsd->Part[brCenter] = 1;	Vsd->Type[brCenter] = btKillers;	
	Vsd->Prio[brBack] = 0;		Vsd->Part[brBack] = 0;

	// Units in buildings
	city->NStrelok = 25;
	city->NUnits = 2;
	//if(GetUnits(&Iro.Unit.Tam)>60&&GetUnits(&Iro.Unit.Tam)<120) city->NUnits = 20;

	// Units
	int FreeUnitPlace = GetMaxUnits(AiNat) - GetCurrentUnits(AiNat);
	if(GetMoney(FOOD)>300&&FreeUnitPlace>100){
		TryUnit(&Iro.Unit.Kri, 100000, 5, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
		TryUnit(&Iro.Unit.Kri, 100000, 3, 100);
	}else{
		if(FreeUnitPlace>20) TryUnit(&Iro.Unit.Kri, 100000, 5, 100);
	}

	TryUnit(&Iro.Unit.Tam, 10000, 20, 100);
	TryUnit(&Iro.Unit.Tam, 10000, 20, 20);

	int NLut=GetUnits(&Iro.Build.Pst)*45;
	if(GetMoney(IRON)>2000&&GetMoney(FOOD)>10000) NLut=10000;
	TryUnit(&Iro.Unit.Lut, NLut, 20, 100);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 60);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 30);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 20);
	TryUnit(&Iro.Unit.Lut, NLut, 20, 100);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 60);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 30);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 20);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 60);
	TryUnit(&Iro.Unit.Lut, NLut, 10, 60);

	TryUnit(&Iro.Unit.S15, 1000, 20, 90);
	TryUnit(&Iro.Unit.S15, 1000, 20, 90);
	
	TryUnit(&Iro.Unit.Sha, 20, 20, 100);	
	TryUnit(&Iro.Unit.Vog, 10, 20, 100);


	if(UpgIsRun(&Iro.Upg.KriDef7)) city->KillFromFirePerc=50;

	// Convertors
	city->PKrepost = 0;
	if((UpgIsRun(&Iro.Upg.Mel_GETRES)||GetMoney(FOOD)>2000)&&(GetReadyUnits(&Iro.Build.Skl)||GetUnits(&Iro.Unit.Kri)>50)){
		city->PKrepost = 10;
		if(GetUnits(&Iro.Unit.Lut)){
			city->PKrepost = 20;
		}
	}

	// Buildings
	TryUnit(&Iro.Build.Mel, 1, 100, 70);
	TryUnit(&Iro.Build.Skl, 1, 100, 70);
	TryUnit(&Iro.Build.Do1, 2, 100, 70);
	if(GetUnits(&Iro.Build.Do1)>1) TryUnit(&Iro.Build.Kre, 1, 100, 70);

	if(UpgIsRun(&Iro.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){
		TryUnit(&Iro.Build.Kre, 2, 100, 80);
		TryUnit(&Iro.Build.Pst, 2, 100, 70);
		TryUnit(&Iro.Build.Stb, 2, 100, 40);				
		TryUnit(&Iro.Build.Pst, 3, 60, 70);
		TryUnit(&Iro.Build.Cen, 1, 100, 70);
		TryUnit(&Iro.Build.Do1, 5, 100, 70);
		if(GetUnits(&Iro.Build.Kre)>2 && GetUnits(&Iro.Build.Do2)>5) TryUnit(&Iro.Build.Do1, 1000, 100, 70);
		TryUnit(&Iro.Build.Do2, 6, 100, 80);
		TryUnit(&Iro.Build.Hra, 1, 100, 70);
	}

	//TryUnit(&Iro.Build.Ver, 2, 100, 70);

	if(UpgIsRun(&Iro.Upg.EnDo2)){
		TryUnit(&Iro.Build.Kre, 3, 100, 70);
		TryUnit(&Iro.Build.Pst, 3, 100, 70);
		TryUnit(&Iro.Build.Stb, 3, 100, 40);
		TryUnit(&Iro.Build.Cen, 2, 100, 70);

		//TryUnit(&Iro.Build.Ver, 3, 100, 70);
	}

	// Upgrades
	// Food
	TryUpgrade(&Iro.Upg.CEN01, 80, 100);
	TryUpgrade(&Iro.Upg.CEN02, 80, 100);
	TryUpgrade(&Iro.Upg.CEN03, 80, 100);
	TryUpgrade(&Iro.Upg.CEN10, 80, 100);
	TryUpgrade(&Iro.Upg.CEN12, 95, 100);

	if(GetUnits(&Iro.Unit.Kri)>50) TryUpgrade(&Iro.Upg.Mel_GETRES, 80, 100);
	if(UpgIsRun(&Iro.Upg.KriDef7)) TryUpgrade(&Iro.Upg.Mel_GETRES2, 95, 100);
	
	TryUpgrade(&Iro.Upg.CEN52, 20, 100);
	TryUpgrade(&Iro.Upg.CEN12, 80, 100);

	// Wood
	if(GetDifficulty()>0){
		TryUpgrade(&Iro.Upg.Wood1, 95, 100);
		TryUpgrade(&Iro.Upg.Wood2, 95, 100);
	}

	// Dom 2
	TryUpgrade(&Iro.Upg.EnDo2, 100, 100);
	if(UpgIsRun(&Iro.Upg.EnDo2)){
		TryUpgrade(&Iro.Upg.CEN52, 80, 100);
	}


	// Market
	if(GetReadyUnits(&Iro.Build.Pst)){
		if(UpgIsRun(&Iro.Upg.EnDo2)){
			if(!UpgIsRun(&Iro.Upg.Mel_GETRES2)&&GetResource(AiNat,IRON)<200&&GetResource(AiNat,WOOD)>2000){
				AI_Torg(WOOD,IRON,2000);
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

		// Parom prepare
		if(city->LandType&&GetMoney(IRON)<51){
			if(GetMoney(WOOD)>500){
				AI_Torg(WOOD,IRON,500);
			}else
			if(GetMoney(FOOD)>3000){
				AI_Torg(FOOD,IRON,1000);
			}
		}

		int FR=GetResource(AiNat,FOOD);
		int WR=GetResource(AiNat,WOOD);
		int IR=GetResource(AiNat,IRON);
		int GR=GetResource(AiNat,GOLD);

		if(!(UpgIsRun(&Iro.Upg.Mel_GETRES2)&&UpgIsRun(&Iro.Upg.EnDo2))){
			if(FR>450000&&GR<5000){
				AI_Torg(WOOD,FOOD,5000);
				AI_Torg(FOOD,GOLD,FR-20000);
			}
		}else{
			int nir=12500;
			int ngr=35500;
			if(UpgIsRun(&Iro.Upg.LutLife1)){
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
		
		// патроны
		int FoodTrade=FR;
		if(FoodTrade>10000) FoodTrade=8000;
		if(GetResource(AiNat,STONE)<200&&FR>10000){
			AI_Torg(STONE,FOOD,100);
			AI_Torg(FOOD,STONE,FoodTrade);
		}

		// Prepare
		if(GetUnits(&Iro.Build.Do1)>4) PrepareUpgrade(AiNat,FOOD,GOLD,&Iro.Upg.EnDo2);
	}

	// Peasat distribution
	int NU=GetUnits(&Iro.Unit.Tam)+GetUnits(&Iro.Unit.Kri)+GetUnits(&Iro.Unit.Lut);//+GetUnits(&May.Unit.Voi);	
	if(NU){ //500
		// Hunters
		city->MinHuters=2;
		if(NU>50) city->MinHuters=NU/9+5;
		// Fermers
		if(GetReadyUnits(&Iro.Build.Mel)){
			city->MinFermers = NU/8;
			if(GetMoney(FOOD)<700) city->MinFermers = NU/6;
			//if(NU<300) city->MinFermers = NU*2/7;
			if(!UpgIsRun(&Iro.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinFermers = NU/4+30;

			int NHunt=GetNUnits(&city->HuntGroup);
			if(NHunt>20&&GetMoney(FOOD)>60000||GetMoney(FOOD)>120000){
				city->MinFermers -= NHunt;
				if(city->MinFermers<20) city->MinFermers=20;
			}

			if(city->MinFermers>200){
				city->MinFermers = 200;
				if(UpgIsRun(&Iro.Upg.Mel_GETRES2)) city->MinFermers = 50;
			}
		}		
		int NMeln=2+city->MinFermers/120;
		if(NMeln>3) NMeln=3;
		if(UpgIsRun(&Iro.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Iro.Build.Mel, NMeln, 100, 70);
		// Wooders
		if(GetUnits(&Iro.Build.Skl)){
			city->MinWooders = NU/5;
			if(!UpgIsRun(&Iro.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinWooders = NU/4+5;
			if(city->MinWooders>300){
				city->MinWooders = 300;
				if(GetUnits(&Iro.Build.Do1)>20) city->MinWooders = 100;
			}
		}
		int NSklad=1+(city->MinWooders+city->MinHuters)/50;
		int MaxSkl=6;
		if(!UpgIsRun(&Iro.Upg.EnDo2)) MaxSkl=4;

		if(NSklad>MaxSkl) NSklad=MaxSkl;
		if(UpgIsRun(&Iro.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Iro.Build.Skl, NSklad, 100, 70);

		// Firers
		city->NFirers=0;
		if(NU>50) city->NFirers=NU/5;
		if(NU>200) city->NFirers=NU/10;
		if(city->NFirers>90) city->NFirers=90;
		
	}

	// Port
	TryUnit(&Iro.Unit.Ka1, 10, 50, 100);
	if(GetUnits(&Iro.Unit.Ka1)>8){
		TryUpgrade(&Iro.Upg.Ka1Fishing1,100,100);
		//TryUpgrade(&Iro.Upg.Ka1Fishing2,100,100);
		//TryUpgrade(&Iro.Upg.Ka1Fishing3,100,100);
		//TryUpgrade(&Iro.Upg.Ka1Fishing4,100,100);
		//TryUpgrade(&Iro.Upg.Ka1Fishing5,100,100);
		//TryUpgrade(&Iro.Upg.Ka1Fishing6,100,100);
	}

	if(GetDifficulty()>0) WarriorsUpg();

	// Enable warriors
	TryUpgrade(&Iro.Upg.EnTam, 90, 100);
	if(GetUnits(&Iro.Build.Pst)&&GetMoney(FOOD)>10000){ //UpgIsRun(&Iro.Upg.EnDo2) && GetResource(AiNat,IRON)>10000){
		TryUpgrade(&Iro.Upg.EnLut, 95, 100);
	}
	if(UpgIsRun(&Iro.Upg.EnDo2)) TryUpgrade(&Iro.Upg.EnVsd, 90, 100);

}

void WarriorsUpg(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// Peasant
	if(UpgIsRun(&Iro.Upg.Mel_GETRES)){
		// produce speed
		TryUpgrade(&Iro.Upg.KriBuildSpeed1, 95, 100);
		TryUpgrade(&Iro.Upg.KriBuildSpeed2, 95, 100);
		// attack
		if(UpgIsRun(&Iro.Upg.Strike1)){
			TryUpgrade(&Iro.Upg.KriAtt, 90, 100);		
			TryUpgrade(&Iro.Upg.KriAtt3, 90, 100);
			TryUpgrade(&Iro.Upg.KriAtt4, 90, 100);
			if(UpgIsRun(&Iro.Upg.EnDo2)){
				TryUpgrade(&Iro.Upg.KriAtt5, 90, 100);
				TryUpgrade(&Iro.Upg.KriAtt6, 90, 50);
				TryUpgrade(&Iro.Upg.KriAtt7, 50, 50);
			}
		}
		// defence
		TryUpgrade(&Iro.Upg.KriDef, 90, 100);
		TryUpgrade(&Iro.Upg.KriDef3, 90, 100);
		TryUpgrade(&Iro.Upg.KriDef4, 90, 100);
		if(UpgIsRun(&Iro.Upg.EnDo2)){
			TryUpgrade(&Iro.Upg.KriDef5, 90, 100);
			TryUpgrade(&Iro.Upg.KriDef6, 90, 100);
			TryUpgrade(&Iro.Upg.KriDef7, 95, 100);
		}
		// life
		TryUpgrade(&Iro.Upg.KriIR, 90, 100);
		TryUpgrade(&Iro.Upg.KriIR3, 90, 100);
		TryUpgrade(&Iro.Upg.KriIR4, 90, 100);
		if(UpgIsRun(&Iro.Upg.EnDo2)){
			TryUpgrade(&Iro.Upg.KriIR5, 90, 100);
			if(UpgIsRun(&Iro.Upg.Mel_GETRES2)){
				TryUpgrade(&Iro.Upg.KriIR6, 90, 100);				
			}
			if(UpgIsRun(&Iro.Upg.LutLife1)) TryUpgrade(&Iro.Upg.KriIR7, 90, 100);
		}
	}
	// Tam
	{		
		// attack
		if(GetUnits(&Iro.Unit.Tam)>30){
			TryUpgrade(&Iro.Upg.Strike1, 90, 100);
			TryUpgrade(&Iro.Upg.TamAtt, 90, 100);
			TryUpgrade(&Iro.Upg.TamAtt3, 90, 100);
			if(UpgIsRun(&Iro.Upg.EnDo2)){
				TryUpgrade(&Iro.Upg.TamAtt4, 90, 100);
				TryUpgrade(&Iro.Upg.TamAtt5, 90, 100);			
				TryUpgrade(&Iro.Upg.TamAtt6, 80, 80);
				if(UpgIsRun(&Iro.Upg.Strike1)) TryUpgrade(&Iro.Upg.TamAtt7, 80, 80);
			}
		}
		// defence
		if(GetUnits(&Iro.Unit.Tam)>30){
			TryUpgrade(&Iro.Upg.TamDef, 90, 100);
			TryUpgrade(&Iro.Upg.TamDef3, 90, 100);
			TryUpgrade(&Iro.Upg.TamDef4, 90, 100);
			if(UpgIsRun(&Iro.Upg.EnDo2)){
				TryUpgrade(&Iro.Upg.TamDef5, 80, 100);
				if(UpgIsRun(&Iro.Upg.Strike1)){
					TryUpgrade(&Iro.Upg.TamDef6, 80, 80);
					TryUpgrade(&Iro.Upg.TamDef7, 80, 80);
				}
			}
		}
	}
	// Lut
	{
		// precision
		if(GetUnits(&Iro.Unit.Lut)>30){
			TryUpgrade(&Iro.Upg.LutPerc1, 90, 100);
			if(UpgIsRun(&Iro.Upg.EnDo2)&&UpgIsRun(&Iro.Upg.KriDef7)) TryUpgrade(&Iro.Upg.LutPerc2, 90, 100);
			// attack			
			if(UpgIsRun(&Iro.Upg.EnDo2)&&UpgIsRun(&Iro.Upg.LutLife1)){
				TryUpgrade(&Iro.Upg.LutAtt, 90, 100);
				TryUpgrade(&Iro.Upg.LutAtt3, 90, 100);
				TryUpgrade(&Iro.Upg.LutAtt4, 90, 100);
				TryUpgrade(&Iro.Upg.LutAtt5, 20, 100);
				TryUpgrade(&Iro.Upg.LutAtt6, 15, 100);
				TryUpgrade(&Iro.Upg.LutAtt7, 15, 100);
			}
			// defence
			TryUpgrade(&Iro.Upg.LutDef, 90, 100);
			TryUpgrade(&Iro.Upg.LutDef3, 90, 100);
			TryUpgrade(&Iro.Upg.LutDef4, 90, 100);
			if(UpgIsRun(&Iro.Upg.EnDo2)){
				TryUpgrade(&Iro.Upg.LutDef5, 90, 100);
				TryUpgrade(&Iro.Upg.LutDef6, 90, 100);
				TryUpgrade(&Iro.Upg.LutDef7, 95, 100);
			}
			TryUpgrade(&Iro.Upg.LutLife1, 95, 100);
		}
	}
	if(UpgIsRun(&Iro.Upg.EnDo2)){
		// Str
		{
			TryUpgrade(&Iro.Upg.EnStr, 90, 100);
		}
	}
	// Horces
	{
		if(UpgIsRun(&Iro.Upg.EnDo2)){
			if(GetUnits(&Iro.Unit.Vsd)>30){
				// attack
				TryUpgrade(&Iro.Upg.VsdAtt, 90, 100);
				TryUpgrade(&Iro.Upg.VsdAtt3, 90, 100);
				TryUpgrade(&Iro.Upg.VsdAtt4, 90, 100);
				TryUpgrade(&Iro.Upg.VsdAtt5, 90, 30);
				TryUpgrade(&Iro.Upg.VsdAtt6, 90, 30);
				TryUpgrade(&Iro.Upg.VsdAtt7, 90, 30);
				// deffence
				TryUpgrade(&Iro.Upg.VsdDef, 90, 100);
				TryUpgrade(&Iro.Upg.VsdDef3, 90, 100);
				TryUpgrade(&Iro.Upg.VsdDef4, 90, 100);
				TryUpgrade(&Iro.Upg.VsdDef5, 40, 30);
				TryUpgrade(&Iro.Upg.VsdDef6, 40, 30);
				TryUpgrade(&Iro.Upg.VsdDef7, 40, 30);
			}
		}
	}
	// Sha
	{
		TryUpgrade(&Iro.Upg.ShaBuild1,35,100);
		if(UpgIsRun(&Iro.Upg.EnDo2)){
			TryUpgrade(&Iro.Upg.ShaBuild1,100,100);
			if(UpgIsRun(&Iro.Upg.Mel_GETRES2)){
				TryUpgrade(&Iro.Upg.ShaMedic1,100,20);
				TryUpgrade(&Iro.Upg.ShaLife1,100,20);
			}
		}
	}
	TryUpgrade(&Iro.Upg.EnVog, 90, 100);
}

void WaterScript(){
	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Iro.Build.Skl)) TryUnit(&Iro.Build.Ver,1,100,90);
	if(GetUnits(&Iro.Build.Kre)>1) TryUnit(&Iro.Build.Ver,3,60,60);

	//int NU=GetUnits(&Iro.Unit.Tam)+GetUnits(&Iro.Unit.Lut)+city->NFirers;
	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&Iro.Unit.Par, NPar, 100, 100);
	
	int FreeUnitPlace = GetMaxUnits(AiNat) - GetCurrentUnits(AiNat);
	if(FreeUnitPlace>15){
		TryUnit(&Iro.Unit.Ka1, 4, 100, 100);
		if(TryUnit(&Iro.Unit.Ka1, 10, 10, 100)){
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
			TryUnit(&Iro.Unit.Ka1, 10, 100, 100);
		}
	}
	
	if(FreeUnitPlace>10){
		TryUnit(&Iro.Unit.Ka3, 4, 100, 100);
		if(UpgIsRun(&Iro.Upg.Ka3Build6)){
			TryUnit(&Iro.Unit.Ka3, 20, 100, 100);
		}
	}

	if(GetUnits(&Iro.Unit.Par)){
		TryUpgrade(&Iro.Upg.ParSpeed1,100,100);
		TryUpgrade(&Iro.Upg.ParSpeed2,100,100);
		TryUpgrade(&Iro.Upg.ParSpeed3,100,100);
		if(GetUnits(&Iro.Build.Do1)>2){
			TryUpgrade(&Iro.Upg.ParSpeed4,100,100);
		}
		if(GetUnits(&Iro.Build.Do1)>2){
			TryUpgrade(&Iro.Upg.ParSpeed5,100,100);
			TryUpgrade(&Iro.Upg.ParSpeed6,100,100);
		}
	}

	if(GetUnits(&Iro.Build.Do1)>2){
		TryUpgrade(&Iro.Upg.Ka3Build1,100,100);
		TryUpgrade(&Iro.Upg.Ka3Build2,100,100);
		TryUpgrade(&Iro.Upg.Ka3Build3,100,100);
		TryUpgrade(&Iro.Upg.Ka3Build4,100,100);
		TryUpgrade(&Iro.Upg.Ka3Build5,100,100);
		TryUpgrade(&Iro.Upg.Ka3Build6,100,100);
	}

	if(GetUnits(&Iro.Unit.Ka1)>2){
		TryUpgrade(&Iro.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Iro.Upg.Ka1Fishing2,100,100);
		TryUpgrade(&Iro.Upg.Ka1Fishing3,100,100);
		TryUpgrade(&Iro.Upg.Ka1Fishing4,100,100);
		TryUpgrade(&Iro.Upg.Ka1Fishing5,100,100);
		TryUpgrade(&Iro.Upg.Ka1Fishing6,100,100);
	}
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
