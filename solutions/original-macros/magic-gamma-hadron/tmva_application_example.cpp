#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TMVA/Reader.h>

void tmva_application_example() {

// Set up an output file and book some histograms

  TFile* histFile = new TFile("analysis.root", "RECREATE");
  TH1D* hFishSig = new TH1D("hFishSig", "Fisher, signal", 100, -10.0, 10.0);
  TH1D* hFishBkg = new TH1D("hFishBkg", "Fisher, background", 100, -10.0, 10.0);

// Set up the TMVA Reader object.
// The names in AddVariable must be same as in the input (weight) file.

  TMVA::Reader* reader = new TMVA::Reader();
  float x, y, z;                       // TMVA needs float, not double
  reader->AddVariable("x", &x);  
  reader->AddVariable("y", &y);
  reader->AddVariable("z", &z);  
  std::string dir    = "weights/";
  std::string prefix = "tmvaTest";
  reader->BookMVA("Fisher", dir + prefix + "_Fisher.weights.xml");

// Open input file, get the TTrees, put into a vector

  TFile* inputFile = new TFile("testData.root");
  inputFile->ls();
  TTree* sig = dynamic_cast<TTree*>(inputFile->Get("sig"));
  TTree* bkg = dynamic_cast<TTree*>(inputFile->Get("bkg"));
  
  // Questo potrebbe non funzionare se non si usa ACLiC
  // std::vector<TTree*> treeVec;
  // treeVec.push_back(sig);
  // treeVec.push_back(bkg);

  TTree* treeVec[2] ;
  treeVec[0] = sig ;
  treeVec[1] = bkg ;

// Loop over TTrees

  // for (int i=0; i<treeVec.size(); i++) //modificato per non usare ACLiC
  for (int i=0; i<2 ; i++)
  {  
    double xx,yy,zz;
    treeVec[i]->Print();
    treeVec[i]->SetBranchAddress("x", &xx);
    treeVec[i]->SetBranchAddress("y", &yy);
    treeVec[i]->SetBranchAddress("z", &zz);
    int numEntries = treeVec[i]->GetEntries();
    std::cout << "number of entries = " << numEntries << std::endl;

// Loop over events.  The test statistic is identified by the first 
// argument used above in BookMVA (below, e.g., "Fisher").

    for (int j=0; j<numEntries; j++){
      treeVec[i]->GetEntry(j);                // sets evt
      x = xx;                              // set variables of reader
      y = yy;
      z = zz;
      double tFisher = reader->EvaluateMVA("Fisher");
      // std::cout << evt.x << "  " << evt.y << "  " << evt.z << std::endl;
      // std::cout << "tFisher = " << tFisher << std::endl;



      if ( i == 0 ){ 
        hFishSig->Fill(tFisher);
      }
      else if ( i == 1 ){
        hFishBkg->Fill(tFisher);
      }

    }

  }

  histFile->Write();
  histFile->Close();
  return;

}
