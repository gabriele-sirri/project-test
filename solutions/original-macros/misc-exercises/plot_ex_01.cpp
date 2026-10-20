// Simple ROOT macro to plot a histogram.
// Modify arguments as needed.
// To execute, type .X plot_ex_01.cpp

#include "TCanvas.h"

TCanvas* c;

int plot_ex_01()
{
  c = new TCanvas();
  c->Divide(2, 2);

  TFile* f = new TFile("ex1.root");
  f->ls();

  c->cd(1);
  TH1D* h1 = (TH1D*)f->Get("h_Uni");
  h1->SetXTitle("x");
  h1->SetYTitle("f(x)");
  h1->Draw();

  c->cd(2);
  TH1D* h2 = (TH1D*)f->Get("h_a");
  h2->SetXTitle("x");
  h2->SetYTitle("f(x)");
  h2->Draw();

  c->cd(3);
  TH1D* h3 = (TH1D*)f->Get("h_b");
  h3->SetXTitle("x");
  h3->SetYTitle("f(x)");
  h3->Draw();

  c->cd(4);
  TH1D* h4 = (TH1D*)f->Get("h_c");
  h4->SetXTitle("x");
  h4->SetYTitle("f(x)");
  h4->Draw();

  return 0;
}