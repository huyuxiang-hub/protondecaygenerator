// nc generator  include deexcitation process, author : Jie Cheng , email : chengjie@ihep.ac.cn
// NC six nuclear models :
// -f 2 : model1 : genie+talys , event rate = 3.59*1e-5/s/20kton
// -f 3 : model3 : nuwro-1 + talys , event rate = 2.82586*1e-5/s/20kton
// -f 4 : model2 : nuwro-2 + talys , event rate = 2.885*1e-5/s/20kton
// -f 5 : model4 : nuwro-3 + talys , event rate = 3.341*1e-5/s/20kton
// -f 6 : model5 : nuwro-4 + talys , event rate = 3.28265*1e-5/s/20kton
// -f 7 : model6 : nuwro-5 + talys , event rate = 2.14872*1e-5/s/20kton
// difference between models, please see https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/ShowDocument?docid=3210
//  CC nuclear model :
//  -f 1 : genie + talys , event rate = 8.0*1e-5/s
//  genie includes neutrino+C12 and neutrino+p interaction for NC and CC
//  nuwro only includes neutrino+C12
#include "deex.h"
#include "ProtonDecayGen.h"

using namespace std;
using namespace CLHEP;
/*
struct Params{

   Params(){
     rseed = 0;
     nEvents = 1000000;
     outFilename=NULL; 
     stream = stdout;
     data_dir = getenv("JUNOTOP")+"/data/Generator/ProtonDecay/data";        
     GenieFilename = "pd1.1.ghep.histo.root";
   }
   long rseed;
   unsigned long int nEvents;
   TString data_dir;         
   TString GenieFilename;
   char* outFilename; 
   FILE* stream ; 
};

*/
//class  ProtonDecayEvent;

int main(int argc, char** argv)
{
  
  Params params;
 
//  char* outFilename = NULL;
//  char* user_output = NULL;
//  int flag = 2;
  ProcessArgs(argc, argv, params);
  TString path_name = params.data_dir+params.GenieFilename;
  cout<<path_name<<endl;
  
  ProtonDecayEvent* aEvent = new ProtonDecayEvent(path_name);

 // LoadReadFile(params.data_dir+params.GenieFilename);
  gRandom->SetSeed(params.rseed);
  deex* DEProcess = new deex(params.data_dir);  
 
  
 // bool IsStableFlag = false;
 // bool IsNoIsoFlag = false;

 // DEProcess = new deex;
   
 
  int nentries = aEvent->GetEntries();
  for (int i = 0; i < params.nEvents; i++) {
    int ievent = (int)(gRandom->Uniform() * (nentries - 1));
    aEvent->LoadEvent(ievent);
  //  initial();
  //  IsStableFlag = false;
  //  IsNoIsoFlag = false;


    int PARS = aEvent->GetNpars();
//    bool isQEL = ISQEL(ievent);
//    bool ishigh = ISHighEEvt(ievent);
    //if(isQEL==false || ishigh== true) {
  /*  if(isQEL==false) {
      i--;
      continue;
    }*/
   // IsStableFlag = ISSTABLEFLAG(ievent);
   // IsNoIsoFlag = ISNOISOFLAG(ievent);
    if (aEvent->GetIsNoIsoFlag()) {
      aEvent-> PrintTotalPars(PARS);
      //std::cout<<"isnoisoflag="<<aEvent->GetIsNoIsoFlag()<<endl;
     // fprintf(stream, "%d\n", PARS);
      //ReadTreeEvent(i, ievent);
      aEvent->PrintNormPars();
     // t_Npars = PARS;
    } else if (aEvent -> GetIsStableFlag() ) {
      aEvent->PrintTotalPars(PARS+1);
     // fprintf(stream, "%d\n", PARS + 1);
     // ReadTreeEvent(i, ievent);
      aEvent->PrintNormPars();
     // ReadIsoInfo(PARS, ievent);
      aEvent->PrintIos();
     // t_Npars = PARS + 1;
    } else {
      
      int rp = aEvent->GetIsoP();
      int rn = aEvent->GetIsoN();
      std::cout<<"rp="<<rp<<std::endl;
      std::cout<<"rn="<<rn<<std::endl;
    
      DEProcess->SetParams(rp,rn);
      
      double exe = DEProcess-> GetExE();
     // std::cout<<"exe="<<exe<<endl;

      if (exe > 0) {
        aEvent -> Info = DEProcess -> GetAfterDeexInfo();
        
      
        aEvent->PrintDeexInfo();
        aEvent->PrintNormPars();
        //ReadTreeEvent(i, ievent);
      //  t_Npars = count00;
      } else {
        aEvent->PrintTotalPars(PARS+1);
        aEvent->PrintNormPars();
        aEvent->PrintIos();   
       // ReadTreeEvent(i, ievent);
       // ReadIsoInfo(PARS, ievent);
       // t_Npars = PARS + 1;
      }
    }
   /* std::cout << "---> Jie Check === simulated particles (event " << i << " ) "<< "\t";
    for(int cc=0; cc<t_Npars; cc++) {
      std::cout << t_pdg[cc] << "\t";
    }
    std::cout << endl;
   
    if (IsExistUserFile == true) {
      outTree->Fill();
    }*/
  }
 /* if (IsExistUserFile == true) {
    outFile->cd();
    outTree->Write();
    outFile->Close();
  }*/
  delete DEProcess;  
  return 0;
}

/*void initial()
{
  t_evtID = 0;
  t_Npars = 0;
  t_type = 0;
  //t_pPdg = 0;
  t_tPdg = 0;
  t_tPx=0;
  t_tPy=0;
  t_tPz=0;
  t_tMass=0;
  t_tE=0; 
  t_tRemovalE=0;

 // t_pEn = 0;
  t_isoPdg = 0;
 // t_channelID = 0;
 // t_interType = 0;
  t_deexID = 0;
  t_deEx = 0.;

  for (int jj = 0; jj < 100; jj++) {
    t_pdg[jj] = 0;
   // t_tag[jj] = 0;
    t_px[jj] = 0.;
    t_py[jj] = 0.;
    t_pz[jj] = 0.;
    t_ek[jj] = 0.;
    t_ektest[jj] = 0.;
    t_mass[jj] = 0.;
  }
}*/
/*void LoadReadFile(TString infile)
{

  genieFile = TFile::Open(infile, "read");
  if (!genieFile) {
    cout << "Can not find file: " << infile << endl;
    exit(-1);
  }
  geTree = (TTree*)genieFile->Get("events");
 // geTree->SetBranchAddress("pPdg", &m_pPdg);
  geTree->SetBranchAddress("evtID", &m_evtID);
  geTree->SetBranchAddress("tPdg", &m_tPdg);
 // geTree->SetBranchAddress("pEn", &m_pEn);
  geTree->SetBranchAddress("tPx", &m_tPx);
  geTree->SetBranchAddress("tPy", &m_tPy);
  geTree->SetBranchAddress("tPz", &m_tPz);
  geTree->SetBranchAddress("tE", &m_tE);
  geTree->SetBranchAddress("tMass", &m_tMass);
  geTree->SetBranchAddress("tRemovalE", &m_tRemovalE);
  
  //geTree->SetBranchAddress("channelID", &m_channelID);
 // geTree->SetBranchAddress("interType", &m_interType);
  geTree->SetBranchAddress("m_isoPDG", &m_isoPDG);
  geTree->SetBranchAddress("m_isoPx", &m_isoPx);
  geTree->SetBranchAddress("m_isoPy", &m_isoPy);
  geTree->SetBranchAddress("m_isoPz", &m_isoPz);
  geTree->SetBranchAddress("Npars", &m_Npars);
  geTree->SetBranchAddress("pdg", m_pdg);
  geTree->SetBranchAddress("px", m_px);
  geTree->SetBranchAddress("py", m_py);
  geTree->SetBranchAddress("pz", m_pz);
  geTree->SetBranchAddress("energy", m_energy);
  geTree->SetBranchAddress("mass", m_mass);
  geTree->SetBranchAddress("energyT", m_energyT); 
}*//*
void LoadOutTree()
{

  outTree = new TTree("genEvt", "genEvent");
  outTree->Branch("t_evtID", &t_evtID, "t_evtID/I");
 // outTree->Branch("t_pPdg", &t_pPdg, "t_pPdg/I");
  outTree->Branch("t_tPdg", &t_tPdg, "t_tPdg/I");
 // outTree->Branch("t_pEn", &t_pEn, "t_pEn/D");
  //outTree->Branch("t_channelID", &t_channelID, "t_channelID/I");
  //outTree->Branch("t_interType", &t_interType, "t_interType/I");
  outTree->Branch("t_tPx", &t_tPx, "t_tPx/D");
  outTree->Branch("t_tPy", &t_tPy, "t_tPy/D");
  outTree->Branch("t_tPz", &t_tPz, "t_tPz/D");
  outTree->Branch("t_tE", &t_tE, "t_tE/D");
  outTree->Branch("t_tMass", &t_tMass, "t_tMass/D"); 
  outTree->Branch("t_tRemovalE", &t_tRemovalE, "t_tRemovalE/D"); 
  
  outTree->Branch("t_deexID", &t_deexID, "t_deexID/I");
  outTree->Branch("t_deEx", &t_deEx, "t_deEx/D");
  outTree->Branch("t_isoPdg", &t_isoPdg, "t_isoPdg/I");
  outTree->Branch("t_Npars", &t_Npars, "t_Npars/I");
  outTree->Branch("t_type", &t_type, "t_type/I");
  outTree->Branch("t_pdg", t_pdg, "t_pdg[t_Npars]/I");
  //outTree->Branch("t_tag", t_tag, "t_tag[t_Npars]/I");
  outTree->Branch("t_px", t_px, "t_px[t_Npars]/D");
  outTree->Branch("t_py", t_py, "t_py[t_Npars]/D");
  outTree->Branch("t_pz", t_pz, "t_pz[t_Npars]/D");
  outTree->Branch("t_ek", t_ek, "t_ek[t_Npars]/D");
  outTree->Branch("t_ektest", t_ektest, "t_ektest[t_Npars]/D");
  outTree->Branch("t_mass", t_mass, "t_mass[t_Npars]/D");
}
*/
/*
int GetTreePars(int evtid)
{
  geTree->GetEntry(evtid);
  return m_Npars;
}

int GetIsoP(int evtid)
{
  geTree->GetEntry(evtid);
  int rp = int((m_isoPDG - 1000000000) / 10000);
  return rp;
}

int GetIsoN(int evtid)
{
  geTree->GetEntry(evtid);
  int rp = int((m_isoPDG - 1000000000) / 10000);
  int rn = int((m_isoPDG - 1000000000 - rp * 10000) / 10) - rp;
  return rn;
}
*/
/*
bool ISSTABLEFLAG(int evtid)
{
  bool isstable = false;
  geTree->GetEntry(evtid);
  int rp = GetIsoP(evtid);
  int rn = GetIsoN(evtid);
  if (m_isoPDG == 1000060120 || m_isoPDG == 1000030060 || rp < 3 || rn < 3 || rp>6 || rn>6) {
    isstable = true;
  }
  return isstable;
}

*/
/*
bool ISNOISOFLAG(int evtid)
{
  bool isnoiso = false;
  geTree->GetEntry(evtid);
  if (m_isoPDG == 0 || m_channelID == 2 || m_channelID == 3*) {
    isnoiso = true;
  }
  int rp = GetIsoP(evtid);
  int rn = GetIsoN(evtid); 
  if (rp + rn > 11){
     
     isnoiso = true;
  } 

  return isnoiso;
}
int GetType(int evtid)
{
  int type = 0;
  geTree->GetEntry(evtid);
  if (m_isoPDG == 1000060110) {
    type = 611;
  }
  if (m_isoPDG == 1000050110) {
    type = 511;
  }
  if (m_isoPDG == 1000050100) {
    type = 510;
  }
  if (m_isoPDG == 1000060100) {
    type = 610;
  }
  if (m_isoPDG == 1000040100) {
    type = 410;
  }
  return type;
}
*/
/*bool ISQEL(int evtid)
{
  bool isqel = false;
  geTree->GetEntry(evtid);
  if (m_interType==1 || m_interType==5) {
    isqel = true;
  }
  return isqel;
}
*//*
bool ISHighEEvt(int evtid)
{
  bool ishighe = false;
  geTree->GetEntry(evtid);
  double tfinalnuE = 0.;
  for(int jj=0; jj<m_Npars; jj++) {
    if(m_pdg[jj]==12 || m_pdg[jj]==-12 || m_pdg[jj]==14 || m_pdg[jj]==-14) {
      tfinalnuE = sqrt(m_px[jj]*m_px[jj] + m_py[jj]*m_py[jj] +  m_pz[jj]*m_pz[jj]);
    }
  }
  double entrans = m_pEn-tfinalnuE;
  if(entrans>0.1) {
    ishighe=true;
  }

  return ishighe;
}
*/
/*
void ReadTreeEvent(int id, int evtid)
{
  geTree->GetEntry(evtid);
  t_evtID = id;
 // t_pPdg = m_pPdg;
  t_tPdg = m_tPdg;
  t_isoPdg = m_isoPDG;
  //t_channelID = m_channelID;
 // t_interType = m_interType;
//t_pEn = m_pEn;
  for (int jj = 0; jj < m_Npars; jj++) {
    fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", m_pdg[jj], m_px[jj], m_py[jj], m_pz[jj], m_mass[jj]);
    t_pdg[jj] = m_pdg[jj];
   // t_tag[jj] = 0;
    t_px[jj] = m_px[jj];
    t_py[jj] = m_py[jj];
    t_pz[jj] = m_pz[jj];
    t_mass[jj] = m_mass[jj];
    t_ek[jj] = sqrt(t_px[jj]*t_px[jj] + t_py[jj]*t_py[jj] + t_pz[jj]*t_pz[jj] + t_mass[jj]*t_mass[jj]) - t_mass[jj];
  }
}

void ReadIsoInfo(int pars, int evtid)
{
  geTree->GetEntry(evtid);
  double isomass = GetMass(m_isoPDG);
  fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", m_isoPDG, m_isoPx, m_isoPy, m_isoPz, isomass);
  t_pdg[pars] = m_isoPDG;
  //t_tag[pars] = 3;
  t_px[pars] = m_isoPx;
  t_py[pars] = m_isoPy;
  t_pz[pars] = m_isoPz;
  t_mass[pars] = isomass;
  t_ek[pars] = 0.;
}


void ReadDeexInfo(int pars, int resp, int resn, int exetag, TString datadir)
{
 // vector<double> afterDeexEn;
 // vector<int> afterDeexPDG;
  AfterDeexInfo info;
  DEProcess->InputParams(resp, resn, exetag, datadir);
  
 // deex* DEProcess = new deex(resp, resn, exetag, datadir);
  //DEProcess->GetDeeProcess();
  info = DEProcess -> GetAfterDeexInfo();
 // afterDeexEn = DEProcess->GetDeeParE();
 // afterDeexPDG = DEProcess->GetDeePDG();
 // int residulZafterDee = DEProcess->GetResNuelZ();
 // int residulNafterDee = DEProcess->GetResNuelN();
 // int deexID = DEProcess->GetDeexChannelID();
 // t_deexID = deexID;
  t_deexID = info.DeexChannelID;
  t_deEx = double(exetag);
  count00 = 0;
  count00 = pars + info.NPars;
 // count00 = pars + afterDeexEn.size();
  if (info.ResidualZ >= 3 && info.ResidualN >= 3) {
    count00 = count00 + 1;
  }
  fprintf(stream, "%d\n", count00);
  for (int kk = 0; kk < info.NPars; kk++) {
    //pv = PointPv(afterDeexEn[kk]);
    double MASS = GetMass(info.Pdg[kk]);
    pv = PointPv(info.Energy[kk], MASS);
    fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", info.Pdg[kk], pv.x(), pv.y(), pv.z(), MASS);
    t_pdg[pars + kk] = info.Pdg[kk];
   // t_tag[pars + kk] = 1;
    t_px[pars + kk] = pv.x();
    t_py[pars + kk] = pv.y();
    t_pz[pars + kk] = pv.z();
    t_mass[pars+kk] = MASS;
    t_ek[pars +kk] = sqrt( t_px[pars + kk]* t_px[pars + kk] + t_py[pars + kk]*t_py[pars + kk] +  t_pz[pars + kk]* t_pz[pars + kk] +  t_mass[pars+kk]* t_mass[pars+kk]) -  t_mass[pars+kk];
    t_ektest[pars+kk] = info.Energy[kk];
  }
  if (info.ResidualN >= 3 && info.ResidualZ >= 3) {
   // int isoPdgafterDeex = 1000000000 + info.ResidualZ * 10000 + (info.ResidualZ+info.ResidualN) * 10;
    double isomassafterDeex = GetMass(info.ResidualPdg);
    fprintf(stream, "1\t%d 0 0 %f %f %f %f\n", info.ResidualPdg, m_isoPx, m_isoPy, m_isoPz, isomassafterDeex);
    t_pdg[count00 - 1] = info.ResidualPdg;
   // t_tag[count00 - 1] = 3;
    t_px[count00 - 1] = m_isoPx;
    t_py[count00 - 1] = m_isoPy;
    t_pz[count00 - 1] = m_isoPz;
    t_mass[count00 -1] = isomassafterDeex;
    t_ek[count00-1] = 0.;
  }
}


Hep3Vector PointPv(double Energy, double Mass)
{
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
  phi = gRandom->Uniform(0, 2 * PI);
  xdir = sint * cos(phi);
  ydir = sint * sin(phi);
  zdir = cost;
  //double px = xdir * Energy * 1e-3;  // GeV
  //double py = ydir * Energy * 1e-3;  // GeV
  //double pz = zdir * Energy * 1e-3;  // GeV
  double px = xdir * Pval;  // GeV
  double py = ydir * Pval;  // GeV
  double pz = zdir * Pval;  // GeV
  Hep3Vector Pv;
  Pv = Hep3Vector(px, py, pz);
  return Pv;
}


double getExE(int rZ, int rN)
{
  int temA = rZ + rN;
  double exeval = -1;
  if (temA == 11) {
    exeval = getExEval(fracIso1);
  } else if (temA == 10) {
    if (rZ > 5 || rZ > 5) {
      exeval = getExEval(fracIso2);
    } else {
      exeval = getExEval(fracIso3);
    }
  } else if (temA == 9) {
    if (rZ == 3 || rN == 3) {
      exeval = getExEval(fracIso4);
    } else {
      exeval = getExEval(fracIso5);
    }
  } else if (temA == 8) {
    if (rZ == 3 || rN == 3) {
      exeval = getExEval(fracIso6);
    } else {
      exeval = getExEval(fracIso7);
    }
  } else {

    exeval = getExEval(fracIso8);
  }

  return exeval;
}

double getExEval(double* frac)
{
  //-----------------------based on simple shell model
  double exeval0 = -1;
  exe_pro.clear();
  for (int ii = 0; ii < 5; ii++) {
    exe_pro.insert(map<double, double>::value_type(ExcitedE[ii], frac[ii]));
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

  exe_pro.clear();
  return exeval0;
}

double GetMass(int pdg)
{

  pdg_mass.clear();
  pdg_mass[22] = 0;
  pdg_mass[2112] = 0.93957;  // GeV
  pdg_mass[2212] = 0.93827;
  pdg_mass[1000010020] = 1.8756;
  pdg_mass[1000010030] = 2.8089;
  pdg_mass[1000020030] = 2.8084;
  pdg_mass[1000020040] = 3.7274;
  pdg_mass[1000030060] = 5.6015;
  pdg_mass[1000030070] = 6.5335;
  pdg_mass[1000030080] = 7.4708;
  pdg_mass[1000030090] = 8.4061;
  pdg_mass[1000040070] = 6.5344;
  pdg_mass[1000040080] = 7.4548;
  pdg_mass[1000040090] = 8.3925;
  pdg_mass[1000040100] = 9.3249;
  pdg_mass[1000050080] = 7.4728;
  pdg_mass[1000050090] = 8.3935;
  pdg_mass[1000050100] = 9.3244;
  pdg_mass[1000050110] = 10.2522;
  pdg_mass[1000060090] = 8.4100;
  pdg_mass[1000060100] = 9.3280;
  pdg_mass[1000060110] = 10.2542;
  pdg_mass[1000060120] = 11.1748;
  return pdg_mass[pdg];
}*/
void ProcessArgs(int argc, char** argv, Params& params)
{
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-seed") == 0) {
      i++;
      sscanf(argv[i], "%ld", &params.rseed);
    } else if (strcmp(argv[i], "-n") == 0) {
      i++;
      sscanf(argv[i], "%d", &params.nEvents);
    } else if (strcmp(argv[i], "-data_dir") == 0) {
      i++;
      char * data_dir = new char[strlen(argv[i]) + 1];
      strcpy(data_dir, argv[i]);
      params.data_dir = data_dir;
    } else if (strcmp(argv[i], "-h") == 0) {
      Usage();
      exit(0);
    }
  }
}

void Usage()
{
  cout << "eg. \"ProtonDecay.exe -seed 10 -n 1000\" " << endl;
}

