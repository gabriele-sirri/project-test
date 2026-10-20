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

  RooBinning bins(0.5, 14);
  for (double b = 0.5; b < 9.1; b += 0.5) {
    bins.addBoundary(b);
  }
  bins.addBoundary(9.75);
  bins.addBoundary(10.50);
  bins.addBoundary(11.25);
  bins.addBoundary(12.00);
  bins.addBoundary(13.00);
  bins.addBoundary(14.00);

  e.setBinning(bins);

  RooDataHist data{"data", "data", e};                          // C++11
  RooDataHist h_pdf_noosc{"h_pdf_noosc", "h_pdf_noosc", e};        // C++11
  RooDataHist h_func_noosc{"h_func_noosc", "h_func_noosc", e};  // C++11

  // RooDataHist data("data", "data", e);  // Root 5
  // RooDataHist h_pdf_noosc( "h_pdf_noosc", "h_pdf_noosc", e); // Root 5

  // clang-format off
  e.setVal(0.75);  data.set(e, 13);        h_pdf_noosc.set(e, 22.1);          h_func_noosc.set(e, 22.1);
  e.setVal(1.25);  data.set(e, 19);        h_pdf_noosc.set(e, 118.9);         h_func_noosc.set(e, 118.9);
  e.setVal(1.75);  data.set(e, 58);        h_pdf_noosc.set(e, 253.0);         h_func_noosc.set(e, 253.0);
  e.setVal(2.25);  data.set(e, 113);       h_pdf_noosc.set(e, 378.8);         h_func_noosc.set(e, 378.8);
  e.setVal(2.75);  data.set(e, 257);       h_pdf_noosc.set(e, 471.4);         h_func_noosc.set(e, 471.4);
  e.setVal(3.25);  data.set(e, 346);       h_pdf_noosc.set(e, 500.5);         h_func_noosc.set(e, 500.5);
  e.setVal(3.75);  data.set(e, 353);       h_pdf_noosc.set(e, 453.5);         h_func_noosc.set(e, 453.5);
  e.setVal(4.25);  data.set(e, 285);       h_pdf_noosc.set(e, 359.4);         h_func_noosc.set(e, 359.4);
  e.setVal(4.75);  data.set(e, 197);       h_pdf_noosc.set(e, 269.6);         h_func_noosc.set(e, 269.6);
  e.setVal(5.25);  data.set(e, 156);       h_pdf_noosc.set(e, 207.4);         h_func_noosc.set(e, 207.4);
  e.setVal(5.75);  data.set(e, 126);       h_pdf_noosc.set(e, 168.0);         h_func_noosc.set(e, 168.0);
  e.setVal(6.25);  data.set(e, 97);        h_pdf_noosc.set(e, 146.5);         h_func_noosc.set(e, 146.5);
  e.setVal(6.75);  data.set(e, 109);       h_pdf_noosc.set(e, 130.6);         h_func_noosc.set(e, 130.6);
  e.setVal(7.25);  data.set(e, 126);       h_pdf_noosc.set(e, 121.7);         h_func_noosc.set(e, 121.7);
  e.setVal(7.75);  data.set(e, 95);        h_pdf_noosc.set(e, 118.9);         h_func_noosc.set(e, 118.9);
  e.setVal(8.25);  data.set(e, 102);       h_pdf_noosc.set(e, 112.7);         h_func_noosc.set(e, 112.7);
  e.setVal(8.75);  data.set(e, 118);       h_pdf_noosc.set(e, 107.8);         h_func_noosc.set(e, 107.8);
  e.setVal(9.40);  data.set(e, 1.5 * 108); h_pdf_noosc.set(e, 1.5* 102.3);    h_func_noosc.set(e, 102.3);
  e.setVal(10.10); data.set(e, 1.5 * 106); h_pdf_noosc.set(e, 1.5*  96.8);    h_func_noosc.set(e,  96.8);
  e.setVal(10.80); data.set(e, 1.5 * 86);  h_pdf_noosc.set(e, 1.5*  94.0);    h_func_noosc.set(e,  94.0);
  e.setVal(11.50); data.set(e, 1.5 * 84);  h_pdf_noosc.set(e, 1.5*  85.7);    h_func_noosc.set(e,  85.7);
  e.setVal(12.50); data.set(e, 2 * 92);    h_pdf_noosc.set(e, 2 * 82.9);      h_func_noosc.set(e, 82.9);
  e.setVal(13.50); data.set(e, 2 * 70);    h_pdf_noosc.set(e, 2 * 77.4);      h_func_noosc.set(e, 77.4);
  // clang-format on

  data.Print();

  //////
										 									
  h_pdf_noosc.Print();
  RooHistPdf pdf_noosc{"pdf_noosc", "No oscillation", e, h_pdf_noosc, 0};

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
  prob_osc.plotOn(f, LineColor(kGreen), Normalization(500));
  pdf_noosc.plotOn(f, LineStyle(kDashed), LineColor(kGray), RooFit::Normalization(1.3));


  func_noosc.plotOn(f, LineColor(kOrange), RooFit::Normalization(1.0965),
                    Binning(bins));

  model.plotOn(f, LineColor(kRed), Binning(bins));
  model.paramOn(f);

  f->Draw();

  w.import(h_pdf_noosc);
  w.import(model);
  w.import(data);

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
  RooMinuit m(*nll);

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
  RooPlot* frame = m.contour(*mix, *dm2, 2.3, 4.61);
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

void minos_2013()
{
  RooWorkspace w("minos");
  createModel(w);
  w.writeToFile("minos_2013_model_simple_binning.root");
  useModel(w);
}
