#include "Rtypes.h"
#include "TH1.h"
#include "TMath.h"
#include "TRandom.h"
#include <iostream>
using namespace std ;

void clt(int Nsum=1, int Nexp=10000)
{
  // Distribution of measurement
  TH1* h_N = new TH1D("h_N","h_N",100,0,Nsum) ;

  for (int i=0 ; i<10000 ; i++) {
    // Do 'fake' measurement resulting in
    // random value of x with uniform distribution
    Double_t x = gRandom->Uniform(0,1) ;
    h_N->Fill(x) ;
  }

  h_N->SetMinimum(0) ;
  h_N->Draw() ;

}
