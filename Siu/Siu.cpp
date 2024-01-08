#define CONQUEST
#include "..\Import.h"
#include "..\SiuNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Siu.Unit.Kri.Index;
	city->Init(AiNat);

	city->HuntNIndex=Siu.Unit.Lut.Index;
	city->NIndexOff = Siu.Unit.KVog.Index;
	city->NIndexMoff=Siu.Unit.KVog.Index;
	//city->NIndexBrb=Siu.Unit.KVog.Index;
	//city->NIndexFlg=Siu.Unit.KVog.Index;
	//city->HuntNIndex=Siu.Unit.Kri.Index;
}

void Script();
void WarriorsUpg();
void WaterScript();
void SmallWaterScript();

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
		SmallWaterScript();
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
	city->ParomNIndex=Siu.Unit.Par.Index;
	
	int Diff=GetDifficulty();
	switch(Diff){
	case 0:
	case 1:
		city->SetStartRes(0,4000,0,0,0,0);
		break;
	case 2:
		city->SetStartRes(0,8000,0,0,0,0);
		break;
	case 3:
		city->SetStartRes(0,12000,0,0,0,0);
		break;
	};
}


void Script(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	// Units
	city->PKrepost = GetUnits(&Siu.Unit.Kri)/5;	
	if(city->PKrepost>12) city->PKrepost = 12;

	city->MinFermers = 0;

	city->MinHuters=GetUnits(&Siu.Unit.Lut)/2+20;
	if(city->MinHuters>80) city->MinHuters=80;
	
	city->NUnits=0;
	if(GetUnits(&Siu.Unit.Lut)>40) city->NUnits=2;

	// Role planing
	city->AddBranch(Siu.Unit.KLut.Index,brBack,10,180);
	city->AddBranch(Siu.Unit.Sha.Index,brBack,50,120);
	city->AddBranch(Siu.Unit.KPik.Index,brBack,60,220);
	city->AddBranch(Siu.Unit.KVog.Index,brBack,0,200);
	city->AddBranch(Siu.Unit.KStr.Index,brBack,20,240);
	city->AddBranch(Siu.Unit.Lut.Index,brBack,40,0);

	Branch* KStr=city->AddBranch(Siu.Unit.KStr.Index,0,0,0);
	Branch* KLut=city->AddBranch(Siu.Unit.KLut.Index,0,0,0);
	Branch* Sha=city->AddBranch(Siu.Unit.Sha.Index,0,0,0);
	Branch* KPik=city->AddBranch(Siu.Unit.KPik.Index,0,0,0);
	Branch* Lut=city->AddBranch(Siu.Unit.Lut.Index,0,0,0);
	Branch* KVog=city->AddBranch(Siu.Unit.KVog.Index,0,0,0);

	KLut->Prio[brForward] = 2;	KLut->Part[brForward] = 0;	KLut->Type[brForward] = btFire;
	KLut->Prio[brCenter] = 0;	KLut->Part[brCenter] = 0;
	KLut->Prio[brBack] = 1;		KLut->Part[brBack] = 1;		KLut->Type[brForward] = btTomahawk;
	KLut->Formation=1;
	KLut->Domovoi=false;

	KStr->Prio[brForward] = 0;	KStr->Part[brForward] = 0;
	KStr->Prio[brCenter] = 0;	KStr->Part[brCenter] = 1;	KStr->Type[brCenter] = btTomahawk;
	KStr->Prio[brBack] = 1;		KStr->Part[brBack] = 0;
	KStr->Formation=1;
	//KStr->Strelok=1;
	KStr->Domovoi=false;

	Sha->Prio[brForward] = 0;	Sha->Part[brForward] = 0;
	Sha->Prio[brCenter] = 0;	Sha->Part[brCenter] = 0;
	Sha->Prio[brBack] = 1;		Sha->Part[brBack] = 1;
	Sha->BaseGuard=1;

	KPik->Prio[brForward] = 0;	KPik->Part[brForward] = 0;
	KPik->Prio[brCenter] = 0;	KPik->Part[brCenter] = 1;	KPik->Type[brCenter] = btKillers;
	KPik->Prio[brBack] = 1;		KPik->Part[brBack] = 0;
	KPik->Formation=1;
	KPik->Domovoi=false;

	KVog->Domovoi=false;

	Lut->Prio[brForward] = 2;	Lut->Part[brForward] = 1;	Lut->Type[brForward] = btTomahawk;
	Lut->Prio[brCenter] = 1;	Lut->Part[brCenter] = 0;	Lut->Type[brCenter] = btStorm;
	Lut->Prio[brBack] = 0;		Lut->Part[brBack] = 0;	

	if(GetUnits(&Siu.Unit.Lut)>40) Lut->Max=80;	
	//Lut->Domovoi=(GetUnits(&Siu.Unit.Lut)>20);

	if(GetReadyUnits(&Siu.Build.Skl)) city->MinWooders = 10;
	if(GetReadyUnits(&Siu.Build.Kre)){
		city->MinWooders = 15;
	}
	if(GetReadyUnits(&Siu.Build.Pst)){
		city->MinWooders = 30;
	}
	if(GetReadyUnits(&Siu.Build.Kre)>1){
		city->MinWooders = 60;
	}


	//if(GetUnits(&Siu.Unit.Lut)>7 || UpgIsRun(&Siu.Upg.Mel_GETRES)) 
	TryUnit(&Siu.Unit.Kri, 200, 20, 100);
	TryUnit(&Siu.Unit.Lut, 10000, 30, 100);

	if(GetUnits(&Siu.Unit.KVog)<5) TryUnit(&Siu.Unit.KVog, 5, 20, 100);

	//if(Chief){
	//	TryUnit(&Siu.Unit.KVog, 1000, 20, 100);
	//	TryUnit(&Siu.Unit.KVog, 1000, 20, 100);
	//}else{
		//TryUnit(&Siu.Unit.KPik, 10000, 20, 100);
		//TryUnit(&Siu.Unit.KPik, 10000, 20, 100);
		//TryUnit(&Siu.Unit.KPik, 10000, 20, 100);
		//if(GetUnits(&Siu.Unit.KVog) && GetMoney(FOOD)>20000){
		//	Chief=1;
		//}
	//}

	if(UpgIsRun(&Siu.Upg.Mel_GETRES2)||GetMoney(FOOD)>15000){
		TryUnit(&Siu.Unit.KPik, 10000, 40, 100);
		TryUnit(&Siu.Unit.KPik, 10000, 20, 85);

		TryUnit(&Siu.Unit.KLut, 10000, 50, 100);
		TryUnit(&Siu.Unit.KLut, 10000, 50, 100);
		TryUnit(&Siu.Unit.KLut, 10000, 50, 100);
		TryUnit(&Siu.Unit.KLut, 10000, 30, 60);
	}

	TryUnit(&Siu.Unit.KStr, 1000, 20, 100);

	if(GetUnits(&Siu.Unit.Sha)<10) TryUnit(&Siu.Unit.Sha, 50, 20, 100);

	// Buildings
	//TryUnit(&Siu.Build.Blg, 3, 100, 70);
	//TryUnit(&Siu.Build.Blg2, 3, 100, 70);	
	
	TryUnit(&Siu.Build.Mel, 1, 100, 95);
	TryUnit(&Siu.Build.Pst, 1, 100, 95);
	TryUnit(&Siu.Build.Do1, 2, 100, 95);
	TryUnit(&Siu.Build.Skl, 1, 100, 95);
	if(GetUnits(&Siu.Unit.Kri)>50) TryUnit(&Siu.Build.Skl, 3, 80, 70);
	TryUnit(&Siu.Build.Kre, 1, 100, 70);
	if(GetUnits(&Siu.Build.Pst)){
		TryUnit(&Siu.Build.Kre, 4, 100, 70);
		TryUnit(&Siu.Build.Do1, 3, 100, 70);
		TryUnit(&Siu.Build.Mel, 4, 100, 70);
		//if(GetReadyUnits(&Siu.Build.Mel)) Kri->Part[brCenter] = 1;
		//if(GetReadyUnits(&Siu.Unit.Lut)>5) Kri->Part[brCenter] = 1;
		//if(GetMaxUnits(AiNat)<=GetCurrentUnits(AiNat)){
			TryUnit(&Siu.Build.Do1, 5, 70, 70);
			TryUnit(&Siu.Build.Do2, 6, 70, 70);
		//}
		if(UpgIsRun(&Siu.Upg.Do2_ENABLE)){
			TryUnit(&Siu.Build.Do1, 6, 70, 70);
		}
	}

	if(GetReadyUnits(&Siu.Build.Pst)){
		if(GetResource(AiNat,FOOD)>200000 && GetResource(AiNat,GOLD)<2000){
			AI_Torg(GOLD,FOOD,500);
			AI_Torg(FOOD,GOLD,200000);
		}
		if(GetResource(AiNat,FOOD)<100){
			AI_Torg(WOOD,FOOD,GetResource(AiNat,WOOD)*8/10);
			AI_Torg(WOOD,GOLD,GetResource(AiNat,GOLD)*8/10);
		}		
		AI_Torg(STONE,FOOD,GetMoney(STONE)-100);
		//AI_Torg(IRON,FOOD,GetMoney(IRON)-100);
		AI_Torg(COAL,FOOD,GetMoney(COAL)-100);
		if(!UpgIsDone(&Siu.Upg.Mel_GETRES) && GetMoney(WOOD)>4000){
			AI_Torg(WOOD,FOOD,4000);
		}
		if(!UpgIsDone(&Siu.Upg.Mel_GETRES2) && GetMoney(GOLD)>4000){
			AI_Torg(GOLD,FOOD,4000);
		}
		if(GetMoney(GOLD)>20000 && GetMoney(IRON)<4000){
			//if(GetMoney(IRON)<4000){
				AI_Torg(IRON,GOLD,500);	
				AI_Torg(GOLD,IRON,10000);
			//}
			//AI_Torg(GOLD,FOOD,GetMoney(GOLD));
		}
	}
	
	TryUnit(&Siu.Build.Cen, 1, 100, 70);
	TryUnit(&Siu.Build.Hra, 2, 90, 70);


	if(GetUnits(&Siu.Build.Mel)>1) TryUnit(&Siu.Build.Pst, 3, 92, 70);
	//if(GetReadyUnits(&Siu.Build.Do1)>2)
	
	TryUnit(&Siu.Build.Ver, 2, 100, 70);

	// Upgrades
	// Food
	if(GetUnits(&Siu.Unit.Lut)>5) TryUpgrade(&Siu.Upg.Mel_GETRES, 70, 100);
	TryUpgrade(&Siu.Upg.Mel_GETRES2, 85, 100);

	TryUpgrade(&Siu.Upg.CEN01, 80, 100);
	TryUpgrade(&Siu.Upg.CEN02, 80, 100);
	TryUpgrade(&Siu.Upg.CEN03, 80, 100);

	// Wood
	TryUpgrade(&Siu.Upg.Wood1, 100, 100);

	if(GetUnits(&Siu.Build.Kre)>2){
		TryUpgrade(&Siu.Upg.Do2_ENABLE, 95, 100);
	}

	// Market
	if(GetReadyUnits(&Siu.Build.Pst)){

		// Parom prepare
		if(city->LandType&&GetMoney(IRON)<51){
			if(GetMoney(WOOD)>500){
				AI_Torg(WOOD,IRON,500);
			}else
			if(GetMoney(FOOD)>3000){
				AI_Torg(FOOD,IRON,1000);
			}
		}

		int FR=GetMoney(FOOD);
		int WR=GetMoney(WOOD);
		int GR=GetMoney(GOLD);
		
		if(FR<5000){
			if(WR>30000){
				AI_Torg(FOOD,WOOD,100);
				AI_Torg(FOOD,WOOD,100);
				AI_Torg(FOOD,WOOD,100);
				AI_Torg(WOOD,FOOD,WR);
			}
			if(GR>5000){
				AI_Torg(FOOD,GOLD,100);
				AI_Torg(FOOD,GOLD,100);
				AI_Torg(FOOD,GOLD,100);
				AI_Torg(GOLD,FOOD,GR);
			}
		}
	}

	// Fishing
	{
		if(!city->LandType){
			TryUnit(&Siu.Build.Ver,1,100,90);
			TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		}
		if(GetUnits(&Siu.Unit.Ka1)>3){
			TryUpgrade(&Siu.Upg.Ka1Fishing1,100,100);
			TryUpgrade(&Siu.Upg.Ka1Fishing2,100,100);
			TryUpgrade(&Siu.Upg.Ka1Fishing3,100,100);
			TryUpgrade(&Siu.Upg.Ka1Fishing4,100,100);
			TryUpgrade(&Siu.Upg.Ka1Fishing5,100,100);
			TryUpgrade(&Siu.Upg.Ka1Fishing6,100,100);
		}
	}

	if(GetDifficulty()>0) WarriorsUpg();

	// Enable warriors
	if(UpgIsRun(&Siu.Upg.Mel_GETRES2)) TryUpgrade(&Siu.Upg.KLutEnable, 100, 100);
	TryUpgrade(&Siu.Upg.KStrEnable, 90, 100);
	if(UpgIsRun(&Siu.Upg.Mel_GETRES2)) TryUpgrade(&Siu.Upg.KVogEnable, 100, 100);

}

void WarriorsUpg(){

	// Pika
	{
		if(GetUnits(&Siu.Unit.KPik)>10) TryUpgrade(&Siu.Upg.KPikCenDamage1, 90, 60);		
		
	}

	// KPik
	{
		if(GetUnits(&Siu.Build.Kre)>2) TryUpgrade(&Siu.Upg.KPikBuild1, 100, 80);
		if(GetUnits(&Siu.Unit.KPik)>10){
			TryUpgrade(&Siu.Upg.KPikDamage, 90, 60);
			TryUpgrade(&Siu.Upg.KPikDamage3, 90, 60);
			TryUpgrade(&Siu.Upg.KPikDamage4, 90, 60);
			TryUpgrade(&Siu.Upg.KPikDamage5, 90, 60);
			TryUpgrade(&Siu.Upg.KPikDamage6, 80, 60);
			TryUpgrade(&Siu.Upg.KPikDamage7, 80, 60);
			TryUpgrade(&Siu.Upg.KPikProtect, 90, 60);
			TryUpgrade(&Siu.Upg.KPikProtect3, 90, 60);
			TryUpgrade(&Siu.Upg.KPikProtect4, 90, 60);
			TryUpgrade(&Siu.Upg.KPikProtect5, 90, 60);
			TryUpgrade(&Siu.Upg.KPikProtect6, 80, 60);
			TryUpgrade(&Siu.Upg.KPikProtect7, 80, 60);

			TryUpgrade(&Siu.Upg.KPikCenDamage1, 90, 60);
			TryUpgrade(&Siu.Upg.KPikCenProtect1, 90, 60);
		}		
	}

	// KLut
	{
		TryUpgrade(&Siu.Upg.KLutBuild1, 100, 100);
		TryUpgrade(&Siu.Upg.KLutBuild2, 100, 100);
		if(GetUnits(&Siu.Unit.KVog)>30){
			TryUpgrade(&Siu.Upg.KLutRazbros1, 100, 100);
			TryUpgrade(&Siu.Upg.KLutRazbros2, 100, 100);
			
		}
	}

	// Vog
	{		
		if(GetUnits(&Siu.Unit.KVog)>10){
			TryUpgrade(&Siu.Upg.KVogDamage, 90, 40);
			TryUpgrade(&Siu.Upg.KVogDamage3, 90, 40);
			TryUpgrade(&Siu.Upg.KVogDamage4, 90, 40);
			TryUpgrade(&Siu.Upg.KVogDamage5, 90, 40);
			TryUpgrade(&Siu.Upg.KVogDamage6, 90, 40);
			TryUpgrade(&Siu.Upg.KVogDamage7, 90, 40);

			TryUpgrade(&Siu.Upg.KVogProtect, 90, 40);
			TryUpgrade(&Siu.Upg.KVogProtect3, 90, 40);
			TryUpgrade(&Siu.Upg.KVogProtect4, 90, 40);
			TryUpgrade(&Siu.Upg.KVogProtect5, 90, 40);
			TryUpgrade(&Siu.Upg.KVogProtect6, 90, 40);
			TryUpgrade(&Siu.Upg.KVogProtect7, 90, 40);
		}
	}

	// Sha
	{
		if(GetUnits(&Siu.Build.Hra)) TryUpgrade(&Siu.Upg.ShaBuild1, 100, 100);
	}
}

void WaterScript(){
	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	int NU=GetUnits(&Siu.Unit.KPik)+GetUnits(&Siu.Unit.Lut)+city->NFirers;
	
	if(GetUnits(&Siu.Build.Skl)) TryUnit(&Siu.Build.Ver,1,100,90);
	if(GetUnits(&Siu.Build.Kre)>1) TryUnit(&Siu.Build.Ver,3,60,60);

	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&Siu.Unit.Par, NPar, 100, 100);
	
	TryUnit(&Siu.Unit.Ka1, 4, 10, 100);
	if(TryUnit(&Siu.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Siu.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Siu.Upg.Ka3Build6)){
		TryUnit(&Siu.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Siu.Upg.ParSpeed1,100,100);
	TryUpgrade(&Siu.Upg.ParSpeed2,100,100);
	TryUpgrade(&Siu.Upg.ParSpeed3,100,100);
	TryUpgrade(&Siu.Upg.ParSpeed4,100,100);
	TryUpgrade(&Siu.Upg.ParSpeed5,100,100);
	TryUpgrade(&Siu.Upg.ParSpeed6,100,100);

	if(GetUnits(&Siu.Unit.Ka1)){
		TryUpgrade(&Siu.Upg.Ka3Build1,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build2,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build3,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build4,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build5,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build6,100,100);
	}

	if(GetUnits(&Siu.Unit.Ka1)>3){
		TryUpgrade(&Siu.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing2,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing3,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing4,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing5,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing6,100,100);
	}

};

void SmallWaterScript(){
	
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	if(GetUnits(&Siu.Build.Skl)) TryUnit(&Siu.Build.Ver,1,100,90);
	if(GetUnits(&Siu.Build.Kre)>1) TryUnit(&Siu.Build.Ver,3,60,60);
	
	TryUnit(&Siu.Unit.Ka1, 4, 10, 100);
	if(TryUnit(&Siu.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
		TryUnit(&Siu.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Siu.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Siu.Upg.Ka3Build6)){
		TryUnit(&Siu.Unit.Ka3, 20, 100, 100);
	}

	if(GetUnits(&Siu.Unit.Ka1)){
		TryUpgrade(&Siu.Upg.Ka3Build1,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build2,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build3,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build4,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build5,100,100);
		TryUpgrade(&Siu.Upg.Ka3Build6,100,100);
	}

	if(GetUnits(&Siu.Unit.Ka1)>3){
		TryUpgrade(&Siu.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing2,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing3,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing4,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing5,100,100);
		TryUpgrade(&Siu.Upg.Ka1Fishing6,100,100);
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