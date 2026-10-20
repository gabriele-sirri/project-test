using namespace RooFit;
using namespace RooStats;

//  first part 
//
// "We observed 17 events with an expected background of 3.8+/-0.6 events"
//
// load ex40_2020_counting_model_factory and run 
// root [] CountingModel(17, 3.8, 0.6/3.8 )
// root [] confidence_level(0.95)
// 

void on_off_2020_top_quark(  int nobs = 17,        // number of observed events when ON
                  int noff = 40,                   // number of observed events when OFF
                  double tau = 10.53)
{
   RooWorkspace w("w");
   
// make Poisson model * Poisson model for Control Region
   w.factory("sum:nexp(s[3,0,200],b[1,0,200])");
// Poisson of (n | s+b)
   w.factory("Poisson:pdf(nobs[0,300],nexp)");

   w.factory("prod:tb(t[100],b)");

   w.factory("Poisson:cr_pdf(noff[90,0,300],tb)");
   w.factory("PROD:model(pdf,cr_pdf)");

   w.var("t")->setVal(tau);
   w.var("noff")->setVal(noff);
   w.var("noff")->setConstant(true); // needed for being treated as global observables
   

   ModelConfig mc("ModelConfig",&w);
   mc.SetPdf(*w.pdf("model"));
   mc.SetParametersOfInterest(*w.var("s"));
   mc.SetObservables(*w.var("nobs"));
   mc.SetNuisanceParameters(*w.var("b"));

   // these are needed for the hypothesis tests
   mc.SetSnapshot(*w.var("s"));
   mc.SetGlobalObservables(*w.var("noff"));

   mc.Print();
   // import model in the workspace 
   w.import(mc);

   // make data set with the namber of observed events
   RooDataSet data("data","", *w.var("nobs"));
   w.var("nobs")->setVal(nobs);
   data.add(*w.var("nobs") );
   // import data set in workspace and save it in a file
   w.import(data);

   w.Print();

   TString fileName = "OnOffModel.root"; 

   // write workspace in the file (recreate file if already existing)
   w.writeToFile(fileName, true);

   // Calculate the significance: SL2 estimator
  // create the class using data and model
  RooStats::ProfileLikelihoodCalculator plc(data, mc);
  
  w.var("s")->setVal(0);
  plc.SetNullParameters(*w.var("s"));
  RooStats::HypoTestResult* hypotest = plc.GetHypoTest();
  cout << "Significance (SL2): " <<  hypotest->Significance() << endl;
  cout << "Null Pvalue : " << hypotest->NullPValue() << endl;


}
