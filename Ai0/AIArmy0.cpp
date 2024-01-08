// AIArmy0.cpp: implementation of the AIArmy0 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIHeader0.h"
#include "..\AICity.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void AttackByArcher(GAMEOBJ* Arch, GAMEOBJ* Zone, byte NI, int Top, int RetTop);

AIArmy0::AIArmy0()
{
	Index=0xFFFF;

}

AIArmy0::~AIArmy0()
{

}

void AIArmy0::Init(word index, byte player, word base){
	if(index==0xFFFF) return;
	Index=index;
	PlayerID=player;
	BaseID=base;

	NBrigade=0;
	//memset(Brigade,)

	Prim=0xFFFF;
	Secd=0xFFFF;
};

word AIArmy0::RegisterBrigade(){
	for(int i=0;i<N_AI_BRIGADE_0;i++){
		AIBrigade0* brg=Brigade+i;
		if(brg->Index==0xFFFF){
			brg->Init(i,Index,PlayerID);
			if(i>=NBrigade) NBrigade=i+1;
			return i;
		}
	}
	return 0xFFFF;
};

extern AICity Village[8];
void AIArmy0::Attack(){
	if(Index==0xFFFF) return;
	AIPlayer0* P = AIPlayer+PlayerID;

	GetInfo();
	
	GAMEOBJ* donor = &P->NewUnits;
	int ndonor=CleanGroup(donor);

	// Razvedka
	bool needrazv=false;
	for(int i=0;i<7;i++) if(!P->DetectEnemy[i]){
		needrazv=true;
		break;
	}
	if(needrazv){
		if(GetMaxPeaceTime()>0&&GetPeaceTimeLeft()==0 || GetMaxPeaceTime()==0&&GetGlobalTime()>8000){
			for(int i=0;i<7;i++) P->DetectEnemy[i]=true;
		}
		if(P->DetectDelay>0){
			P->DetectDelay--;
		}else{
			if(ndonor){
				P->DetectDelay=40;
				int rid = RegisterBrigade();
				AIBrigade0* brg = Brigade+rid;
				brg->Order=9;
				RemoveNUnits(&brg->Men, donor, 1);
				brg->GetInfo();
			}
		}
	}
	
	// 
	if(ndonor>9){		
		if(Acceptor==0xFFFF) Acceptor = RegisterBrigade();		
		if(Acceptor!=0xFFFF){
			AIBrigade0* acc = Brigade+Acceptor;
			if(acc && acc->Index!=0xFFFF && GetNUnits(&acc->Men)<300){				
				RemoveNUnits(&acc->Men, donor, ndonor);
				Village[P->GetColor()].CallPeasantToStorm(&acc->Men);			
				acc->GetInfo();
				
				acc->DivideByCategory(&acc->Men, true);
				SetUnitsState(&acc->Arch,1,0,0,1);
				// create order
				if(acc->Order==0xFF){
					if(Prim==0xFFFF){
						Prim = acc->Index;
						acc->Order=0;
					}else
					if(Secd==0xFFFF){
						Secd = acc->Index;
						acc->Order=1;
					}else{
						byte ord;
						int ex0 = NMen[0]-NeedMen[0];
						int ex1 = NMen[1]-NeedMen[1];
						int excess = (ex0 + ex1)>>1;
						if(ex0<=excess){
							ord=2;
						}else{
							ord=3;
						}					
						acc->Order=ord;				
					}
				}
			}
		}
	}


	// Enemy near the base
	DWORD ea[1024];
	memset(ea,0xFF,sizeof(ea));
	int nea=EnumEnemyArmies(P->GetColor(),5,ea,1024);

	AIBase0* Bs=P->Base+BaseID;
	int bx=Bs->cX;
	int by=Bs->cY;

	int NEnmArmy=0;
	word EnmArmy[20];
	memset(EnmArmy,0xFF,sizeof(EnmArmy));

	for(int j=0; j<nea; j++){
		DWORD* EnAr=ea+j*3;
		DWORD X = *(EnAr++);
		DWORD Y = *(EnAr++);
		DWORD FORCE = *EnAr;
			
		int nrm = Norma(bx-X, by-Y);
		if(nrm<5000&&NEnmArmy<20){
			EnmArmy[NEnmArmy]=j;
			NEnmArmy++;
		}
	}
	
	// personal deffenders init
	int NPersDef=0;
	word PersDef[20];
	memset(PersDef,0xFF,sizeof(PersDef));
	
	// Check each brigade
	for(int i=0;i<NBrigade;i++){		
		AIBrigade0* brg = Brigade+i;
		if(brg->Index!=0xFFFF){
			switch(brg->Order){
			case 0:
				if(Prim==i){
					DeleteHiddenUnits(&brg->Men);
					int Dist = GetZonesDist(brg->Top, TopDest[0]);
					if(Dist<20&&!brg->Storm){
						//brg->Order=5;
						brg->Storm=true;
						brg->StormSect=aSec[0];
						brg->EnemyID=EnemyID;
						brg->EnemyBaseID=EnemyBaseID;
						brg->Divert=0;						
					}else
					if(brg->Storm){
						StormTheBase(brg);
					}else
						SafeMoveToZone(brg,TopDest[0]);
				}else{
					brg->Order=2;
				}
				break;
			case 1:
				if(Secd==i){
					DeleteHiddenUnits(&brg->Men);
					int Dist = GetZonesDist(brg->Top, TopDest[1]);
					if(Dist<20&&!brg->Storm){
						//brg->Order=5;
						brg->Storm=true;
						brg->StormSect=aSec[1];
						brg->EnemyID=EnemyID;
						brg->EnemyBaseID=EnemyBaseID;
						brg->Divert=0;
					}else
					if(brg->Storm){
						StormTheBase(brg);
					}else
						SafeMoveToZone(brg,TopDest[1]);
				}else{
					brg->Order=3;
				}
				break;
			case 2:
				if(Prim!=0xFFFF){
					AIBrigade0* prim = Brigade+Prim;				
					int DT = prim->Top;
					int Dist = GetZonesDist(brg->Top, DT);
					if(Dist<10){						
						SetUnitsState(&prim->Men,1,0,0,1);
						prim->DivideByCategory(&brg->Men);
						RemoveGroup(&brg->Men, &prim->Men);
						//SafeMoveToZone(prim,DT);
					}else
					if(DT<0xFFFE){
						SafeMoveToZone(brg,DT);
					}
				}
				break;
			case 3:
				if(Secd!=0xFFFF){
					AIBrigade0* secd = Brigade+Secd;
					int DT = secd->Top;
					int Dist = GetZonesDist(brg->Top, DT);
					if(Dist<10){
						SetUnitsState(&secd->Men,1,0,0,1);
						secd->DivideByCategory(&brg->Men);
						RemoveGroup(&brg->Men, &secd->Men);
						//SafeMoveToZone(secd,DT);
					}else
					if(DT<0xFFFE){
						SafeMoveToZone(brg,DT);
					}
				}
				break;
			case 5:
				StormTheBase(brg);
				break;
			case 9:
				Razvedka(brg);
				break;
			case 10:
				ConnectToNearestArmy(brg);
				break;
			case 11:
				if(NPersDef<20){
					PersDef[NPersDef]=i;
					
					int minorm=1000000;
					int EnmID=0xFFFF;
					for(int j=0; j<NEnmArmy; j++){
						if(EnmArmy[j]!=0xFFFF){
							DWORD* EnAr=ea+EnmArmy[j]*3;
							DWORD X = *(EnAr++);
							DWORD Y = *(EnAr++);
							DWORD FORCE = *EnAr;
								
							int nrm = Norma(bx-X, by-Y);
							if(nrm<minorm){
								EnmID=j;
								minorm=nrm;
							}
						}
					}
					
					if(EnmID!=0xFFFF){
						DWORD* EnAr=ea+EnmArmy[EnmID]*3;
						brg->EnmX = *(EnAr++);
						brg->EnmY = *(EnAr++);
						brg->EnmForce = *EnAr;
						brg->EnmNorm = minorm;

						EnmArmy[EnmID]=0xFFFF;
						
						NPersDef++;

						AIBuilding0* dbuil=NULL;
						int minr=100000;
						word dir;
						for(int i=0;i<N_AI_BUILD_0;i++){							
							if(P->Build[i].Index!=0xFFFF) {
								AIBuilding0* b=P->Build+i;
								
								int dx=brg->EnmX-b->gX;
								int dy=brg->EnmY-b->gY;
								int r=Norma(dx,dy);
								if(r<minr){
									minr=r;
									dbuil=b;
									dir=GetDir(dx,dy);
								}
							}
						}

						GAMEOBJ Zone;
						SetZone(&Zone,brg->EnmX,brg->EnmY,1000);
						if(dbuil){
							DWORD purp=GetCurrentPurpose(&brg->Men);

							int gTop=GetTopZone(dbuil->gX,dbuil->gY);
							int GrpForce=GetGroupForce(&brg->Men);
							if(GrpForce>brg->EnmForce){							
								//attack
								
								if(CleanGroup(&brg->Arch)){
									AttackByArcher(&brg->Men,&Zone,P->GetColor(),0xFFFF,gTop);
								}
								if((GrpForce+20)>brg->EnmForce){
									AttackEnemyInZone2(&brg->Cold,&Zone,P->GetColor());
									AttackEnemyInZone2(&brg->Peasant,&Zone,P->GetColor());
								}

							}else{
								//movet to							
								if(purp!=P_MOVE&&dbuil&&gTop!=brg->Top){
									SGP_MoveToPoint(P->GetColor(),&brg->Men,dbuil->gX,dbuil->gY,dir,0,0,32);
									//SGP_MakeOneStepTo(P->GetColor(),&brg->Men,dbuil->gX,dbuil->gY,dir,0,0,32);
								}
							}
						}else{
							AttackEnemyInZone2(&brg->Men,&Zone,P->GetColor());
						}
					}else{
						brg->Clear();
					}
					
				}
				break;
			};
		}

	}

	// Personal deffenders create
	for(int j=0; j<NEnmArmy; j++){
		if(EnmArmy[j]!=0xFFFF){
			if(ndonor){
				int NPD=RegisterBrigade();
				if(NPD!=0xFFFF){
					AIBrigade0* brg=Brigade+NPD;

					brg->Order = 11;

					DWORD* EnAr=ea+EnmArmy[j]*3;
					brg->EnmX = *(EnAr++);
					brg->EnmY = *(EnAr++);
					brg->EnmForce = *EnAr;					
					
					brg->CallFree(brg->EnmX,brg->EnmY);

					brg->EnmNorm = Norma(brg->EnmX-brg->x,brg->EnmY-brg->y);

					if(NPersDef<20){
						//PersDef[NPersDef]=i;
						PersDef[NPersDef]=j;
						NPersDef++;
					}
				}
			}
		}
	};

	int dForce=1000;
	AIBrigade0* weak=NULL;
	for(int i=0;i<NPersDef;i++){
		if(PersDef[i]!=0xFFFF){
			AIBrigade0* pd=Brigade+PersDef[i];

			int dF=GetGroupForce(&pd->Men)-pd->EnmForce;
			if(dF<dForce){
				dForce=dF;
				weak=pd;
			}
		}
	}
	if(weak){
		dForce=abs(dForce)>>3;
		while(weak->CallFree(weak->EnmX,weak->EnmY)&&dForce>0) dForce--;
	}

}

void AIArmy0::Razvedka(AIBrigade0* Br){
	if(Index==0xFFFF) return;

	DWORD purp = GetCurrentPurpose(&Br->Men);
	if(purp==0){
		
		AIPlayer0* P = AIPlayer+PlayerID;

		word* zlist=NULL;
		int NZ = GetListOfNearZones(Br->Top, &zlist);
		
		int Zone=0xFFFF;
		int sx,sy;	// Top coor of Candidat zone to otstupat
		
		int ntid = GetRND(NZ+1);		
		if(ntid==NZ){
			
			AIBase0* Bs = P->Base+BaseID;

			int Dist=0;
			
			for(int i=0; i<NZ; i++){
				int zzz=zlist[i<<1];
				
				GetTopZRealCoor(zzz,&sx,&sy);
				//int ddd=GetZonesDist(Br->Top,zzz);
				int ddd=Norma(sx-Bs->cX,sy-Bs->cY);
				
				if(ddd>Dist){
					Dist=ddd;
					Zone=zzz;
				}
			}
		}else{
			Zone=zlist[ntid];
			GetTopZRealCoor(Zone,&sx,&sy);			
		}				
		
		if(Zone!=0xFFFF&&Zone!=Br->PrevTop){
			SGP_MoveToPoint(P->GetColor(),&Br->Men,sx,sy,512,0,0,32);
			Br->PrevTop=Br->Top;
		}
	}

};

void AttackByArcher(GAMEOBJ* Arch, GAMEOBJ* Zone, byte NI, int Top, int RetTop){
	int NArm;
	DWORD purp=GetCurrentPurpose(Arch);
	if(Attack3(Arch,Zone,NI,NArm)){
		int r=800;
		if(NArm>0){
			int sx,sy;	// Top coor of Candidat zone to otstupat
			GetTopZoneCoor(RetTop,&sx,&sy);
			SGP_MakeOneStepTo(NI,Arch,sx<<6,sy<<6,512,32);			
		};
	}/*else
	if(purp==0){
		int dz = GetNextZone(Top,RetTop);
		if(dz<0xFFFE){
			int dx,dy;
			GetTopZRealCoor(dz,&dx,&dy);
			SGP_MakeOneStepTo(NI, Arch, dx, dy, 512, 1+16+32);
		}
	}*/
}

void AIArmy0::StormTheBase(AIBrigade0* Br){
	if(Index==0xFFFF) return;

	AIPlayer0* P = AIPlayer+PlayerID;
	
	AIPlayer0* EPl = AIPlayer+Br->EnemyID;
	AIBase0* EBs = EPl->Base+Br->EnemyBaseID;
	

	// Search target building
	
	byte sec = Br->StormSect;
	/*
	int norm[4];
	for(int i;i<4;i++) norm[i]=100000;
	word bld[4];
	memset(bld,0xFF,sizeof(bld));
	
	for(i=-1;i<2;i++){
		int NB=EBs->NBSect[sec];
		for(int j=0;j<NB;j++){
		}
	}
	*/
	
	
	int i=-1;
	int j=0; // glubina prosmotra sdaniy v sektore
		
	int nmax=-100;
	AIBuilding0* Bl=NULL;	// to storm, t.e. zahvat
	OneObject* BlO=NULL;
	
	int NormFire=1000000;
	AIBuilding0* FireBl=NULL;	// to fire, t.e. podjog
	//byte nsec;
	int EForce;
	
	GAMEOBJ Zone;
	int Force=GetGroupForce(&Br->Men);

	do{
		word bid = EBs->BSect[(sec+8+i)%8][j];
		if(bid!=0xFFFF){
			AIBuilding0* EBl = EPl->Build + bid;
			if(EBl->Index!=0xFFFF){
				OneObject* BOU = GetOBJ(EBl->GroupID);
				if(BOU){
					//int norm=Norma(EBl->gX-)

					SetZone(&Zone,EBl->gX,EBl->gY,600);
					ClearGroup(&Br->Enemy);
					AddUnitsInZoneToGroup(&Zone,&Br->Enemy,BOU->NNUM);
					
					EForce=GetGroupForce(&Br->Enemy);
					int n=StormSimulator(&Br->Men,&Br->Enemy,EBl->GroupID);
					//if(Force>EForce){
						if(n>nmax){
							nmax=n;
							Bl=EBl;
							BlO=BOU;
						}
					//}
					
					if(!FireBl&&!BOU->InFire){
						FireBl=EBl;
					}
				}

			}
		}

		i++;
		if(i>1){
			i=-1;
			j++;
		}

	}while(j<2);

	// Lets go storm
	if(Bl&&Bl->Index!=0xFFFF){
		// sturmuem

		//int StormTop = GetTopZone(Bl->gX, Bl->gY);
				
		// Prepare to storm
		DWORD purp = GetCurrentPurpose(&Br->Men);
		int norm=Norma(Bl->gX-Br->x,Bl->gY-Br->y);
		
		if(norm<250){
			//InviteUnitIntoBuilding(BlO->Index, UIndex,byte Type);
			//DWORD purp=GetCurrentPurpose(&Br->Men);
			
			//if(nmax>0){
				if(purp!=P_COMEINTO){
					SGP_ComeIntoBuilding(&Br->Men,0,BlO->Index);
				}
			//}
		}else{
			bool guard=AttackEnemyInZone2(&Br->Cold,&Zone,P->GetColor());
			guard|=AttackEnemyInZone2(&Br->Peasant,&Zone,P->GetColor());
			if(FireBl){
				GrpAttackObject(P->GetColor(),&Br->Arch,FireBl->GroupID);
			}else{
				AttackByArcher(&Br->Arch,&Zone,P->GetColor(),Br->Top,EBs->zStorm[sec]);
			}			
			if(!guard){
				if(purp!=P_MOVE){
					SGP_MoveToPoint(P->GetColor(),&Br->Men,Bl->gX,Bl->gY,512,0,0,32);
				}
			};			
		}		

	}else
	if(FireBl&&FireBl->Index!=0xFFFF&&GetNUnits(&Br->Arch)){
		// podjigaem
		bool guard=AttackEnemyInZone2(&Br->Cold,&Zone,P->GetColor());
		guard|=AttackEnemyInZone2(&Br->Peasant,&Zone,P->GetColor());

		GrpAttackObject(P->GetColor(),&Br->Arch,FireBl->GroupID);
		//Br->DivideByCategory();	

	}
	else{
		// jdem podkreplenia
		
		Br->Storm=false;
		Br->Order=10;

		if(Secd==Br->Index){
			if(Prim==0xFFFF){
				Prim=Br->Index;
				Br->Order=0;
				Br->Storm=true;
			}
			Secd=0xFFFF;
		}else
		if(Prim==Br->Index){
			if(Secd==0xFFFF){
				Secd=Br->Index;
				Br->Order=1;
				Br->Storm=true;
			}
			Prim=0xFFFF;
		}
		//else{
		//}
		
		// divert - otvlechenie krestian
		/*
		if(Br->Divert>0) Br->Divert--;
		else{
			word bid=RegisterBrigade();
			if(bid!=0xFFFF){
				AIBrigade0* brg=Brigade+bid;
				RemoveNUnits(&brg->Men,&Br->Cold,1);
				Br->Order=7;
				Br->EnemyID=EnemyID;
				Br->EnemyBaseID=EnemyBaseID;
			}
			Br->Divert=200;			
		}
		*/
	}	
	

	/*
	//AttackEnemyInZone2
	int NArm;
	GAMEOBJ Zone;
	//SetZone(&Zone,EBs->cX,EBs->cY,4000);
	SetZone(&Zone,Br->x,Br->y,1000);

	//
	//AttackEnemyInZone2(&Br->Men,&Zone,P->GetColor());
	if(Attack4(&Br->Men,&Zone,P->GetColor(),NArm)){
	}else{
		DWORD purp = GetCurrentPurpose(&Br->Men);
		if(purp==0){
			SGP_MoveToPoint(P->GetColor(),&Br->Men,EBs->cX,EBs->cY,512,0,0,1);
		}
	};
	*/
}

void AIArmy0::ConnectToNearestArmy(AIBrigade0* Br){
	int TD = Br->Top;
	word bid = 0xFFFF;
	int bnorm = 100000;
	AIBrigade0* bdst=NULL;
	for(int j=0;j<NBrigade;j++){
		AIBrigade0* b = Brigade+j;
		if(b!=Br){
			int norm = GetZonesDist(b->Top,TD);
			if(norm<bnorm){
				bid = j;
				bnorm = norm;
				bdst = b;
			}
		}				
	}
	if(bdst){
		if(bnorm<20){
			SetUnitsState(&Br->Men,1,0,0,1);
			bdst->DivideByCategory(&Br->Men);
			RemoveGroup(&Br->Men, &bdst->Men);
		}else{
			SafeMoveToZone(Br,bdst->Top);
		}
	}

};

bool AIArmy0::GiveBackUpForBuild(AIBuilding0* Bl){ // backup for buildings
	int BrID=Bl->BackUpID;

	if(BrID==0xFFFF){
		BrID=RegisterBrigade();
		if(BrID!=0xFFFF) Bl->BackUpID=BrID;
	}
	
	if(BrID!=0xFFFF){
		AIBrigade0* Br=Brigade+BrID;
		return true;
	}
	return false;
};

void AIArmy0::SafeMoveToZone(AIBrigade0* BR, int DstTop){
	if(Index==0xFFFF || DstTop>=0xFFFE) return;

	AIPlayer0* P = AIPlayer+PlayerID;

	DWORD purp = GetCurrentPurpose(&BR->Men);
	
	GAMEOBJ Zone;
	SetZone(&Zone,BR->x,BR->y,1500);
	
	int NArm;
	//int Force=GetGroupForce(&BR->Men);	
	//int Narch=GetNUnits(&BR->Arch);	
	
	int EForce=GetEnemyForce(&Zone,P->GetColor());
	int Force=GetGroupForce(&BR->Men);
	if(Force>EForce){

		if(EForce>0){
			int NArch=CleanGroup(&BR->Arch);
			bool att=false;
			if(NArch){
				att=Attack3(&BR->Arch,&Zone,P->GetColor(),NArm);
				if(NArm){
					int x=P->Base[BaseID].cX;
					int y=P->Base[BaseID].cY;
					
					int dsz = GetTopZone(x,y);					
					int maxdan;
					int sz = FindNextZoneOnTheSafeWay(BR->Top,dsz,P->TD,&maxdan,6);
					if(sz<0xFFFE){
						GetTopZRealCoor(dsz,&x,&y);
					}

					if(GetCurrentPurpose(&BR->Arch)!=P_MOVE){
						SGP_MakeOneStepTo(P->GetColor(),&BR->Arch,x,y,512,32); //GetDir(BR->x-x,BR->y-y)
					}
				}else{
					CancelCurrentPurpose(&BR->Arch);
				}
			}
			att|=AttackEnemyInZone2(&BR->Cold,&Zone,P->GetColor());
			att|=AttackEnemyInZone2(&BR->Peasant,&Zone,P->GetColor());
			if(att) return;
		}
	
		/*
		if(Narch && att && !NArm){
			CancelAllPurposes(&BR->Arch);
			CancelAllPurposes(&BR->Men);
		};
		*/
		
		if(purp!=P_MOVE){
			int x,y;

			//GetGrpCenter(&BR->Men, &x, &y); delaetsia v GetInfo()
			//BR->Top = GetTopZone(x,y);
			
			int MaxDan;
			int SZ = FindNextZoneOnTheSafeWay(BR->Top,DstTop,P->TD,&MaxDan,10);
			if(SZ==0xFFFF) SZ=DstTop;

			//GetTopZRealCoor(DT,&x,&y);
			GetTopZRealCoor(SZ,&x,&y);

			SGP_MakeOneStepTo(P->GetColor(), &BR->Men, x, y, 512, 32);
		}
	}else{
		if(purp!=P_MOVE){
			//int DZ=
			
			/*
			int SZ = FindNextZoneOnTheSafeWay(BR->Top,,P->TD,&MaxDan,10); // Safe zone
			if(SZ==0xFFFF) SZ=DstTop;
			*/

			int x,y;
			//GetTopZRealCoor(SZ,&x,&y);
			x=P->Base[BaseID].cX;
			y=P->Base[BaseID].cY;

			int dsz = GetTopZone(x,y);					
			int maxdan;
			int sz = FindNextZoneOnTheSafeWay(BR->Top,dsz,P->TD,&maxdan,6);
			if(sz<0xFFFE){
				GetTopZRealCoor(dsz,&x,&y);
			}

			SGP_MakeOneStepTo(P->GetColor(), &BR->Men, x, y, 512, 32);
		}
	}
};

void AIArmy0::MoveToEBase(AIBrigade0* BR){
	if(Index==0xFFFF) return;

	AIPlayer0* P = AIPlayer+PlayerID;

	int DT;	// destination top zone
	if(BR->Order==0) DT=TopDest[0];
		else DT=TopDest[1];
	
	if(DT!=0xFFFF){
		DWORD purp = GetCurrentPurpose(&BR->Men);
		if(purp==0){
			int x,y;

			GetGrpCenter(&BR->Men, &x, &y);
			int BZ = GetTopZone(x,y);
			int MaxDan;
			int SZ = FindNextZoneOnTheSafeWay(BZ,DT,P->TD,&MaxDan,10); // Safe zone

			//GetTopZRealCoor(DT,&x,&y);
			GetTopZRealCoor(SZ,&x,&y);

			SGP_MakeOneStepTo(P->GetColor(), &BR->Men, x, y, 512, 32);
		}
	}
		
}

void AIArmy0::Defend(){
	if(Index==0xFFFF) return;

	GetInfo();
}

void AIArmy0::GetInfo(){
	if(Index==0xFFFF) return;
	AIPlayer0* P = AIPlayer+PlayerID;
	//AIArmy0* A = P-
	
	Acceptor = 0xFFFF;
	int minDist=3000;	
	memset(NMen,0,sizeof(NMen));

	for(int i=0;i<NBrigade;i++){
		AIBrigade0* brg = Brigade+i;
		if(brg->Index!=0xFFFF){
			GAMEOBJ* men = &brg->Men;
			int n=CleanGroup(men);			
			if(n){
				brg->GetInfo();
				
				AIBase0* base = P->Base+BaseID;
				
				// seek for acceptor
				int dist = Norma(brg->x-base->cX, brg->y-base->cY);
				if(dist<minDist&&brg->Order!=9){
					minDist=dist;
					Acceptor=i;
				}
				
				// zapolniaem NMen[]
				if(brg->Order!=0xFF){
					switch(brg->Order){
					case 2:
						NMen[0]+=n;
						break;
					case 3:
						NMen[1]+=n;
						break;
					default:
						NMen[brg->Order]+=n;
					};
				}				

			}else{
				brg->Index=0xFFFF;
				if(Prim==0xFFFF || Brigade[Prim].Index==0xFFFF || Brigade[Prim].Order!=0){
					int TD = TopDest[0];
					word bid = 0xFFFF;
					int bnorm = 100000;
					for(int j=0;j<NBrigade;j++){
						AIBrigade0* b = Brigade+j;
						if(b->Index!=0xFFFF && b->Order==2){
							int norm = GetZonesDist(b->Top,TD);
							if(norm<bnorm){
								bid = j;
								bnorm = norm;
							}
						}						
					}
					Prim=bid;
					Brigade[Prim].Order=0;
				}
				if(Secd==0xFFFF || Brigade[Secd].Index==0xFFFF || Brigade[Secd].Order!=1){
					int TD = TopDest[1];
					word bid = 0xFFFF;
					int bnorm = 100000;
					for(int j=0;j<NBrigade;j++){
						AIBrigade0* b = Brigade+j;
						if(b->Index!=0xFFFF && b->Order==3){
							int norm = GetZonesDist(b->Top,TD);
							if(norm<bnorm){
								bid = j;
								bnorm = norm;
							}
						}						
					}
					Secd=bid;
					Brigade[Secd].Order=1;
				}
			}
		}
	}
		
};