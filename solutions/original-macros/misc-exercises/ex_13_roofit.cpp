
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"

using namespace RooFit;

void ex_13_roofit()
{
  // S e t u p   m o d e l
  // ---------------------

  // Declare observable x
  RooRealVar x("x", "x", -10, 10);

  // Create one Gaussian p.d.f. sig(x,mean,sigma) and its paramaters
  RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
  RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);
  RooGaussian sig("signal", "signal", x, mean, sigma);

  // Build a Exponential p.d.f. bkg and its parameter
  RooRealVar tau("tau", "tau", 10, 0, 30);
  RooFormulaVar alpha("alpha", "alpha", "-1./tau", tau);
  RooExponential bkg("bkg", "background", x, alpha);

  // Sum the composite signal and background
  RooRealVar fsig("fsig", "fraction of signal", 0.4, 0., 1.);
  RooAddPdf model("model", "fsig*sig+(1-fsig)*bkg", RooArgList(sig, bkg),
                  RooArgList(fsig));

  // Construct plot frame in 'x'
  RooPlot* xframe = x.frame(Title("Gaussian signal, Exponential background"));

  /// S a m p l e ,   f i t   a n d   p l o t   m o d e l
  // ---------------------------------------------------

  // Generate a data sample of 1000 events in x from model
  RooDataSet* data = model.generate(x, 1000);

  // Fit model to data
  model.fitTo(*data);

  // Plot data and PDF overlaid
  RooPlot* xframe = x.frame(Title("Example of composite pdf=sig+bkg"));
  data->plotOn(xframe);
  model.plotOn(xframe);

  // Overlay the background component of model with a dashed line
  model.plotOn(xframe, Components(bkg), LineStyle(kDashed));

  // Print structure of composite p.d.f.
  model.Print("t");

  // Draw the frame
  xframe->Draw();
}
