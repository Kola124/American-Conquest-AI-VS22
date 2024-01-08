#define CONQUEST
#include "..\Import.h"
#include "..\PueNation.h"
#include "..\AICity.h"

DLLEXPORT
void InitAI(){
	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;
	
	city->Peasant = Pue.Unit.Kri.Index;
	city->Init(AiNat);
}

void Script();
void WarriorsUpg(bool EnHorce);
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
		city->LandType=1;
		WaterScript();		
		break;
	};
	Script();

	city->DefenceLess=1;
	city->Process();
	city->ParomNIndex=Pue.Unit.Par.Index;

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
	city->AddBranch(Pue.Unit.Lut.Index,brBack,15,50);
	city->AddBranch(Pue.Unit.S15.Index,brBack,60,120);
	city->AddBranch(Pue.Unit.Sha.Index,brBack,50,120);
	city->AddBranch(Pue.Unit.Vsd.Index,brBack,40,196);

	Branch* Lut=city->AddBranch(Pue.Unit.Lut.Index,0,0,0);
	Branch* S15=city->AddBranch(Pue.Unit.S15.Index,0,0,0);
	Branch* Sha=city->AddBranch(Pue.Unit.Sha.Index,0,0,0);
	Branch* Vsd=city->AddBranch(Pue.Unit.Vsd.Index,0,0,0);

	Lut->Prio[brForward] = 3;	Lut->Part[brForward] = 1;	Lut->Type[brForward] = btTomahawk;
	Lut->Prio[brCenter] = 2;	Lut->Part[brCenter] = 1;	Lut->Type[brCenter] = btStorm;
	Lut->Prio[brBack] = 4;		Lut->Part[brBack] = 0;
	Lut->Formation=1;
	if(GetUnits(&Pue.Unit.S15)>100){
		Lut->Max=220;
		Lut->Type[brCenter] = btTomahawk;
	}

	S15->Prio[brForward] = 3;	S15->Part[brForward] = 2;	S15->Type[brForward] = btTomahawk;	
	S15->Prio[brCenter] = 2;	S15->Part[brCenter] = 0;	S15->Type[brCenter] = btKillers;	
	S15->Prio[brBack] = 1;		S15->Part[brBack] = 1;		S15->Type[brBack] = btStorm;
	S15->Formation=1;

	Sha->Prio[brForward] = 3;	Sha->Part[brForward] = 1;	Sha->Type[brForward] = btStorm;	
	Sha->Prio[brCenter] = 2;	Sha->Part[brCenter] = 1;	Sha->Type[brCenter] = btKillers;	
	Sha->Prio[brBack] = 0;		Sha->Part[brBack] = 0;

	Vsd->Prio[brForward] = 3;	Vsd->Part[brForward] = 1;	Vsd->Type[brForward] = btKillers;	
	Vsd->Prio[brCenter] = 2;	Vsd->Part[brCenter] = 1;	Vsd->Type[brCenter] = btKillers;	
	Vsd->Prio[brBack] = 0;		Vsd->Part[brBack] = 0;

	// Units in buildings
	city->NStrelok = 5;
	if(GetUnits(&Pue.Unit.S15)>80) city->NStrelok = 15;
	if(GetUnits(&Pue.Unit.S15)>160) city->NStrelok = 10;
	city->NUnits = 2;
	//if(GetUnits(&Pue.Unit.Lut)>150&&GetUnits(&Pue.Unit.Lut)<200||GetUnits(&Pue.Unit.S15)>100) city->NUnits = 15;
	city->PKrepost=0;

	// Units
	int MaxKri=0;
	{
		MaxKri=70;
		if(UpgIsRun(&Pue.Upg.FoodMel2)||GetMoney(FOOD)>12000||UpgIsRun(&Pue.Upg.FieldCen10)) MaxKri=GetUnits(&Pue.Build.Gor)*130;

		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);
		TryUnit(&Pue.Unit.Kri, MaxKri, 5, 100);

		if(MaxKri>70||GetPeaceTimeLeft()<2){
			if(!UpgIsRun(&Pue.Upg.S15Build3)){
				TryUnit(&Pue.Unit.Lut, 10000, 20, 100);
				TryUnit(&Pue.Unit.Lut, 10000, 20, 90);
				TryUnit(&Pue.Unit.Lut, 10000, 20, 80);
			}
			TryUnit(&Pue.Unit.Lut, 10000, 20, 70);
			TryUnit(&Pue.Unit.Lut, 10000, 20, 60);			

			if(UpgIsRun(&Pue.Upg.S15Build3)) TryUnit(&Pue.Unit.S15, 10000, 20, 100);
			if(UpgIsRun(&Pue.Upg.S15Build2)) TryUnit(&Pue.Unit.S15, 10000, 20, 60);
			if(UpgIsRun(&Pue.Upg.S15Build1)) TryUnit(&Pue.Unit.S15, 10000, 20, 60);
			TryUnit(&Pue.Unit.S15, 10000, 20, 30);
			
			if(GetUnits(&Pue.Unit.Sha)<10)TryUnit(&Pue.Unit.Sha, 10000, 20, 5);
			if(GetUnits(&Pue.Unit.Vog)<10) TryUnit(&Pue.Unit.Vog, 10000, 20, 100);
			TryUnit(&Pue.Unit.Vsd, 10000, 20, 70);
			TryUnit(&Pue.Unit.Vsd, 10000, 20, 60);
		}
	}

	// Buildings
	{
		TryUnit(&Pue.Build.Mel, 1, 100, 95);
		if(GetReadyUnits(&Pue.Build.Mel)) TryUnit(&Pue.Build.Gor, 2, 100, 70);
		if(GetReadyUnits(&Pue.Build.Gor)){
			TryUnit(&Pue.Build.Skl, 1, 100, 60);
			TryUnit(&Pue.Build.Mel, 2, 100, 70);
			if(GetMoney(FOOD)>12000||UpgIsRun(&Pue.Upg.FoodMel2)) TryUnit(&Pue.Build.Pst, 3, 100, 70);
			//TryUnit(&Pue.Build.Ver, 1, 100, 70);
			// Max
			if(MaxKri>70&&GetUnits(&Pue.Build.Gor)>1){
				TryUnit(&Pue.Build.Mel, 3, 100, 70);
				TryUnit(&Pue.Build.Skl, 3, 100, 70);
				TryUnit(&Pue.Build.Pst, 3, 100, 70);
			}
		}
	}

	// Center
	{
		TryUpgrade(&Pue.Upg.CenStage1, 80, 100);
		TryUpgrade(&Pue.Upg.CenStage2, 80, 100);
		TryUpgrade(&Pue.Upg.CenStage3, 30, 100);		
	}

	// Food & field
	{
		TryUpgrade(&Pue.Upg.FoodMel1, 80, 100);
		TryUpgrade(&Pue.Upg.FoodMel2, 90, 100);
		if(UpgIsRun(&Pue.Upg.FieldCen10)&&GetUnits(&Pue.Build.Pst)>1){
			TryUpgrade(&Pue.Upg.FoodCen01, 100, 100);		
			TryUpgrade(&Pue.Upg.FoodCen02, 100, 100);
			TryUpgrade(&Pue.Upg.FoodCen03, 100, 100);
		}

		TryUpgrade(&Pue.Upg.FieldCen10, 100, 100);	// 2000
		//TryUpgrade(&Pue.Upg.FieldCen52, 90, 100);	// 3000
		//TryUpgrade(&Pue.Upg.FieldCen12, 90, 100);	// 3000
	}
	
	// Wood
	{
		TryUpgrade(&Pue.Upg.Wood1, 95, 100);
		TryUpgrade(&Pue.Upg.Wood2, 95, 100);
	}

	// Mine
	if(GetReadyUnits(&Pue.Build.Gor)){
		TryUnit(&Pue.Build.Rud, 1, 100, 70);
		TryUnit(&Pue.Build.Stn, 1, 100, 70);
		if(MaxKri>70){
			TryUnit(&Pue.Build.Rud, 2, 100, 70);
			TryUnit(&Pue.Build.Stn, 2, 100, 70);
			TryUnit(&Pue.Build.Coa, 1, 100, 70);
			TryUnit(&Pue.Build.Iro, 1, 100, 70);
			
			if(GetDifficulty()>1){
				//TryUpgrade(&Pue.Upg.Gld0, 95, 100);
				//TryUpgrade(&Pue.Upg.Gld1, 95, 100);
				//TryUpgrade(&Pue.Upg.Gld2, 95, 100);
				//TryUpgrade(&Pue.Upg.Gld3, 95, 100);
				TryUpgradeEx(&Pue.Upg.Stn0, 100, 100, 9000, 4000);
				TryUpgradeEx(&Pue.Upg.Stn1, 100, 100, 6000, 1000);
				//TryUpgrade(&Pue.Upg.Stn2, 100, 100);
				//if(UpgIsRun(&Pue.Upg.EnDo1)){
					//TryUpgrade(&Pue.Upg.Gld4, 100, 100);
					//TryUpgrade(&Pue.Upg.Gld5, 100, 100);
					//TryUpgrade(&Pue.Upg.Stn3, 100, 100);
					//TryUpgrade(&Pue.Upg.Stn4, 90, 100);
					//TryUpgrade(&Pue.Upg.Stn5, 90, 100);
				//}
				
				//TryUpgrade(&Pue.Upg.Iro0, 90, 100);
				//TryUpgrade(&Pue.Upg.Iro1, 80, 100);
				
				//TryUpgrade(&Pue.Upg.Iro2, 70, 100);
				//TryUpgrade(&Pue.Upg.Coa0, 90, 100);
				//TryUpgrade(&Pue.Upg.Coa1, 80, 100);
				//TryUpgrade(&Pue.Upg.Coa2, 70, 100);
			}
		}
	}

	// Market
	if(GetReadyUnits(&Pue.Build.Pst)){
		//PrepareUpgrade(AiNat,GOLD,STONE,&Pue.Upg.
		
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

		if(IR<1000&&GR>1000){
			AI_Torg(GOLD,IRON,1000);
		}
		if(CR<1000&&GR>1000){
			AI_Torg(GOLD,COAL,1000);
		}

		if(GetUnits(&Pue.Build.Gor)<2){
			int NeedST = GetUnitCost(AiNat,&Pue.Build.Gor,STONE)-GetMoney(STONE);
			int NeedGL = GetSellAmount(GOLD, STONE, NeedST);
			if(NeedST>3000&&GR>NeedGL){
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(GOLD,STONE,NeedGL);
			}
			/*
			int NeedFD = GetSellAmount(FOOD, STONE, NeedST);
			if(NeedST>3000&&FR>NeedFD){
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(STONE,GOLD,100);
				AI_Torg(GOLD,STONE,NeedGL);
			}
			*/
		}

		PrepareUpgrade(AiNat,FOOD,COAL,&Pue.Upg.S15Enable);

	}	

	// Peasat distribution
	int NU=GetUnits(&Pue.Unit.Kri);
	if(NU){ //500
		if(GetReadyUnits(&Pue.Build.Mel)){
			city->MinFermers = NU/3;
			if(NU>100&&UpgIsRun(&Pue.Upg.FoodMel2)) city->MinFermers=NU/2-20;
			if(city->MinFermers>300) city->MinFermers = 300;
		}
		if(GetUnits(&Pue.Build.Skl)){
			city->MinWooders = NU/4;
			if(NU>100) city->MinWooders=NU/2-40;
			if(city->MinWooders>200) city->MinWooders = 200;
		}
	}

	if(GetDifficulty()>0) WarriorsUpg(Lut->Min>200);

	// Enable warriors
	TryUpgrade(&Pue.Upg.S15Enable, 100, 100);	

}

void WarriorsUpg(bool EnHorce){
	
	int AiNat=GetAINation();
	
	// Warriors
	{
		if(GetUnits(&Pue.Unit.S15)>30 || GetUnits(&Pue.Unit.Vsd)>30) TryUpgrade(&Pue.Upg.WarDamage1, 80, 100);
		if(GetUnits(&Pue.Unit.Lut)>30) TryUpgrade(&Pue.Upg.WarLife1, 80, 100);
	}

	// Lut
	{
		if(GetUnits(&Pue.Unit.Lut)>30){
			TryUpgrade(&Pue.Upg.LutRazbros1, 80, 100);
			if(GetUnits(&Pue.Build.Gor)>1) TryUpgrade(&Pue.Upg.LutRazbros2, 80, 100);
			TryUpgrade(&Pue.Upg.LutLife1, 80, 100);
		}
		TryUpgrade(&Pue.Upg.LutBuild1, 80, 100);
		if(GetUnits(&Pue.Build.Gor)>1){
			TryUpgrade(&Pue.Upg.LutBuild2, 80, 100);
			TryUpgrade(&Pue.Upg.LutBuild3, 80, 100);
		}
	}

	// S15
	{	

		TryUpgrade(&Pue.Upg.S15Build1, 90, 100);
		TryUpgrade(&Pue.Upg.S15Build2, 90, 100);
		TryUpgrade(&Pue.Upg.S15Build3, 90, 100);

		if(GetUnits(&Pue.Unit.S15)>50){
			TryUpgrade(&Pue.Upg.S15Att, 80, 100);
			TryUpgrade(&Pue.Upg.S15Att3, 80, 100);
			TryUpgrade(&Pue.Upg.S15Att4, 80, 100);
			TryUpgrade(&Pue.Upg.S15Att5, 80, 100);
			TryUpgrade(&Pue.Upg.S15Att6, 80, 100);
			TryUpgrade(&Pue.Upg.S15Att7, 20, 100);
			TryUpgrade(&Pue.Upg.S15Def, 80, 100);
			TryUpgrade(&Pue.Upg.S15Def3, 80, 100);
			TryUpgrade(&Pue.Upg.S15Def4, 80, 100);
			TryUpgrade(&Pue.Upg.S15Def5, 80, 100);
			TryUpgrade(&Pue.Upg.S15Def6, 20, 100);
			TryUpgrade(&Pue.Upg.S15Def7, 20, 100);
			if(GetUnits(&Pue.Build.Gor)>1){
				TryUpgrade(&Pue.Upg.S15Att7, 100, 100);
				TryUpgrade(&Pue.Upg.S15Def6, 100, 100);
				TryUpgrade(&Pue.Upg.S15Def7, 100, 100);
			}
		}
	}

	// Vsd
	{
		if(GetUnits(&Pue.Unit.S15)>60&&EnHorce){
			//TryUpgrade(&Pue.Upg.CenStage4, 80, 100);
			//TryUpgrade(&Pue.Upg.VsdBuild1, 80, 100);
		}
	}

	// Sha
	if(GetUnits(&Pue.Build.Gor)>1){
		if(GetUnits(&Pue.Unit.Sha)>30) TryUpgrade(&Pue.Upg.ShaLife1, 80, 100);
		TryUpgrade(&Pue.Upg.ShaMedik1, 80, 100);
		TryUpgrade(&Pue.Upg.ShaBuild1, 80, 100);
	}

	// Vog
	{
		TryUpgrade(&Pue.Upg.VogEnable, 80, 100);
	}

}

void WaterScript(){	

	int AiNat = GetAINation();	
	AICity* city = Village + AiNat;

	int NU=GetUnits(&Pue.Unit.S15)+GetUnits(&Pue.Unit.Lut)+city->NFirers;
	
	if(GetUnits(&Pue.Build.Skl)) TryUnit(&Pue.Build.Ver,1,100,90);
	if(GetUnits(&Pue.Build.Gor)>1) TryUnit(&Pue.Build.Ver,3,60,60);

	int NPar=1+NU/100;
	if(NPar>5) NPar=5;
	if(NU>50) TryUnit(&Pue.Unit.Par, NPar, 100, 100);

	TryUnit(&Pue.Unit.Ka1, 4, 100, 100);
	if(TryUnit(&Pue.Unit.Ka1, 10, 10, 100)){
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
		TryUnit(&Pue.Unit.Ka1, 10, 100, 100);
	}
	
	TryUnit(&Pue.Unit.Ka3, 4, 100, 100);
	if(UpgIsRun(&Pue.Upg.Ka3Build6)){
		TryUnit(&Pue.Unit.Ka3, 20, 100, 100);
	}

	TryUpgrade(&Pue.Upg.ParSpeed1,100,100);
	TryUpgrade(&Pue.Upg.ParSpeed2,100,100);
	TryUpgrade(&Pue.Upg.ParSpeed3,100,100);
	TryUpgrade(&Pue.Upg.ParSpeed4,100,100);
	TryUpgrade(&Pue.Upg.ParSpeed5,100,100);
	TryUpgrade(&Pue.Upg.ParSpeed6,100,100);

	TryUpgrade(&Pue.Upg.Ka3Build1,100,100);
	TryUpgrade(&Pue.Upg.Ka3Build2,100,100);
	TryUpgrade(&Pue.Upg.Ka3Build3,100,100);
	TryUpgrade(&Pue.Upg.Ka3Build4,100,100);
	TryUpgrade(&Pue.Upg.Ka3Build5,100,100);
	TryUpgrade(&Pue.Upg.Ka3Build6,100,100);

	if(GetUnits(&Pue.Unit.Ka1)>3){
		TryUpgrade(&Pue.Upg.Ka1Fishing1,100,100);
		TryUpgrade(&Pue.Upg.Ka1Fishing2,90,100);
		TryUpgrade(&Pue.Upg.Ka1Fishing3,80,100);
		TryUpgrade(&Pue.Upg.Ka1Fishing4,70,100);
		TryUpgrade(&Pue.Upg.Ka1Fishing5,60,100);
		TryUpgrade(&Pue.Upg.Ka1Fishing6,70,100);
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