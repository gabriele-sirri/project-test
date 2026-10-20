
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooUniform.h"
#include "RooWorkspace.h"

using namespace RooFit;

int cuore0(RooWorkspace& w)
{
  RooRealVar x{"x", "Reconstructed Energy", 2470, 2570, "keV"};
  x.setBins(50);

  RooDataSet data = *RooDataSet::read("cuore0.dat", x, "v");
  data.Print();

  w.import(data);

  RooUniform bck{"bkg", "Flat Background", x};

  RooRealVar co60_m{"cob_m", "Co-60 mean", 2507};
  co60_m.setConstant();
  co60_m.removeRange();
  co60_m.removeError();
  RooRealVar co60_s{"cob_s", "Co-60 width", 4, 1, 7};
  RooGaussian co60{"co60", "Co-60", x, co60_m, co60_s};

  RooRealVar sign_m{"sign_m", "Signal mean", 2527};
  sign_m.setConstant();
  sign_m.removeRange();
  sign_m.removeError();
  RooRealVar sign_s{"sign_s", "Signal width", 4, 1, 7};

  RooGaussian sign{"sign", "0-#nu DBD", x, sign_m, sign_s};

  RooRealVar n_bck{"n_bkg", "N. Background Events", 200, 0, 400};
  RooRealVar n_co60{"n_co60", "N. Co-60 Events", 10, 0, 100};
  RooRealVar n_sign{"n_sign", "N. Signal Events", 10, 0, 100};

  RooAddPdf model{"model", "model", RooArgSet{bck, co60, sign},
                  RooArgSet{n_bck, n_co60, n_sign}};

  auto result = model.fitTo(data, Save());

  w.Print();

  auto frame1 = x.frame();
  data.plotOn(frame1);
  model.plotOn(frame1);
  model.plotOn(frame1, Components("bkg"), LineColor(kBlue), LineStyle(kDashed));
  model.plotOn(frame1, Components("co60"), LineColor(kGreen));
  model.plotOn(frame1, Components("sign"), LineColor(kRed));
  model.plotOn(frame1);
  model.paramOn(frame1);

  frame1->Draw();

  w.import(model);
  w.import(data);
  // w.import(result);
  // w.writeToFile("cuore0.root");

  auto c4 = new TCanvas{"c4", "c4"};
  gStyle->SetPalette(1);
  result->correlationHist()->Draw("colz");

  // C a l c u l a t x   c h i ^ 2
  // ------------------------------

  // Show the chi^2 of the curve w.r.t. the histogram
  // If multiple curves or datasets live in the frame you can specify
  // the name of the relevant curve and/or dataset in chiSquare()
  cout << "chi^2 = " << frame1->chiSquare() << endl;

  // S h o w   r x s i d u a l   a n d   p u l l   d i s t s
  // -------------------------------------------------------

  // Construct a histogram with the residuals of the data w.r.t. the curve
  RooHist* hresid = frame1->residHist();
  hresid->Print();

  // Construct a histogram with the pulls of the data w.r.t the curve
  RooHist* hpull = frame1->pullHist();

  // Create a new frame to draw the residual distribution and add the
  // distribution to the frame
  RooPlot* frame2 = x.frame(Title("Residual Distribution"));
  frame2->addPlotable(hresid, "P");

  // Create a new frame to draw the pull distribution and add the distribution
  // to the frame
  RooPlot* frame3 = x.frame(Title("Pull Distribution"));
  frame3->addPlotable(hpull, "P");

  TCanvas* c =
      new TCanvas("rf109_chi2residpull", "rf109_chi2residpull", 800, 800);
  c->Divide(1, 3);
  c->cd(1);
  gPad->SetLeftMargin(0.15);
  frame1->GetYaxis()->SetTitleOffset(1.6);
  frame1->Draw();
  c->cd(2);
  gPad->SetLeftMargin(0.15);
  frame2->GetYaxis()->SetTitleOffset(1.6);
  frame2->Draw();
  c->cd(3);
  gPad->SetLeftMargin(0.15);
  frame3->GetYaxis()->SetTitleOffset(1.6);
  frame3->Draw();

  return 0;
}

void evaluate_events_in_the_subrange(RooWorkspace& w)
{
  w.Print();

  // we need the fit results...

  auto pdf = w.pdf("model");
  auto data = w.data("dataset");
  pdf->Print();
  data->Print();
  auto fr = pdf->fitTo(*data, RooFit::Save());
  fr->Print();

  // define the sub range
  // w.var("x")->setRange("sigrange", 2498, 2514); // Co-60
  w.var("x")->setRange("sigrange", 2520, 2530);

  // Create an integral object that represents the fraction of background events
  // in the signal range
  w.factory("int::f_bkg_sigRange(bkg,x|sigrange,x)");

  // the first x indicates which observable to integrate over and in which
  // range, the second x indicates which observables to normalize over. (Without
  // a range specification this would result in 1 by construction)
  // - Retrieve the value of the fraction by calling

  cout << "f_bkg in sig range = " << w.function("f_bkg_sigRange")->getVal()
       << '\n';

  //- Now construct a formula named Nbkg_sigRange that expresses the number of
  // background events in the signal range: use product operator

  w.factory("prod::n_bkg_sigRange(n_bkg,f_bkg_sigRange)");

  // - Evaluate the n_bkg_SigRange function in the workspace to count the
  // number of signal events in the range [2498,2514]

  cout << "n_bkg in sig range" << w.function("n_bkg_sigRange")->getVal()
       << '\n';

  // Linear error propagation
  //	Now we calculate the error on n_bkg_SigRange. To that end we
  // first need to save a RooFitResult object from the fitTo() operation

  // Save the RooFitResult* pointer returned by fitTo() in an object named
  // fr, and add a Save() argument to fitTo() to instruct to make sure an
  // fit resulted will be returned. –	Calculate the error on the
  // number of background events by calling

  cout << "      +/- " << w.function("n_bkg_sigRange")->getPropagatedError(*fr)
       << '\n';
}

void cuore0_2020()
{
  auto w = new RooWorkspace("w");
  cuore0(*w);

  evaluate_events_in_the_subrange(*w);
}
