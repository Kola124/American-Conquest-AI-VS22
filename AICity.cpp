// AICity.cpp: implementation of the AICity class.
//
//////////////////////////////////////////////////////////////////////

#define CONQUEST
#include <malloc.h>
#include <crtdbg.h>
#include <assert.h>

#include "import.h"
#include "AICity.h"

AICity Village[8];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AICity::AICity()
{
	memset(this,0,sizeof(*this));
	NatID=-1;

	Peasant = 0xFFFF;
	StartRes=true;

	CannonNIndex=0xFFFF;
	FirersType=0xFFFF;
	PsKillType=0xFFFF;

	MaxDuzers = 5;
	NeedHunt=3;

	NIndexBrb=0xFFFF;
	NIndexOff=0xFFFF;
	NIndexFlg=0xFFFF;
	NIndexMoff = 0xFFFF;


	HuntNIndex=0xFFFF;

	memset(Meat,0xFF,sizeof(Meat));
	memset(Farm,0xFF,sizeof(Farm));
	MeatEnabled=false;

	CoolHuntNIndex=0xFFFF;

	// House deffenders
	InDefNIndex=0xFFFF;

	//ParomNIndex=0xFFFF;
	//ParomIndex=0xFFFF;
	ParomIsArrive=false;
	
}

AICity::~AICity()
{	
	AIFree();
}

void AICity::AIFree()
{	
	assert(_CrtCheckMemory());
	if(HUNTERS){
		free(HUNTERS);
		HUNTERS=NULL;
		NHunters=0;
	}
	for(int i=0;i<NBranch;i++){
		GAMEOBJ* def=BRANCH[i].DefTopGrp;
		if(def){
			free(def);
			BRANCH[i].DefTopGrp=NULL;
		}
	}
	if(BRANCH){
		free(BRANCH);
		BRANCH=NULL;
		NBranch=0;
	}

	if(DefTop){
		free(DefTop);
		DefTop=NULL;
	}
	if(EnmAgrTopGrp){
		free(EnmAgrTopGrp);
		EnmAgrTopGrp=NULL;
	}

	memset(this,0,sizeof(*this));
	NatID=-1;
	assert(_CrtCheckMemory());
}

DLLEXPORT
void FreeAICityData(byte NI){
	AICity* city=Village+NI;	
	city->AIFree();
}

void AICity::Init(byte NI)
{
	NatID = NI;
}


void AICity::Process()
{
	if(NatID==-1) return;

	if(!StartArmy){
		StartArmy=1;
		
		// Dynamic groups
		RegisterDynGroup(&Paroms);		

		RegisterDynGroup(&iGuardGrp);
		RegisterDynGroup(&iGuardLut);
		RegisterDynGroup(&iGuardStr);

		RegisterDynGroup(&Firers);
		RegisterDynGroup(&PsKill);	
		RegisterDynGroup(&Tomahawks);

		RegisterDynGroup(&Baraban);
		RegisterDynGroup(&Officer);
		RegisterDynGroup(&Flag);
		RegisterDynGroup(&MOfficer);

		RegisterDynGroup(&Squad);
		RegisterDynGroup(&HuntGroup);	

		RegisterDynGroup(&AnimKill);

		RegisterDynGroup(&ArmHunt);
		RegisterDynGroup(&ArmFood);
		RegisterDynGroup(&ArmWood);

		RegisterDynGroup(&CoolHuntGroup);

		for(int i=0; i<6; i++) RegisterDynGroup(Gu + i);		

		RegisterDynGroup(&Cannons);

		RegisterDynGroup(&NewUnits);
		RegisterDynGroup(&NewHouses);

		RegisterDynGroup(&Free);
		RegisterDynGroup(&Militia);
		RegisterDynGroup(&Fire);

		RegisterDynGroup(&MainArmy);
		
		RegisterDynGroup(&Fermers);	
		RegisterDynGroup(&Wooders);

		RegisterDynGroup(&DesantArchers);
		RegisterDynGroup(&DesantStrelki);
		RegisterDynGroup(&DesantWarriors);

		RegisterDynGroup(&DesantIn);
		RegisterDynGroup(&DesantOut);

		int NZ=GetNZones();	

		DefTop=(word*)malloc(NZ<<1);
		memset(DefTop,0,NZ<<1);

		EnmAgrTopGrp=(GAMEOBJ*)malloc(sizeof(GAMEOBJ)*NZ);
		for(int z=0;z<NZ;z++) RegisterDynGroup(EnmAgrTopGrp+z);

		// Water AI
		AssignDesantStartGroup(NatID,&DesantIn);
		AssignDesantDestGroup(NatID,&DesantOut);
		// Collectors
		SetUnitsCollector(NatID, &NewUnits);
		SetBuildingsCollector(NatID, &NewHouses);		
		// Friend AI with tribes
		int x,y;
		if(GetGrpCenter(&NewUnits,&x,&y)){
			SetAIForDiplo(NatID,x,y);
		}
		// Assign economy group
		SGP_TakeResources(&HuntGroup, 0, NatID, 8);
		SGP_TakeResources(&Fermers, 0, NatID, FOOD);
		SGP_TakeResources(&Wooders, 0, NatID, WOOD);
	}

	// setting the number of units in the transfer vessel to start expansion
	int NPassanger=250;
	/*
	for(int i=0;i<NBranch;i++){
		Branch* brn=BRANCH+i;
		
		GAMEOBJ PT;
		PT.Index=brn->NIndex;
		PT.Serial=0;
		PT.Type='UTYP';

		if(GetUnits(&PT)) NPassanger+=brn->Min-1;
	}
	
	if(NFirers>NPassanger) NPassanger=NFirers;

	if(NPassanger>250) NPassanger=250;
	*/
	if(NPassanger) SetMaxInTransport(NatID,NPassanger);

	// build a ferry
	//OneObject* PO=GetOBJ(ParomIndex);
	//if(PO->Index==0xFFFF || PO->Serial!=ParomSerial || PO->DestX<0) ParomIndex=0xFFFF;	

	// Read the life of ferries
	if(ParomNIndex!=0xFFFF) RemoveNUnits(&Paroms,&NewUnits,1000,ParomNIndex);

	int NPar=CleanGroup(&Paroms);
	for(int i=0;i<NPar;i++){
		OneUnit PU;
		GetUnitInfo(&Paroms,i,&PU);
		if(PU.Index!=0xFFFF&&PU.MaxLife<65000){
			OneObject* PO=GetOBJ(PU.Index);
			PO->MaxLife=65000;
			PO->Life+=64950;
		}
	}	
	
	/*
	int Diff=GetDifficulty();
	switch(Diff){
	case 2:
		if(GetMoney(FOOD)<200) AddResource(NatID,FOOD,500);
		break;
	case 3:
		if(GetMoney(FOOD)<200) AddResource(NatID,FOOD,1000);
		break;
	default:
		if(GetMoney(FOOD)<10) AddResource(NatID,FOOD,10);
		break;		
	};
	*/

	// sowing the fields
	/*
	DWORD curt=GetGlobalTime();
	if(curt>TimeNextField){
		TimeNextField=curt+500;
		CreateFields(NatID);
	}
	*/

	// delete hidden
	DeleteHiddenUnits(&Fermers);
	DeleteHiddenUnits(&Wooders);
	DeleteHiddenUnits(&Free);
	DeleteHiddenUnits(&HuntGroup);

	// collect own units
	int NNew=CleanGroup(&NewUnits);
	int NFree=CleanGroup(&Free);

	CleanGroup(&Militia);
	CleanGroup(&Fire);

	if(NIndexBrb!=0xFFFF) RemoveNUnits(&Baraban,&NewUnits,1000,NIndexBrb);
	if(NIndexOff!=0xFFFF) RemoveNUnits(&Officer,&NewUnits,1000,NIndexOff);
	if(NIndexFlg!=0xFFFF) RemoveNUnits(&Flag,&NewUnits,1000,NIndexFlg);
	if(NIndexMoff!=0xFFFF) RemoveNUnits(&MOfficer, &NewUnits, 1000, NIndexMoff);
	if(CannonNIndex!=0xFFFF) RemoveNUnits(&Cannons,&NewUnits,1000,CannonNIndex);


	int NHunt=CleanGroup(&HuntGroup);
	if(HuntNIndex!=0xFFFF && NHunt<MinHuters && rando()<8000){
		RemoveNUnits(&HuntGroup,&NewUnits,1,HuntNIndex);
		RemoveNUnits(&HuntGroup,&Free,1,HuntNIndex);
	}

	//cool hunters

	int NCoolHunt=CleanGroup(&CoolHuntGroup);	
	//SelectUnits(&CoolHuntGroup,0);
	if(CoolHuntNIndex!=0xFFFF && !NCoolHunt){
		RemoveNUnits(&CoolHuntGroup, &NewUnits, 1, CoolHuntNIndex);
	}

	RemoveNUnits(&Free, &NewUnits, GetNUnits(&NewUnits), Peasant);
	
	// collect own buildings	

	GAMEOBJ* build = &NewHouses;
	int N = CleanGroup(build);
	for(int i=0; i<N; i++){
		OneUnit bu;
		GetUnitInfo(build, i, &bu);
		if(bu.Index!=0xFFFF){
			// the house was won back
			bool find=false;
			for(int h=0; h<NHOUSES; h++){
				AIBuild* dom = House + h;
				
				OneObject* DO=GetOBJ(bu.Index);
				if(DO && !DO->Sdoxlo && DO->Serial==dom->Unit.Serial){
					DeleteUnitFromGroup(build, i);
					find=true;
					break;
				}
			}

			
			if(!find){			
				
				if(bu.Stage && bu.Stage>(bu.MaxStage>>3)){
					// an enemy building was captured
					OneObject* BO=GetOBJ(bu.Index);
					int NIn=GetDifficulty()<<1;
					if(BO&&!BO->InFire&&BO->NInside<NIn) DieUnit(bu.Index);
					DeleteUnitFromGroup(build, i);
				}else{
					// set autoignition
					OneObject* BO=GetOBJ(bu.Index);
					if(BO){
						BO->AutoKill=0;
						int ak=GetDifficulty()-GetRND(2);
						if(ak>0) BO->AutoKill=1;
					}
					// new stock
					for(int h=0; h<NHOUSES; h++){
						AIBuild* dom = House + h;
						OneObject* BO=GetOBJ(dom->Unit.Index);
						if(dom->Unit.Index==0xFFFF || BO&&(BO->Serial>>1)!=(dom->Unit.Serial>>1)){
							int NBuil=0;
							switch(bu.Usage){
							case MineID:
								NBuil=5;
								break;
							case DiplomatID:
								//NBuil=20;
								break;
							case SkladID:
								//NBuil=5;
								break;
							case TowerID:
								//NBuil=10;
								break;
							};
							dom->Init(bu.Index, NBuil, bu.Usage);
							//InsertUnitToGroup(build,&AIPlayer[NatID].NewBld,i);
							DeleteUnitFromGroup(build, i);
							break;
						}
					}
				}
			}
		}
	}

	rando();
	Tactica();
	rando();
	Economica();
	rando();

	rando();
	ProcessHunter();
	rando();
	CrewProcess();
	rando();

}

void AICity::Economica(){

	int NFers=CleanGroup(&Fermers);
	int NWods=CleanGroup(&Wooders);

	int NeedFood=MinFermers-NFers;
	int NeedWood=MinWooders-NWods;

	//SelectUnits(&Fermers,0);
	//ClearGroup(&Fermers);

	int NHunt=CleanGroup(&HuntGroup);
	if(HuntNIndex!=0xFFFF && HuntNIndex==Peasant && NHunt<MinHuters && rando()<3000){
		if(NeedFood<0) RemoveNUnits(&HuntGroup,&Fermers,1,HuntNIndex);
		if(NeedWood<0) RemoveNUnits(&HuntGroup,&Wooders,1,HuntNIndex);
	}
	
	// food & wood distribution
	if(NeedFood>NeedWood && NeedFood>0 && NFers<300) RemoveNUnits(&Fermers, &Free, 1);
		else if(NeedWood>0) RemoveNUnits(&Wooders, &Free, 1);
	
	// svobodnie mesta, perenaselenie

	int FreeUnitPlace = GetMaxUnits(NatID) - GetCurrentUnits(NatID);

	// center of base (first building)
	int cx=-1;
	int cy=-1;

	// building

	for(int h=0; h<NHOUSES; h++){
		AIBuild* dom = House + h;
		OneObject* BO=GetOBJ(dom->Unit.Index);
		if(BO && (dom->Unit.Serial>>1)==(BO->Serial>>1)){
			
			DeleteHiddenUnits(&dom->Invaters);				
			
			OneUnit du;
			GetUnitGlobalInfo(dom->Unit.Index, &du);
			int NDuz=CleanGroup(&dom->Duzers);
			int NFermers = GetNUnits(&Fermers);
			NWods=GetNUnits(&Wooders);

			GAMEOBJ* GrpDuz=&dom->Duzers;

			if(dom->Unit.Alive()){
				if(dom->UnderConst){
					// construction
					
					//if(BO->Index==108){
					//	SelectUnits(&dom->Duzers,0);
					//}
					if(du.Stage==du.MaxStage){
						
						// setting the center of the base
						if(cx>0){
							cx=du.x;
							cy=du.y;
						}

						// completed or lost
						dom->UnderConst = false;
						
						if(dom->Usage==MineID){	
							// get workers
							int InMax = GetMaxInsideAmount(BO->Index);							
							RemoveNUnits(&dom->Invaters, &dom->Duzers, InMax);
						}/*else{
							// start a defense
							int InMax = GetMaxInsideAmount(BO->Index)-GetNUnits(&dom->Invaters);
							int dif=GetDifficulty();
							if(dif<2) InMax>>=2-dif;
							
						}*/
						OneObject* BO=GetOBJ(dom->Unit.Index);
						if(BO){
							int index=dom->Unit.Index;
							int bx=BO->RealX>>4;
							int by=BO->RealY>>4;
							int TZ=GetTopZone(bx,by);
							if(TZ<=0xFFFE){
								for(int i=0;i<NBranch;i++){
									Branch* BRN=BRANCH+i;
									GAMEOBJ* Group=&BRN->DefTopGrp[TZ];
									RemoveNUnits(Group, &dom->Guard, 1000, BRN->NIndex);
								}
							}
						}
						RemoveGroup(&dom->Duzers, &Free);
						RemoveGroup(&dom->Guard, &NewUnits);
						
					}else{
						// not completed

						//if(dom->Duzers.Index==4540) SelectUnits(&dom->Duzers,0);
						if(NDuz<dom->NConstructs && !RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000)){
							if(NeedWood<0&&NWods>5 || NWods>10){
								RemoveNearestUnit(&Wooders, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 5000);
							}
							RemoveNearestNotBusyUnit(&Wooders, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							if(NeedFood<20 && NFers>16 || NFers>8 && GetMoney(FOOD)>8000){
								RemoveNearestUnit(&Fermers, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 5000);
							}
							RemoveNearestNotBusyUnit(&Fermers, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							if(FreeUnitPlace<=0 && GetResource(NatID, FOOD)>2000 && NDuz<4){
								RemoveNearestUnit(&Wooders, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 5000);
								RemoveNearestUnit(&Fermers, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 5000);
							}
							if(Peasant==HuntNIndex) RemoveNearestNotBusyUnit(&HuntGroup, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 5000);
						}
						if(dom->Usage!=MineID && GetNUnits(GrpDuz)<18) RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
						SGP_RepairBuilding(&dom->Duzers,0,BO->Index);

						// Oh, it's early, the guard is on
				
						int NMax=GetMaxInsideAmount(du.Index);
						int NGuard;
						switch(du.Usage){
						case TowerID:
						case WeakID:
						case DiplomatID:
							if(NUnits) NGuard=NMax/2;
							break;
						default:
							if(NUnits) NGuard=5;
						};					
						if(CleanGroup(&dom->Guard)<NGuard){
							OneUnit u;
							for(int i=0;i<NBranch;i++){
								Branch* BRN=BRANCH+i;
								if(BRN->Domovoi&&(!dom->Pulemet||BRN->Strelok)){
									GAMEOBJ* src=&BRN->Group;								
									GetUnitInfo(src,0,&u);
									if(u.Index!=0xFFFF){
										word OID = u.Index;
										int ex,ey;
										GetBuildingEntryPoint(&ex,&ey,BO->Index,128);
										//OneObject* OB=GetOBJ();
										int x=128-GetRND(256)+ex;
										int y=128-GetRND(256)+ey;
										OBJ_SendTo(OID,x,y,128+1,0);
										InsertUnitToGroup(src, &dom->Guard, 0);
										DeleteUnitFromGroup(src, 0);
									}
								}
							}
						}					
					}
				}else{
					// repair
					if(BO->Life<BO->MaxLife && du.Stage==du.MaxStage /*&& BO->InFire*/){
						if(NDuz<dom->NDuzers){
							RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							RemoveNearestUnit(&Free, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							if(NFermers>(MinFermers>>1)||GetMoney(FOOD)>30000){
								RemoveNearestUnit(&Fermers, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							}
							if(NWods>(MinWooders>>2)){
								RemoveNearestUnit(&Wooders, &dom->Duzers, BO->RealX>>4, BO->RealY>>4, 8000);
							}
						}
						SGP_RepairBuilding(&dom->Duzers,0,BO->Index);
					}else{
						RemoveGroup(&dom->Duzers, &Free);
					}
				}
				SetToInternalResourcesZero(&dom->Duzers);
			}else{
				// the building is captured by the enemy
				if(GrpDuz->Type=='UNIT') RemoveGroup(GrpDuz,&Free);
			}
		}else{
			if(dom->Duzers.Type=='UNIT' && CleanGroup(&dom->Duzers)) RemoveGroup(&dom->Duzers,&Free);
			//RemoveNUnits(&Free,&dom->Invaters,GetNUnits(&dom->Invaters),Peasant);
			//RemoveGroup(&dom->Invaters,&NewUnits);
		}
	}

	//////////////////////////////////////////////////
	short Dang[4096];
	int Fear[256];			
	for(int j=0;j<256;j++)Fear[j]=1;
	CreateDangerMapForDef(NatID,Dang,GetNZones(),Fear,3);

	// Show in the game screen 'Q'
	
	/*
	if(NatID==1){
		int DM[2048];
		for(int d=0;d<2048;d++){
			if(Dang[d]<0) Dang[d]=0;
			DM[d]=Dang[d];
		}
		DM[0]=12345;
		SetDangerMap(DM);
	}
	*/
		
	//////////////////////////////////////////////////

	DefendAlarm=0;

	// peasant convertors

	for (int h = 0; h<NHOUSES; h++) {
		AIBuild* dom = House + h;
		OneObject* BO=GetOBJ(dom->Unit.Index);
		if(BO){
			int index=dom->Unit.Index;
			int bx=BO->RealX>>4;
			int by=BO->RealY>>4;

			GAMEOBJ* GrpIn=&dom->Invaters;

			int Frms=GetNUnits(&Fermers);
			int Wods=GetNUnits(&Wooders);

			int NIn=GetInsideAmount(index);
			int NInv=CleanGroup(GrpIn);
			int CurIn=NIn+NInv;
			int MaxIn=GetMaxInsideAmount(index);
			int dif=GetDifficulty();
			if(dif<2) MaxIn>>=2-dif;

			// the house is captured, it is necessary to fight back
			//if(BO->Index==260) SelectUnits(&dom->Invaters,0);
			if(!BO->Sdoxlo && BO->Serial!=dom->Unit.Serial && (BO->Serial|1)==(dom->Unit.Serial|1) && NInv<5){
				// set the building on fire
				if(BO&&!dom->UjePodjigali){
					//DieUnit(BO->Index);
					dom->UjePodjigali=1;
				}

				// assault by the military
				int Z=GetTopZone(bx,by);
				if(Z<0xFFFE){
					for(int i=0;i<NBranch;i++)if(CurIn<MaxIn){
						Branch* BRN=BRANCH+i;
						GAMEOBJ* grp=&BRN->DefTopGrp[Z];
						InsertUnitToGroup(grp,&dom->Invaters,0);
						CurIn++;
						DeleteUnitFromGroup(grp,0);
						//RemoveGroup(grp,&dom->Invaters);
					}
				}

				// assault with crosses??? original: shturm krestami

				if(Peasant!=0xFFFF&&GetUnitStorm(Peasant)>9){
					if(CurIn<MaxIn && !RemoveNearestUnit(&Free, &dom->Invaters, bx, by, 3000)){
						if(CurIn<MaxIn && (NFers>60||NeedFood<0) && RemoveNearestUnit(&Fermers, &dom->Invaters, bx, by, 1000)) CurIn++;
						if(CurIn<MaxIn && (NWods>40||NeedWood<0) && RemoveNearestUnit(&Wooders, &dom->Invaters, bx, by, 2000)) CurIn++;
					}else{
						CurIn++;
					}
				}
				SGP_ComeIntoBuilding(&dom->Invaters,0,index);
			}else{
				dom->UjePodjigali=0;
			}

			// the house is built
			//Tu sam mjenjao sranja tagovi Peasant, Convertor, Zamjena, Zgrade, Buildings, Change

			if(dom->Unit.Alive() && !dom->UnderConst){
				int InUnits=NUnits;
				int VeryNeedUnits=0;
				int InStrelok=NStrelok;
				int InPeasant=0;
				switch(dom->Usage){
				case MineID:
					InUnits=0;
					MaxIn=GetMaxInsideAmount(index);
					InPeasant=MaxIn;
					break;
				case DiplomatID:
					if(!dom->Pulemet) InUnits+=MaxIn*15/100;
					InStrelok+=MaxIn*15/100;
					InPeasant=PKrepost;
					if(InUnits) VeryNeedUnits=4;
					//if(BO->Index==165) SelectUnits(&dom->Invaters,0);
					break;
				case HardHorceID:
					if(!dom->Pulemet) InUnits+=MaxIn*5/100;
					InStrelok+=MaxIn*5/100;
					InPeasant=PKrepost;
					if(InPeasant>12) InPeasant=12;
					if(InUnits) VeryNeedUnits=4;
					break;
				case HorseStrelokID:
					if(!dom->Pulemet) InUnits+=MaxIn*5/100;
					InStrelok+=MaxIn*5/100;
					InPeasant=PKrepost;
					if(InPeasant>10) InPeasant=10;
					if(InUnits) VeryNeedUnits=4;
					break;
				case FastHorseID:
					if(!dom->Pulemet) InUnits+=MaxIn*5/100;
					InStrelok+=MaxIn*5/100;
					InPeasant=PKrepost;
					if(InPeasant>15) InPeasant=15;
					if(InUnits) VeryNeedUnits=4;
					break;						
				case TowerID:
				case WeakID:
					if(dom->Pulemet){
						InStrelok=MaxIn;
						//InUnits=0;
					}else{
						InUnits=MaxIn;						
					}
					VeryNeedUnits=5;
					break;					
				//default:
				};
				if(!dom->Pulemet) InStrelok=0;

				if(CurIn>MaxIn){
					RemoveNUnits(&NewUnits,&dom->Invaters,CurIn-MaxIn);
				}
				
				word OutPeasantIndex=0xFFFF;
				word OutUnitIndex=0xFFFF;
				word OutNIndex=0xFFFF;
				word OutStrIndex=0xFFFF;
				word OutStrNIndex=0xFFFF;

				int CurInUnits=0;
				int CurInStrelok=0;
				int CurInPeasant=0;

				// counting units in the building
				word* List=NULL;
				int NList=GetInsideList(index,&List);
				if(List){
					for(int i=0;i<NList;i++){
						OneObject* UO=GetOBJ(List[i]);
						word USE=GetMonUsage(UO->NIndex);
						if(UO->NIndex==Peasant){
							if(OutPeasantIndex==0xFFFF) OutPeasantIndex=UO->Index;
							CurInPeasant++;
						}else
						if(USE==StrelokID||USE==HorseStrelokID||USE==ArcherID){
							if(OutStrIndex==0xFFFF){
								OutStrIndex=UO->Index;
								OutStrNIndex=UO->NIndex;
							}
							CurInStrelok++;
							CurInUnits++;
						}else
						{
							if(OutUnitIndex==0xFFFF){
								OutUnitIndex=UO->Index;
								OutNIndex=UO->NIndex;
							}
							CurInUnits++;
						}

					}
				}

				// deffenders indoor in deffend mode
				if(BO){					

					int Z=GetTopZone(bx,by);
					if(Z<0xFFFE){
						int NEx=CleanGroup(&dom->Exiters);
						int NIn=GetInsideAmount(index);
						int NInv=CleanGroup(&dom->Invaters);

						int CurIn=NInv+NIn;
						//int MaxIn=GetMaxInsideAmount(index);
						int NeedIn=MaxIn-CurIn;

						int NEn=Dang[Z];
						if(NEn<0) NEn=0;
						if(NEn){
							//NEn+=5;
							DefendAlarm=1;
						}

						// get peasants

						int InPes=InPeasant-(CurInPeasant+GetUnitsTypeInGroup(&dom->Invaters,Peasant));
						if(InPes>NeedIn) InPes=NeedIn;
						if(InPes>0){							
							if(RemoveNearestUnit(&Free, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;
							if(InPes>0&& RemoveNearestUnit(&Free, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;
							if(InPes>0&& RemoveNearestUnit(&Free, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;
							if(InPes>0&& RemoveNearestUnit(&Free, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;
							if(InPes>0&& Peasant==HuntNIndex && RemoveNearestNotBusyUnit(&HuntGroup, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;							
							if(InPes>0&& NeedWood<10 && NWods>16 && RemoveNearestUnit(&Wooders, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000)) InPes--;
							if(InPes>0&& NeedFood<10 && NFers>24) RemoveNearestUnit(&Fermers, &dom->Invaters, BO->RealX>>4, BO->RealY>>4, 8000);
						}

						CurIn=GetInsideAmount(index)+CleanGroup(&dom->Invaters);
						//MaxIn=GetMaxInsideAmount(index);
						NeedIn=MaxIn-CurIn;

						// start a military
						int InGrp=CleanGroup(GrpIn);

						int InUn=InUnits-(CurInUnits+InGrp-GetUnitsTypeInGroup(GrpIn,Peasant));
						int InSt=InStrelok-(CurInStrelok+InGrp-GetUnitsTypeInGroup(GrpIn,Peasant));
						//if(dom->Pulemet) InUn+=NStrelok;
						
						if(InUn>NeedIn) InUn=NeedIn;
						if(InSt>NeedIn) InSt=NeedIn;

						if((InUn>0||InSt>0)&&NBranch){
							
							GAMEOBJ* moststorm_grp=NULL;
							int moststorm_n=0;
							GAMEOBJ* pulemet_grp=NULL;
							int pulemet_n=0;
							
							for(int i=0;i<NBranch;i++){
								Branch* BRN=BRANCH+i;
								if(BRN->Domovoi||InUn<VeryNeedUnits){
									GAMEOBJ* grp=&BRN->DefTopGrp[Z];
									int n=GetNUnits(grp);
									if(BRN->Strelok&&n>pulemet_n){
										pulemet_grp=grp;
										pulemet_n=n;
									}
									if(n>moststorm_n){
										moststorm_grp=grp;
										moststorm_n=n;
									}
								}
								
							}

							GAMEOBJ* src=NULL;
							if(dom->Pulemet&&pulemet_grp&&InSt>0){
								src=pulemet_grp;
							}else{
								if(!dom->Pulemet||(InUn>0&&InSt>1)) src=moststorm_grp;
							}
							
							if(src){
								OneUnit u;
								GetUnitInfo(src,0,&u);
								if(u.Index!=0xFFFF){
									InsertUnitToGroup(src, GrpIn, 0);
									DeleteUnitFromGroup(src, 0);
								}
							}
						}

						//CurIn=GetInsideAmount(index)+CleanGroup(&dom->Invaters);
						//MaxIn=GetMaxInsideAmount(index);
						//NeedIn=MaxIn-CurIn;

						// military mode: input, output of units

						InGrp=CleanGroup(GrpIn);
						CurIn=GetInsideAmount(index)+InGrp;

						CurInPeasant+=GetUnitsTypeInGroup(GrpIn,Peasant);
						CurInUnits+=InGrp-CurInPeasant;
						
						if(NEn>MaxIn) NEn=MaxIn;

						if(CurIn<NEn&&CurIn<MaxIn){
							if(dom->Usage!=MineID){
								/*
								if(!RemoveNearestUnit(&Free, &dom->Invaters, bx, by, 1000))
									if(!RemoveNearestUnit(&Wooders, &dom->Invaters, bx, by, 1000))
										RemoveNearestUnit(&Fermers, &dom->Invaters, bx, by, 1000);
								*/
								for(int i=0;i<NBranch;i++)if(CurIn<NEn){
									Branch* BRN=BRANCH+i;
									if(BRN->Domovoi){
										GAMEOBJ* grp=&BRN->DefTopGrp[Z];
										InsertUnitToGroup(grp,&dom->Invaters,0);
										DeleteUnitFromGroup(grp,0);
										CurIn++;
										//RemoveGroup(&BRN->DefTopGrp[Z],&dom->Invaters);
									}
								}
								if(CurIn<NEn && RemoveNearestUnit(&Free, &dom->Invaters, bx, by, 2000)) CurIn++;
								if(CurIn<NEn && RemoveNearestUnit(&Free, &dom->Invaters, bx, by, 2000)) CurIn++;
								if(CurIn<NEn && RemoveNearestUnit(&Free, &dom->Invaters, bx, by, 2000)) CurIn++;
								if(NWods>15 && CurIn<NEn && RemoveNearestUnit(&Wooders, &dom->Invaters, bx, by, 2000)) CurIn++;
								if(NFers>19 &&  CurIn<NEn && RemoveNearestUnit(&Fermers, &dom->Invaters, bx, by, 2000)) CurIn++;
							}
						}else{
							if(dom->Usage!=MineID && InPes<=0){
								// bring out the peasant
								if(OutPeasantIndex!=0xFFFF && CurInPeasant>(InPeasant+NEn)){
									if(OBJ_LeaveMine(index,Peasant)){
										InsertUnitToGroup(&dom->Exiters,OutPeasantIndex);
									}
								}
								// withdraw the military
								if(OutUnitIndex!=0xFFFF && CurInUnits>(InUnits+NEn) && CurInUnits>(InStrelok+NEn)){
									if(OBJ_LeaveMine(index,OutNIndex)){
										InsertUnitToGroup(&dom->Exiters,OutUnitIndex);
									}
								}

								// draw an arrow
								if(OutStrIndex!=0xFFFF && CurInStrelok>(InStrelok+NEn) && CurInStrelok>(InUnits+NEn)){
									if(OBJ_LeaveMine(index,OutStrNIndex)){
										InsertUnitToGroup(&dom->Exiters,OutStrIndex);
									}
								}
							}
						}
						//SGP_ComeIntoBuilding(&dom->InDeffend,0,index);
					}
					RemoveUpperGroundUnits(&dom->Exiters,&NewUnits);
				}
				SGP_ComeIntoBuilding(&dom->Invaters,0,index);
			}
		}
		SetToInternalResourcesZero(&dom->Invaters);
	}
	

	if((!DefendAlarm||(NeedFood+NeedWood)<0)&&GetPeaceTimeLeft()<=0&&FirersType!=0xFFFF){
		int N=CleanGroup(&Firers);
		int NF=-NeedFood>0?-NeedFood:0;
		int NW=-NeedWood>0?-NeedWood:0;
		int NFree=GetNUnits(&Free);
		if(NFirers && N+NF+NW+NFree>NFirers && (!LandType||ParomIsArrive)){
			RemoveNUnits(&Firers,&Fermers,NF,FirersType);
			RemoveNUnits(&Firers,&Wooders,NW,FirersType);
			RemoveNUnits(&Firers,&Free,NFree,FirersType);

			SetToInternalResourcesZero(&Firers);
			if(LandType){
				//RemoveGroup(&Firers,&DesantIn);
				AddIslandGuard(&Firers);
			}else{
				if(KillFromFirePerc&&KillFromFirePerc>GetRND(100)){
					AddPsKillers(&Firers,NatID);
				}else{
					AddFirers(&Firers,NatID);
				}
			}
		}
	}

	/*
	if(GetPeaceTimeLeft()<=0&&PsKillType!=0xFFFF){
		//CollectUnits(&PsKill,&AIPlayer[NatID].NewUnits,NPsKill,PsKillType);
		CollectUnits(&PsKill,&NewUnits,NPsKill,PsKillType);
		CollectUnits(&PsKill,&Free,NPsKill,PsKillType);
		int N=CleanGroup(&PsKill);
		if(N&&NPsKill&&N>=NPsKill){
			AddPsKillers(&PsKill,NatID);
		}
	}

	if(GetPeaceTimeLeft()<=0&&NTomahawk){
		//FilterUnitsByCategory(&AIPlayer[NatID].NewUnits,&Tomahawks,5);
		FilterUnitsByCategory(&NewUnits,&Tomahawks,5);
		int N=CleanGroup(&Tomahawks);
		if(N>NTomahawk){
			AddTomahawks(&Tomahawks,NatID,0,0,0);
		}
	}
	*/

	rando();
	int NFree=CleanGroup(&Free);
	if(NFree>5){
		if(MinFermers){
			if(GetRND(10)<7 && NFers<300){
				RemoveNUnits(&Fermers, &Free, 1);
			}else{
				if(MinWooders) RemoveNUnits(&Wooders, &Free, 1);
			}
			
		}else
		if(MinWooders){
			RemoveNUnits(&Wooders, &Free, 1);
		}
	}

	if(NHunt&&cx>0&&cy>0){
		if(Peasant==HuntNIndex){
			if((NeedFood>NeedWood||!MinWooders)&&MinFermers){
				RemoveNearestNotBusyUnit(&HuntGroup, &Fermers, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Fermers, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Fermers, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Fermers, cx, cy, 5000);
			}else{
				RemoveNearestNotBusyUnit(&HuntGroup, &Wooders, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Wooders, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Wooders, cx, cy, 5000);
				//RemoveNearestNotBusyUnit(&HuntGroup, &Wooders, cx, cy, 5000);
			}
		}else{
			RemoveNearestNotBusyUnit(&HuntGroup, &NewUnits, cx, cy, 5000);
		}
	}

	rando();
	
	// food & wood distribution
	/*
	if(NeedFood>NeedWood && NFers<300) if(MinFermers) RemoveNUnits(&Fermers, &Free, 1);
		else if(MinWooders) RemoveNUnits(&Wooders, &Free, 1);
	*/

};

int AICity::CallPeasantToStorm(GAMEOBJ* Dst){
	int x,y;
	GetGrpCenter(Dst, &x, &y);
	int N=CombatPeasant-CallPeasant(Dst,CombatPeasant,x,y,3000);	
	SetToInternalResourcesZero(Dst);	
	return N;
};

int AICity::CallPeasant(GAMEOBJ* Dst, int n, int x, int y, int r){
	if(n<=0) return 0;
	int ferm=GetNUnits(&Fermers);
	int wood=GetNUnits(&Wooders);
	
	while(n&&RemoveNearestUnit(&Free,Dst,x,y,r)) n--;
	while(n&&ferm>MinFermers&&RemoveNearestUnit(&Fermers,Dst,x,y,r)){
		n--;
		ferm--;
	}	
	while(n&&wood>MinWooders*3&&RemoveNearestUnit(&Wooders,Dst,x,y,r)){
		n--;
		wood--;
	}

	SetToInternalResourcesZero(Dst);
	return n;
};

// Hunter
void AICity::AddHunter(GAMEOBJ* Grp){
	OneUnit HU;
	GetUnitInfo(Grp,0,&HU);
	if(HU.Index!=0xFFFF){
		HUNTERS=(Hunter*)realloc(HUNTERS,(NHunters+1)*sizeof(Hunter));
		Hunter* HUNT=HUNTERS+NHunters;
		memset(HUNT,0xFF,sizeof(Hunter));
		HUNT->Index=HU.Index;
		HUNT->Serial=HU.Serial;
		
		OneObject* HOB=GetOBJ(HU.Index);
		HOB->RType=0xFF;
		HOB->RAmount=0;
		HOB->GroundState=0;
		HOB->NewState=0;

		NHunters++;
		DeleteUnitFromGroup(Grp,0);
	}
};
void AICity::ProcessHunter(){
	if(HuntNIndex==0xFFFF) return;	
		
	int tm=GetGlobalTime();
	if(tm>NextMeatSearch){
		NextMeatSearch=tm+512;
		CreateMeatList(Meat,NatID,30);

		// remove bison that are already being hunted
		for(int i=0;i<NHunters;i++){
			Hunter* HUNT=HUNTERS+i;			
			word HID=HUNT->Index;
			word HSN=HUNT->Serial;			
			OneObject* HOB=GetOBJ(HID);
			if(HOB&&HSN==HOB->Serial&&!HOB->Sdoxlo){
				word BID=HUNT->TargetID;
				word BSN=HUNT->TargetSN;
				OneObject* BOB=GetOBJ(BID);
				if(BOB&&BOB->Serial==BSN&&!BOB->Sdoxlo&&!(BOB->NMask&HOB->NMask)){
					int bx=BOB->RealX>>4;
					int by=BOB->RealY>>4;
					int top=GetTopZone(bx,by);
					if(top>=0||top<0xFFFE) Meat[top]=0xFFFF;
				}
			}
		}
	}

	if(tm>NextFarmSearch){
		NextFarmSearch=tm+1024;
		CreateFarmList(Farm,NatID);
	}

	if(tm>NextDeadMeatSearch){
		NextDeadMeatSearch=tm+256;
		MeatEnabled=IsResourceEnabled(NatID,8);
	}

	int NDanAnm=0;
	word DanAnim[256];
	
	int NHunt=0;
	for(int i=0;i<NHunters;i++){
		Hunter* HUNT=HUNTERS+i;
		
		word HID=HUNT->Index;
		word HSN=HUNT->Serial;		
		
		OneObject* HOB=GetOBJ(HID);
		if(HOB&&HSN==HOB->Serial&&!HOB->Sdoxlo){
			NHunt++;
			
			//AddUnitToSel(HID);		

			int hx=HOB->RealX>>4;
			int hy=HOB->RealY>>4;
			int top=GetTopZone(hx,hy);

			int ord=GetOrderType(HOB);

			word BID=HUNT->TargetID;
			word BSN=HUNT->TargetSN;
			
			bool attract=false;
			// check finded bizon
			int btop=0xFFFF;
			OneObject* BOB=GetOBJ(BID);
			if(BOB&&BOB->Serial==BSN&&!BOB->Sdoxlo&&!(BOB->NMask&HOB->NMask)){
				int bx=BOB->RealX>>4;
				int by=BOB->RealY>>4;
				btop=GetTopZone(bx,by);

				word ID,SN;
				GetTargetObject(BID,&ID,&SN);
				if(HID==ID&&HSN==SN){
					attract=true;
					int BR=GetTopDist(hx,hy,bx,by);
					if(BR<1){
						//ord=0;
					}
				}
			}else{
				BID=0xFFFF;
				HUNT->TargetID=0xFFFF;
			}
			
			if(!ord || ord==238){
				HOB->RType=0xFF;
				HOB->RAmount=0;
				HOB->GroundState=0;
				HOB->NewState=0;
				HOB->UnlimitedMotion=0;

				if(btop<0xFFFE) Meat[btop]=BID;

				short Dang[4096];
				int Fear[256];			
				for(int j=0;j<256;j++)Fear[j]=5;
				CreateDangerMap(NatID,Dang,GetNZones(),Fear,4);

				// Show in the game screen 'Q'
				/*
				int DM[2048];
				for(int d=0;d<2048;d++) DM[d]=Dang[d];
				SetDangerMap(DM);
				*/

				int maxdang;
				word DST=0xFFFF;
				
				if(attract){					
					int zf=FindNextZoneOnTheSafeWayToObject(top,Dang,Farm,&maxdang,3,&DST);
					OneObject* DO=GetOBJ(DST);
					if(DO&&zf<0xFFFE){
						int x,y;
						GetTopZRealCoor(zf,&x,&y);

						int bx=BOB->RealX>>4;
						int by=BOB->RealY>>4;

						int fx=DO->RealX>>4;
						int fy=DO->RealY>>4;

						int BR=GetTopDist(hx,hy,bx,by);
						int DR=GetTopDist(hx,hy,fx,fy);
						int FR=GetTopDist(fx,fy,bx,by);

						if(FR<25){
							if(DR<3){
								OBJ_AttackObj(HID,BID,128+15,1);
							}
							DanAnim[NDanAnm]=BID;
							NDanAnm++;
						};
						
						if(BR<10&&DR>3){
							OBJ_SendTo(HID,x+GetRND(128)-64,y+GetRND(128)-64,128+16,0);
						}else{
							if(BOB->Life==BOB->MaxLife) OBJ_AttackObj(HID,BID,128+15,1);
						}
					}
				}else{					
					int zb=FindNextZoneOnTheSafeWayToObject(top,Dang,Meat,&maxdang,3,&DST);
					OneObject* DO=GetOBJ(DST);
					if(DO&&zb<0xFFFE){
						int x,y;
						GetTopZRealCoor(zb,&x,&y);
						if(BID!=DO->Index){
							// new bizon finded
							BOB=DO;
							BID=DO->Index;
							HUNT->TargetID=DO->Index;
							HUNT->TargetSN=DO->Serial;

							int bx=DO->RealX>>4;
							int by=DO->RealY>>4;
							int top=GetTopZone(bx,by);
							if(top>=0||top<0xFFFE) Meat[top]=0xFFFF;
						}
						if(BID!=0xFFFF){
							int bx=BOB->RealX>>4;
							int by=BOB->RealY>>4;
							btop=GetTopZone(bx,by);


							int BR=GetTopDist(hx,hy,bx,by);
							int sr=GetSearchRadius(BID);

							word FID;
							int zf=FindNextZoneOnTheSafeWayToObject(top,Dang,Farm,&maxdang,3,&FID);
							int FR=10000;
							OneObject* FOB=GetOBJ(FID);

							int fx,fy;
							int DR=10000;

							if(FOB){
								FR=GetTopDist(FOB->RealX>>4, FOB->RealY>>4, bx, by);
								fx=DO->RealX>>4;
								fy=DO->RealY>>4;
								DR=GetTopDist(hx,hy,fx,fy);
							}							

							if(FR<25){
								DanAnim[NDanAnm]=BID;
								NDanAnm++;
							}

							if(BR<(sr>>3)){
								if(BOB->Life<BOB->MaxLife||GetRND(100)>40){									
									int dx=bx-hx;
									int dy=by-hy;
									int norm=Norma(dx,dy);
									if(norm>sr){
										x=hx+128*dx/norm;
										y=hy+128*dy/norm;
										OBJ_SendTo(HID,x,y,128+16,0);
										HOB->NoSearchVictim=1;
									}
									if(BR<=(sr>>4)) OBJ_AttackObj(BID,HID,128+15,0);
								}else
									//HOB->ArmAttack=1;
									OBJ_AttackObj(HID,BID,128+15,1);
									//OBJ_SendTo(HID,fx,fy,128+16,2);									
							}else{
								OBJ_SendTo(HID,x+GetRND(128)-64,y+GetRND(128)-64,128+16,0);
							}
							if(DR<3){
								OBJ_AttackObj(HID,BID,128+15,1);
							}
						}
					}
				}
				// will prohibit it for other hunters
				if(btop<0xFFFE) Meat[btop]=0xFFFF;
			}			
		}else{
			HUNT->Index=0xFFFF;			
		}
	}

	if(/*MeatEnabled&&*/NeedHunt<2){
		for(int i=0;i<NHunters;i++){
			Hunter* HUNT=HUNTERS+i;			
			word HID=HUNT->Index;
			word HSN=HUNT->Serial;
			OneObject* HOB=GetOBJ(HID);
			if(HOB&&HSN==HOB->Serial&&!HOB->Sdoxlo){
				AddOneUnitToGroup(&HuntGroup,HOB);
				HUNT->Index=0xFFFF;
			}
		}
		//
	}else{
		if(NHunt==0||NHunt<3&&NHunt<NeedHunt){
			if(CoolHuntNIndex==0xFFFF) AddHunter(&HuntGroup);
				else AddHunter(&CoolHuntGroup);
		}
	}

	if(NDanAnm){
		for(int i=0;i<NDanAnm;i++){
			word AnmID=DanAnim[i];
			OneObject* Anm=GetOBJ(AnmID);
			if(Anm){
				if(!Anm->Sdoxlo){
					int x=Anm->RealX>>4;
					int y=Anm->RealY>>4;
					int top=GetTopZone(x,y);
					//GAMEOBJ Zone;
					//SetZone(&Zone,x,y,3000);				
					
					//RemoveGroup(&HuntGroup,&ArmHunt);
					if(!RemoveNearestUnit(&HuntGroup,&ArmHunt,x,y,3000)){}
					else if(!RemoveNearestUnit(&Wooders,&ArmWood,x,y,3000)){}
							else RemoveNearestUnit(&Fermers,&ArmFood,x,y,3000);
					
					//ClearGroup(&AnimKill);
					//AddUnitsInZoneToGroup(&Zone,&AnimKill,NatID);
					
					GrpAttackObject(NatID,&ArmHunt,AnmID);
					GrpAttackObject(NatID,&ArmWood,AnmID);
					GrpAttackObject(NatID,&ArmFood,AnmID);
					break;
				}else{
					DanAnim[i]=0xFFFF;
				}
			}		
		}
	}else{
		RemoveGroup(&ArmHunt,&HuntGroup);
		RemoveGroup(&ArmWood,&Wooders);
		RemoveGroup(&ArmFood,&Fermers);
	}

};

// Start resource
void AICity::SetStartRes(int Wood, int Food, int Stone, int Gold, int Coal, int Iron){
	if(StartRes){
		StartRes=0;
		AddResource(NatID,FOOD,Food);
		AddResource(NatID,WOOD,Wood);
		AddResource(NatID,STONE,Stone);
		AddResource(NatID,GOLD,Gold);
		AddResource(NatID,IRON,Coal);
		AddResource(NatID,COAL,Iron);
	}
};

#undef TryUnit
bool AICity::Try(GAMEOBJ* UnitType,int Max,byte CostPercent,byte Probability){
	if(Fermers.Type!='UNIT'||Wooders.Type!='UNIT'||Free.Type!='UNIT') return false;
	int NPeas=GetNUnits(&Fermers)+GetNUnits(&Wooders)+GetNUnits(&Free);
	if(Peasant!=0xFFFF&&NHunters==Peasant&&HuntGroup.Type=='UNIT') NPeas+=GetNUnits(&HuntGroup);
	bool Result=false;
	if(NPeas||(GetMoney(FOOD)>1000&&UnitType->Index==Peasant)) Result=TryUnit(UnitType,Max,CostPercent,Probability);
	return Result;
};

// Hunter

// --- distribution warriors: forward, center, backward ---

Branch* AICity::AddBranch(int NIndex, byte Role, int Min, int Max){	
	int id=-1;
	for(int i=0;i<NBranch;i++){
		Branch* BRN=BRANCH+i;
		if(BRN->NIndex==NIndex){
			id=i;
			break;
		}
	}
	if(id!=-1&&NBranch){
		return BRANCH+id;
	}else{
		BRANCH=(Branch*)realloc(BRANCH,(NBranch+1)*sizeof Branch);
		Branch* BRN=BRANCH+NBranch;
		memset(BRN,0,sizeof Branch);

		BRN->NIndex=NIndex;
		RegisterDynGroup(&BRN->Group);
		BRN->Min=GetRND(Min)*2+GetRND(Max)*(GetDifficulty()+1)/8;
		
		if(BRN->Min>=Max/2) BRN->Min=Max/4;
		
		BRN->Max=Max;
		//BRN->Rise=(Max-Min)/5;

		for(int i=0;i<NBrRole;i++) BRN->Type[i]=btStorm;

		BRN->Formation=false;

		// protect captured units
		int NZ=GetNZones();

		BRN->DefTopGrp=(GAMEOBJ*)malloc(sizeof(GAMEOBJ)*NZ);

		for(int z=0;z<NZ;z++) RegisterDynGroup(BRN->DefTopGrp+z);

		byte USE=GetMonUsage(NIndex);

		BRN->Strelok=(USE==StrelokID||USE==HorseStrelokID||USE==ArcherID);

		BRN->SeakMine=true;
		BRN->Domovoi=true;
		BRN->Hunter=false;

		NBranch++;
		return BRN;
	}
};

void AICity::AddForward(GAMEOBJ* Grp, int NIndex){
};
void AICity::AddCenter(GAMEOBJ* Grp, int NIndex){
};
void AICity::AddBack(GAMEOBJ* Grp, int NIndex, int BuildID){
};

void AICity::CrewProcess(){
	int i,j;
	
	int NCan=CleanGroup(&Cannons);
	if(NCan){
		AddCannon(&Cannons,NatID);
	}

	int T0=GetGlobalTime();

	// Search enemy aggressor
	if(T0>NextSearchDefTop){
		NextSearchEnmAgrTop=T0+41;
		MakeEnemyAgrTopGrp(NatID,EnmAgrTopGrp,DefTop);
	}

	// Search top zones for defend	
	if(T0>NextSearchDefTop){
		NextSearchDefTop=T0+511;
		//NDefTop=
		SearchCapturedTopToDeffend(NatID,DefTop);

		/*
		for(int h=0; h<NHOUSES; h++){
			AIBuild* dom = House + h;
			OneObject* BO=GetOBJ(dom->Unit.Index);		
			if(BO&&!BO->Sdoxlo){
				int x=BO->RealX>>4;
				int y=BO->RealY>>4;
				int z=GetTopZone(x,y);
				if(z<0xFFFE){
					DefTop[z]|=2;
				}				
			}
		}
		*/

		/*
		int NZ=GetNZones();
		int* DefMap=(int*)malloc(NZ*sizeof(int));
		for(int i=0;i<NZ;i++) DefMap[i]=DefTop[i];
		SetDangerMap(DefMap);
		free(DefMap);
		*/
	}

	DefendAlarm=0;
	for(i=0;i<NBranch;i++){		
		Branch* BRN=BRANCH+i;
		GAMEOBJ* BrGroup=&BRN->Group;
		
		CollectUnits(BrGroup,&NewUnits,BRN->Max,BRN->NIndex);
		int NBrn=CleanGroup(BrGroup);

		if(BRN->Hunter) RemoveGroup(BrGroup,&HuntGroup);

		byte pid=0xFF;
		int prio=-1;
		for(j=0;j<NBrRole;j++){
			int p=BRN->Prio[j];
			if(p>prio&&BRN->RestPart[j]>0){
				prio=p;
				pid=j;
			}
		}				
		
		int N=0;
		int NGuardZone=0;
		
		int NZ=GetNZones();
		
		// processing TOP defender zones
		for(int z=0;z<NZ;z++){
			GAMEOBJ* g=BRN->DefTopGrp+z;
			int NG=CleanGroup(g);
			word DT=DefTop[z];
			
			if(DT&3){
				N+=NG;
				if(DT&2) NGuardZone++;
			}else{
				if(NG){
					RemoveGroup(g,&BRN->Group);
				}
			}

			// attack enemies from this area
			if(NG){
				int R=10000;
				word ZEnm=0xFFFF;
				GAMEOBJ* EnmGrp=NULL;
				for(int j=0;j<NZ;j++){
					GAMEOBJ* EG=EnmAgrTopGrp+j;
					if(CleanGroup(EG)){
						int r=GetZonesDist(j,z);
						if(r<R){
							R=r;
							ZEnm=j;
							EnmGrp=EG;
						}
					}
				}
				if(R<40&&ZEnm!=0xFFFF&&!(DT&1)){
					AttackGrpByGrp(g,EnmGrp);
					DefendAlarm=1;
				}//else{
					CheckDef(g,z,&BRN->Group,DefTop);
				//}
			}
			
		}

		// distribution into zones
		int NBr=GetNUnits(&BRN->Group);
		for(int i=0;i<NBr;i++){
			//add a new defender
			OneUnit u;
			GetUnitInfo(&BRN->Group,i,&u);
			word UID=u.Index;
			if(UID!=0xFFFF){
				int NMin=10000;
				GAMEOBJ* G=NULL;
				int zone=0xFFFF;

				// find the injection group
				for(int z=0;z<NZ;z++){
					GAMEOBJ* g=BRN->DefTopGrp+z;
					int NG=GetNUnits(g);
					word DT=DefTop[z];
					if(DT&3){
						if(NG<NMin){
							NMin=NG;
							G=g;
							zone=z;
						}
					}
				}
				if(G){
					int x,y;
					GetTopZRealCoor(zone,&x,&y);
					OBJ_SendTo(UID,x+256-GetRND(512),y+256-GetRND(512),128+1,0);
					InsertUnitToGroup(&BRN->Group,G,i);
					DeleteUnitFromGroup(&BRN->Group,i);
				}
			}
		}
		CleanGroup(&BRN->Group);

		if(pid!=0xFF){
			//CollectUnits(&BRN->Group,&AIPlayer[NatID].NewUnits,BRN->Max,BRN->NIndex);

			word hid=0xFFFF;
			int min=100000;

			bool Formation=BRN->Formation;
			bool NotHorsemen=BRN->Domovoi;
			if(LandType==1) Formation=false;

			N+=CleanGroup(&BRN->Group)-NGuardZone;
			//if(DefenceLess) NGuardZone=0;

			switch(pid){
			case 0:	// forward
			case 1:	// center
			case 2:	// back
				if(/*!DefendAlarm&&*/GetPeaceTimeLeft()<=0&&!BRN->BaseGuard){
					/*
					if(GetNUnits(&Wooders)>MinWooders){
						RemoveNUnits(&BRN->Group,&Wooders,1,BRN->NIndex);
						SetToInternalResourcesZero(&BRN->Group);
					}
					*/					
					bool Perepoln=(GetMaxUnits(NatID)-GetCurrentUnits(NatID)<20);
					if(N>=BRN->Min || N>20&&Perepoln){
						for(int z=0;z<NZ;z++){
							GAMEOBJ* g=BRN->DefTopGrp+z;
							int n=CleanGroup(g); //GetRND()
							if(DefTop[z]&1) n-=1;
							if(n<0) n=0;
							CopyUnits(g,&BRN->Group,0,n,1,1);
						}
						if(LandType==1){
							// water ai
							RemoveGroup(&BRN->Group,&iGuardGrp);
						}
						else{
							if(Formation){
								if(NotHorsemen){
										if (N >= 196) {
											if (BRN->Strelok) CreateFormation(NatID, &Officer, &Baraban, &Flag, &BRN->Group, &Squad, "#LINE196");
											else CreateFormation(NatID, &Officer, &Baraban, &Flag, &BRN->Group, &Squad, "#KARE196");
										}
										if (N >= 120){ 
											if (BRN->Strelok) CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#LINE120");
											else CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#KARE120");
										}
										else if(N>=72){ 
											if (BRN->Strelok) CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#LINE72");
											else CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#KARE72");
										}
										else if (N >= 36) {
											if (BRN->Strelok) CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#LINE36");
											else CreateFormation(NatID,&Officer,&Baraban,&Flag,&BRN->Group,&Squad,"#KARE36");
										}
								}
								if(!NotHorsemen){
										//PRUS-Column, SHER-Line, TRI-Wedge
										if (N >= 160) {
											if (BRN->Strelok) {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#PRUS");
											}
											else {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#TRI");
											}
										}
										if (N >= 90) {
											if (BRN->Strelok) {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#PRUS2");
											}
											else {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#TRI2");
											}
										}
										if (N >= 40) {
											if (BRN->Strelok) {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#PRUS3");
											}
											else {
												CreateFormation(NatID, &MOfficer, &MOfficer, &MOfficer, &BRN->Group, &Squad, "#TRI3");
											}
										}
									
								}
							}
							RemoveGroup(&BRN->Group, &Squad);
							switch(BRN->Type[pid]){
							case btStorm:
								AddStorm(&Squad,NatID,GetDifficulty());
								//BRN->Min=BRN->Max+1;
								break;
							case btFire:
								if(DefendAlarm) AddTomahawks(&Squad,NatID,0,0,0);
									else AddFirers(&Squad,NatID);
								break;
							case btTomahawk:
								AddTomahawks(&Squad,NatID,0,0,0);
								break;
							case btKillers:
								AddPsKillers(&Squad,NatID,BRN->SeakMine);
								break;
							case btRifleman:
								AddFirers(&Squad, NatID);
								break;
							};
							
						}

						int Div=GetRND(10)>6?2:6;
						
						int Rise=GetRND((BRN->Max-BRN->Min)/Div);
						BRN->Min+=Rise;
						if(BRN->Min>=BRN->Max){
							if(BRN->Min>(BRN->Max*3/2))
								BRN->Min=BRN->Max>>3;
							else
								BRN->Min=BRN->Max-1;
						}
						if(Perepoln) BRN->Min=BRN->Max>>4;
						
						BRN->RestPart[pid]--;
					}
				}
				break;			
			/*
			case 2:	// back
				if(N){					
					//word weakid=0xFFFF;
					word minid=0xFFFF;
					int min=100000;
					for(j=0;j<NHOUSES;j++){
						AIBuild* dom = House+j;
						//int NInv=GetNUnits(&dom->Invaters);;
						//int MaxIn=GetMaxInsideAmount(dom->Unit.Index);
						if(dom->Unit.Alive()){
							OneObject* BO=GetOBJ(dom->Unit.Index);							
							int men=0;
							for(int b=0;b<NBack;b++){
								Crew* BK=BACK+b;							
								if(BK->BuildID==j&&BK->NIndex==BRN->NIndex){
									men+=GetNUnits(&BK->Group);									
								}
							}
							//if(men==0&&weakid==0xFFFF) weakid=j;
							if(BO->Usage==SkladID||BO->Usage==MelnicaID||BO->Usage==MineID) men-=3;
							if(men<min){
								minid=j;
								min=men;
							}
						}
					}
					int id=0xFFFF;
					//if(weakid!=0xFFFF){
					//	id=weakid;
					//}else					
					if(minid!=0xFFFF){
						id=minid;							
					}
					if(id!=0xFFFF){
						AIBuild* dom = House+id;
						int index=dom->Unit.Index;
						int in=GetInsideAmount(index);
						int maxin=GetMaxInsideAmount(index);
						OneUnit u;
						GetUnitInfo(&BRN->Group,0,&u);
						//if(GetRND(100)>80 && in<maxin && u.Index!=0xFFFF){
						//	InviteUnitIntoBuilding(index,u.Index,0);
						//	DeleteUnitFromGroup(&BRN->Group,0);
						//}else{

							int Perc=10;
							if(u.Usage==SkladID||u.Usage==MelnicaID||u.Usage==MineID) Perc=30;
							//if(GetRND(100)<Perc) AddBack(&BRN->Group, BRN->NIndex, id);
						//}
						BRN->RestPart[pid]--;
						break;
					}
				}
				break;
				*/
			};

		}else{
			for(int j=0;j<NBrRole;j++){
				BRN->RestPart[j]=BRN->Part[j];
			}

		}

	}
	/*
	for(i=0;i<NBack;i++){
		Crew* CRW=BACK+i;
		AIBuild* dom = House+CRW->BuildID;
		if(dom->Unit.Alive()){
			OneObject* BO=GetOBJ(dom->Unit.Index);

			GAMEOBJ Zone;
			int x,y;
			//GetGrpCenter(&CRW->Group,&x,&y);
			x=BO->RealX>>4;
			y=BO->RealY>>4;
			SetZone(&Zone,x,y,1500);

			int NArm;
			if(Attack3(&CRW->Group, &Zone, NatID, NArm)){
				//break;
			}

			DWORD purp=GetCurrentPurpose(&CRW->Group);
			if(purp!=P_MOVE){
				int gx,gy;
				if(!GetGrpCenter(&CRW->Group,&gx,&gy)) gx=-1;
				
				int bx,by;
				GetBuildingEntryPoint(&bx,&by,BO->Index,150);

				int norm=Norma(gx-bx,gy-by);

				if(gx>0&&norm>400)
					SGP_MakeOneStepTo(NatID,&CRW->Group,bx,by,GetDir(bx-(BO->RealX>>4),by-(BO->RealY>>4)),32);
			}

		}else{
			RemoveGroup(&CRW->Group,&NewUnits);
			//RemoveGroup(&CRW->Group,&AIPlayer[NatID].NewUnits);
		}
	}
	*/
};

// --- distribution warriors: forward, center, backward ---

void AICity::AddIslandGuard(GAMEOBJ* Src){
	if(!(Src->Type=='UNIT'&&CleanGroup(Src))) return;
	iGuards=(iGuardGroup*)realloc(iGuards,(NiGuards+1)* sizeof iGuardGroup);
	
	iGuardGroup* Grp=iGuards+NiGuards;	
	RegisterDynGroup(&Grp->Group);
	CopyUnits(Src,&Grp->Group,0,10000,0,1);
	
	GetGrpCenter(&Grp->Group,&Grp->x,&Grp->y);
	Grp->LastTop=0xFFFF;

	Grp->LastMoveTime=GetGlobalTime();
	
	NiGuards++;
};

void AICity::ProcessIslandGuard(){
	if(CleanGroup(&iGuardGrp)){
		FilterUnitsByCategory(&iGuardGrp,&iGuardLut,0);
		AddIslandGuard(&iGuardLut);
		FilterUnitsByCategory(&iGuardGrp,&iGuardStr,2);
		AddIslandGuard(&iGuardStr);
		FilterUnitsByCategory(&iGuardGrp,&iGuardStr,5);
		AddIslandGuard(&iGuardStr);
	}
	//int NLut=CleanGroup(&iGuardLut);
	//int NStr=CleanGroup(&iGuardStr);	

	// search for a ferry that has docked at your home island or is empty
	bool NeedParom=true;
	int px[20];
	int py[20];
	int pn=0;

	//ParomIndex=0xFFFF;								
	int N=GetNUnits(&Paroms);
	for(int i=0;i<N;i++){
		OneUnit PU;
		GetUnitInfo(&Paroms,i,&PU);
		OneObject* PO=GetOBJ(PU.Index);
		if(PO->Index!=0xFFFF&&!PO->Sdoxlo){
			if(PO->DstX>0){
				if(pn<20){
					px[pn]=PO->DstX>>4;
					py[pn]=PO->DstY>>4;
					pn++;
				}
			}else{
				if(!PO->NInside) NeedParom=false;	// found a new ferry
			}
			//ParomIndex=PO->Index;
			//ParomSerial=PO->Serial;
		}
	}

	ParomIsArrive=false;
	bool ExistGuard=false;

	for(int i=0;i<NiGuards;i++){
		int T0=GetGlobalTime();
		iGuardGroup* Grp=iGuards+i;
		int NMen = CleanGroup(&Grp->Group);
		GAMEOBJ* Group=&Grp->Group;
		if(NMen){
			ExistGuard=true;
			// thinking
			int xc,yc;
			if(GetGrpCenter(Group,&xc,&yc)){
				if(T0-Grp->LastMoveTime>72){
					SetToInternalResourcesZero(Group);
					Grp->x=xc;
					Grp->y=yc;
					int top=GetTopZone(xc,yc);
					if(top>=0xFFFE){
						OneUnit UN;
						GetUnitInfo(&Grp->Group,0,&UN);
						xc=UN.x;
						yc=UN.y;
						top=GetTopZone(xc,yc);
					}
					if(top>=0&&top<GetNZones()){
						short Dang[4096];
						int Fear[256];
						word IDS[4096];
						for(int j=0;j<256;j++)Fear[j]=5;
						Fear[1]=100;
						CreateDangerMapForTom(NatID,Dang,GetNZones(),Fear,3);						

						int maxdang;
						
						// looking to enemy force						
						GAMEOBJ Zone;
						SetZone(&Zone,xc,yc,4000);
						int Force=GetGroupForce(&Grp->Group);
						int AliForce=-GetEnemyForce(&Zone,NatID);
						
						bool attacking=true;	// we attack, we retreat
						bool moving=true;		// go to a new top zone
						bool thinktwice=false;		// think more often

						//word Builds[128];
						//int NBuilds=0;
						//bool building=MakeListOfEnBuildingInZone(NatID,&Zone,Builds,&NBuilds);
						bool building=MakeOneShotToBuild(&Zone,&Grp->Group,NatID);

						//if(Force>EForce){
						if((!building&&AliForce>(Force>>2)) || (building&&AliForce>(Force>>1))){
							SetZone(&Zone,xc,yc,4000);							
							if(AttackEnemyInZone2(&Grp->Group,&Zone,NatID)){
								// recession
								//attacking=false;
								moving=false;
							}else{
								// attacking
							}
						}else
						if(!building){
							// recession
							int NArm;
							thinktwice=AttackByTomahawks(&Grp->Group,&Zone,NatID,NArm);
							attacking=false;
						}else{
							attacking=false;
						}
						
						if(Grp->LastTop!=0xFFFF) Dang[Grp->LastTop]+=4000;
						//if(attacking&&Grp->LastTop!=0xFFFF) Dang[Grp->LastTop]+=4000;

						// looking for nearest firest

						bool find=false;	// search for a top zone for cover
						/*
						memset(IDS,0xFF,sizeof(IDS));
						for(int f=0;f<NFirers;f++){
							FiringGroup* SGrp=FIRERS+f;
							int xc,yc;
							if(SGrp->NatID==NatID&&GetNUnits(&SGrp->Group)){								
								int t=SGrp->LastTop;
								if(t!=0xFFFF){
									IDS[t]=f;
									find=true;
								}
							}
						}*/
						
						if(moving){
							if(!find){
								if(attacking){							
									CreateTopListEnArmy(IDS,NatID,NMen>>4);
								}else{
									CreateFriendBuildingsTopList(IDS,NatID);
								}
							}

							word DST=0xFFFF;
							int zf=FindNextZoneOnTheSafeWayToObject(top,Dang,IDS,&maxdang,5,&DST);

							if(DST!=0xFFFF&&zf!=top){
								int dx,dy;
								if(GetTopZRealCoor(zf,&dx,&dy)){
									SGP_MoveToPoint(NatID,&Grp->Group,dx,dy,512,256-GetRND(512),256-GetRND(512),32);
									Grp->LastTop=top;
									if(thinktwice) Grp->LastMoveTime=T0-48;
										else Grp->LastMoveTime=T0;
								}
							}else{
								if(!ParomIsArrive){
									for(int i=0;i<pn&&!ParomIsArrive;i++){
										if(GetTopDist(px[i],py[i],xc,yc)!=0xFFFF){
											ParomIsArrive=true;
										}
									}
									if(ParomIsArrive) RemoveGroup(Group,&DesantIn);
								}
								Grp->LastMoveTime=T0+18;
							}
						}else{
							Grp->LastMoveTime=T0;
						}
					}
				}
			}
		}
	}
	// ferry docked to his native island
	if(ParomIsArrive){
		/*
		for(i=0;i<NiGuards;i++){		
			iGuardGroup* Grp=iGuards+i;
			GAMEOBJ* Group=&Grp->Group;
			int NMen = GetNUnits(Group);		
			if(NMen){
				RemoveGroup(Group,&DesantIn);
				
			}
		}
		*/		
	}
	// hand-to-hand assault units (pikemen, etc.)
	if(GetNUnits(&iGuardGrp)){
		ExistGuard=true;
		if(!ParomIsArrive){
			int xc,yc;
			if(GetGrpCenter(&iGuardGrp,&xc,&yc)){
				for(int i=0;i<pn&&!ParomIsArrive;i++){
					if(GetTopDist(px[i],py[i],xc,yc)!=0xFFFF){
						ParomIsArrive=true;
					}
				}
			}
		}
		//if(DefendAlarm) RemoveGroup(&iGuardGrp,&NewUnits);
		if(ParomIsArrive) RemoveGroup(&iGuardGrp,&DesantIn);
	}
	// build a ferry
	int FreeUnitPlace = GetMaxUnits(NatID) - GetCurrentUnits(NatID);
	if(NeedParom&&ExistGuard&&FreeUnitPlace>5){
		GAMEOBJ POBJ;
		POBJ.Index=ParomNIndex;
		POBJ.Serial=0;
		POBJ.Type='UTYP';
		TryUnit(&POBJ,GetNUnits(&Paroms)+1,100,100);
	}
}

void AICity::Tactica(){
	
	if(!LandType) return;

	ProcessIslandGuard();

	int NDesIn=CleanGroup(&DesantIn);
	SetToInternalResourcesZero(&DesantIn);

	int NDesOut=CleanGroup(&DesantOut);
	
	FilterUnitsByCategory(&DesantOut,&DesantArchers,0);
	FilterUnitsByCategory(&DesantOut,&DesantStrelki,2);
	RemoveGroup(&DesantOut,&DesantWarriors);
	
	int NArch=CleanGroup(&DesantArchers);
	int NShot=CleanGroup(&DesantStrelki);
	int NCool=CleanGroup(&DesantWarriors);

	if(!DesantNOut&&!NDesOut){
		AddFirers(&DesantArchers,NatID);
		AddTomahawks(&DesantStrelki,NatID,0,0,0);
		AddStorm(&DesantWarriors,NatID,GetDifficulty());
	}else{
		if(NArch>16){
			if(GetRND(10)>6) AddFirers(&DesantArchers,NatID);
				else AddTomahawks(&DesantArchers,NatID,0,0,0);
		}
		if(NShot>12){
			if(GetRND(10)>6) AddStorm(&DesantStrelki,NatID,GetDifficulty());
				else AddTomahawks(&DesantStrelki,NatID,0,0,0);
		}
		if(NCool>10){
			if(GetRND(10)>6) AddPsKillers(&DesantWarriors,NatID);
				else AddStorm(&DesantWarriors,NatID,GetDifficulty());
		}
	}

	DesantNOut=NDesOut;

	return;
}

/////////////////////////////////////////////////////////////
void AIArmy::Init(byte Color){
	NI = Color;
	RegisterDynGroup(&Fire);
	RegisterDynGroup(&Ice);
	Target.Index = 0xFFFF;
	State = 0;
	Guard = 0;
};

bool AIArmy::Creat(AIArmyOrder order, int men, bool guard){
	//if(DetectTarget())
	//Donor = *donor;
	Guard = guard;
	Order = order;
	NMen = men;	
	Target.Index = 0xFFFF;
	State = 1;
	return true;
};

void AIArmy::Process(){
};

int AIArmy::DetectTarget(GAMEOBJ* Bld){
	int N = CleanGroup(Bld);
	int L=-1;
	if(Order==aiaCaptureBuild){
		EnemyInfo2 farm; farm.Index = 0xFFFF; int lfarm;
		EnemyInfo2 forg; forg.Index = 0xFFFF; int lforg;
		for(int i=0; i<N; i++){
			OneUnit tar;
			GetUnitInfo(Bld, i, &tar);
			EnemyInfo2 tar2;
			GetUnitInfo2(tar.Index, &tar2);
			int x,y;
			GetGrpCenter(&Ice, &x, &y);
			int ltar = Norma(x-tar.x, y-tar.y);
			if(tar.MaxStage==tar.Stage && tar2.NI!=NI){
				if(tar2.Usage==FarmID){
					if(farm.Index==0xFFFF){
						farm = tar2;
						lfarm = ltar;
					}else{
						if(farm.NInside>tar2.NInside || (lfarm>>1)>ltar){
							farm = tar2;
							lfarm = ltar;
						}
					}
				}else
				if(tar2.Usage!=DiplomatID && tar2.Usage!=MineID){
					if(forg.Index==0xFFFF || (forg.Index!=0xFFFF && forg.NInside>tar2.NInside)){
						forg = tar2;
						lforg = ltar;
					}
				}
			}
		}
		if(forg.Index!=0xFFFF && farm.Index!=0xFFFF && forg.NInside<farm.NInside && lforg<lfarm || farm.Index==0xFFFF){
			Target = forg;
			L = lforg;
		}else{
			Target = farm;
			L = lfarm;
		}
	}else
	if(Order==aiaDestroyMine){
		EnemyInfo2 mine; mine.Index = 0xFFFF; int lmine;
		for(int i=0; i<N; i++){
			OneUnit tar;
			GetUnitInfo(Bld, i, &tar);
			EnemyInfo2 tar2;
			GetUnitInfo2(tar.Index, &tar2);
			int x,y;
			GetGrpCenter(&Ice, &x, &y);
			int ltar = Norma(x-tar.x, y-tar.y);
			if(tar2.NI!=NI){
				if(tar2.Usage==MineID){
					if(mine.Index==0xFFFF || (mine.Index!=0xFFFF && ltar<lmine)){
						mine = tar2;
						lmine = ltar;
					}
				}
			}
		}
		Target = mine;
		L = lmine;
	}
	return L;
};

/////////////////////////////////////////////////////////////
AIBuild::AIBuild()
{
	memset(this,0,sizeof(*this));
	Unit.Clear();	
	//UnderConst = false;
}
/*
bool AIBuild::Alive()
{
	return Unit.Alive();
}
*/
void AIBuild::Init(word Index, byte Repaires, byte usage)
{	
	OneUnit UN;
	GetUnitGlobalInfo(Index,&UN);
	if(UN.Index!=0xFFFF){
		Unit.SetLink(Index);
		Usage = usage;
		
		NConstructs = UN.MaxStage/50;
		if(NConstructs<5) NConstructs=5;
			else if(NConstructs>30) NConstructs=30;

		if(Repaires){
			NDuzers = Repaires;
		}else{
			NDuzers = UN.MaxLife/1000;
		}

		UnderConst = true;	
		BackID=0xFFFF;
		if(Duzers.Type!='UNIT') RegisterDynGroup(&Duzers);
		if(Invaters.Type!='UNIT') RegisterDynGroup(&Invaters);
		if(InDeffend.Type!='UNIT') RegisterDynGroup(&InDeffend);
		if(Exiters.Type!='UNIT') RegisterDynGroup(&Exiters);
		if(Guard.Type!='UNIT') RegisterDynGroup(&Guard);
		SGP_ComeIntoBuilding(&Invaters, 0, Index);

		Pulemet=(GetMinDamage(UN.NIndex)!=GetMaxDamage(UN.NIndex));
	}
}
///////////////////////////////////////////////////////////////////
void NewArmy::Init(int Nat){
	NatID = Nat;
	RegisterDynGroup(&g);
	RegisterDynGroup(&g0);
	RegisterDynGroup(&g1);
	z = 0xFFFF;
};

int GetNNearEnemy(int nat, GAMEOBJ* grp){
	int x,y;
	GetGrpCenter(grp,&x,&y);
	GAMEOBJ zz;
	UnitsCenter(&zz, grp, 3000);
	int n=0;
	for(int i=0; i<7; i++)if(i!=nat){
		n += GetUnitsAmount0(&zz,i);
	}
	return AttackEnemyInZone2(grp, &zz, nat);
	//return n;
};

void NewArmy::GiveToArmy(GAMEOBJ* Src, int N){
	RemoveNUnits(&g1, Src, N);
};

int NewArmy::GetArmyAmount(){
	return GetNUnits(&g)+GetNUnits(&g1);
};

void NewArmy::Process(){
	AICity* City=Village+NatID;

	CleanGroup(&g);
	CleanGroup(&g0);
	CleanGroup(&g1);
	int N=GetNUnits(&g);
	int N0=GetNUnits(&g0);
	int N1=GetNUnits(&g1); // novobranci
		
	//ClearSelection(NatID);
	//SelectUnitsType(&City->Archers[ArchID], NatID, 1);	
	//SaveSelectedUnits(NatID, &g1, 1);
	
	if(N+N0==0){
		GAMEOBJ zz;
		UnitsCenter(&zz, &g1, 1);
		z = GetTopZone(zz.Index, zz.Serial);
		z1=z;
		RemoveGroup(&g1, &g);
		N=GetNUnits(&g);
		N1=GetNUnits(&g1);
	}
	
	DWORD* EA=City->EA;

	//assert(_CrtCheckMemory());
	int nea = EnumEnemyArmies(NatID, AFL_COOR|AFL_NUNITS, EA, 256);
	//assert(_CrtCheckMemory());
	int zNewEnm=0xFFFF;
	int x,y;	// Top enemy coor;
	int ex,ey;	// Real enemy coor
	int minL=20000;
	for(int i=0; i<nea; i++){
		DWORD X = EA[3*i];
		DWORD Y = EA[3*i+1];
		DWORD N = EA[3*i+2];

		int Z = GetTopZone(X,Y);
		int L = GetZonesDist(z,Z);
		if(L<minL){
			zNewEnm = Z;
			minL = L;
			ex = X;
			ey = Y;
		}
	}
	zEnm = zNewEnm;	
	GetTopZoneCoor(zEnm, &x, &y);

	DWORD curPurp = GetCurrentPurpose(&g);

	
	int gx,gy;	// Real army coor
	GetTopZRealCoor(z1,&gx,&gy);
	GAMEOBJ zz;
	//UnitsCenter(&zz, &g, 1000);
	SetZone(&zz,gx,gy,3000);
	
	typedef bool (*ATTACK) (GAMEOBJ* Grp,GAMEOBJ* Zone,byte NI, int& NArm);
	ATTACK AttFun=NULL;

	switch(ArchID){
	case 3:
		AttFun=Attack3;
		break;
	case 4:
		AttFun=Attack4;
		break;
	};

	int NArm;
	if(AttFun&&AttFun(&g,&zz,NatID,NArm)){
		//GetGrpCenter(&g,&gx,&gy);
		//z = GetTopZone(gx,gy);

		int r=800;
		if(NArm>0){
			int NMin = GetEnemy3(z,r,NatID);
			if(NMin){
				word* zlist=NULL;
				int NZ = GetListOfNearZones(z, &zlist);
				int Zone=0xFFFF;
				
				int Dist=0;
				
				for(int i=0; i<NZ; i++){
					int zzz=zlist[i<<1];
					
					int sx,sy;	// Top coor of Candidat zone to otstupat
					GetTopZoneCoor(zzz,&sx,&sy);
					//int ddd=GetTopDist(ex,ey,sx<<6,sy<<6);
					int ddd=GetZonesDist(z1,zzz);
					
					/*if(ddd>Dist){
						Dist=ddd;
						Zone=zzz;
						gx=sx<<6;
						gy=sy<<6;
					}*/

					int nenm = GetEnemy3(zzz,r,NatID);
					if(nenm<=NMin&&ddd>Dist){
						//NMin=nenm;
						Dist=ddd;
						Zone=zzz;					
						//gx=sx<<6;
						//gy=sy<<6;
					}
				}
				if(Zone!=0xFFFF){
					z1=z;
					z=Zone;
				}
			}
			int sx,sy;	// Top coor of Candidat zone to otstupat
			GetTopZoneCoor(z,&sx,&sy);
			SGP_MakeOneStepTo(NatID,&g,sx<<6,sy<<6,512,32);
		};
	}else
	if(curPurp==0){
		int dz = GetNextZone(z1,zEnm);
		if(dz<0xFFFE){
			z = z1;
			z1 = dz;
			int dx,dy;
			GetTopZRealCoor(z1,&dx,&dy);
			SGP_MakeOneStepTo(NatID, &g, dx, dy, 512, 1+16+32);
		}
	}
};

// Rinok
int GetSellAmount(byte SellRes, byte BuyRes, int BuyAmount){
	return BuyAmount*1000/GetTorgResult(SellRes, BuyRes, 1000);
};

bool PrepareUpgrade(byte AiNat, byte SellRes, byte BuyRes, GAMEOBJ* Upgrade){	
	if(UpgIsRun(Upgrade)) return true;
	int deficient = GetUpgradeCost(AiNat, Upgrade, BuyRes) - GetMoney(BuyRes);
	int payment = GetSellAmount(SellRes, BuyRes, deficient);
	if(GetMoney(SellRes)>payment && payment>1000){				
		for(int i=0; i<min(15, payment/15000); i++) AI_Torg(BuyRes, SellRes, 100);
		payment = GetSellAmount(SellRes, BuyRes, deficient);
		AI_Torg(SellRes, BuyRes, payment);
		return true;
	};
	return false;
};
// Rinok

#pragma warning(disable : 4035)
int Norma(int x,int y){
	__asm{
		mov		eax,x
		cmp		eax,0
		jge		ggg1
		neg		eax
ggg1:	mov		ebx,y
		cmp		ebx,0
		jge		ggg2
		neg		ebx
ggg2:	mov		ecx,eax
		cmp		eax,ebx
		ja		ggg3
		mov		ecx,ebx
ggg3:	add		ecx,eax
		add		ecx,ebx
		shr		ecx,1
		mov		eax,ecx
	};
};
#pragma warning(default : 4035)

void SetZone(GAMEOBJ* Zone, int X, int Y, int R){
	Zone->Index = X;
	Zone->Serial = Y;
	Zone->Type='@   '-0x202020+R;
}

//  --- the spirit of the warrior ---
Spirit::Spirit(){
	Clear();
};

bool Spirit::Alive(){
	OneUnit uni;
	GetUnitGlobalInfo(Index, &uni);
	return (Index == uni.Index && Serial == uni.Serial);
};

bool Spirit::SetLink(word ID, GAMEOBJ* Grp){
	OneUnit uni;
	bool link;
	if(Grp)
		link = GetUnitInfo(Grp, ID, &uni);
	else
		link = GetUnitGlobalInfo(ID, &uni);
	Index = uni.Index;
	Serial = uni.Serial;
	return link;
};

void Spirit::Clear(){
	Index = 0xFFFF;
};

bool Spirit::Equal(word ID, GAMEOBJ* Grp){
	OneUnit uni;
	if(Grp)
		GetUnitInfo(Grp, ID, &uni);
	else
		GetUnitGlobalInfo(ID, &uni);
	return (Index == uni.Index && Serial == uni.Serial);
};
//  --- the spirit of the warrior ---

// --- save ---
#define ADTYPE(x,type)\
	if(int(size+sizeof(type))>=MaxSize){\
		MaxSize+=sizeof(type)+8192;\
		*Data=(byte*)realloc(*Data,MaxSize);\
	};\
	*((type*)((*Data)+size))=x;\
	size+=sizeof(type)
#define ADARR(x,type,N)\
	if(int(size+4+sizeof(type)*N)>=MaxSize){\
		MaxSize+=4+sizeof(type)*N+8192;\
		*Data=(byte*)realloc(*Data,MaxSize);\
	};\
	*((int*)((*Data)+size))=N;\
	size+=4;\
	memcpy((*Data)+size,x,N*sizeof(type));\
	size+=N*sizeof(type)

DLLEXPORT int GetDataForSave(byte** Data, byte AiNat){
	*Data=NULL;
	int size=0;
	int MaxSize=0;

	AICity* city=Village+AiNat;	
	ADTYPE(*city,AICity);
	
	ADARR(city->HUNTERS,Hunter,city->NHunters);

	int N=city->NBranch;
	ADARR(city->BRANCH,Branch,N);
	word NZ=GetNZones();
	for(int i=0;i<N;i++){
		ADARR(city->BRANCH[i].DefTopGrp,GAMEOBJ,NZ);
	}

	ADARR(city->DefTop,word,NZ);
	ADARR(city->EnmAgrTopGrp,GAMEOBJ,NZ);

	ADARR(city->iGuards,iGuardGroup,city->NiGuards);

	return size;
};

DLLEXPORT void FreeSaveData(byte* Data){
	if(Data) free(Data);
	Data=NULL;
};

#define LOTYPE(x,type)\
	x=*((type*)LoadPtr);\
	LoadPtr+=sizeof(type);
#define LOARR(x,type,N)\
	N=*((int*)LoadPtr);\
	x=(type*)malloc(N*sizeof(type));\
	memcpy(x,LoadPtr+4,N*sizeof(type));\
	LoadPtr+=4+N*sizeof(type)

DLLEXPORT void SetSaveData(byte* Data, int size, byte AiNat){
	byte* LoadPtr=Data;

	AICity* city=Village+AiNat;
	city->AIFree();

	LOTYPE(*city,AICity);

	LOARR(city->HUNTERS,Hunter,city->NHunters);
	
	LOARR(city->BRANCH,Branch,city->NBranch);
	word NZ=0;
	for(int i=0;i<city->NBranch;i++){
		LOARR(city->BRANCH[i].DefTopGrp,GAMEOBJ,NZ);
	}

	LOARR(city->DefTop,word,NZ);
	LOARR(city->EnmAgrTopGrp,GAMEOBJ,NZ);

	LOARR(city->iGuards,iGuardGroup,city->NiGuards);
};
// --- save ---
