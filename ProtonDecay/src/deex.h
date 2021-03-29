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

struct  AfterDeexInfo{
    AfterDeexInfo(){
    Energy.clear();
    Pdg.clear();
    ResidualZ = 0;
    ResidualN = 0;
    DeexChannelID = 0;
    NPars = 0 ;   
    ResidualPdg = 0 ;

    }  


    std::vector<double> Energy;
    std::vector<int>    Pdg;
    int  ResidualZ;
    int  ResidualN;
    int  DeexChannelID;
    int  NPars;
    int  ResidualPdg;
    
    
};



class deex {

  public:
    deex();
    ~deex() {};
   
    void initial(); 
    void CloseDeeFile();
    void LoadDeeData();
    void GetDeeProcess();
    void InputParams(int Z, int N, int Extag, TString datadir);
    AfterDeexInfo &  GetAfterDeexInfo(){ GetDeeProcess(); return aAfterDeexInfo;}
     
    //-----------------------------------//
    std::vector<double> GetDeeParE();
    std::vector<int> GetDeePDG();
    int GetResNuelZ();
    int GetResNuelN();
    int GetDeexChannelID();
   
  private:
   AfterDeexInfo  aAfterDeexInfo;            

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

