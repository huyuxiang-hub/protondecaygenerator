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


void ProcessArgs(int argc, char** argv, Params& params);
double GetMass(int pdg);
Hep3Vector PointPv(double Energy, double Mass);
map<int, double> pdg_mass;
double PI = 3.1415926;

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

int m_evtID;

//int m_pPdg;
int m_tPdg;
//double m_pEn;
//int m_channelID;
//int m_interType;  // 1-----QEL; 2-----RES; 3-----COH/DFR; 4-----DIS; 5------MEC; -1 -------others

double m_tPx,m_tPy,m_tPz;
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
double m_energyT[100];

TFile* genieFile;
TTree* geTree;

TFile* outFile;
TTree* outTree;

int t_evtID;
//int t_pPdg;
//
double t_tPx,t_tPy,t_tPz;
double t_tRemovalE;
double t_tE;
double t_tMass;


int t_tPdg;
//double t_pEn;
//int t_channelID;
//int t_interType;
int t_deexID;
double t_deEx;
int t_isoPdg;
int t_Npars;
int t_type;
int t_pdg[100];
//int t_tag[100];    // --- 0 : from GENIE or NuWro  --- 1 : from TALYS   --- 3 : isotope
double t_px[100];  // GeV
double t_py[100];  // GeV
double t_pz[100];  // GeV
double t_ek[100];  // GeV
double t_ektest[100];  // GeV
double t_mass[100];  // GeV
FILE* stream = stdout;

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

