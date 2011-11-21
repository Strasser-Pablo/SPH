#include "particles_list.h"
#include "const.h"

Particles_List::Particles_List():m_t(0),m_n(0)
{

}

void Particles_List::Dump() {
  cout<<"Begin Particle List"<<endl;
    for (map< Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
      it->first.Dump();
        it->second.Dump();
    }
    cout<<"End Particle List"<<endl;
}


 void Particles_List::InitializeCG(){
  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.InitializeCG();
    }
}

double Particles_List::CalculateAlpha(double &num,bool &b){
    double denom=0;
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateAlphaPart(num,denom);
    }
	b=num==0 && denom==0;
return num/denom;
}

double Particles_List::CalculateBeta(double &denom,bool &bret,double alpha){
    double num=0;
    bool b=true;
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateBetaPart(num,b,alpha);
    }
    bret=b;
return num/denom;
}

void Particles_List::CalculateP1(double beta){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.CalculateP1(beta);
    }
}

void Particles_List::ConjugateGradiant(){
InitializeCG();
bool bcont=false;
bool b;
int j=0;
while(!bcont){
    double num=0;
	cout<<"loop"<<endl;
double alpha=CalculateAlpha(num,b);
if(b){
	break;
}
double beta=CalculateBeta(num,bcont,alpha);
CalculateP1(beta);
j++;
cout<<"end loop"<<endl;
}
cout<<"conjugate gradient nb it "<<j<<endl;
}
  

void Particles_List::SetB_Speed(){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.SetB_Speed();
    }
}

void Particles_List::PreparePosition(bool &b){
for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();it++) {
        it->second.PreparePosition(b);
    }
 }
class ApplyComputeDensity{
	 Particles_Deque_List& m_vect;
	public:
	ApplyComputeDensity( Particles_Deque_List& vect):m_vect(vect){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			 cout<<"part "<<part<<endl;
			if(part!=0){
				part->ComputeDensity();
			}
		}
		}
	
};

class ApplyCalculate0Density{
	 Particles_Deque_List& m_vect;
	public:
	ApplyCalculate0Density( Particles_Deque_List& vect):m_vect(vect){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->Calculate0Density();
			}
		}
		}
	
};
void Particles_List::Calculate0Density(){
	/*cout<<m_list.size()<<endl;
	cout<<"norm for"<<endl;
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.ComputeDensity();
	}
	cout<<"parallel for"<<endl;
	 */
 parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()), ApplyComputeDensity(m_vect),m_af);		
 parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()), ApplyCalculate0Density(m_vect),m_af);		
 
}



class ApplypreComputeMove_predictor{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplypreComputeMove_predictor( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->preComputeMove_predictor(m_Dt);
			}
		}
		}
	
};


class ApplyDoMove_predictor{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyDoMove_predictor( Particles_Deque_List& vect):m_vect(vect){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->DoMove_predictor();
			}
		}
		}
	
};

class ApplyComputeMove_predictor{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	 bool m_b;
	public:
	ApplyComputeMove_predictor( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt),m_b(false){
	};
	ApplyComputeMove_predictor( ApplyComputeMove_predictor& B,split):m_vect(B.m_vect),m_b(false){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
		bool b=m_b;
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->ComputeMove_predictor(m_Dt,b);
			}
		}
		m_b=b;
		}
	bool GetB(){return m_b;}
	void join(const ApplyComputeMove_predictor& B){
		m_b=m_b||B.m_b;
	}
};
void Particles_List::predictor_corrector_compute(double DT){

parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()), ApplypreComputeMove_predictor(m_vect,DT),m_af);		
	
bool b=true;
while(b){
UpdateForce();
ApplyComputeMove_predictor ap(m_vect,DT);
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()),ap,m_af);		
b=ap.GetB();
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyDoMove_predictor(m_vect),m_af);		
}



class ApplyBeeman_precompute{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyBeeman_precompute( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->Beeman_precompute(m_Dt);
			}
		}
		}
	
};


class ApplyBeeman_compute{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyBeeman_compute( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->Beeman_compute(m_Dt);
			}
		}
		}
	
};

class ApplyBeeman_first_time{
	 Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyBeeman_first_time( Particles_Deque_List& vect,double dt):m_vect(vect),m_Dt(dt){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->Beeman_first_time(m_Dt);
			}
		}
		}
	
};

void Particles_List::beeman_compute(double DT){
static bool b=true;
if(b){
b=false;
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()), ApplyBeeman_first_time(m_vect,DT),m_af);		
return;
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()), ApplyBeeman_precompute(m_vect,DT),m_af);		
UpdateForce();
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyBeeman_compute(m_vect,DT),m_af);		

}

class ApplyNextForceTimeStep{
	const Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyNextForceTimeStep(const Particles_Deque_List& vect):m_vect(vect),m_Dt(DT){
	};
	ApplyNextForceTimeStep( ApplyNextForceTimeStep& B,split):m_vect(B.m_vect),m_Dt(DT){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
		double dt=m_Dt;
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			const Particles * part=m_vect[i];
			if(part!=0){
				part->NextForceTimeStep(dt);
			}
		}
		m_Dt=dt;
		}
	double GetDt(){return m_Dt;}
	void join(const ApplyNextForceTimeStep& B){
		if(m_Dt>B.m_Dt){
			m_Dt=B.m_Dt;
		}
	}
};


class ApplyNextCourantVisciousTimeStep{
	const Particles_Deque_List& m_vect;
	 double m_Dt;
	public:
	ApplyNextCourantVisciousTimeStep(const Particles_Deque_List& vect):m_vect(vect),m_Dt(DT){
	};
	ApplyNextCourantVisciousTimeStep( ApplyNextCourantVisciousTimeStep& B,split):m_vect(B.m_vect),m_Dt(DT){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
		double dt=m_Dt;
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			const Particles * part=m_vect[i];
			if(part!=0){
				part->NextCourantVisciousTimeStep(dt);
			}
		}
		m_Dt=dt;
		}
	double GetDt(){return m_Dt;}
	void join(const ApplyNextCourantVisciousTimeStep& B){
		if(m_Dt>B.m_Dt){
			m_Dt=B.m_Dt;
		}
	}
};

double Particles_List::NextTimeStep()const{
	double dt=DT;
	UpdateForce();
	ApplyNextCourantVisciousTimeStep courvis(m_vect);
	ApplyNextForceTimeStep force(m_vect);
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()),courvis,m_af);		
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size()),force,m_af);
	double dta=courvis.GetDt();
	double dtb=force.GetDt();
    if(dta>dtb){
		dt=dtb;
	}
	else{
		dt=dta;
	}
return 0.25*dt;	
}

class ApplyUpdateForce{
	const Particles_Deque_List& m_vect;
	public:
	ApplyUpdateForce(const Particles_Deque_List& vect):m_vect(vect){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			const Particles * part=m_vect[i];
			if(part!=0){
				part->UpdateForce();
			}
		}
		}
	
};

void Particles_List::UpdateForce()const{
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyUpdateForce(m_vect),m_af);		
/*for (map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();++it) {
		it->second.UpdateForce();
    }*/
}



class ApplyCalculateSubGridTens{
	 Particles_Deque_List& m_vect;
	public:
	ApplyCalculateSubGridTens( Particles_Deque_List& vect):m_vect(vect){
	};
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->CalculateSubGridTens();
			}
		}
		}
	
};
void Particles_List::Compute(double &dt)
{
	parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);		
	  parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyCalculateSubGridTens(m_vect),m_af);		
	dt=DT;
	//  dt=NextTimeStep();
     bool ret=false;
	 if(presure_laplacien){
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		ret=it->second.PreComputeMove(dt)||ret;
    }
		 }
	if(ret){
	CorrectDensity();	
	}
	if(presure_eq_state){
		//euler
		/*
	  for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
        it->second.ComputeMove(DT);
    }
	 */
	 //predictor corrector
	 //predictor_corrector_compute(dt);
	  // beeman_compute(dt);
	  predictor_corrector_compute(dt);
	}
    m_t+=dt;
	map<Key<DIM> ,Particles>::iterator it=m_list.begin();
   while(it!=m_list.end()){
	   map<Key<DIM> ,Particles>::iterator it2=it;
	   ++it;
        it2->second.Update(this);
    }
	m_vect.Update(m_list);
    #if DOXYGEN
    ParticleReal p;
    p.ComputePressure_Density();
    p.ComputeSurface_Tensor();
    p.ComputeInternal_Force();
    p.ComputeInternal_Force();
    p.ComputeGravity_Force();
    p.ComputeMove(DT);
    p.Update(this);
    #endif //DOXYGEN
}