#define CONQUEST
#include "..\Import.h"
#include "..\DelNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Init(AiNat);

	city->Peasant = Del.Unit.Kri.Index;
	city->FirersType=Del.Unit.Kri.Index;	
	city->ParomNIndex=Del.Unit.Par.Index;
	city->NIndexBrb=Del.Unit.Sha.Index;
	city->NIndexFlg=Del.Unit.Sha.Index;
	city->NIndexOff=Del.Unit.Vog.Index;
	city->DefenceLess=1;

}

void Script();
void WaterScript();
void WarriorsUpg();

DLLEXPORT
void ProcessAI(){
	int AiNat = GetAINation();
	AICity* city = Village + AiNat;

	city->Process();
	if(GetDifficulty()>1) city->HuntNIndex=Del.Unit.Kri.Index;

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
	city->AddBranch(Del.Unit.Pik.Index,brBack,14,128);
	city->AddBranch(Del.Unit.Lut.Index,brBack,30,298);
	city->AddBranch(Del.Unit.S15.Index,brBack,60,128);
	city->AddBranch(Del.Unit.Sha.Index,brBack,100,120);
	city->AddBranch(Del.Unit.Vog.Index,brBack,60,120);
	city->AddBranch(Del.Unit.Vsd.Index,brBack,40,100);

	Branch* Pik=city->AddBranch(Del.Unit.Pik.Index,0,0,0);
	Branch* Lut=city->AddBranch(Del.Unit.Lut.Index,0,0,0);
	Branch* S15=city->AddBranch(Del.Unit.S15.Index,0,0,0);
	Branch* Sha=city->AddBranch(Del.Unit.Sha.Index,0,0,0);
	Branch* Vog=city->AddBranch(Del.Unit.Vog.Index,0,0,0);
	Branch* Vsd=city->AddBranch(Del.Unit.Vsd.Index,0,0,0);

	Pik->Prio[brForward] = 1;	Pik->Part[brForward] = 1;	Pik->Type[brForward] = btStorm;	
	Pik->Prio[brCenter] = 1;	Pik->Part[brCenter] = 1;	Pik->Type[brCenter] = btKillers;	
	Pik->Prio[brBack] = 0;		Pik->Part[brBack] = 0;
	Pik->Formation=1;
	if(UpgIsRun(&Del.Upg.PikLife1)||GetUnits(&Del.Unit.Pik)>400) Pik->Max=298;
	Pik->SeakMine=false;

	Lut->Prio[brForward] = 0;	Lut->Part[brForward] = 0;	//Lut->Type[brForward] = ;	
	Lut->Prio[brCenter] = 1;	Lut->Part[brCenter] = 1;	Lut->Type[brCenter] = btTomahawk;	
	Lut->Prio[brBack] = 0;		Lut->Part[brBack] = 0;
	Lut->Formation=1;

	S15->Prio[brForward] = 3;	S15->Part[brForward] = 1;	S15->Type[brForward] = btTomahawk;
	S15->Prio[brCenter] = 0;	S15->Part[brCenter] = 0;
	S15->Prio[brBack] = 0;		S15->Part[brBack] = 1;
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

	// Units in buildings
	city->NStrelok = 25;
	city->NUnits = 2;
	if(GetUnits(&Del.Unit.Pik)>100&&GetUnits(&Del.Unit.Pik)<220) city->NUnits = 25;	

	// Units
	if(GetMoney(FOOD)>300){
		TryUnit(&Del.Unit.Kri, 1000, 5, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
		TryUnit(&Del.Unit.Kri, 1000, 3, 100);
	}

	if(GetUnits(&Del.Build.Skl)) TryUnit(&Del.Unit.Pik, 1000, 20, 100);
	TryUnit(&Del.Unit.Pik, 1000, 20, 100);

	TryUnit(&Del.Unit.Lut, 10000, 20, 100);
	TryUnit(&Del.Unit.Lut, 10000, 10, 100);
	TryUnit(&Del.Unit.Lut, 10000, 10, 50);

	int MaxSha=30;
	if(UpgIsRun(&Del.Upg.PikLife1)) MaxSha=1000;
	if(GetUnits(&Del.Unit.Sha)<20)TryUnit(&Del.Unit.Sha, 10000, 20, 100);
	
	TryUnit(&Del.Unit.S15, 10000, 20, 100);
	if(GetUnits(&Del.Unit.Vog)<10) TryUnit(&Del.Unit.Vog, 10000, 20, 100);
	TryUnit(&Del.Unit.Vsd, 10000, 20, 100);	// vsadnik

	int NeedSquad = (GetUnits(&Del.Unit.Pik)+GetUnits(&Del.Unit.Lut)+GetUnits(&Del.Unit.S15)) / 5;
	//TryUnit(&Del.Unit.Vog, NeedSquad, 50, 100);
	//TryUnit(&Del.Unit.Sha, NeedSquad, 50, 100);


	// Convertors
	city->PKrepost = 0;
	if((UpgIsRun(&Del.Upg.Mel_GETRES)||GetMoney(FOOD)>2000)&&GetReadyUnits(&Del.Build.Skl)){
		city->PKrepost = 35;
	}

	// Wood
	if(GetDifficulty()>0){
		TryUpgrade(&Del.Upg.Wood1, 95, 100);
		TryUpgrade(&Del.Upg.Wood2, 95, 100);
	}

	// Buildings
	TryUnit(&Del.Build.Mel, 1, 100, 70);
	TryUnit(&Del.Build.Do1, 2, 100, 70);
	TryUnit(&Del.Build.Skl, 1, 100, 70);
	if(GetUnits(&Del.Build.Do1)>1) TryUnit(&Del.Build.Kaz, 1, 100, 70);
	
	if(UpgIsRun(&Del.Upg.Mel_GETRES)||GetMoney(FOOD)>2000){

		if(GetUnits(&Del.Build.Skl)) TryUnit(&Del.Build.Do1, 7, 100, 70);
		if(UpgIsRun(&Del.Upg.EnDo2) && GetUnits(&Del.Build.Kaz)>2 && GetUnits(&Del.Build.Do2)>5) TryUnit(&Del.Build.Do1, 1000, 100, 70);
		TryUnit(&Del.Build.Do2, 6, 100, 70);

		TryUnit(&Del.Build.Kaz, 2, 100, 70);
		TryUnit(&Del.Build.Pst, 2, 100, 80);
		TryUnit(&Del.Build.Pst, 3, 60, 80);
		
		TryUnit(&Del.Build.Cen, 1, 100, 40);
		TryUnit(&Del.Build.Hra, 2, 100, 40);
		if(GetUnits(&Del.Build.Pst)>2) TryUnit(&Del.Build.Hra, 3, 100, 40);
		TryUnit(&Del.Build.Kre, 2, 100, 40);

		if(UpgIsRun(&Del.Upg.EnDo2)){
			TryUnit(&Del.Build.Kaz, 3, 100, 70);
			TryUnit(&Del.Build.Pst, 3, 100, 70);
			TryUnit(&Del.Build.Cen, 3, 100, 40);
			TryUnit(&Del.Build.Kre, 3, 100, 40);
		}
	}

	//TryUnit(&Del.Build.Ver, 1, 100, 70);

	// Upgrades
	// Food
	TryUpgrade(&Del.Upg.CEN10, 80, 100); //EFFECT_FOOD +2000
	TryUpgrade(&Del.Upg.CEN12, 70, 100); //EFFECT_FOOD +3000
	TryUpgrade(&Del.Upg.FOOD52, 60, 100); //EFFECT_FOOD +3000
	
	
	if(GetUnits(&Del.Unit.Kri)>50) TryUpgrade(&Del.Upg.Mel_GETRES, 80, 100);		
	if(UpgIsRun(&Del.Upg.PikLife1)) TryUpgrade(&Del.Upg.Mel_GETRES2, 95, 100);

	TryUpgrade(&Del.Upg.CEN01, 90, 100); //EFFECT_FOOD +4
	TryUpgrade(&Del.Upg.CEN02, 90, 100); //EFFECT_FOOD +4
	TryUpgrade(&Del.Upg.CEN03, 90, 100); //EFFECT_FOOD +5
	
	// Dom	
	TryUpgrade(&Del.Upg.EnDo2, 100, 100); //ENABLE Do2
	if(GetUnits(&Del.Build.Do2)) 
		TryUpgrade(&Del.Upg.EnKre, 100, 100); //ENABLE Vsd
	else
		TryUpgrade(&Del.Upg.EnKre, 70, 1); //ENABLE Kre

	// Market
	if(GetReadyUnits(&Del.Build.Pst)){

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
		int WR=GetResource(AiNat,WOOD);
		int IR=GetResource(AiNat,IRON);
		int GR=GetResource(AiNat,GOLD);

		// Patroni i t.d.
		if(GetResource(AiNat,STONE)<300 && GetResource(AiNat,WOOD)>2300) AI_Torg(WOOD,STONE,2000);

		// Prepare
		if(GetUnits(&Del.Build.Do1)>6) PrepareUpgrade(AiNat,FOOD,GOLD,&Del.Upg.EnDo2);
		if(GetReadyUnits(&Del.Build.Pst)) PrepareUpgrade(AiNat,FOOD,GOLD,&Del.Upg.PikLife1);		
	}
	
	// Peasat distribution
	int NU=GetUnits(&Del.Unit.Kri)+GetUnits(&Del.Unit.Pik)+GetUnits(&Del.Unit.Lut);//+GetUnits(&Del.Unit.Voi);	
	if(NU){ //500
		// Hunters
		city->MinHuters=2;
		if(NU>50) city->MinHuters=5+NU/8;
		// Fermers
		if(GetReadyUnits(&Del.Build.Mel)){
			city->MinFermers = NU/8;
			if(GetMoney(FOOD)<700) city->MinFermers = NU/6;
			if(!UpgIsRun(&Del.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinFermers = NU/4+30;
						
			int NHunt=GetNUnits(&city->HuntGroup);
			if(NHunt>20&&GetMoney(FOOD)>60000||GetMoney(FOOD)>120000){
				city->MinFermers -= NHunt;
				if(city->MinFermers<20) city->MinFermers=20;
			}
			
			if(city->MinFermers>200) city->MinFermers = 200;
			if(UpgIsRun(&Del.Upg.Mel_GETRES2)) city->MinFermers = 50;
		}
		int NMeln=2+city->MinFermers/120;
		if(NMeln>3) NMeln=3;
		if(UpgIsRun(&Del.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Del.Build.Mel, NMeln, 100, 70);
		// Wooders
		if(GetReadyUnits(&Del.Build.Skl)){
			city->MinWooders = NU/4;
			if(!UpgIsRun(&Del.Upg.Mel_GETRES)&&GetMoney(FOOD)<2000) city->MinWooders = NU/4+5;
			if(city->MinWooders>300) city->MinWooders = 300;
		}
		int NSklad=1+(city->MinWooders+city->MinHuters)/50;
		int MaxSkl=6;
		if(!UpgIsRun(&Del.Upg.EnDo2)) MaxSkl=4;

		if(NSklad>MaxSkl) NSklad=MaxSkl;
		if(UpgIsRun(&Del.Upg.Mel_GETRES)||GetMoney(FOOD)>2000) TryUnit(&Del.Build.Skl, NSklad, 100, 70);
		// Firers
		if(!city->LandType||(city->LandType&&GetUnits(&Del.Unit.Par))){
			city->NFirers=0;
			if(NU>50) city->NFirers=NU/10;
			//if(NU>200) city->NFirers=NU/9;
			if(city->NFirers>90) city->NFirers=90;
		}
		
	}	

	if(GetDifficulty()>1) WarriorsUpg();

	// Enable warriors
	TryUpgrade(&Del.Upg.EnLut, 90, 100);
	TryUpgrade(&Del.Upg.EnStr, 90, 100);
	if(GetUnits(&Del.Unit.S15)>60) TryUpgrade(&Del.Upg.EnVog, 90, 100);
	if(UpgIsRun(&Del.Upg.EnDo2)) TryUpgrade(&Del.Upg.EnVsd, 90, 100);
	
}

void WaterScript(){

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Del.Build.Skl)) TryUnit(&Del.Build.Ver,1,100,90);
	if(GetUnits(&Del.Build.Kre)>1) TryUnit(&Del.Build.Ver,3,60,60);

	int NU=GetUnits(&Del.Unit.Pik)+GetUnits(&Del.Unit.Lut)+city->NFirers;

	//int NPar=1+NU/100;
	//if(NPar>5) NPar=5;
	//if(NU>50) TryUnit(&Del.Unit.Par, NPar, 100, 100);
	
	TryUnit(&Del.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&Del.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
		TryUnit(&Del.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Del.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Del.Upg.Ka3Build6)){
		TryUnit(&Del.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Del.Upg.ParSpeed1,100,100);
	TryUpgrade(&Del.Upg.ParSpeed2,100,100);
	TryUpgrade(&Del.Upg.ParSpeed3,100,100);
	TryUpgrade(&Del.Upg.ParSpeed4,100,100);
	TryUpgrade(&Del.Upg.ParSpeed5,100,100);
	TryUpgrade(&Del.Upg.ParSpeed6,100,100);

	TryUpgrade(&Del.Upg.Ka3Build1,100,100);
	TryUpgrade(&Del.Upg.Ka3Build2,100,100);
	TryUpgrade(&Del.Upg.Ka3Build3,100,100);
	TryUpgrade(&Del.Upg.Ka3Build4,100,100);
	TryUpgrade(&Del.Upg.Ka3Build5,100,100);
	TryUpgrade(&Del.Upg.Ka3Build6,100,100);

	if(GetUnits(&Del.Unit.Ka1)>3){
		TryUpgrade(&Del.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Del.Upg.Ka1Fishing2,100,100);
		TryUpgrade(&Del.Upg.Ka1Fishing3,100,100);
		TryUpgrade(&Del.Upg.Ka1Fishing4,100,100);
		TryUpgrade(&Del.Upg.Ka1Fishing5,100,100);
		TryUpgrade(&Del.Upg.Ka1Fishing6,100,100);
	}
};

void WarriorsUpg(){
	int AiNat = GetAINation();

	// Warriors
	int NU=GetUnits(&Del.Unit.Pik)+GetUnits(&Del.Unit.Kri)+GetUnits(&Del.Unit.Lut);//+GetUnits(&Del.Unit.Voi);

	// Kri
	TryUpgrade(&Del.Upg.KriBu1,90,100);
	TryUpgrade(&Del.Upg.KriBu2,90,100);

	// Pik
	TryUpgrade(&Del.Upg.PikLife1, 100, 100);

	if(UpgIsRun(&Del.Upg.Mel_GETRES)){
		TryUpgrade(&Del.Upg.PikA2, 80, 100);
		TryUpgrade(&Del.Upg.PikA3, 80, 100);
		if(GetDifficulty()>0){
			TryUpgrade(&Del.Upg.PikA4, 80, 100);
			TryUpgrade(&Del.Upg.PikA5, 80, 100);
			TryUpgrade(&Del.Upg.PikA6, 80, 100);
			TryUpgrade(&Del.Upg.PikA7, 80, 100);
		}
		TryUpgrade(&Del.Upg.PikS2, 80, 100);
		TryUpgrade(&Del.Upg.PikS3, 80, 100);
		TryUpgrade(&Del.Upg.PikS4, 80, 50);
		if(UpgIsRun(&Del.Upg.EnDo2)){
			TryUpgrade(&Del.Upg.PikS4, 80, 100);
			TryUpgrade(&Del.Upg.PikS5, 80, 100);
			TryUpgrade(&Del.Upg.PikS6, 80, 100);
			TryUpgrade(&Del.Upg.PikS7, 80, 100);
		}
	}
	
	// Lut
	{
		int NLut=GetUnits(&Del.Unit.Lut);
		
		if(NLut>40){
			TryUpgrade(&Del.Upg.LutRaz1, 100, 100);
			if(UpgIsRun(&Del.Upg.EnDo2)){
				TryUpgrade(&Del.Upg.LutRaz2, 100, 100);
			}
			TryUpgrade(&Del.Upg.LutStrike1, 100, 100);
		}

		if(NLut>30){
			TryUpgrade(&Del.Upg.LutA2, 90, 100);
			TryUpgrade(&Del.Upg.LutA3, 90, 100);
			TryUpgrade(&Del.Upg.LutA4, 90, 100);
		}
		if(NLut>60){
			TryUpgrade(&Del.Upg.LutA5, 90, 100);
			TryUpgrade(&Del.Upg.LutA6, 90, 100);
			TryUpgrade(&Del.Upg.LutA7, 90, 100);
		}

		if(NLut>30){
			TryUpgrade(&Del.Upg.LutS2, 90, 100);
			TryUpgrade(&Del.Upg.LutS3, 90, 100);
			TryUpgrade(&Del.Upg.LutS4, 90, 100);
		}
		if(NLut>60){
			TryUpgrade(&Del.Upg.LutS5, 90, 100);
			TryUpgrade(&Del.Upg.LutS6, 90, 100);
			TryUpgrade(&Del.Upg.LutS7, 90, 100);
		}
	}

	// Str
	{		
		// attack
		if(GetReadyUnits(&Del.Unit.S15)>35){
			TryUpgrade(&Del.Upg.StrAtt, 10, 100);
			TryUpgrade(&Del.Upg.StrAtt3, 10, 100);
		}
		if(GetReadyUnits(&Del.Unit.S15)>65){
			TryUpgrade(&Del.Upg.StrAtt4, 10, 100);
			TryUpgrade(&Del.Upg.StrAtt5, 10, 100);
			TryUpgrade(&Del.Upg.StrAtt6, 10, 100);
			TryUpgrade(&Del.Upg.StrAtt7, 10, 100);
		}
		// defence
		if(GetReadyUnits(&Del.Unit.S15)>35){
			TryUpgrade(&Del.Upg.StrDef, 10, 100);
			TryUpgrade(&Del.Upg.StrDef3, 10, 100);
			TryUpgrade(&Del.Upg.StrDef4, 10, 100);
		}
		if(GetReadyUnits(&Del.Unit.S15)>65){
			TryUpgrade(&Del.Upg.StrDef5, 10, 100);
			TryUpgrade(&Del.Upg.StrDef6, 10, 100);
			TryUpgrade(&Del.Upg.StrDef7, 10, 100);
		}
	}

	// Vog
	{		
	}

	// Sha
	if(UpgIsRun(&Del.Upg.EnDo2)){
		TryUpgrade(&Del.Upg.ShaBuild1,35,100);
		TryUpgrade(&Del.Upg.ShaBuild1,100,100);
		if(UpgIsRun(&Del.Upg.Mel_GETRES2)){
			TryUpgrade(&Del.Upg.ShaMedic1,100,20);
			TryUpgrade(&Del.Upg.ShaLife1,100,20);
		}
	}

	// Horces
	if(UpgIsRun(&Del.Upg.EnDo2)){
		if(GetUnits(&Del.Unit.Vsd)>30){
			// attack
			TryUpgrade(&Del.Upg.VsdAtt, 90, 100);
			TryUpgrade(&Del.Upg.VsdAtt3, 90, 100);
			TryUpgrade(&Del.Upg.VsdAtt4, 90, 100);
			TryUpgrade(&Del.Upg.VsdAtt5, 90, 30);
			TryUpgrade(&Del.Upg.VsdAtt6, 90, 30);
			TryUpgrade(&Del.Upg.VsdAtt7, 90, 30);
			// deffence
			TryUpgrade(&Del.Upg.VsdDef, 90, 100);
			TryUpgrade(&Del.Upg.VsdDef3, 90, 100);
			TryUpgrade(&Del.Upg.VsdDef4, 90, 100);
			TryUpgrade(&Del.Upg.VsdDef5, 40, 30);
			TryUpgrade(&Del.Upg.VsdDef6, 40, 30);
			TryUpgrade(&Del.Upg.VsdDef7, 40, 30);
		}
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
