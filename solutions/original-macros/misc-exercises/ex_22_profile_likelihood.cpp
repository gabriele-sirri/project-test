#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif

#include "RooAddPdf.h"
#include "RooConstVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooMinuit.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"

using namespace RooFit;

void useModel(RooWorkspace& w)
{
  RooRealVar& x = *w.var("x");
  RooRealVar& mean = *w.var("mean");
  RooRealVar& sigma_g1 = *w.var("sigma_g1");
  RooRealVar& sigma_g2 = *w.var("sigma_g2");
  RooRealVar& frac = *w.var("frac");
  RooAbsPdf& g1 = *w.pdf("g1");
  RooAbsPdf& g2 = *w.pdf("g2");
  RooAbsPdf& model = *w.pdf("model");
  RooDataSet* data = static_cast<RooDataSet*>(w.data("data"));

  // Construct unbinned likelihood of model w.r.t. data
  RooAbsReal* nll = model.createNLL(*data);

  RooMinuit m(*nll);  // Create MINUIT interface object

  m.migrad();  // Call MIGRAD to minimize the likelihood
  // m.hesse();          // Run HESSE to calculate errors from d2L/dp2
  // m.minos(sigma_g2);  // Run MINOS on one parameter only
  //
  // RooFitResult* r = m.save();
  // r->Print("v");

  RooAbsReal* pll = nll->createProfile(sigma_g2);

  RooPlot* frame = sigma_g2.frame(Title("Likelihood function"));
  nll->plotOn(frame, ShiftToZero());
  pll->plotOn(frame, LineColor(kRed));
  frame->SetMinimum(0);
  frame->SetMaximum(8);
  frame->Draw();

  gPad->SaveAs("ex_22.png");
}

void ex_22_profile_likelihood()
{
  TFile* f = TFile::Open("ex_21.root");

  RooWorkspace& w = *static_cast<RooWorkspace*>(f->Get("w"));
  w.Print("t");
  useModel(w);
}
