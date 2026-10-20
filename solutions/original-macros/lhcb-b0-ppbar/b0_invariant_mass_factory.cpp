//
//  b0_invariant_mass.cpp
//

using namespace RooFit;

void makeModel(RooWorkspace& w)
{
  // define the observable
  RooRealVar x{"x", "x", 3, 8, "GeV"};

  // define parameters and models
  RooRealVar mean1{"mean1", "mean1", 5.5, 5., 6., "GeV"};
  RooRealVar sigma{"sigma", "sigma", 0.2, 0., 1., "GeV"};
  RooGaussian gs("gauss", "gaussian", x, mean1, sigma);
  
  RooRealVar mean2{"mean2", "mean2", 5.5, 5., 6., "GeV"};
  RooRealVar width{"width", "width", 0., 1., "GeV"};
  RooBreitWigner bw("breit", "breit-wigner", x, mean2, width);

  // Import histogram from ROOT file
  auto f = TFile::Open("B0sInvariantMass.root");
  auto h = static_cast<TH1F*>(f->Get("massaB0"));
  RooDataHist dh{"dh", "LHCb data", x, Import(*h)};

  // import pdfs and data in the workspace
  w.import(gs);
  w.import(bw);
  w.import(dh);
}

void makeModel_factory(RooWorkspace& w)
{
  w.factory("Gaussian::gauss(x[3,8], mean1[5.5,5,6], sigma[0.2,0,1])");
  w.factory("BreitWigner::breit(x, mean2[5.5,5,6], width[0.3,0,1])");
  
  // we have to extract the observable outside the Workspace
  // to import the histogram
  
  auto x = w.var("x");  // RooWorkspace returns a pointer 
                        // to RooRealVar

  // Import histogram from ROOT file
  auto f = TFile::Open("B0sInvariantMass.root");
  auto h = static_cast<TH1F*>(f->Get("massaB0"));
  RooDataHist dh{"dh", "LHCb data", *x, Import(*h)};

  // import data in the workspace
  w.import(dh);
}

void useModel(RooWorkspace& w)
{
  w.Print();

  // get pointers to objects inside workspace
  auto gs = w.pdf("gauss"); // return value is a RooAbsPdf*
  auto bw = w.pdf("breit");
  auto dh = w.data("dh");   // return value is a RooAbsData*

  // fit the models to the data
  gs->fitTo(*dh, Range(5., 5.7));
  bw->fitTo(*dh, Range(5., 5.7));

  // draw data and models after fitting
  RooPlot* frame = w.var("x")->frame();
  dh->plotOn(frame);
  bw->plotOn(frame, LineColor(kRed));
  gs->plotOn(frame, LineColor(kBlue));
  frame->Draw();
}

// RooWorkspace w{"w"};

int b0_invariant_mass_factory()
{
  RooWorkspace w{"w"};	
	
  // makeModel(w);
  makeModel_factory(w);
  
  useModel(w);

  return 0;
}
