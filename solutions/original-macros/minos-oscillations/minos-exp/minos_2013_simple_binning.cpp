#include "RooAddPdf.h"
#include "RooBinning.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooGenericPdf.h"
#include "RooHistFunc.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "RooRealVar.h"
#include "RooUniform.h"
#include "RooWorkspace.h"
#include "TFile.h"

using namespace RooFit;

void createModel(RooWorkspace& w)
{
  // auto file = TFile::Open("minos_2013_data.root");
  // auto& w = *static_cast<RooWorkspace*>(file->Get("minos"));

  /////

  RooRealVar e{"e", "Neutrino Energy", 0.5, 14, "GeV"};
  e.setBins(27);

  cout << "-- read minos_2013_data.dat\n";
  RooDataSet data = *RooDataSet::read("minos_2013_data.dat", e, "v");
  data.SetName("data"); // just to import the object in the RooWorkpsace with a (more) generic name, the default name assigned by read(..) was "dataset"
  
  data.Print();

  cout << "-- read minos_2013_unbinned.dat\n";
  RooDataSet mc_noosc = *RooDataSet::read("minos_2013_unbinned.dat", e, "v");
  mc_noosc.Print();

  // Create a binned dataset
  cout << "-- create a binned dataset\n";

  // when importing the dataset RooFit appends a blinding state category to
  // variable list remove the variable "blindState" from the dataset
  RooDataSet* dd = (RooDataSet*)mc_noosc.reduce(RooArgSet(e));
  RooDataHist h_func_noosc = *dd->binnedClone();
  
  h_func_noosc.Print();
  RooHistFunc func_noosc{"func_noosc", "No oscillation", e, h_func_noosc, 2};

  cout << "-- define the model\n";
  RooRealVar dm2{"dm2", "|#Delta m^{2}|", 2, 0.01, 10, "10^{-3} eV/c^{2}"};
  RooRealVar mixing{"mixing", "sin^{2}(2#theta)", 0.90, 0.00001, 1};
  // RooRealVar L{"L", "L", 730};

  RooFormulaVar prob_osc{"prob_osc",
                         "(1-mixing*pow(sin(1.27*0.001*dm2*730./e),2))",
                         RooArgSet{mixing, dm2, e}};


  // model (shape of the oscillated neutrino signal - without bkg which is
  // negligible)
  
  auto model =
      RooGenericPdf{"model", "model", "@0*@1", RooArgSet(prob_osc, func_noosc)};

  auto res = model.fitTo(data, RooFit::Save());

  double fitted_dm2 = dm2.getVal();
  double fitted_mix = mixing.getVal();

  // -- create the plot frame
  // to improve the plot readibility, force the range from 0 to 14
  // instead of the default RooRealVar range (0.5, 14)
  
  auto f = e.frame(Range(0., 14.));

  data.plotOn(f);
  // prob_osc.plotOn(f, LineColor(kGreen), Normalization(500));
  // pdf_noosc.plotOn(f, LineColor(kGray), RooFit::Normalization(1.3));
  // func_noosc.plotOn(f, LineColor(kOrange), RooFit::Normalization(1.0965));

  // -- method B --- 
  dm2.setVal(0.01);
  mixing.setVal(0.0001);
  model.plotOn(f, LineColor(kOrange),
               Normalization(4500, RooAbsReal::NumEvent));
  dm2.setVal(fitted_dm2);
  mixing.setVal(fitted_mix);

  model.plotOn(f, LineColor(kRed));
  model.paramOn(f);

  f->Draw();

  w.import(model);
  w.import(data);

  w.import(mc_noosc);

  res->Print();

  return;
}

void useModel(RooWorkspace& w)
{
  auto model = w.pdf("model");
  auto data = w.data("data");

  auto dm2 = w.var("dm2");
  auto mix = w.var("mixing");

  // Construct unbinned likelihood of model w.r.t. data
  RooAbsReal* nll = model->createNLL(*data);

  // Create MINUIT interface object
  // RooMinuit m(*nll); obsolete starting from ROOT v6.30
  RooMinimizer m(*nll);

  // Activate verbose logging of MINUIT parameter space stepping
  m.setVerbose(kTRUE);

  // Call MIGRAD to minimize the likelihood
  m.migrad();

  // Print values of all parameters, that reflect values (and error estimates)
  // that are back propagated from MINUIT
  std::cout << "=== MIGRAD ===\n";
  // model.getParameters(x)->Print("s");
  dm2->Print();
  mix->Print();

  // Disable verbose logging
  m.setVerbose(kFALSE);

  // Run HESSE to calculate errors from d2L/dp2
  m.hesse();

  // Print value (and error) of dm2 parameter, that reflects
  // value and error back propagated from MINUIT
  std::cout << "=== HESSE ===\n";
  dm2->Print();
  mix->Print();

  // Run MINOS on dm2 parameter only
  m.minos(*dm2);

  // Print value (and error) of dm2 parameter, that reflects
  // value and error back propagated from MINUIT
  std::cout << "=== MINOS ===\n";
  dm2->Print();
  mix->Print();

  /*/
  new TCanvas();
  RooAbsReal* pll = nll->createProfile(*dm2);

  RooPlot* frame1 = dm2->frame(Title("Likelihood function"));
  nll->plotOn(frame1, ShiftToZero());
  pll->plotOn(frame1, LineColor(kRed));
  frame1->SetMinimum(0);
  frame1->SetMaximum(8);
  frame1->Draw();

  gPad->SaveAs("ex_22.png");
  */
  // S a v i n g   r e s u l t s ,   c o n t o u r   p l o t s
  // ---------------------------------------------------------

  // Save a snapshot of the fit result. This object contains the initial
  // fit parameters, the final fit parameters, the complete correlation
  // matrix, the EDM, the minimized FCN , the last MINUIT status code and
  // the number of times the RooFit function object has indicated evaluation
  // problems (e.g. zero probabilities during likelihood evaluation)
  RooFitResult* r = m.save();

  // Make contour plot of mx vs sx at 2.3 (68%), 4.61 (90%)
  // RooPlot* frame = m.contour(*mix, *dm2, 2.3, 4.61);  //NO DIREI CHE BISOGNA METTERE LE SIGMA


  RooPlot* frame = m.contour(*mix, *dm2, 1, 2, 3);
  frame->SetTitle("RooMinuit contour plot");

  // Print the fit result snapshot
  r->Print("v");

  new TCanvas("my_minos", "my_minos", 600, 600);
  gPad->SetLeftMargin(0.15);
  frame->GetYaxis()->SetTitleOffset(1.4);

  frame->GetYaxis()->SetRangeUser(1.7, 3.5);
  frame->GetXaxis()->SetRangeUser(0.70, 1.);

  frame->Draw();

  gPad->SaveAs("my_minos.png");

  return;
}

void minos_2013_simple_binning()
{
  RooWorkspace w("minos");
  createModel(w);
  w.writeToFile("minos_2013_model_simple_binning.root");
  useModel(w);
}
