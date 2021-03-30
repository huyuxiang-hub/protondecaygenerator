#include <iostream>
#include <fstream>
#include <cassert>
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Units/PhysicalConstants.h>
#include <TROOT.h>
#include <TRandom.h>
#include <vector>
#include <TSystem.h>
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <cstdlib>
#include <TChain.h>
#include <TString.h>
#include "deex.h"
#include <map>

using namespace std;
using namespace CLHEP;
void Usage();

struct Params{

   Params(){
     rseed = 0;
     nEvents = 1000000;
     outFilename=NULL;
     stream = stdout;
     const char* path = getenv("JUNOTOP");
     data_dir = path;
     data_dir += "/data/Generator/ProtonDecay/data/";
     GenieFilename = "pd1.1.ghep.histo.root";
   }

   long rseed;
   unsigned long int nEvents;
   TString data_dir;
   TString GenieFilename;
   char* outFilename;
   FILE* stream ;
};

struct Data{

  Data(){
  
     evtID = 0 ;
     tPdg  = 0 ;
     tPx = 0. ;
     tPy  = 0.;
     tPz  = 0.;
     tRemovalE =0.;
     tE = 0.;
     tMass = 0.;

     m_isoPDG = 0 ;
     m_isoPdg = 0 ;
     m_isoTag = 0 ;
     m_isoPx  = 0.;
     m_isoPy  = 0.;
     m_isoPz  = 0.;
     m_isoE   = 0.;
     m_isoMass = 0.;
     m_isoEffMass = 0.;

     Npars = 0.;
     pdg[20] = {0};
     px[20] = {0};      // GeV
     py[20] = {0};      // GeV
     pz[20] = {0};      // GeV
     energy[20] = {0};  // GeV
     mass[20] = {0};    // GeV
     energyT = 0;

     Kpx = 0 ;
     Kpy = 0  ;
     Kpz = 0  ;
     Kenergy = 0;
}
  
  int evtID;
  int tPdg;
  double tPx;
  double tPy;
  double tPz;
  double tRemovalE;
  double tE;
  double tMass;
  
  int m_isoPDG;
  int m_isoPdg;
  int m_isoTag;
  double m_isoPx;
  double m_isoPy;
  double m_isoPz;
  double m_isoE;
  double m_isoMass;
  double m_isoEffMass;


  int Npars;
  int pdg[20];
  double px[20];      // GeV
  double py[20];      // GeV
  double pz[20];      // GeV
  double energy[20];  // GeV
  double mass[20];    // GeV
  double energyT;

 
  double Kpx ;
  double Kpy  ;           
  double Kpz   ;          
  double Kenergy;         
};

class ProtonDecayEvent{
   public: 
   ProtonDecayEvent(TString path);
   ~ProtonDecayEvent();
   
   private:
     Data data;
   private:
     TFile* genieFile;
     TTree* geTree;
     TFile* outFile;
     TTree* outTree; 
  public:
     void LoadReadFile(TString infile);
     void LoadEvent(int evtid);
     int GetNpars();
     int GetIsoP();
     int GetIsoN();
     bool GetIsStableFlag();
     bool GetIsNoIsoFlag();
  private:
     int entries;
     int iso_rp;
     int iso_rn;
     bool isstable;
     bool isnoiso;
  public:
     int GetEntries() {return entries; }
  public:
     AfterDeexInfo  Info;

  public:
     void PrintTotalPars( int num );
     void PrintNormPars();
     void PrintIos();
     void PrintDeexInfo();
  private:
     FILE* stream = stdout;

  private:
    std::map<int, double> pdg2mass;     

  public:
    Hep3Vector PointPv(double Energy, double Mass);
    
};

ProtonDecayEvent::ProtonDecayEvent(TString path){
    iso_rp = 0 ;
    iso_rn = 0 ;
    isstable = false ;
    isnoiso = false ;
    genieFile = NULL;
    geTree  = NULL;
    outFile = NULL;
    outTree = NULL;
    entries = 0;
  
    pdg2mass[22] = 0;
    pdg2mass[2112] = 0.93957;
    pdg2mass[2212] = 0.93827;
    pdg2mass[1000010020] = 1.8756;
    pdg2mass[1000010030] = 2.8089;
    pdg2mass[1000020030] = 2.8084;
    pdg2mass[1000020040] = 3.7274;
    pdg2mass[1000030060] = 5.6015;
    pdg2mass[1000030070] = 6.5335;
    pdg2mass[1000030080] = 7.4708;
    pdg2mass[1000030090] = 8.4061;
    pdg2mass[1000040070] = 6.5344;
    pdg2mass[1000040080] = 7.4548;
    pdg2mass[1000040090] = 8.3925;
    pdg2mass[1000040100] = 9.3249;
    pdg2mass[1000050080] = 7.4728;
    pdg2mass[1000050090] = 8.3935;
    pdg2mass[1000050100] = 9.3244;
    pdg2mass[1000050110] = 10.2522;
    pdg2mass[1000060090] = 8.4100;
    pdg2mass[1000060100] = 9.3280;
    pdg2mass[1000060110] = 10.2542;
    pdg2mass[1000060120] = 11.1748;    

    LoadReadFile(path);  
 }

ProtonDecayEvent::~ProtonDecayEvent(){
  
   delete geTree;
   delete genieFile;

}

void ProtonDecayEvent::PrintTotalPars( int num ){
    fprintf(stream, "%d\n", num);    
}
void ProtonDecayEvent::PrintNormPars(){
  
    for (int i = 0; i < data.Npars; i++) {
       fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", data.pdg[i], data.px[i], data.py[i], data.pz[i], data.mass[i]);
     }
}
 
void ProtonDecayEvent::PrintIos(){
     fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", data.m_isoPDG,data.m_isoPx,data.m_isoPy, data.m_isoPz, pdg2mass[data.m_isoPDG]);
}

void ProtonDecayEvent::PrintDeexInfo(){
   
    int count = 0;
    count = data.Npars + Info.NPars;
    if ( Info.ResidualZ >= 3 && Info.ResidualN >= 3)  {
          count = count + 1;
          fprintf(stream, "%d\n", count);
          fprintf(stream, "1\t%d 0 0 %f %f %f %f\n",Info.ResidualPdg , data.m_isoPx, data.m_isoPy,data.m_isoPz,pdg2mass[Info.ResidualPdg]);
       }
    for (int k = 0; k < Info.NPars; k++) {
 
           double MASS = pdg2mass[Info.Pdg[k]];
           Hep3Vector pv = PointPv(Info.Energy[k], MASS);
           fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", Info.Pdg[k], pv.x(), pv.y(), pv.z(), MASS);     
     }

 }

Hep3Vector ProtonDecayEvent::PointPv(double Energy, double Mass ){

  double xdir = 0;
  double ydir = 0;
  double zdir = 0;
  double cost = 0.;
  double sint =0.;
  double phi = 0.;
  double Ekval = Energy*1e-3;
  double Pval = sqrt(pow(Ekval,2)+2*Mass*Ekval);

  cost = 1-2*gRandom->Uniform(0., 1.);
  sint = sqrt(1-cost*cost);
  phi = gRandom->Uniform(0, twopi);
  xdir = sint * cos(phi);
  ydir = sint * sin(phi);
  zdir = cost;

  double px = xdir * Pval;  // GeV
  double py = ydir * Pval;  // GeV
  double pz = zdir * Pval;  // GeV
  Hep3Vector Pv;
  Pv = Hep3Vector(px, py, pz);
  return Pv;

}



void ProtonDecayEvent::LoadReadFile(TString infile){

     genieFile = TFile::Open(infile, "read");
     if (!genieFile) {
        cout << "Can not find file: " << infile << endl;
        exit(-1);
     }
     geTree = (TTree*)genieFile->Get("events"); 
     entries = (int)geTree->GetEntries();
    
  geTree->SetBranchAddress("evtID", &data.evtID);
  geTree->SetBranchAddress("tPdg", &data.tPdg);
  geTree->SetBranchAddress("tPx", &data.tPx);
  geTree->SetBranchAddress("tPy", &data.tPy);
  geTree->SetBranchAddress("tPz", &data.tPz);
  geTree->SetBranchAddress("tE", &data.tE);
  geTree->SetBranchAddress("tMass", &data.tMass);
  geTree->SetBranchAddress("tRemovalE", &data.tRemovalE);
  geTree->SetBranchAddress("m_isoPDG", &data.m_isoPDG);
  geTree->SetBranchAddress("m_isoPdg", &data.m_isoPdg);
  geTree->SetBranchAddress("m_isoPx", &data.m_isoPx);
  geTree->SetBranchAddress("m_isoPy", &data.m_isoPy);
  geTree->SetBranchAddress("m_isoPz", &data.m_isoPz);
  geTree->SetBranchAddress("m_isoE", &data.m_isoE);
  geTree->SetBranchAddress("m_isoMass", &data.m_isoMass);
  geTree->SetBranchAddress("m_isoEffMass", &data.m_isoEffMass);  

  geTree->SetBranchAddress("Npars", &data.Npars);
  geTree->SetBranchAddress("pdg", data.pdg);
  geTree->SetBranchAddress("px", data.px);
  geTree->SetBranchAddress("py", data.py);
  geTree->SetBranchAddress("pz", data.pz);
  geTree->SetBranchAddress("energy", data.energy);
  geTree->SetBranchAddress("mass", data.mass);
  geTree->SetBranchAddress("energyT", &data.energyT);
  
  geTree->SetBranchAddress("Kpx", &data.Kpx);
  geTree->SetBranchAddress("Kpy", &data.Kpy);
  geTree->SetBranchAddress("Kpz", &data.Kpz);
  geTree->SetBranchAddress("Kenergy", &data.Kenergy);
}

void ProtonDecayEvent::LoadEvent(int evtid){
     geTree->GetEntry(evtid);
     std::cout<<"LoadEvent m_isoPDG="<<data.m_isoPDG<<std::endl;
     iso_rp = int((data.m_isoPDG - 1000000000) / 10000);
     iso_rn = int((data.m_isoPDG - 1000000000 - iso_rp * 10000) / 10) - iso_rp;

     if (data.m_isoPDG == 1000060120 || data.m_isoPDG == 1000030060 || iso_rp < 3 || iso_rn < 3 || iso_rp>6 || iso_rn>6) {
         isstable = true;
     }
     else{
         isstable = false;
     }
     if (data.m_isoPDG == 0 || iso_rp + iso_rn > 11) {
         isnoiso = true;
     }
     else{
         isnoiso = false;
     }                    
}

int ProtonDecayEvent::GetNpars(){
    return data.Npars;
}

int ProtonDecayEvent::GetIsoP()
{
     return iso_rp;
}

int ProtonDecayEvent::GetIsoN()
{
     return iso_rn ;
}

bool ProtonDecayEvent::GetIsStableFlag()
{
  return isstable ;
}

bool ProtonDecayEvent::GetIsNoIsoFlag(){
  return isnoiso ;
}


void ProcessArgs(int argc, char** argv, Params& params);
//double GetMass(int pdg);
//Hep3Vector PointPv(double Energy, double Mass);
//map<int, double> pdg_mass;
//double PI = 3.1415926;

/*
void LoadReadFile(TString infile);
void LoadOutTree();
void initial();
int GetTreePars(int evtid);
int GetIsoP(int evtid);
int GetIsoN(int evtid);
void ReadTreeEvent(int id, int evtid);
void ReadIsoInfo(int pars, int evtid);
void ReadDeexInfo(int pars, int resp, int resn, int exetag, TString datadir);
bool ISSTABLEFLAG(int evtid);
bool ISNOISOFLAG(int evtid);
bool ISQEL(int evtid);
bool ISHighEEvt(int evtid);
int GetType(int evtid);
double getExE(int rZ, int rN);
double getExEval(double* frac);
*/
//int m_evtID;

//int m_pPdg;
//int m_tPdg;
//double m_pEn;
//int m_channelID;
//int m_interType;  // 1-----QEL; 2-----RES; 3-----COH/DFR; 4-----DIS; 5------MEC; -1 -------others

/*double m_tPx,m_tPy,m_tPz;
double m_tRemovalE;
double m_tE;
double m_tMass;

int m_isoPDG;
double m_isoPx, m_isoPy, m_isoPz;
int m_Npars;
int m_pdg[100];
double m_px[100];      // GeV
double m_py[100];      // GeV
double m_pz[100];      // GeV
double m_energy[100];  // GeV
double m_mass[100];    // GeV
double m_energyT[100];*/

/*TFile* genieFile;
TTree* geTree;

TFile* outFile;
TTree* outTree;*/
/*
int t_evtID;
int t_pPdg;

double t_tPx,t_tPy,t_tPz;
double t_tRemovalE;
double t_tE;
double t_tMass;


int t_tPdg;
double t_pEn;
int t_channelID;
int t_interType;
int t_deexID;
double t_deEx;
int t_isoPdg;
int t_Npars;
int t_type;
int t_pdg[100];
int t_tag[100];    // --- 0 : from GENIE or NuWro  --- 1 : from TALYS   --- 3 : isotope
double t_px[100];  // GeV
double t_py[100];  // GeV
double t_pz[100];  // GeV
double t_ek[100];  // GeV
double t_ektest[100];  // GeV
double t_mass[100];  // GeV*/
/*FILE* stream = stdout;

Hep3Vector pv;
int gammapdg = 22;
double gammamass = 0;
int count00 = 0;

//-----------------------based on simple shell model
double ExcitedE[5] = {0, 23, 46, 69, 92};
double fracIso1[5] = {2. / 3., 1. / 3., 0., 0., 0.};                                 //--------------> for C-11 and B-11
double fracIso2[5] = {6. / 15., 8. / 15., 1. / 15., 0., 0.};                         //--------------> for C-10 and Be-10
double fracIso3[5] = {4. / 7., 2. / 7., 1. / 7., 0., 0.};                            //--------------> for B-10
double fracIso4[5] = {1. / 5., 3. / 5., 1. / 5., 0., 0.};                            //--------------> for Li-9/C-9
double fracIso5[5] = {12. / 45., 22. / 45., 10. / 45., 1. / 45., 0.};                //--------------> for Be-9/B-9
double fracIso6[5] = {2. / 15., 7. / 15., 5. / 15., 1. / 15., 0.};                   //--------------> for B-8/Li-8
double fracIso7[5] = {36. / 225., 96. / 225., 76. / 225., 16. / 225., 1. / 225.};    //--------------> for Be-8
double fracIso8[5] = {24. / 300., 104. / 300., 124. / 300., 44. / 300., 4. / 300.};  //--------------> for Li-7/Be-7
std::map<double, double> exe_pro;

//---------------//

deex* DEProcess;*/
