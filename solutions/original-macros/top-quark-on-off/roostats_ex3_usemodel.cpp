
using namespace RooStats; 
using namespace RooFit; 

void roostats_ex3_usemodel()
{ 
   const char * fileName = "model_with_nuisance.root" ;

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
   //model->paramOn(xframe);

   xframe->Draw();

   fitresult->Print();

   fitresult->correlationMatrix().Print();


   dataCanvas->cd(2);

   // get the modelConfig out of the file
   ModelConfig* mc = (ModelConfig*) w.obj("ModelConfig");

   // create the class using data and model
   ProfileLikelihoodCalculator plc(*data, *mc);
   // set the confidence level
   plc.SetConfidenceLevel(0.683);
   // compute the interval
   LikelihoodInterval* interval = plc.GetInterval();
   double lowerLimit = interval->LowerLimit(*Ns);
   double upperLimit = interval->UpperLimit(*Ns);
   // plot the interval
   LikelihoodIntervalPlot plot(interval);
   plot.Draw();
   
   // Calculate the significance: SL2 estimator
   Ns->setVal(0);
   plc.SetNullParameters(*Ns);
   HypoTestResult* hypotest = plc.GetHypoTest();
   double SL2 = hypotest->Significance();

   
   cout << "Limits: [" << lowerLimit << " - " 
                       << upperLimit << "]" << endl;
   cout << "Significance (SL2): " << SL2 << endl;

}
