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

deex::deex(int Z, int N, int Extag, TString datadir)
{

  initial();
  TString name = isotopename(Z);
  // Deedata = "/junofs/users/chengj/workdir/NC/generator/talys/talys_sample/";
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
  ResidualZ = 0;
  ResidualN = 0;
  isoname.clear();
  deeParE.clear();
  deePDG.clear();
}

TString deex::isotopename(int Z)
{
  isoname.clear();
  isoname[6] = "C";
  isoname[5] = "B";
  isoname[4] = "Be";
  isoname[3] = "Li";
  return isoname[Z];
}

void deex::LoadDeeData()
{
  Deefile = new TFile(Deedata, "read");
  if (!Deefile) {
    cout << "not find right file!" << endl;
    // exit(0);
  }

  Nucldee = (TTree*)Deefile->Get("TreeNucldee");
  Nucldee->SetBranchAddress("deexchiID", &deexchiID);
  Nucldee->SetBranchAddress("isoRZ", &isoRZ);
  Nucldee->SetBranchAddress("isoRN", &isoRN);
  Nucldee->SetBranchAddress("ndeexPars", &ndeexPars);
  Nucldee->SetBranchAddress("deexPartag", deexPartag);
  Nucldee->SetBranchAddress("deexParEn", deexParEn);
}

void deex::CloseDeeFile()
{
  Deefile->Close();
}

void deex::GetDeeProcess()
{
  LoadDeeData();
  int entries = (int)Nucldee->GetEntries();
  int entry = int(gRandom->Uniform(0, entries));
  Nucldee->GetEntry(entry);
  DeexID = deexchiID;
  for (int jj = 0; jj < ndeexPars; jj++) {
    deeParE.push_back(deexParEn[jj]);
    deePDG.push_back(deexPartag[jj]);
  }
  ResidualZ = isoRZ;
  ResidualN = isoRN;
  CloseDeeFile();
}

std::vector<double> deex::GetDeeParE()
{
  return deeParE;
}

std::vector<int> deex::GetDeePDG()
{
  return deePDG;
}

int deex::GetResNuelZ()
{
  return ResidualZ;
}

int deex::GetResNuelN()
{
  return ResidualN;
}

int deex::GetDeexChannelID()
{
  return DeexID;
}
