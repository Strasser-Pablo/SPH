#include "world.h"
#include <iomanip>

extern "C" {
#include <spooles/InpMtx.h>
#include <spooles/IVL.h>
#include <spooles/Graph.h>
#include <spooles/misc.h>
#include <spooles/FrontMtx.h>
#include <spooles/SubMtxManager.h>
#include <spooles/SymbFac.h>
#include <spooles/SPOOLES.h>
#include <spooles/ChvManager.h>
#include <umfpack.h>
}
#include "physvector.h"
#ifndef VECTOR_FINISH
 #error vector not complet
#endif
/**
 * \file world.cpp
 * @brief Contain constructor for World.
 */

World::World():m_list(this) {

}

World::~World() {

}
	#ifdef PRESSURE_LAPLACIEN
void World::SolveMatrix(){
	cout<<"begin prep"<<endl;
	CreateMatLink();
		int neqns=m_particle_real_list.size();
	int nent=neqns*100;
	int ilog=0;
	 srand ( time(NULL) );
	 //cout<<"solveMatrix"<<endl;
	 FILE *pFile = fopen ("../spooleslog.txt","w");
	InpMtx* mtxA=InpMtx_new();
	InpMtx_init(mtxA,INPMTX_BY_ROWS,SPOOLES_REAL,nent,neqns);
	
	
	
	DenseMtx* mtxB=DenseMtx_new();
	DenseMtx_init(mtxB,SPOOLES_REAL,0,0,neqns,1,1,neqns);
	DenseMtx_zero(mtxB);
	
cout<<"fil matrix"<<endl;
	for(int i=0 ;i<m_particle_real_list.size();++i){
		for(Voisin::iterator it=m_mat_link[m_particle_real_list[i].m_voisin].begin();it!=m_mat_link[m_particle_real_list[i].m_voisin].end();++it){
			int j=m_part_to_int[&(**it)];
		InpMtx_inputRealEntry(mtxA,i,j,Matrice(i,j));
	}
	DenseMtx_setRealEntry(mtxB,i,0,m_particle_real_list[i].GetB());
	}
	cout<<"end fill"<<endl;
	InpMtx_changeStorageMode(mtxA,INPMTX_BY_VECTORS);
	IVL* adjIVL=InpMtx_fullAdjacency(mtxA);
	int nedges=IVL_tsize(adjIVL);
	Graph* graph=Graph_new();
	Graph_init2(graph,0,neqns,0,nedges,neqns,nedges,adjIVL,NULL,NULL);
	ETree * frontETree=orderViaMMD(graph,1,ilog,pFile);
	IV* OldToNewIV=ETree_oldToNewVtxPerm(frontETree);
	int* OldToNew=IV_entries(OldToNewIV);
	IV* newToOldIV=ETree_newToOldVtxPerm(frontETree);
	int* newToOld=IV_entries(newToOldIV);
	ETree_permuteVertices(frontETree,OldToNewIV);
	InpMtx_permute(mtxA,OldToNew,OldToNew);
	InpMtx_changeCoordType(mtxA,INPMTX_BY_CHEVRONS);
	InpMtx_changeStorageMode(mtxA,INPMTX_BY_VECTORS);
	DenseMtx_permuteRows(mtxB,OldToNewIV);
	IVL* symbfacIVL=SymbFac_initFromInpMtx(frontETree,mtxA);
	FrontMtx* frontmtx=FrontMtx_new();
	SubMtxManager* mtxmanager =SubMtxManager_new();
	SubMtxManager_init(mtxmanager,NO_LOCK,0);
	FrontMtx_init(frontmtx,frontETree,symbfacIVL,SPOOLES_REAL,SPOOLES_NONSYMMETRIC,FRONTMTX_DENSE_FRONTS,SPOOLES_PIVOTING,NO_LOCK,0,NULL,mtxmanager,ilog,pFile);
	ChvManager* chvmanager= ChvManager_new();
	ChvManager_init(chvmanager,NO_LOCK,1);
	double cpus[9];
	int stats[10];

	int error;
	Chv* rootchv =FrontMtx_factorInpMtx(frontmtx,mtxA,100,0,chvmanager,&error,cpus,stats,ilog,pFile);
	ChvManager_free(chvmanager);
	FrontMtx_postProcess(frontmtx,1,pFile);
	DenseMtx* mtxX =DenseMtx_new();
	DenseMtx_init(mtxX,SPOOLES_REAL,0,0,neqns,1,1,neqns);
	DenseMtx_zero(mtxX);
	FrontMtx_solve(frontmtx,mtxX,mtxB,mtxmanager,cpus,ilog,pFile);
	DenseMtx_permuteRows(mtxX,newToOldIV);
	for(int i=0;i<m_particle_real_list.size();++i){
		double val;
		DenseMtx_realEntry(mtxX,i,0,&val);
		m_particle_real_list[i].SetP(val);
		m_particle_real_list[i].SetP1(val);
	}
	fclose(pFile);
	 
	/* 
int    n =m_particle_real_list.size() ;
int Ap[n+1];
double b[n];
	for(deque<ParticleReal>::iterator it=m_particle_real_list.begin();it!=m_particle_real_list.end();++it){
		it->SetP1(0);	
	}
int l=0;
	for(int i=0 ;i<m_particle_real_list.size();++i){
		Ap[i]=l;
		m_particle_real_list[i].SetP1(1);
		m_list.CalculatePressForConjugateGradiant();
		for(int j=0;j<m_particle_real_list.size();++j){
		if(m_particle_real_list[j].CalculateA()!=0)
			{
				++l;
			};
	}
	m_particle_real_list[i].SetP1(0);
	b[i]=m_particle_real_list[i].GetB();
	}
	Ap[n]=l;
int  Ai[l];
double Ax[l];
	for(deque<ParticleReal>::iterator it=m_particle_real_list.begin();it!=m_particle_real_list.end();++it){
		it->SetP1(0);	
	}
	l=0;
	for(int i=0 ;i<m_particle_real_list.size();++i){
		m_particle_real_list[i].SetP1(1);
		m_list.CalculatePressForConjugateGradiant();
		for(int j=0;j<m_particle_real_list.size();++j){
			
		double temp=m_particle_real_list[j].CalculateA();
		if(temp!=0)
			{
				Ax[l]=temp;
				Ai[l]=j;
				++l;
			};
	}
	m_particle_real_list[i].SetP1(0);
	}


	double x [n] ;
    double *null = (double *) NULL ;
    int i ;
    void *Symbolic, *Numeric ;
	cout<<"begin solve"<<endl;
    (void) umfpack_di_symbolic (n, n, Ap, Ai, Ax, &Symbolic, null, null) ;
    (void) umfpack_di_numeric (Ap, Ai, Ax, Symbolic, &Numeric, null, null) ;
    umfpack_di_free_symbolic (&Symbolic) ;
    (void) umfpack_di_solve (UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, null, null) ;
    umfpack_di_free_numeric (&Numeric) ;
    for (i = 0 ; i < n ; i++)
	{
		m_particle_real_list[i].SetP(x[i]);
		m_particle_real_list[i].SetP1(x[i]);
	}
	 */
}


void World::OutputMatrix(){
fstream out ("../matrice.csv", fstream::out);
	
	for(deque<ParticleReal>::iterator it=m_particle_real_list.begin();it!=m_particle_real_list.end();++it){
		it->SetP1(0);	
	}
	for(deque<ParticleReal>::iterator it=m_particle_real_list.begin();it!=m_particle_real_list.end();++it){
		it->SetP1(1);
		m_list.CalculatePressForConjugateGradiant();
		for(deque<ParticleReal>::iterator it2=m_particle_real_list.begin();it2!=m_particle_real_list.end();++it2){
				out<<it2->CalculateA()<<" ";
	}
	out<<endl;
	it->SetP1(0);
	}
	out<<endl;
	out<<endl;
	
		for(int i=0;i<m_particle_real_list.size();++i){
		for(int j=0;j<m_particle_real_list.size();++j){
				out<<Matrice(i,j)<<" ";
	}
	out<<endl;
	}
}

void World::CreateMatLink()
{
	m_mat_link.clear();
	m_part_to_int.clear();
	for(int i=0;i< m_particle_real_list.size();++i)
	{
		m_part_to_int.insert(pair<ParticleReal*,int>(&m_particle_real_list[i],i));
		if(m_mat_link.count(m_particle_real_list[i].m_voisin)==0)
		{
			list<Particles*> temppart=m_particle_real_list[i].m_voisin->GetParticlesVect();
			for(list<Particles*>::iterator it=temppart.begin();it!=temppart.end();++it)
			{
				if(*it!=m_particle_real_list[i].m_container)
				{
				list<Particles*> temppart2=(*it)->GetNeighbour().GetParticlesVect();
				for(list<Particles*>::iterator it2=temppart.begin();it2!=temppart.end();++it2)
				{
					temppart2.remove(*it2);
				}
				temppart.splice(temppart.begin(),temppart2);
				}
			}
			m_mat_link.insert(pair<Voisin*,Voisin>(m_particle_real_list[i].m_voisin,Voisin(temppart)));
		}
	}
}
 
#endif
