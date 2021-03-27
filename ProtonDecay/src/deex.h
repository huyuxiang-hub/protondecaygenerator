#ifndef _DEEX_
#define _DEEX_

#include <iostream>
#include <TROOT.h>
#include <TRandom.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <map>
#include <vector>

class deex {

  public:
    deex(int Z, int N, int Extag, TString datadir);
    ~deex() {};
   
    void initial(); 
    void CloseDeeFile();
    TString isotopename(int Z);
    void LoadDeeData();
    void GetDeeProcess();
    
    std::vector<double> GetDeeParE();
    std::vector<int> GetDeePDG();
    int GetResNuelZ();
    int GetResNuelN();
    int GetDeexChannelID();

            
  private:
    TFile *Deefile;
    TTree *Nucldee;
    TString Deedata;
    
  private:
    int deexZ;
    int deexN;
    int ResidualZ;
    int ResidualN;
    int DeexID;
    std::map<int, TString> isoname;

    std::vector<double> deeParE;
    std::vector<int> deePDG;

    int deexchiID;
    int isoRZ;
    int isoRN;
    int ndeexPars;
    int deexPartag[20];
    double deexParEn[20];
    
};

#endif

