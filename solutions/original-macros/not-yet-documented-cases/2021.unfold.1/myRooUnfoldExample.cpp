
// gSystem->Load("$HOME/software/roounfold/libRooUnfold.so");

//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id$
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson
// <fwilson@slac.stanford.edu>
//
//==============================================================================

#if !(defined(__CINT__) || defined(__CLING__)) || defined(__ACLIC__)
#include <iostream>
using std::cout;
using std::endl;

#include "TCanvas.h"
#include "TH1D.h"
#include "TRandom.h"

#include "RooUnfoldBayes.h"
#include "RooUnfoldResponse.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"
//#include "RooUnfoldIds.h"
#endif

void try_inversion_approach(TMatrixD responseMatrix,
                            TH1D* model_truth /* hTrue */,
                            TH1D* model_meas /* hMeas */);

//==============================================================================
// Global definitions
//==============================================================================

const double cutdummy = -99999.0;

//==============================================================================
// Gaussian smearing, systematic translation, and variable inefficiency
//==============================================================================

// Detector effects are simulated with a function smear(..) that simulates a
// finite detector efficiency and resolution as well as a shift of the measured
// values wrt. the truth ones.

double smear(double xt)
{
  double xeff = 0.3 + (1.0 - 0.3) / 20 * (xt + 10.0);  // efficiency
  double x = gRandom->Rndm();
  if (x > xeff) {
    return cutdummy;
  }
  double xsmear = gRandom->Gaus(-2.5, 0.2);  // bias and smear
  return xt + xsmear;
}

//==============================================================================
// Example Unfolding
//==============================================================================

void myRooUnfoldExample()
{
  cout << "==================================== TRAIN "
          "===================================="
       << endl;

  // ** First steps with RooUnfold: creating the response **
  // We now use our first RooUnfold class, the RooUnfoldResponse to build the
  // response matrix. For a known "MC" value, we apply the smearing, then if the
  // event is "accepted" (not lost), pass the truth and smeared events to the
  // response model. If the event is lost, we just pass the truth, because we
  // need to know what our acceptance is.

  RooUnfoldResponse response(40, -10.0, 10.0);

  // Train with a Breit-Wigner, mean 0.3 and width 2.5.
  for (int i = 0; i < 100000; i++) {
    double xt = gRandom->BreitWigner(0.3, 2.5);
    double x = smear(xt);
    if (x != cutdummy) {
      response.Fill(x, xt);
    } else {
      response.Miss(xt);
    }
  }

  // ** Having created the response matrix, let's plot it **

  auto responseMatrix = response.Mresponse();  // Response matrix as a TMatrixD:
                                               // (row,column)=(measured,truth)
  new TCanvas("", "response matrix");
  responseMatrix.Draw("colz");

  cout << "==================================== TEST "
          "====================================="
       << endl;

  // Generate histograms that we will fill from the model before and after
  // detector effects It uses Gaus(x; 0, 2) as a truth spectrum.

  TH1D* hTrue = new TH1D("true", "Test Truth", 40, -10.0, 10.0);
  TH1D* hMeas = new TH1D("meas", "Test Measured", 40, -10.0, 10.0);

  // Fill the histograms applyingdetector effects to get a "realistic
  // measurement". Test with a Gaussian, mean 0 and width 2.

  for (int i = 0; i < 50000; i++) {
    double xt = gRandom->Gaus(0.0, 2.0);
    double x = smear(xt);
    hTrue->Fill(xt);
    if (x != cutdummy) {
      hMeas->Fill(x);
    }
  }

  cout << "==================================== UNFOLD "
          "==================================="
       << endl;

  // ** try_inversion_approach **

  try_inversion_approach(responseMatrix, hTrue, hMeas);

  //  ** Using RooUnfold **
  // Finally, the measured spectrum is unfolded with a method of the user’s
  // choice The default is RooUnfoldBayes which is the D’Agostini’s method

  // note for RooUnfoldSvd and RooUnfoldTUnfold
  // Error in <TUnfold::SetInput>: 2/37 output bins are not constrained by any
  // data. Unfolding result may be wrong: 2 unconstrained output bins Error in
  // <TUnfold::GetInputInverseEmatrix>: number of parameters 37 > 32 (rank of
  // input covariance). Problem can not be solved

  RooUnfoldBayes unfold1(&response, hMeas, 4);  // OR
  // RooUnfoldSvd unfold2(&response, hMeas, 20);   // OR
  // RooUnfoldTUnfold unfold3(&response, hMeas);   // OR
  RooUnfoldIds unfold4(&response, hMeas, 1);

  unfold1.PrintTable(cout, hTrue);
  // unfold2.PrintTable(cout, hTrue);
  // unfold3.PrintTable(cout, hTrue);
  unfold4.PrintTable(cout, hTrue);

  // Just for a sanity check, plot the histograms

  TH1D* hReco1 = (TH1D*)unfold1.Hreco();
  // TH1D* hReco2 = (TH1D*)unfold2.Hreco();
  // TH1D* hReco3 = (TH1D*)unfold3.Hreco();
  TH1D* hReco4 = (TH1D*)unfold4.Hreco();

  auto draw = [&]() {
    hMeas->Draw("SAME");
    hTrue->SetLineColor(8);
    hTrue->Draw("SAME");
  };

  auto cv = new TCanvas("output", "check unfold");
  cv->Divide(2, 2);

  cv->cd(1);
  hReco1->Draw();
  draw();
  /*
    cv->cd(2);
    hReco2->Draw();
    draw();

    cv->cd(3);
    hReco3->Draw();
    draw();
  */
  cv->cd(4);
  hReco4->Draw();
  draw();

  // c1->SaveAs("RooUnfoldExample.pdf");
}

#ifndef __CINT__
int main()
{
  myRooUnfoldExample();
  return 0;
}  // Main program when run stand-alone
#endif

// ===============================================================================

void try_inversion_approach(TMatrixD responseMatrix,
                            TH1D* model_truth /* hTrue */,
                            TH1D* model_meas /* hMeas */)
{
  // ** try our hand at the matrix inversion approach  **

  // Note: depending on your choice of true function and detector effects, ROOT
  // may give errors due to the matrix being singular, in which case this is
  // simply not an option.
  auto responseInv = *static_cast<TMatrixD*>(responseMatrix.Clone());
  responseInv.Invert();

  // plot the inverse, which seems to have some slightly alarmingly large
  // values...
  new TCanvas("", "inverted matrix");
  responseInv.Draw("colz");

  // We can try applying the inverted response matrix to the "reco" histogram as
  // one way to undo the detector response.

  auto model_meas_Rinv =
      static_cast<TH1D*>(model_meas->Clone("model_meas_Rinv"));
  model_meas_Rinv->Reset();
  for (int ibin = 1; ibin < model_meas_Rinv->GetNbinsX() + 1; ibin++) {
    double matsum = 0;
    for (int jbin = 1; jbin < model_meas_Rinv->GetNbinsX() + 1; jbin++) {
      matsum +=
          model_meas->GetBinContent(jbin) * responseInv[ibin - 1][jbin - 1];
    }
    model_meas_Rinv->SetBinContent(ibin, matsum);
  }

  auto c4 = new TCanvas("", "matrix inversion approach");
  c4->Divide(2, 2);
  c4->cd(1);
  model_truth->Draw("hist");
  c4->cd(2);
  model_meas->Draw("pe same");
  c4->cd(3);
  model_meas_Rinv->SetLineColor(EColor::kOrange);
  model_meas_Rinv->Draw("histsame");

  // ... Let's plot the "unfolded" distribution on its own just to check.
  // Recall what the "problems" with the simple matrix inversion

  c4->cd(4);
  model_meas_Rinv->Draw("hist");
}
