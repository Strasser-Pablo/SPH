#include "particles_list.h"
#include "const.h"
double MEAN_MASS=1;
double DIV_MEAN_MASS=1;
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

#ifdef PRESSURE_LAPLACIEN
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
#endif

class ApplyCalculate0Density{
	 Particles_Deque_List& m_vect;
	 double m_m;
	public:
	ApplyCalculate0Density( Particles_Deque_List& vect):m_vect(vect),m_m(300000){
	};
		ApplyCalculate0Density( ApplyCalculate0Density &B,split):m_vect(B.m_vect),m_m(300000){
	};
	double GetMeanMass()const{
		return m_m;
	}
	void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
		double m=m_m;
		for(Particles_Deque_List::size_type i=r.begin();i!=r.end();i++){
			 Particles * part=m_vect[i];
			if(part!=0){
				part->Calculate0Density(m);
			}
		}
		m_m=m;
		}
		
		void join(const ApplyCalculate0Density& B){
		if(B.m_m<m_m){
			m_m=B.m_m;
		}
	}
	
};
void Particles_List::Calculate0Density(){
	 #ifdef PARALLEL
 parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);
 ApplyCalculate0Density Calc0Dens(m_vect);
 parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), Calc0Dens,m_af);	
 MEAN_MASS=Calc0Dens.GetMeanMass();
 DIV_MEAN_MASS=1/MEAN_MASS;
 parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplySetToMeanMass(m_vect),m_af);
    #else
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.ComputeDensity();
	}
	double m=30000;
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.Calculate0Density(m);
	}
	MEAN_MASS=m;
	 DIV_MEAN_MASS=1/MEAN_MASS;
	 
	 	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.SetToMeanMass();
	}
	#endif
}






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


void Particles_List::predictor_corrector_compute(double DT){
#ifdef PARALLEL
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplypreComputeMove_predictor(m_vect,DT),m_af);		
bool b=true;
while(b){
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);		
UpdateForce();
ApplyComputeMove_predictor ap(m_vect,DT);
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),ap,m_af);		
b=ap.GetB();
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyDoMove_predictor(m_vect),m_af);	
#else
for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.preComputeMove_predictor(DT);
	}
	bool b=true;
while(b){
	b=false;
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.ComputeDensity();
	}
UpdateForce();
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.ComputeMove_predictor(DT,b);
	}
}
#endif
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
	#ifdef PARALLEL
static bool b=true;
if(b){
b=false;
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyBeeman_first_time(m_vect,DT),m_af);		
return;
}
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyBeeman_precompute(m_vect,DT),m_af);		
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);		
UpdateForce();
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyBeeman_compute(m_vect,DT),m_af);		
#else
static bool b=true;
if(b){
b=false;
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.Beeman_first_time(DT);
	}
return;
}
for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.Beeman_precompute(DT);
	}
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.ComputeDensity();
	}
	UpdateForce();
	for(map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.Beeman_compute(DT);
	}
	#endif
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
	#ifdef PARALLEL
	double dt=DT;
	UpdateForce();
	ApplyNextCourantVisciousTimeStep courvis(m_vect);
	ApplyNextForceTimeStep force(m_vect);
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),courvis,m_af);		
parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),force,m_af);
	double dta=courvis.GetDt();
	double dtb=force.GetDt();
    if(dta>dtb){
		dt=dtb;
	}
	else{
		dt=dta;
	}
return 0.25*dt;
#else

	
UpdateForce();
double dt=DT;
for(map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.NextCourantVisciousTimeStep(dt);
	}
	for(map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();++it){
		it->second.NextForceTimeStep(dt);
	}
return 0.25*dt;	
#endif
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
	#ifdef PARALLEL
parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyUpdateForce(m_vect),m_af);		
#else
for (map<Key<DIM> ,Particles>::const_iterator it=m_list.begin();it!=m_list.end();++it) {
		it->second.UpdateForce();
    }
	#endif
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
	#ifdef OUTPUT_PART_TIMING
		static fstream outtim ("../timing.tim", std::fstream::binary |std::fstream::out);
		outtim<<m_n<<" ";
	struct tms ti;
	struct tms tf;
	long end;
	long deb=times(&ti);
	double nb=double(sysconf(_SC_CLK_TCK));
	#endif

	#ifdef PARALLEL
	parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);		
	#ifdef OUTPUT_PART_TIMING
	end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	#endif
	parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyCalculateSubGridTens(m_vect),m_af);		
	//dt=DT;
	#ifdef OUTPUT_PART_TIMING
	end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	  #endif
	  dt=NextTimeStep();
	  #ifdef OUTPUT_PART_TIMING
	  end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
	 if(presure_laplacien){
		   bool ret=false;
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		ret=it->second.PreComputeMove(dt)||ret;
    }
	if(ret){
	CorrectDensity();	
	}
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
	   beeman_compute(dt);
	 // predictor_corrector_compute(dt);
	 #ifdef OUTPUT_PART_TIMING
	   end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	#endif
	}
    m_t+=dt;
	map<Key<DIM> ,Particles>::iterator it=m_list.begin();
   while(it!=m_list.end()){
	   map<Key<DIM> ,Particles>::iterator it2=it;
	   ++it;
        it2->second.Update(this);
    }
	 #ifdef OUTPUT_PART_TIMING
	 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
	#endif
	m_vect.Update(m_list);
	 #ifdef OUTPUT_PART_TIMING
	 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
	#else
		
	for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		it->second.ComputeDensity();
    }
	 #ifdef OUTPUT_PART_TIMING
	 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
	for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		it->second.CalculateSubGridTens();
    }
	 #ifdef OUTPUT_PART_TIMING
	 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
		//dt=DT;
	  dt=NextTimeStep();
	   #ifdef OUTPUT_PART_TIMING
	   end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
    
	 if(presure_laplacien){
		  bool ret=false;
    for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
		ret=it->second.PreComputeMove(dt)||ret;
    }
	if(ret){
	CorrectDensity();	
	}
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
	   beeman_compute(dt);
	  //predictor_corrector_compute(dt);
	   #ifdef OUTPUT_PART_TIMING
	   end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
	}
    m_t+=dt;
	map<Key<DIM> ,Particles>::iterator it=m_list.begin();
   while(it!=m_list.end()){
	   map<Key<DIM> ,Particles>::iterator it2=it;
	   ++it;
        it2->second.Update(this);
    }
	 #ifdef OUTPUT_PART_TIMING
	 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
	m_vect.Update(m_list);
		 #ifdef OUTPUT_PART_TIMING
		 end=times(&tf);
	outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
   #endif
		#endif
		 #ifdef OUTPUT_PART_TIMING
	outtim<<endl;
	#endif
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
