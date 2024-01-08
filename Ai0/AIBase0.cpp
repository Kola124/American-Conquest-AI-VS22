// AIBase0.cpp: implementation of the AIBase0 class.
//
//////////////////////////////////////////////////////////////////////

#include "AIHeader0.h"
#include "..\AiPurpose.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AIBase0::AIBase0()
{
	Index=0xFFFF;
}

AIBase0::~AIBase0()
{

}

void AIBase0::Init(word index, byte player){
	Index=index;
	PlayerID=player;
	// Army
	AIPlayer0* P = AIPlayer + PlayerID;
		
	DefID=P->RegisterArmy(Index);
	AgrID[0]=P->RegisterArmy(Index);
	
	// Buildings
	NBldTotal=0;
	memset(Bld,0xFFFF,sizeof(Bld));
	// Geometry
	ValidState=false;
	// Storm strategy
	LastPredictTime=0;
};

// Insert new building to the base
bool AIBase0::AddBuild(word buildID){
	if(Index==0xFFFF) return false;
	AIPlayer0* P = AIPlayer + PlayerID;
	if(buildID<N_AI_BUILD_0){
		AIBuilding0* B = P->Build + buildID;
		if(B->Index!=0xFFFF){
			int N=9*32;
			int newId=0xFFFF;
			for(int i=0;i<N;i++){
				if(Bld[i]==0xFFFF && newId==0xFFFF) newId=i;
				if(Bld[i]==B->Index){
					newId=0xFFFF;
					break;
				}
			}
			if(newId!=0xFFFF){
				Bld[newId]=B->Index;
				B->BaseID=Index;
				int dx = cX-B->cX;
				int dy = cY-B->cY;
				B->Norm = Norma(dx,dy);
				B->Dir = GetDir(dx,dy);
				if(NBldTotal){
					cX = (cX*NBldTotal+B->cX)/(NBldTotal+1);
					cY = (cY*NBldTotal+B->cY)/(NBldTotal+1);
					
					AIBuilding0* RB = P->Build + Remote;
					int n1 = Norma(cX-RB->cX, cY-RB->cY);					
					if(B->Norm>n1){
						Remote = newId;
						R=B->Norm+B->R;
					}else{
						R=n1+RB->R;
					}
				}else{
					cX = B->cX;
					cY = B->cY;
					R = B->R;
					Remote = newId;
				}
				NBldTotal++;
				ValidState=false;
				//CalcBaseZone();
				return true;
			}
		}
	}
	return false;
}

void AIBase0::CalcBaseZone(){
	if(Index==0xFFFF) return;
	AIBuilding0* B = AIPlayer[PlayerID].Build;
	int N=9*32;
	cX=0;
	cY=0;
	NBldTotal=0;
	for(int i=0;i<N;i++){
		word bid=Bld[i];
		if(bid!=0xFFFF && B[bid].Index!=0xFFFF){
			cX+=B[bid].cX;
			cY+=B[bid].cY;
			NBldTotal++;
		}
	}
	cX/=NBldTotal;
	cY/=NBldTotal;
};

byte DirToSec[256];

void InitSectorsModel(){
	int onesec = 256/8;
	for(int i=0;i<256;i++) DirToSec[i] = i/onesec;
}

// Geometry model of the base
void AIBase0::MakeSectors(){
	if(Index==0xFFFF) return;
	if(ValidState) return;
	AIPlayer0* P = AIPlayer + PlayerID;
	memset(NBSect,0,sizeof(NBSect));	
	memset(BSect,0xFF,sizeof(BSect));
	int N=9*32;	
	for(int i=0;i<N;i++){
		word bid=Bld[i];
		if(bid!=0xFFFF){
			AIBuilding0* b = P->Build + bid;
			int dx = cX - b->cX;
			int dy = cY - b->cY;
			b->Dir = GetDir(dx,dy);			
			b->Norm = Norma(dx,dy);
			byte sec;
			if(b->Norm<R/3) sec=8;
				else sec = DirToSec[b->Dir];
			
			word NBS = NBSect[sec];
			word* BS = BSect[sec];
			if(NBS<32){
				word id=NBS;
				for(int j=0;j<NBS;j++) if(BS[j]!=0xFFFF){
					AIBuilding0* bs = P->Build + BS[j];
					if(bs->Norm<b->Norm){
						id=j;
						break;
					}
				}
				word* bld=BS+id;
				if(id!=NBS){
					memmove(bld+1,bld,(NBS-id)<<1);
				}
				*bld=bid;
				NBSect[sec]++;
			}
		}		
	}
	
	int zSeek[8];
	int zRMin[8];
	for(int i=0;i<8;i++){
		zSeek[i]=0xFFFF;
		zRMin[i]=10000;
	}
	int NZ=GetNZones();
	for(int i=0;i<8;i++){
		int cx,cy,r;
		word NBS = NBSect[i];
		word* BS = BSect[i];
		if(NBS>0){
			AIBuilding0* bs = P->Build + BS[0];
			cx = bs->cX;
			cy = bs->cY;
			r = bs->R;
		}else{
			cx = cX;
			cy = cY;
			r = R>>1; 
		}
		int StormRMin=1000;
		int StormRMax=1800;
		for(int j=0;j<NZ;j++){
			int zx,zy;
			GetTopZRealCoor(j,&zx,&zy);
			int dx=cx-zx;
			int dy=cy-zy;
			int norm=Norma(dx,dy)-r;
			word dir=GetDir(dx,dy);
			byte sec=DirToSec[dir];
			if(sec==i&&norm>StormRMin&&norm<StormRMax&&norm<zRMin[i]){
				zSeek[i]=j;
				zRMin[i]=norm;
			}				
		}
	}
	for(int i=0;i<8;i++){
		zStorm[i]=zSeek[i];
		//zRmin[i]=10000;
	}

	ValidState=true;
};

// Storm strategy of the base
void AIBase0::PredictStorm(){
	if(Index==0xFFFF) return;
	
	//int tmtmt=GetGlobalTime();
	//if(tmtmt<LastPredictTime+300) return;
	
	if(LastPredictTime>0){
		LastPredictTime--;
		return;
	}else{
		LastPredictTime=25;
	}
	
	if(!ValidState) MakeSectors();
	
	AIPlayer0* P = AIPlayer + PlayerID;
	
	// Enemy bases
	int min=1000000;
	int epl=0xFFFF;	// enemy player
	int ebs=0xFFFF;	// base
	for(int i=0;i<7;i++)if(i!=PlayerID){
		AIPlayer0* ply=AIPlayer+i;		
		for(int j=0;j<5;j++){
			AIBase0* bse=ply->Base+j;
			if(bse->Index!=0xFFFF){
				int dist=GetTopDist(bse->cX,bse->cY,cX,cY);
				if(dist<min){
					epl=i;
					ebs=j;
				}
			}
		}
	}

	if(epl!=0xFF&&ebs!=0xFFFF){
		EnemyID=epl;
		EnemyBaseID=ebs;		
		
		word* ag=AgrID;
		if(*ag==0xFFFF){
			*ag=P->RegisterArmy(Index);
		}
		if(*ag!=0xFFFF){
			AIArmy0* agr = P->Army + (*ag);
			if(agr->Index!=0xFFFF){
				agr->EnemyBaseID=EnemyBaseID;
				agr->EnemyID=EnemyID;

			}
		}
	}else{
		EnemyID=0xFF;
		EnemyBaseID=0xFFFF;
	}

	if(AgrID[0]!=0xFFFF && EnemyID!=0xFF && EnemyBaseID!=0xFFFF){		
		AIArmy0* Agr = P->Army+AgrID[0];

		AIPlayer0* EP = AIPlayer+EnemyID;
		AIBase0* EB = EP->Base+EnemyBaseID;
		
		int nmin=1000000;
		byte sm=0xFF;
		int n[8];
		memset(n,0xFF,sizeof(n));

		for(int i=0;i<8;i++){
			n[i]=0;
			//for(int j=0;j<2&&j<EB->NBSect[i];j++) n[i]+=GetInsideAmount(EP->Build[EB->BSect[i][j]].GroupID);
			
			int EBTop=EB->zStorm[i];
			if(EBTop!=0xFFFF){
				int x,y;
				GetTopZRealCoor(EBTop,&x,&y);

				GAMEOBJ Zone;
				SetZone(&Zone,x,y,1500);
				
				n[i]=GetEnemyForce(&Zone,P->GetColor());

				//if(j>0&&n[i]<nmin){
				if(n[i]<nmin){
					nmin=n[i];
					sm=i;
				}
			}
		}
		int s0=0xFF;
		int s1=0xFF;
		if(sm!=0xFFFF){
			byte ss=sm;
			int i=1;
			do{
				if(EB->zStorm[ss]!=0xFFFF) break;
				ss=(sm+8-i)%8;
				if(EB->zStorm[ss]!=0xFFFF) break;
				ss=(sm+i)%8;
				i++;
			}while(i<3);

			if(EB->zStorm[ss]!=0xFFFF){
				s0 = ss;
			}

			ss=(ss+4)%8;
			sm=ss;
			i=1;
			do{
				if(EB->zStorm[ss]!=0xFFFF) break;
				ss=(sm+8-i)%8;
				if(EB->zStorm[ss]!=0xFFFF) break;
				ss=(sm+i)%8;
				i++;
			}while(i<3);

			if(EB->zStorm[ss]!=0xFFFF){
				s1 = ss;
			}
		}

		byte as=Agr->aSec[0];
		if(as!=0xFF){
			int sdmin=100;
			byte ss0=s0;
			byte ss1=s1;
			if(ss0!=0xFF){
				int ds = abs(as-ss0);
				if(ds<sdmin || as==ss0){
					s0=ss0;
					s1=ss1;
				}
			}
			if(ss1!=0xFF){
				int ds = abs(as-ss1);
				if(ds<sdmin || as==ss1){
					s0=ss1;
					s1=ss0;
				}
			}
		}
		/*
		int ds00=100;
		int ds10=100;
		if(s0!=0xFF){
			if(Agr->aSec[0]!=0xFF){
				ds00 = abs(Agr->aSec[0]-s0);
			}
			if(Agr->aSec[1]!=0xFF){
				ds10 = abs(Agr->aSec[1]-s0);
			}
		}
		int ds01=100;
		int ds11=100;
		if(s1!=0xFF){
			if(Agr->aSec[0]!=0xFF){
				ds01 = abs(Agr->aSec[0]-s1);
			}
			if(Agr->aSec[1]!=0xFF){
				ds11 = abs(Agr->aSec[1]-s1);
			}
		}
		if(ds10+ds01>ds00+ds11){
			int sss = s0;
			s0 = s1;
			s1 = sss;
		}
		*/

		if(EB->zStorm[s0]!=0xFFFF){
			Agr->aSec[0] = s0;
			Agr->NeedMen[0] = (n[s0]+1)*10;
			Agr->TopDest[0] = EB->zStorm[s0];
		}else{
			Agr->aSec[1] = 0xFF;
			Agr->NeedMen[1] = 0;
			Agr->TopDest[1] = 0xFFFF;
		}

		if(EB->zStorm[s1]!=0xFFFF){
			Agr->aSec[1] = s1;
			Agr->NeedMen[1] = (n[s1]+1)*10;
			Agr->TopDest[1] = EB->zStorm[s1];
		}else{
			Agr->aSec[1] = 0xFF;
			Agr->NeedMen[1] = 0;
			Agr->TopDest[1] = 0xFFFF;
		}

	}

	// Enemy armies near the base
	for(int i=0;i<8;i++) GetEArmyInfo(P->GetColor(),eAgr+i,800);

	//LastPredictTime=tmtmt;
};

void AIBase0::ClearEnemyArmies(){
	for(int i=0;i<8;i++) eAgrL[i]=10000;
};

int AIBase0::AddEnemyArmy(int x, int y, int norm, int dir){
	byte sec=DirToSec[dir];
	if(eAgrL[sec]>norm){
		eAgrL[sec]=norm;
		eAgr[sec].x=x;
		eAgr[sec].y=y;
	}
	return -1;
};

void AIBase0::CheckBuild(){
	if(Index==0xFFFF) return;
	
	AIPlayer0* P = AIPlayer + PlayerID;

	int NB=9*32;
	int n=0;
	for(int i=0;i<NB;i++){
		int bid=Bld[i];
		if(bid!=0xFFFF){
			AIBuilding0* Bl=P->Build+bid;			
			if(Bl->Index!=0xFFFF){
				OneObject* BlO=GetOBJ(Bl->GroupID);
				
				// Proverka na zahvat
				if(BlO&&(BlO->Sdoxlo||(BlO->Serial>>1)!=(Bl->GroupSN>>1)||BlO->NNUM!=P->GetColor())){
					Bl->Index=0xFFFF;
					ValidState=false;
					break;
				}else n++;
				
				// vichisliaem blijayshego vraga
				word aid=0xFFFF;
				int amn=100000;
				//int dir;

				DWORD* ea=P->EA;
				int nea=P->NEA;
				int bx=Bl->gX;
				int by=Bl->gY;

				for(int j=0; j<nea; j++){
					DWORD X = *ea; ea++;
					DWORD Y = *ea; ea++;
					DWORD N = *ea; ea++;					
					
					int nrm = Norma(bx-X, by-Y);
					if(nrm<amn){
						aid=j;
						amn=nrm;
						//dir= GetDir(dx,dy);
					}
				}
				if(aid!=0xFFFF){
					Bl->NearestEnemy=aid;
					Bl->EnemyNorm=amn;
				}else{
					Bl->NearestEnemy=0xFFFF;
					Bl->EnemyNorm=100000;
				}
			}
		}
	}
	if(n==0){
		Index=0xFFFF;
		return;
	}
}

void AIBase0::Process(){
	if(Index==0xFFFF) return;
	AIPlayer0* P = AIPlayer + PlayerID;

	AIArmy0* Def = P->Army+DefID;
	AIArmy0* Agr = P->Army+AgrID[0];

	int NDB=0;	// Number of buildings in danger
	for(int j=0;j<8;j++){
		// collect army
		int eL = eAgrL[j];
		if(eL<3000) Def->NeedMen[j] = eAgr[j].NMen<<1;
		//if(eL<500) Def

		// defend buildings
	}

	/*
	int NB=9*32;
	// Building defence
	for(int i=0;i<NB;i++){
		int bid=Bld[i];
		if(bid!=0xFFFF){
			AIBuilding0* Bl=P->Build+bid;			
			if(Bl->Index!=0xFFFF){
				OneUnit BU;
				GetUnitGlobalInfo(Bl->GroupID,&BU);
				if(Bl->GroupSN==BU.Serial){
					OneObject* BlO=GetOBJ(Bl->GroupID);

					int nr=10-CleanGroup(&Bl->Remont);
					int ni=5-CleanGroup(&Bl->Invite)-BlO->NInside;

					AICity* vil=Village+P->GetColor();
					if(BU.IsBuilt){
						int HouseMenType=P->HouseMenType;
						if(HouseMenType!=0xFFFF){
							CollectUnits(&Bl->Invite,&P->NewUnits,5,HouseMenType);
						}
						if(Bl->EnemyNorm<4000){
							int food=vil->MinFermers;
							int wood=vil->MinWooders;
							if(Bl->EnemyNorm<1500){
								ni+=5;
							}
							if(Bl->EnemyNorm<2000 && ni>0){
								vil->MinFermers=food>>1;
								vil->MinWooders=wood>>1;
							}
							if(ni>0){
								if(HouseMenType!=0xFFFF){
									RemoveNUnits(&Bl->Invite,&P->NewUnits,1,HouseMenType);
									//RemoveNUnits(&Bl->Invite,&P->NewUnits,1,HouseMenType);
								}else{
									vil->CallPeasant(&Bl->Invite,1,Bl->cX,Bl->cY,5000);									
								}
							}
							vil->MinFermers=food;
							vil->MinWooders=wood;
						}else{
							if(ni<4) 
								CopyUnits(&Bl->Invite,&Bl->Leave,0,1,1,1);
						}
						FilterUnitsByCategory(&Bl->Leave,&P->NewUnits,4);
						FilterUnitsByCategory(&P->NewUnits,&vil->Free,3);
					}
				}
			}
		}
	}
	*/
	

	//GAMEOBJ* NU=P->NewUnits;	
	//CleanGroup(NU);
	//RemoveNUnits(
		
	Def->Defend();
	Agr->Attack();

	/*
	word nea=P->NEA;
	for(int i=0;i<nea;i++){
	}
	*/
}
