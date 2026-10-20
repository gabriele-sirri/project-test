
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "TAxis.h"
#include "TCanvas.h"

using namespace RooFit;

// void rf101_basics()
void ex_12_binned_markov()
{
  // S e t u p   m o d e l
  // ---------------------

  // Declare variables x,mean,sigma with associated name, title, initial value
  // and allowed range
  RooRealVar x("x", "x", 0, 1);
  RooRealVar a("a", "coefficient", 5, 0, 20);

  // Build gaussian p.d.f in terms of x,mean and sigma
  RooPolynomial pol("pol", "pol", x, RooArgList(a));
  //   RooExponential pol("pol", "pol", x, a);

  {
    RooPlot* xframe = x.frame(Title("Linear p.d.f. with data"));
    pol.plotOn(xframe);
    // Draw all frames on a canvas
    xframe->Draw();
    new TCanvas;
  }

  // G e n e r a t e   e v e n t s
  // -----------------------------

  // Generate a dataset of 1000 events in x from gauss
  // RooDataSet* data = gauss.generate(x,1000) ;     // THIS IS UNBINNED :
  // return a RooDataSet*

  //******* GENERATE A BINNED DATA SET ********
  //
  // The binning of the returned RooDataHist is controlled by the default
  // binning associated with the observables generated. To set the number
  // of bins in x to 200, do e.g. x.setBins(200) prior to the call to 
  // generateBinned() 

  x.setBins(5);

  RooDataSet a_values("data_a", "", a);

  for (int i = 0; i < 1; i++) {
    a.setVal(5);
    a.Print();
    RooDataHist* data =
        pol.generateBinned(x, 20);  // THIS IS   BINNED : return a RooDataHist

    // Fit pdf to data
    auto fit_res = pol.fitTo(*data, Save(), PrintLevel(-1), Verbose(false),
                             PrintEvalErrors(-1), Warnings(false));
    // pol.chi2FitTo(*data, PrintLevel(-1), Verbose(true), PrintEvalErrors(-1));
    a_values.add(a);
    a.Print();
    pol.Print();
    // Print values of mean and sigma (that now reflect fitted values and
    // errors)
    // Make a plot frame in x and draw both the
    // data and the p.d.f in the frame
    RooPlot* xframe = x.frame(Title("Linear p.d.f. with data"));
    data->plotOn(xframe);
    pol.plotOn(xframe);
    // Draw all frames on a canvas
    xframe->Draw();
  }

  new TCanvas;

  a.setBins(30);
  RooPlot* aframe = a.frame(Title("Coefficient"));
  a_values.plotOn(aframe);
  aframe->Draw();

  a_values.Print("v");
}
