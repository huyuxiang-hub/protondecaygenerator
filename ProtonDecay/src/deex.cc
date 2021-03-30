#include "deex.h"
#include <iostream>
#include <TROOT.h>
#include <TRandom.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <map>
#include <stdio.h>

using namespace std;

deex::deex(TString datadir)
{
  Deedata = datadir;  
  initial();
 // TString name = isotopename(Z);
  // Deedata = "/junofs/users/chengj/workdir/NC/generator/talys/talys_sample/";
 /* Deedata = datadir;
  Deedata += "/talys_sample/";
  Deedata += name;
  int A = Z + N;
  Deedata += A;
  Deedata += "_";
  Deedata += Extag;
  Deedata += "_";
  Deedata += "deexcitation.root";

  deexZ = Z;
  deexN = N;*/
  
}

deex::~deex(){

   std::map<TString,TFile*>::iterator it;
   for (it=TString2File.begin(); it!=TString2File.end(); ++it){
      (it->second)->Close();
      std::cout<<it->first<<std::endl;
   }
}
void deex::SetParams(int Z, int N){

 /* TString name = isoname[Z];
  Deedata = datadir;
  Deedata += "/talys_sample/";
  Deedata += name;
  int A = Z + N;
  Deedata += A;
  Deedata += "_";
  Deedata += Extag;
  Deedata += "_";
  Deedata += "deexcitation.root";
  */
  deexZ = Z;
  deexN = N;
  caculateExE();
  
 }

void deex::caculateExE(){
  int temA = deexZ + deexN;
  double exeval = -1;
  if (temA == 11) {
    exeval = getExEval(fracIso1);
  } else if (temA == 10) {
    if (deexZ> 5 || deexN > 5) {
      exeval = getExEval(fracIso2);
    } else {
      exeval = getExEval(fracIso3);
    }
  } else if (temA == 9) {
    if (deexZ == 3 || deexN == 3) {
      exeval = getExEval(fracIso4);
    } else {
      exeval = getExEval(fracIso5);
    }
  } else if (temA == 8) {
    if (deexZ == 3 || deexN == 3) {
      exeval = getExEval(fracIso6);
    } else {
      exeval = getExEval(fracIso7);
    }
  } else {

    exeval = getExEval(fracIso8);
  }
  
   exe = exeval;
   Extag = (int)exeval; 

}

double deex::getExEval(double*frac){

  double exeval0 = -1;
  exe_pro.clear();
  for (int i = 0; i < 5; i++) {
    exe_pro.insert(std::map<double, double>::value_type(ExcitedE[i], frac[i]));
  }
  std::map<double, double>::iterator it;

  double last_pro = 0.;
  double curr_pro = 0.;
  double seed1 = gRandom->Uniform(0, 1);
  for (it = exe_pro.begin(); it != exe_pro.end(); ++it) {
    curr_pro = (it->second) + last_pro;
    if (seed1 < curr_pro && seed1 >= last_pro) {
      exeval0 = it->first;
      break;
    }
    last_pro = (it->second) + last_pro;
  }

 // exe_pro.clear();
  return exeval0;
}

void deex::initial()
{
 isoname[6] = "C";
 isoname[5] = "B";
 isoname[4] = "Be";
 isoname[3] = "Li";
/*
 ExcitedE[5] = {0, 23, 46, 69, 92};
 fracIso1[5] = {2. / 3., 1. / 3., 0., 0., 0.};                                 //--------------> for C-11 and B-11
 fracIso2[5] = {6. / 15., 8. / 15., 1. / 15., 0., 0.};                         //--------------> for C-10 and Be-10
 fracIso3[5] = {4. / 7., 2. / 7., 1. / 7., 0., 0.};                            //--------------> for B-10
 fracIso4[5] = {1. / 5., 3. / 5., 1. / 5., 0., 0.};                            //--------------> for Li-9/C-9
 fracIso5[5] = {12. / 45., 22. / 45., 10. / 45., 1. / 45., 0.};                //--------------> for Be-9/B-9
 fracIso6[5] = {2. / 15., 7. / 15., 5. / 15., 1. / 15., 0.};                   //--------------> for B-8/Li-8
 fracIso7[5] = {36. / 225., 96. / 225., 76. / 225., 16. / 225., 1. / 225.};    //--------------> for Be-8
 fracIso8[5] = {24. / 300., 104. / 300., 124. / 300., 44. / 300., 4. / 300.};
*/

 /* 
  ResidualZ = 0;
  ResidualN = 0;
  isoname.clear();
  deeParE.clear();
  deePDG.clear();*/
}

/*
TString deex::isotopename(int Z)
{
  return isoname[Z];
}
*/
void deex::LoadDeeData()
{
  int A = deexZ + deexN;
  TString Deefilename = Deedata + "/talys_sample/"+isoname[deexZ]+A+"_"+Extag+"_deexcitation.root";
  std::cout<<Deefilename<<std::endl;
  std::map<TString,TFile*>::iterator it;
  it = TString2File.find(Deefilename);
 
  if(it != TString2File.end()) {
        std::cout<<"no new file??"<<std::endl;
        Nucldee = (TTree*)(it->second)->Get("TreeNucldee");
     }
  else{
       std::cout<<"add new file??"<<std::endl;
       TFile* Deefile = new TFile(Deefilename, "read");
       if (!Deefile) {
           cout << "not find right file!" << endl;
           exit(0);
           }
       Nucldee = (TTree*)(Deefile)->Get("TreeNucldee");       
       TString2File.insert(std::pair<TString,TFile*>(Deefilename,Deefile));  

    }
  	Nucldee->SetBranchAddress("deexchiID", &aAfterDeexInfo.DeexChannelID);
  	Nucldee->SetBranchAddress("isoRZ", &aAfterDeexInfo.ResidualZ);
  	Nucldee->SetBranchAddress("isoRN", &aAfterDeexInfo.ResidualN);
  	Nucldee->SetBranchAddress("ndeexPars", &aAfterDeexInfo.NPars);
  	Nucldee->SetBranchAddress("deexPartag", deexPartag);
  	Nucldee->SetBranchAddress("deexParEn", deexParEn);

}

/*void deex::CloseDeeFile()
{
  Deefile->Close();
}
*/
void deex::GetDeeProcess()
{
  aAfterDeexInfo.Energy.clear();
  aAfterDeexInfo.Pdg.clear();
  LoadDeeData();
  int entries = (int)Nucldee->GetEntries();
  int entry = int(gRandom->Uniform(0, entries));
  Nucldee->GetEntry(entry);
 // DeexID = deexchiID;
  for (int jj = 0; jj < aAfterDeexInfo.NPars; jj++) {
     aAfterDeexInfo.Energy.push_back(deexParEn[jj]);
     aAfterDeexInfo.Pdg.push_back(deexPartag[jj]);
  }
 // ResidualZ = isoRZ;
 // ResidualN = isoRN;
  aAfterDeexInfo.ResidualPdg = 1000000000 + aAfterDeexInfo.ResidualZ * 10000 + (aAfterDeexInfo.ResidualZ + aAfterDeexInfo.ResidualN) * 10; 
  
  
  //CloseDeeFile();
}

std::vector<double> deex::GetDeeParE()
{
  return aAfterDeexInfo.Energy;
}

std::vector<int> deex::GetDeePDG()
{
  return aAfterDeexInfo.Pdg;
}

int deex::GetResNuelZ()
{  
  return aAfterDeexInfo.ResidualZ;
}

int deex::GetResNuelN()
{
  return aAfterDeexInfo.ResidualN;
}

int deex::GetDeexChannelID()
{
  return aAfterDeexInfo.DeexChannelID;
}
