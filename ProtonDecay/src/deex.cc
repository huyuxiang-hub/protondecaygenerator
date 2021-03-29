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

deex::deex()
{

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
void deex::InputParams(int Z, int N, int Extag, TString datadir){

  TString name = isoname[Z];
  Deedata = datadir;
  Deedata += "/talys_sample/";
  Deedata += name;
  int A = Z + N;
  Deedata += A;
  Deedata += "_";
  Deedata += Extag;
  Deedata += "_";
  Deedata += "deexcitation.root";

  deexZ = Z;
  deexN = N;
 }


void deex::initial()
{
 isoname[6] = "C";
 isoname[5] = "B";
 isoname[4] = "Be";
 isoname[3] = "Li";
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
  Deefile = new TFile(Deedata, "read");
  if (!Deefile) {
    cout << "not find right file!" << endl;
    // exit(0);
  }

  Nucldee = (TTree*)Deefile->Get("TreeNucldee");
  Nucldee->SetBranchAddress("deexchiID", &aAfterDeexInfo.DeexChannelID);
  Nucldee->SetBranchAddress("isoRZ", &aAfterDeexInfo.ResidualZ);
  Nucldee->SetBranchAddress("isoRN", &aAfterDeexInfo.ResidualN);
  Nucldee->SetBranchAddress("ndeexPars", &aAfterDeexInfo.NPars);
  Nucldee->SetBranchAddress("deexPartag", deexPartag);
  Nucldee->SetBranchAddress("deexParEn", deexParEn);
}

void deex::CloseDeeFile()
{
  Deefile->Close();
}

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
  
  
  CloseDeeFile();
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
