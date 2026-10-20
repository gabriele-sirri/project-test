using namespace RooFit;

void lhcb_rarest_decay_2020()
{
  int nbins = 25;
  double xmin = 5080;
  double xmax = 5080 + 19 * nbins;

  RooRealVar x{"x", "m(p-pbar)", xmin, xmax, "Mev/c^2"};
  x.setBins(nbins);
  auto data = *RooDataSet::read("rarest_b0_decay.dat", x, "D");

  RooRealVar c{"c", "exponential par", -0.0001, -1, -0.000001};
  RooExponential b{"bkg", "Comb. bkg.", x, c};

  // RooUniform b{"bkg", "Comb. bkg." "Comb. bkg.", x};

  RooRealVar m0{"m0", "B0 mass", 5279, 5220, 5320};
  RooRealVar s0{"s0", "B0 width", 10, 2, 50};
  RooGaussian g0{"g0", "B0 peak", x, m0, s0};

  RooRealVar m1{"m1", "B0s mass", 5380, 5320, 5420};
  RooRealVar s1{"s1", "B0s width", 10, 2, 50};
  RooGaussian g1{"g1", "B0s peak", x, m1, s0};

  // RooRealVar fb{"fb", "fraction of background", 0.8, 0.0001, 1};
  RooRealVar f0{"f0", "fraction of B0", 0.2, 0.0001, 1};
  RooRealVar f1{"f1", "fraction of Bs", 0.2, 0.0001, 1};

  RooAddPdf model{"model", "model", RooArgList{g0, g1, b}, RooArgList{f0, f1}};
  // RooAddPdf model{"model", "model", RooArgList{b, g0}, RooArgList{fb}};

  auto fit_res = model.fitTo(data, RooFit::Save());

  auto xframe = x.frame();
  data.plotOn(xframe);
  model.plotOn(xframe);
  model.plotOn(xframe, RooFit::Components("bkg"), RooFit::LineColor(kGreen));
  model.plotOn(xframe, RooFit::Components("g0"), RooFit::LineColor(kRed));
  model.plotOn(xframe, RooFit::Components("g1"), RooFit::LineColor(kGray));

  // model.plotOn(xframe, VisualizeError(*fit_res, RooArgSet(f1, f0), 2),
  //             FillColor(kGreen));

  xframe->Draw();

  new TCanvas{"c2"};
  gStyle->SetPalette(1);
  fit_res->correlationHist()->Draw("colz");

  fit_res->Print();
}
