#include "particles_list.h"
#include "const.h"
#include "world.h"
double MEAN_MASS=1;
double DIV_MEAN_MASS=1;
double DT_ACT=DT;
Particles_List::Particles_List(World *w) : m_t(0),m_n(0),m_w(w)
{
}

void Particles_List::Dump() {
	cout<<"Begin Particle List"<<endl;
	for (map< Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
		it->first.Dump();
		it->second.Dump();
	}
	cout<<"End Particle List"<<endl;
}

#ifdef PRESSURE_LAPLACIEN
	void Particles_List::InitializeCG(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.InitializeCG();
		}
	}

	double Particles_List::CalculateAlpha(double &num,bool &b){
		double denom=0;
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CalculateAlphaPart(num,denom);
		}
		if(denom==0){
			b=true;
			return 0;
		}
		return num/denom;
	}

	double Particles_List::CalculateBeta(double &denom,double alpha,double &rmax){
		double num=0;
		rmax=0;
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CalculateBetaPart(num,alpha,rmax);
		}
		return num/denom;
	}

	void Particles_List::CalculateP1(double beta){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CalculateP1(beta);
		}
	}

	void Particles_List::ConjugateGradiant(fstream &out){
		double rs1=DBL_MAX;
		double rs2=DBL_MAX;
		while(true){
		SetPToP1();
		CalculatePressForConjugateGradiant();
		InitializeCG();
		int j=0;
		double r1=0;
		double r2=DBL_MAX;
		out<<"begin"<<endl;
		while(true) {
			double num=0;
			double r=0;
			CalculatePressForConjugateGradiant();
			bool b=false;
			double alpha=CalculateAlpha(num,b);
			if(b) {
				out<<"denom0_ALPHA"<<endl;
				break;
			}
			double beta=CalculateBeta(num,alpha,r);
			
			
			if(r>r1){
				r1=r;
			}
			j++;
			out<<j<<" "<<alpha<<" "<<beta<<" "<<r<<" "<<r1<<" "<<r2<<endl;
			if(j%10==0&&j>0){
				if(5.0*r1>r2){
					out<<"restart "<<r1<<" "<<r2<<endl;
					break;
				}
				if(r1<1E-30){
					out<<"restart end"<<r1<<endl;
					break;
				}
				r2=r1;
				r1=0;
			}
			CalculateP1(beta);
		}
		double r=0;
		SetPToP1();
		CalculatePressForConjugateGradiant();
		TestCGSolution(r);
		double corect=0;
		GetMaxCGGradCorrection(corect);
		out<<"max_correct "<<sqrt(corect)<<endl;
		rs2=rs1;
		rs1=r;
		if(rs1>=rs2){
			out<<"end "<<rs1<<" "<<rs2<<endl;
			break;
		}
		if(rs1<1E-30){
			out<<"endglob "<<rs1<<endl;
			break;
		}
		}
	}
	/*
	bool Particles_List::ConjugateGradiantOneiter(double &rmax){
		cout<<"conjugate grad one iter"<<endl;
		  
			double num=0;
			bool b=false;
			CalculatePressForConjugateGradiant();
			 double alpha=CalculateAlpha(num,b);
			if(b) {
				return true;
			}
			bool blucky;
			double beta=CalculateBeta(num,alpha,blucky,rmax);
			if(blucky){
				return true;
			}
			CalculateP1(beta);
			
			return false;
			 
			 return true;
		}
*/

	void Particles_List::SetB_Speed(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); it++) {
			it->second.SetB_Speed();
		}
	}

	void Particles_List::PreparePosition(bool &b){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); it++) {
			it->second.PreparePosition(b);
		}
	}
#endif

class ApplyCalculate0Density {
Particles_Deque_List& m_vect;
double m_m;
public:
ApplyCalculate0Density( Particles_Deque_List& vect) : m_vect(vect),m_m(300000){
};
ApplyCalculate0Density( ApplyCalculate0Density &B,split) : m_vect(B.m_vect),m_m(300000){
};
double GetMeanMass() const {
	return m_m;
}
void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
	double m=m_m;
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
			part->Calculate0Density(m);
		}
	}
	m_m=m;
}

void join(const ApplyCalculate0Density& B){
	if(B.m_m<m_m) {
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
		//parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplySetToMeanMass(m_vect),m_af);
   #else
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.ComputeDensity();
		}
		double m=30000;
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.Calculate0Density(m);
		}
		MEAN_MASS=m;
		DIV_MEAN_MASS=1/MEAN_MASS;

		/*for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.SetToMeanMass();
		}*/
   #endif
   #ifdef PRESSURE_LAPLACIEN
   //CorrectDensity();
   #endif
}






class ApplyDoMove_predictor {
Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyDoMove_predictor( Particles_Deque_List& vect) : m_vect(vect){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
			part->DoMove_predictor();
		}
	}
}

};


void Particles_List::predictor_corrector_compute(double DT){
   #ifdef PARALLEL
		parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplypreComputeMove_predictor(m_vect,DT),m_af);
		bool b=true;
		int i=0;
		while(b) {
			parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyComputeDensity(m_vect),m_af);
			UpdateForce();
			ApplyComputeMove_predictor ap(m_vect,DT);
			parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),ap,m_af);
			b=ap.GetB();
			++i;
			if(i>10)
			{
				break;
			}
		}
		parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyDoMove_predictor(m_vect),m_af);
   #else
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.preComputeMove_predictor(DT);
		}
		bool b=true;
		while(b) {
			b=false;
			for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
				it->second.ComputeDensity();
			}
			UpdateForce();
			for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
				it->second.ComputeMove_predictor(DT,b);
			}
		}
   #endif
}



class ApplyBeeman_precompute {
Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyBeeman_precompute( Particles_Deque_List& vect,double dt) : m_vect(vect),m_Dt(dt){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
			part->Beeman_precompute(m_Dt);
		}
	}
}

};


class ApplyBeeman_compute {
Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyBeeman_compute( Particles_Deque_List& vect,double dt) : m_vect(vect),m_Dt(dt){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
			part->Beeman_compute(m_Dt);
		}
	}
}

};

class ApplyBeeman_first_time {
Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyBeeman_first_time( Particles_Deque_List& vect,double dt) : m_vect(vect),m_Dt(dt){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
			part->Beeman_first_time(m_Dt);
		}
	}
}

};

void Particles_List::beeman_compute(double DT){
   #ifdef PARALLEL
		static bool b=true;
		if(b) {
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
		if(b) {
			b=false;
			for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
				it->second.Beeman_first_time(DT);
			}
			return;
		}
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.Beeman_precompute(DT);
		}
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.ComputeDensity();
		}
		UpdateForce();
		for(map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.Beeman_compute(DT);
		}
   #endif
}

class ApplyNextForceTimeStep {
const Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyNextForceTimeStep(const Particles_Deque_List& vect) : m_vect(vect),m_Dt(DT){
};
ApplyNextForceTimeStep( ApplyNextForceTimeStep& B,split) : m_vect(B.m_vect),m_Dt(DT){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
	double dt=m_Dt;
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		const Particles * part=m_vect[i];
		if(part!=0) {
			part->NextForceTimeStep(dt);
		}
	}
	m_Dt=dt;
}
double GetDt(){
	return m_Dt;
}
void join(const ApplyNextForceTimeStep& B){
	if(m_Dt>B.m_Dt) {
		m_Dt=B.m_Dt;
	}
}
};


class ApplyNextCourantVisciousTimeStep {
const Particles_Deque_List& m_vect;
double m_Dt;
public:
ApplyNextCourantVisciousTimeStep(const Particles_Deque_List& vect) : m_vect(vect),m_Dt(DT){
};
ApplyNextCourantVisciousTimeStep( ApplyNextCourantVisciousTimeStep& B,split) : m_vect(B.m_vect),m_Dt(DT){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r )  {
	double dt=m_Dt;
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		const Particles * part=m_vect[i];
		if(part!=0) {
			part->NextCourantVisciousTimeStep(dt);
		}
	}
	m_Dt=dt;
}
double GetDt(){
	return m_Dt;
}
void join(const ApplyNextCourantVisciousTimeStep& B){
	if(m_Dt>B.m_Dt) {
		m_Dt=B.m_Dt;
	}
}
};

double Particles_List::NextTimeStep() const {
   #ifdef PARALLEL
		double dt=DT;
		UpdateForce();
		ApplyNextCourantVisciousTimeStep courvis(m_vect);
		//ApplyNextForceTimeStep force(m_vect);
		parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),courvis,m_af);
		//parallel_reduce(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE),force,m_af);
		double dta=courvis.GetDt();
		/*double dtb=force.GetDt();
		if(dta>dtb) {
			dt=dtb;
		}
		else{
			dt=dta;
		}
		 */
		if(dt>dta)
		{
			dt=dta;
		}
		DT_ACT=1/3.*dt;
		return 1/3.*dt;
   #else


		UpdateForce();
		double dt=DT;
		for(map<Key<DIM>,Particles>::const_iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.NextCourantVisciousTimeStep(dt);
		}
		for(map<Key<DIM>,Particles>::const_iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.NextForceTimeStep(dt);
		}
		return 0.25*dt; 
   #endif
}

class ApplyUpdateForce {
const Particles_Deque_List& m_vect;
public:
ApplyUpdateForce(const Particles_Deque_List& vect) : m_vect(vect){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		const Particles * part=m_vect[i];
		if(part!=0) {
			part->UpdateForce();
		}
	}
}

};

void Particles_List::UpdateForce() const {
   #ifdef PARALLEL
		parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyUpdateForce(m_vect),m_af);
   #else
		for (map<Key<DIM>,Particles>::const_iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.UpdateForce();
		}
   #endif
}



class ApplyCalculateSubGridTens {
Particles_Deque_List& m_vect;
public:
ApplyCalculateSubGridTens( Particles_Deque_List& vect) : m_vect(vect){
};
void operator()( const blocked_range<Particles_Deque_List::size_type>& r ) const {
	for(Particles_Deque_List::size_type i=r.begin(); i!=r.end(); i++) {
		Particles * part=m_vect[i];
		if(part!=0) {
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
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		parallel_for(blocked_range<Particles_Deque_List::size_type>(0,m_vect.size(),CHUNK_SIZE), ApplyCalculateSubGridTens(m_vect),m_af);
		//dt=DT;
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		dt=NextTimeStep();
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
   #ifdef PRESSURE_LAPLACIEN
		if(presure_laplacien) {
			bool ret=false;
			for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
				ret=it->second.PreComputeMove(dt)||ret;
			}
			if(ret) {
				CorrectDensity();
			}
		}
		#endif
		if(presure_eq_state) {
			//euler
			  /* for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
			   it->second.ComputeMove(DT);
			   }
			 */
			//predictor corrector
			predictor_corrector_compute(dt);
			// beeman_compute(dt);
			// predictor_corrector_compute(dt);
   #ifdef OUTPUT_PART_TIMING
				end=times(&tf);
			#pragma GCC diagnostic ignored "-Wconversion"
				outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
			#pragma GCC diagnostic pop
   #endif
		}
		m_t+=dt;
		map<Key<DIM>,Particles>::iterator it=m_list.begin();
		while(it!=m_list.end()) {
			map<Key<DIM>,Particles>::iterator it2=it;
			++it;
			it2->second.Update(this);
		}
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		m_vect.Update(m_list);
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
   #else

		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.ComputeDensity();
		}
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CalculateSubGridTens();
		}
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		//dt=DT;
		dt=NextTimeStep();
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
	#ifdef PRESSURE_LAPLACIEN
		if(presure_laplacien) {
			bool ret=false;
			for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
				ret=it->second.PreComputeMove(dt)||ret;
			}
			if(ret) {
				CorrectDensity();
			}
		}
#endif
		if(presure_eq_state) {
			//euler
			/*
			   for (map<Key<DIM> ,Particles>::iterator it=m_list.begin();it!=m_list.end();++it) {
			   it->second.ComputeMove(DT);
			   }
			 */
			//predictor corrector
			predictor_corrector_compute(dt);
			// beeman_compute(dt);
			//predictor_corrector_compute(dt);
   #ifdef OUTPUT_PART_TIMING
				end=times(&tf);
			#pragma GCC diagnostic ignored "-Wconversion"
				outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
			#pragma GCC diagnostic pop
   #endif
		}
		m_t+=dt;
		map<Key<DIM>,Particles>::iterator it=m_list.begin();
		while(it!=m_list.end()) {
			map<Key<DIM>,Particles>::iterator it2=it;
			++it;
			it2->second.Update(this);
		}
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
   #endif
		m_vect.Update(m_list);
   #ifdef OUTPUT_PART_TIMING
			end=times(&tf);
		#pragma GCC diagnostic ignored "-Wconversion"
			outtim<<(end-deb)/nb<<" "<<(tf.tms_utime-ti.tms_utime)/nb<<" "<<(tf.tms_stime-ti.tms_stime)/nb<<" ";
		#pragma GCC diagnostic pop
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
   #endif  //DOXYGEN
}
#ifdef PRESSURE_LAPLACIEN
	void Particles_List::CorrectPosition(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CorrectPosition();
		}
	}
	void Particles_List::CorrectSpeed(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.CorrectSpeed();
	}
	}
	void Particles_List::Store0PosAndSpeed(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.Store0PosAndSpeed();
	}
	}
	void Particles_List::PrepareSpeed(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.PrepareSpeed();
	}
	}
	
	void Particles_List::PreparePos(){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.PreparePos();
	}
	}

double Particles_List::TestPositionOK(bool &b){
	double ret=0;
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
		double temp=it->second.TestPositionOK(b);
		if(temp>ret){
			ret=temp;
		}
	}
	return ret;
}
	
double Particles_List::TestSpeedOK(bool &b){
	double ret=0;
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			double temp=it->second.TestSpeedOK(b);
			if(temp>ret){
			ret=temp;
		}
	}
	return ret;
}

void Particles_List::TestPositionOKShort(bool &b){
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
		it->second.TestPositionOK(b);
		if(b){
			return;
		}
	}
}
	
void Particles_List::TestSpeedOKShort(bool &b){
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.TestSpeedOK(b);
			if(b){
			return;
		}
	}
}

void Particles_List::To0Pos(){
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.To0Pos();
		}
	}
	
void Particles_List::TestCGSolution(double &R){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.TestCGSolution(R);
		}
}

void Particles_List::SetPToP1(){
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.SetPToP1();
		}
}

void Particles_List::OutputB(fstream &out){
		for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.OutputB(out);
		}
}

void Particles_List::GetMaxCGGradCorrection(double &corect){
	for (map<Key<DIM>,Particles>::iterator it=m_list.begin(); it!=m_list.end(); ++it) {
			it->second.GetMaxCGGradCorrection(corect);
		}
}

	
void Particles_List::SolveLinearSystem(){
	m_w->SolveMatrix();
	CalculatePressForConjugateGradiant();
	double r=0;
	TestCGSolution(r);
	cout<<"r linear system "<<r<<endl;
}
#endif