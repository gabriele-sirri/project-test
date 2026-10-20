// roostats_ex1_makemodel.C
//

using namespace RooStats;

void makeModel(RooWorkspace& w)
{
  // Construct model here
  w.factory(
      "Exponential:bkg(x[110,120], expr('(-1./tau)',tau[10,-1000,1000]) )");
  w.factory("Gaussian:sig(x, mean[115,105,120], sigma[1.0,0,10])");
  w.factory("SUM:model( Ns[100,0,120]*sig, Nb[1000,0,10000]*bkg)");

  // or do it in one line.....
  // w.factory("SUM:model(  Ns[300,0,10000]*Gaussian:sig(x[0,1000],
  // mean[2,0,10], sigma[0.5,0,10]), Nb[700,0,10000]*Exponential:bkg(x,
  // expr('(-1./tau)',tau[2,-1000,1000]) ))");

  // Looking into a workspace
  w.Print();

  // Getting variables and functions out of a workspace
  RooAbsPdf* model = w.pdf("model");
  RooRealVar* x = w.var("x");    // the observable
  RooRealVar* Ns = w.var("Ns");  // the parameter

  x->setBins(30);

  // you can set constant some parameters
  w.var("mean")->setConstant(true);
  w.var("sigma")->setConstant(true);
  w.var("tau")->setConstant(true);
  w.var("Nb")->setConstant(true);

  // specify components of model for statistical tools
  ModelConfig modelConfig("ModelConfig");
  modelConfig.SetWorkspace(w);
  // set components using the name of ws objects
  modelConfig.SetPdf("model");
  modelConfig.SetObservables("x");
  modelConfig.SetParametersOfInterest("Ns");

  // import modelConﬁg into workspace too
  w.import(modelConfig);

  // generate the data (nsig = 50, nbkg=1000)
  w.var("Ns")->setVal(50);
  w.var("Nb")->setVal(1000);
  // use fixed random numbers for reproducibility
  RooRandom::randomGenerator()->SetSeed(111);
  // int N = 1000 ;
  RooDataSet* data =
      model->generate(*x);  // will generate according to total S+B events
  data->Print();

  // add data to the workspace
  data->SetName("data");
  w.import(*data);

  // Looking into a workspace
  w.Print();

  // write the workspace in the file
  const char* fileName = "model.root";
  w.writeToFile(fileName, true);
}

void roostats_ex1_makemodel()
{
  RooWorkspace w("w");
  makeModel(w);
}
