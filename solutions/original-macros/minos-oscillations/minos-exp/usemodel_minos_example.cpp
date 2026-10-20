void useModel(RooWorkspace& w)
{

  auto model = w.pdf("model");
  auto data = w.data("dataset");

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

  // Make contour plot of mx vs sx at 1,2,3 
  RooPlot* frame = m.contour(*mix, *dm2, 1, 2, 3);
  frame->SetTitle("RooMinuit contour plot");

  // Print the fit result snapshot
  r->Print("v");

  new TCanvas("my_minos", "my_minos", 600, 600);
  gPad->SetLeftMargin(0.15);
  frame->GetYaxis()->SetTitleOffset(1.4);

  frame->GetYaxis()->SetRangeUser(0.001,0.004);
  frame->Draw();

  gPad->SaveAs("my_minos.png");


  return;
}
