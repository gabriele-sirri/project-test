

using namespace RooStats; 
using namespace RooFit; 

void roostats_ex2_usemodel( const char * fileName = "model.root" )
{ 

   // read from a file or generate then  
   TFile * f = TFile::Open(fileName) ;
   bool fileNotFound = (f == 0) ;
   
   if (fileNotFound) 
   {
      cout << "ERROR: "<< fileName<<"not found : make model first....." << endl ;
      return ;
   }

   // read from a file
   std::cout << "Reading workspace from file " << f->GetName() << std::endl;
   RooWorkspace * w  = 0;
   w = (RooWorkspace *) f->Get("w");

   // use model
   useModel(*w) ; 
} 


void useModel(RooWorkspace& w ) 
{ 
   // Make fit, plots etc here 
   

   // Let's make a plot and some maquillage
   TCanvas* dataCanvas = new TCanvas("res","The Result",800,400);
   dataCanvas->Divide(2,1); dataCanvas->cd(1);



   // Looking into a workspace   
   w.Print() ;
      
   // Getting variables and functions out of a workspace 
   RooAbsPdf  * model  = w.pdf("model");
   RooRealVar * x      = w.var("x");      // the observable
   RooRealVar * Ns     = w.var("Ns");    // the parameter
   RooDataSet * data   = w.data("data");  // the data

   // fit the data

    // you can choose the minizer
   RooFitResult * fitresult = model->fitTo( *data, Save(true), Minimizer("Minuit2","Migrad"),PrintLevel(0));

   
   // plotting

   RooPlot * xframe = x->frame();
   //model->plotOn(xframe,Normalization(N),VisualizeError(*fitresult,3), FillColor(kYellow)); // visualized 3-sigma error band
   //model->plotOn(xframe,Normalization(N),VisualizeError(*fitresult,1,kFALSE),DrawOption("L"),LineWidth(2),LineColor(kRed)); // visualized 1-sigma error lines
   data->plotOn(xframe);
   model->plotOn(xframe);
   model->plotOn(xframe, Components("bkg"), LineStyle(kDashed) );
   model->plotOn(xframe, Components("sig"), LineColor(kRed), LineStyle(kDashed) );
   model->paramOn(xframe);

   xframe->Draw();

   fitresult->Print();

   fitresult->correlationMatrix().Print();


   // get the modelConfig out of the file
   ModelConfig* modelConfig = (ModelConfig*) w.obj("ModelConfig");
   // set confidence level
   double confidenceLevel = 0.95 ;


//----------------------------------------------------
   // example use profile likelihood calculator
   dataCanvas->cd(2);
   
   // create the class using data and model
   ProfileLikelihoodCalculator plc(*data, *modelConfig);
   // set the confidence level
   plc.SetConfidenceLevel(confidenceLevel);
   // compute the interval
   LikelihoodInterval* lint = plc.GetInterval();
    // plot the interval
   LikelihoodIntervalPlot plot(lint);
   plot.Draw();
   
   // Calculate the significance: SL2 estimator
   Ns->setVal(0);
   plc.SetNullParameters(*Ns);
   HypoTestResult* hypotest = plc.GetHypoTest();
   double SL2 = hypotest->Significance();


 
 
   //-----------------------------------------------------
   // example use of Feldman-Cousins

  FeldmanCousins fc(*data, *modelConfig); 
  fc.SetConfidenceLevel( confidenceLevel);
  fc.SetNBins(40); // number of points to test per parameter
  fc.UseAdaptiveSampling(true); // make it go faster

  // Here, we consider only ensembles with 100 events
  // The PDF could be extended and this could be removed
  // fc.FluctuateNumDataEntries(false); 

  // Proof
  //  ProofConfig pc(*wspace, 4, "workers=4", kFALSE);    // proof-lite
  //ProofConfig pc(w, 8, "localhost");    // proof cluster at "localhost"
  //  ToyMCSampler* toymcsampler = (ToyMCSampler*) fc.GetTestStatSampler();
  //  toymcsampler->SetProofConfig(&pc);     // enable proof

  PointSetInterval* interval = (PointSetInterval*) fc.GetInterval();



  cout << "plc interval is [" 
     << lint->LowerLimit(*Ns) << " - " 
     << lint->UpperLimit(*Ns) << "]" << endl;

   std::cout << "fc interval is ["<<  
    interval->LowerLimit(*Ns) << " , "  <<
    interval->UpperLimit(*Ns) << "]" << endl;
   
   cout << "Significance (SL2): " << SL2 << endl;

}
