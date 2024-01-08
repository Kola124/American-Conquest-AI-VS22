#define CONQUEST
#include "..\..\Import.h"
#include "..\MayNation.h"

GAMEOBJ GFood;
GAMEOBJ GWood;
GAMEOBJ GMine;
GAMEOBJ GGuard;
GAMEOBJ GBuild;

GAMEOBJ GUnitsCollect;
GAMEOBJ GFreeKri;

GAMEOBJ Construct;
Spirit NewBld;

Spirit Kre0;
GAMEOBJ GKre0;

Spirit Gold[2];
GAMEOBJ GGold[2];
Spirit Stone[2];
GAMEOBJ GStone[2];

int Food2dom;
bool n3dom;
int Food0;
int Wood0;
bool LockBuild;

int AiNat;

DLLEXPORT
void InitAI(){
	AiNat = GetAINation();

	//RegisterDynGroup(&GUnitsCollect);
	//Register

	RegisterDynGroup(GStone);
	RegisterDynGroup(GStone+1);

	RegisterDynGroup(&GFood);
	RegisterDynGroup(&GWood);
	RegisterDynGroup(&GMine);
	RegisterDynGroup(&GGuard);
	RegisterDynGroup(&GBuild);
	RegisterDynGroup(&Construct);

	RegisterDynGroup(&GKre0);

	SetBuildingsCollector(AiNat, &Construct);
	SetUnitsCollector(AiNat, &GGuard);

	// запись стартовых крестьян	
	SelectUnitsType(&May.Unit.Kri, AiNat, 1);
	SaveSelectedUnits(AiNat, &GBuild, 0);
	ClearSelection(AiNat);

	int n=GetNUnits(&GBuild);

	SGP_TakeResources(&GFood, 0, AiNat, FOOD);
	SGP_TakeResources(&GWood, 0, AiNat, WOOD);

	Food0 = 20;
	Food2dom = 5;
	n3dom = false;
	Wood0 = 10;
	LockBuild = true;

};

DLLEXPORT
void ProcessAI(){
	AiNat = GetAINation();
		
	word kri = May.Unit.Kri.Index;
	word gld = May.Build.Rud.Index;
	word stn = May.Build.Stn.Index;
	//word gld = May.Build.Rud.Index;

	if(Stone[0].Alive()){
		CleanGroup(GStone);
		CleanGroup(&GGuard);
		CollectUnits(&GStone[0], &GGuard, kri, GetMaxInsideAmount(Stone[0].Index));
	}
	if(Stone[1].Alive()){
		//ReorderUnits(&GStone[1], &GGuard, kri, 2);
		//CollectUnits(&GStone[1], &GGuard, kri, GetMaxInsideAmount(Stone[1].Index));		
	}

	//TryUnit(&May.Build.Iro, 20, 100, 100);
	//TryUnit(&May.Build.Coa, 20, 100, 100);
	TryUnit(&May.Build.Stn, 2, 100, 100);
	//TryUnit(&May.Build.Rud, 1, 80, 100);
	TryUnit(&May.Build.Cen, 1, 100, 100);
	TryUpgrade(&May.Upg.CEN10MA, 90, 100);
	TryUpgrade(&May.Upg.EnDo2, 90, 100);
	TryUnit(&May.Build.Do2, 4, 100, 100);


	// скрипт
	TryUnit(&May.Build.Mel, 1, 100, 100);
	if(GetReadyUnits(&May.Build.Mel)){
		TryUpgrade(&May.Upg.Mel_GETRES, 80, 100);
		TryUnit(&May.Build.Kre, 1, 100, 100);
		TryUnit(&May.Build.Do3, 3, 100, 100);
	}
	if(Food0==0 && Wood0>0){
		LockBuild = false;
		TryUnit(&May.Build.Skl, 1, 100, 100);
		if(NewBld.Alive()) ReorderUnits(&GBuild, &GGuard, May.Unit.Kri.Index, 1);
		ReorderUnits(&GKre0, &GGuard, May.Unit.Kri.Index, 2);
	}
	if(GetReadyUnits(&May.Build.Mel)==2 && GetReadyUnits(&May.Build.Do3)==4){
		//TryUpgrade(&May.Upg.
		int n = GetNUnits(&GGuard);
		if(n>3){
			ReorderUnits(&GFood, &GGuard, May.Unit.Kri.Index, 1);
			ReorderUnits(&GKre0, &GGuard, May.Unit.Kri.Index, 3);
		}

	}else
	if(Food0==0 && Wood0==0){
		TryUnit(&May.Build.Mel, 2, 100, 100);
		TryUnit(&May.Build.Do3, 4, 100, 100);
		if(NewBld.Alive()) ReorderUnits(&GBuild, &GGuard, kri, 2);
		ReorderUnits(&GKre0, &GGuard, kri, 4);
	}
	TryUpgrade(&May.Upg.EnLut, 80, 100);
	
	// юниты
	TryUnit(&May.Unit.Kri, 1000, 20, 100);
	if(GetReadyUnits(&May.Build.Kre)){
		TryUnit(&May.Unit.Pik, 1000, 10, 100);
		TryUnit(&May.Unit.Lut, 1000, 10, 100);
	}

	// 5 стартовых на поля
	if(GetReadyUnits(&May.Build.Do3)==2){
		while(Food2dom>0){
			OneUnit uni;
			GetUnitInfo(&GBuild, 0, &uni);
			if(uni.Index!=0xFFFF){
				InsertUnitToGroup(&GFood, uni.Index);
				RemoveUnitFromGroup(&GBuild, 0);
				Food2dom--;
			}
		}
	}
	// стартовые рабочие на поля
	if(GetReadyUnits(&May.Build.Do3)==3 && !n3dom){
		RemoveGroup(&GBuild, &GFood);
		n3dom = true;
	}
	// 20 рабочих на поля из домиков
	int n = GetNUnits(&GGuard);
	while(Food0>0 && n>0){
		n--;
		OneUnit uni;
		GetUnitInfo(&GGuard, n, &uni);
		if(uni.Index!=0xFFFF && uni.NIndex==May.Unit.Kri.Index){
			InsertUnitToGroup(&GFood, uni.Index);
			RemoveUnitFromGroup(&GGuard, n);
			Food0--;			
		}		
	}
	if(Wood0>0 && GetReadyUnits(&May.Build.Skl)){
		Wood0 -= ReorderUnits(&GWood, &GGuard, May.Unit.Kri.Index, Wood0);		
	}
	//
	n = GetNUnits(&GWood);
	n = GetNUnits(&GBuild);
	n = GetNUnits(&Construct);

	// постройка зданий
	GAMEOBJ* gcon = &Construct;	
	int newid = 0xFFFF;

	CleanGroup(gcon);
	int i = GetNUnits(gcon);
	while(i>0){
		i--;
		OneUnit con;
		GetUnitInfo(gcon, i, &con);		
		word index = con.Index;
		word nindex = con.NIndex;
		if(con.Stage==con.MaxStage){
			if(nindex==May.Build.Kre.Index){
				Kre0.SetLink(index);
				SGP_ComeIntoBuilding(&GKre0, 0, index);
			}
			if(nindex==stn){
				if(!Stone[0].Alive()){
					Stone[0].SetLink(index);
					SGP_ComeIntoBuilding(GStone, 0, index);
				}else
				if(!Stone[1].Alive()){
					Stone[1].SetLink(index);
					SGP_ComeIntoBuilding(GStone+1, 0, index);
				}
			}
			DeleteUnitFromGroup(gcon, i);
			if(NewBld.Equal(index)) NewBld.Clear();
		}else{
			if(!NewBld.Alive()){
				newid = index;
			}
		}
	}
	if(newid!=0xFFFF){
		SGP_RepairBuilding(&GBuild, 1, newid);
		NewBld.SetLink(newid);		
	}
	if(NewBld.Alive()){
		//GetGlobalIndex
		CollectUnits(&GBuild, &GGuard, kri, 20);
	}
	if(GetNUnits(gcon)==0 && !LockBuild){
		RemoveGroup(&GBuild, &GGuard);
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

	// собираем бездельников в GGuard
	/*
	ClearSelection(AiNat);
	SelectUnitsType(&May.Unit.Kri, AiNat, 0);
	SaveSelectedUnits(AiNat, &GGuard, 0);
	int i = GetNUnits(&GGuard);
	while(i>0){
		i--;
		OneUnit uni;
		GetUnitInfo(&GGuard, i, &uni);
		if(uni.Index!=0xFFFF){
			UnitExCaps exu;
			GetUnitExCaps(uni.Index, &exu, 1);
			if(exu.OrderType!=-1) RemoveUnitFromGroup(&GGuard, i);
		}else
			RemoveUnitFromGroup(&GGuard, i);
	}
	*/
