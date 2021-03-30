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
    deex(TString datadir);
    ~deex();
   
    void initial(); 
    void CloseDeeFile();
    void LoadDeeData();
    void GetDeeProcess();
    void SetParams(int Z,int N);
    AfterDeexInfo &  GetAfterDeexInfo(){ GetDeeProcess(); return aAfterDeexInfo;}
    //-------------------------------------//
    private:
      int Extag;
      double exe;
    public:
      void caculateExE();
      double GetExE(){return exe;}
      
      double getExEval(double *frac);

     
    //-----------------------------------//
    std::vector<double> GetDeeParE();
    std::vector<int> GetDeePDG();
    int GetResNuelZ();
    int GetResNuelN();
    int GetDeexChannelID();
   
  private:
   AfterDeexInfo  aAfterDeexInfo;            

  private:
   // TFile *Deefile;
    TTree *Nucldee;
    TString Deedata;
    std::map<TString,TFile*> TString2File;
  private:
    int deexZ;
    int deexN;
   // int ResidualZ;
   // int ResidualN;
   // int DeexID;
    std::map<int, TString> isoname;

   // std::vector<double> deeParE;
   // std::vector<int> deePDG;

   // int deexchiID;
   // int isoRZ;
   // int isoRN;
   // int ndeexPars;
    int deexPartag[20];
    double deexParEn[20];
   
    //--------------------------//
   
private:
std::map<double, double> exe_pro;
double ExcitedE[5] = {0, 23, 46, 69, 92};
double fracIso1[5] = {2. / 3., 1. / 3., 0., 0., 0.};                                 //--------------> for C-11 and B-11
double fracIso2[5] = {6. / 15., 8. / 15., 1. / 15., 0., 0.};                         //--------------> for C-10 and Be-10
double fracIso3[5] = {4. / 7., 2. / 7., 1. / 7., 0., 0.};                            //--------------> for B-10
double fracIso4[5] = {1. / 5., 3. / 5., 1. / 5., 0., 0.};                            //--------------> for Li-9/C-9
double fracIso5[5] = {12. / 45., 22. / 45., 10. / 45., 1. / 45., 0.};                //--------------> for Be-9/B-9
double fracIso6[5] = {2. / 15., 7. / 15., 5. / 15., 1. / 15., 0.};                   //--------------> for B-8/Li-8
double fracIso7[5] = {36. / 225., 96. / 225., 76. / 225., 16. / 225., 1. / 225.};    //--------------> for Be-8
double fracIso8[5] = {24. / 300., 104. / 300., 124. / 300., 44. / 300., 4. / 300.};


    
};

#endif

