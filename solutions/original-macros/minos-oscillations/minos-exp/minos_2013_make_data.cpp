
#include "RooBinning.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"

using namespace RooFit;

int minos_2013_make_data()
{
  RooRealVar e{"e", "Reconstructed Energy", 0.1, 14, "GeV"};

  RooBinning bins(0, 14);
  for (double b = 0; b < 9.1; b += 0.5) {
    bins.addBoundary(b);
  }
  bins.addBoundary(9.75);
  bins.addBoundary(10.50);
  bins.addBoundary(11.25);
  bins.addBoundary(12.00);
  bins.addBoundary(13.00);
  bins.addBoundary(14.00);

  e.setBinning(bins);

  RooDataHist data{"data", "data", e};                             // C++11
  RooDataHist h_mc_noosc{"h_mc_noosc", "h_mc_noosc", e};  // C++11

  // RooDataHist data("data", "data", e);  // Root 5
  // RooDataHist h_mc_noosc( "h_mc_noosc", "h_mc_noosc", e); // Root 5

  // clang-format off
  e.setVal( 0.75); data.set(e,        13); h_mc_noosc.set(e,        22.1);
  e.setVal( 1.25); data.set(e,        19); h_mc_noosc.set(e,       118.9);
  e.setVal( 1.75); data.set(e,        58); h_mc_noosc.set(e,       253.0);
  e.setVal( 2.25); data.set(e,       113); h_mc_noosc.set(e,       378.8);
  e.setVal( 2.75); data.set(e,       257); h_mc_noosc.set(e,       471.4);
  e.setVal( 3.25); data.set(e,       346); h_mc_noosc.set(e,       500.5);
  e.setVal( 3.75); data.set(e,       353); h_mc_noosc.set(e,       453.5);
  e.setVal( 4.25); data.set(e,       285); h_mc_noosc.set(e,       359.4);
  e.setVal( 4.75); data.set(e,       197); h_mc_noosc.set(e,       269.6);
  e.setVal( 5.25); data.set(e,       156); h_mc_noosc.set(e,       207.4);
  e.setVal( 5.75); data.set(e,       126); h_mc_noosc.set(e,       168.0);
  e.setVal( 6.25); data.set(e,        97); h_mc_noosc.set(e,       146.5);
  e.setVal( 6.75); data.set(e,       109); h_mc_noosc.set(e,       130.6);
  e.setVal( 7.25); data.set(e,       126); h_mc_noosc.set(e,       121.7);
  e.setVal( 7.75); data.set(e,        95); h_mc_noosc.set(e,       118.9);
  e.setVal( 8.25); data.set(e,       102); h_mc_noosc.set(e,       112.7);
  e.setVal( 8.75); data.set(e,       118); h_mc_noosc.set(e,       107.8);
  e.setVal( 9.40); data.set(e, 1.5 * 108); h_mc_noosc.set(e, 1.5 * 102.3);
  e.setVal(10.10); data.set(e, 1.5 * 106); h_mc_noosc.set(e, 1.5 *  96.8);
  e.setVal(10.80); data.set(e, 1.5 *  86); h_mc_noosc.set(e, 1.5 *  94.0);
  e.setVal(11.50); data.set(e, 1.5 *  84); h_mc_noosc.set(e, 1.5 *  85.7 );
  e.setVal(12.50); data.set(e,  2  *  92); h_mc_noosc.set(e, 2   * 82.9 );
  e.setVal(13.50); data.set(e,  2  *  70); h_mc_noosc.set(e, 2   * 77.4 );
  // clang-format on

  data.Print();
  h_mc_noosc.Print();

  RooWorkspace w{"minos"};  // C++11
  // RooWorkspace w("minos"); // Root 5

  w.import(data);
  w.import(h_mc_noosc);

  w.writeToFile("minos_2013_data.root");
  w.Print();

  return 0;
}
